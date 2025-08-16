#include "989snd.h"

#include "common.h"
#include "text.h"

#include <sdk/ee/eekernel.h>
#include <sdk/ee/sifrpc.h>
#include <sdk/libcdvd.h>

#include <stddef.h>

// Linux style volatile access macro's
#define READ_ONCE(x) (*(const volatile typeof(x)*)(&x))
#define WRITE_ONCE(x, val) (*(volatile typeof(x)*)(&x) = (val))

u_int snd_SendIOPCommandAndWait(int command, int data_used, char* in_data);
void snd_SendIOPCommandNoWait(int command, int data_used, char* in_data, SndCompleteProc done, u_long u_data);
int snd_GotReturns(void);
void snd_SendCurrentBatch(void);
void snd_PostMessage(void);

struct SndCommandReturnDef { // 0x10
    /* 0x0 */ SndCompleteProc done;
    /* 0x8 */ u_long u_data;
};

struct SndCommandBuffer { // 0x1000
    /* 0x0000 */ int num_commands;
    /* 0x0004 */ char buf[4092];
};

typedef struct SndCommandReturnDef* SndCommandReturnDefPtr;

struct SndSystemStatus { // 0x40
    /* 0x00 */ int cd_busy;
    /* 0x04 */ int pad_0;
    /* 0x08 */ int pad_1;
    /* 0x0c */ int pad_2;
    /* 0x10 */ int cd_error;
    /* 0x14 */ int pad_3;
    /* 0x18 */ int pad_4;
    /* 0x1c */ int pad_5;
    /* 0x20 */ char pad_big[32];
};

struct SndMessageData { // 0x20
    /* 0x00 */ int data[7];
    /* 0x1c */ int command;
};
typedef struct SndMessageData* SndMessageDataPtr;

u_int* gCommBusy = 0;
int gAwaitingInts = 0;
int gUnkBankLoadError = 0;
int gStreamingInited = 0;
void (*gCdCallback)(int) = NULL;
int gSSRead = 0;
int gSSReadDone = 0;
int gLoadingFromFS = 0;

extern struct SndCommandBuffer gSndCommandBuffer1;
extern struct SndCommandBuffer gSndCommandBuffer2;
struct SndCommandBuffer* gSndCommandBuffePtr[2] = { &gSndCommandBuffer1, &gSndCommandBuffer2 };

int gCommandBuffeBytesAvail[2] = { 0xffc, 0xffc };

extern struct SndCommandReturnDef gSndCommandReturnDef1[256];
extern struct SndCommandReturnDef gSndCommandReturnDef2[256];
struct SndCommandReturnDef* gSndCommandReturnDefPtr[2] = { gSndCommandReturnDef1, gSndCommandReturnDef2 };

extern unsigned int gActualReturnValues1[272];
extern unsigned int gActualReturnValues2[272];
u_int* gReturnValuesPtr[2] = { gActualReturnValues1, gActualReturnValues2 };

int gCommandFillBuffer = 0;
int gCaching = 0;
u_int gLoadBusy = 0;
struct SndCommandReturnDef gLoadReturnDef = {};
static SndCompleteProc gLoadCB = NULL;
static u_long gLoadUserData = 0;
u_int gLoadCommand = 0;
int gLoadAwaits = 0;

// Aligment for DMA transfer buffers
unsigned int gSyncBuffer[16] __attribute__((aligned(16))) = {};
char gSyncSendBuffer[64] __attribute__((aligned(16))) = {};
char gSyncStringBuffer[256] __attribute__((aligned(16))) = {};
struct SndCommandBuffer gSndCommandBuffer1 __attribute__((aligned(16))) = {};
struct SndCommandBuffer gSndCommandBuffer2 __attribute__((aligned(16))) = {};

struct SndCommandReturnDef gSndCommandReturnDef1[256] = {};
struct SndCommandReturnDef gSndCommandReturnDef2[256] = {};

// Not actually sure on their size
unsigned int gActualReturnValues1[272] __attribute__((aligned(16))) = {};
unsigned int gActualReturnValues2[272] __attribute__((aligned(16))) = {};
struct SndSystemStatus gStats __attribute__((aligned(16))) = {};
unsigned int gLoadReturnValue[16] __attribute__((aligned(16))) = {};
int gLoadParams[8] __attribute__((aligned(16))) = {};

// BSS
extern sceSifClientData gSLClientData;
extern sceSifClientData gSLClientLoaderData;

INCLUDE_ASM(const s32, "P2/989snd", snd_StartSoundSystem);
#ifdef SKIP_ASM
// Assembler delay slot diff
void snd_StartSoundSystem(void)
{
    int i;

    gSndCommandBuffePtr[0] = &gSndCommandBuffer1;
    gSndCommandBuffePtr[1] = &gSndCommandBuffer2;
    gReturnValuesPtr[0] = gActualReturnValues1;
    gReturnValuesPtr[1] = gActualReturnValues2;
    gSndCommandReturnDefPtr[0] = gSndCommandReturnDef1;
    gSndCommandReturnDefPtr[1] = gSndCommandReturnDef2;
    sceSifInitRpc(0);

    while (1) {
        if (sceSifBindRpc(&gSLClientData, 0x123456, 0) < 0) {
            printf("error: sceSifBindRpc in %s, at line %d\n", "989snd.c", 0x6e);
            while (1)
                ;
        }
        i = 10000;
        while (i--)
            ;
        if (gSLClientData.serve != 0) {
            break;
        }
    }

    gLoadBusy = 0;
    gLoadReturnDef.done = NULL;
    gLoadReturnDef.u_data = 0;
    gLoadReturnValue[0] = 0;
    while (1) {
        if (sceSifBindRpc(&gSLClientLoaderData, 0x123457, 0) < 0) {
            printf("error: sceSifBindRpc in %s, at line %d\n", "989snd.c", 0x83);
            while (1)
                ;
        }
        i = 10000;
        while (i--)
            ;
        if (gSLClientLoaderData.serve != 0) {
            break;
        }
    }

    gStats.cd_busy = 0;
    gStats.cd_error = 0;
    gSndCommandBuffer2.num_commands = gSndCommandBuffer1.num_commands = 0;
    gCommandBuffeBytesAvail[1] = gCommandBuffeBytesAvail[0] = 0xffc;

    i = (int)&gStats;
    snd_SendIOPCommandAndWait(0, sizeof(i), (char*)&i);
}
#endif

int snd_FlushSoundCommands()
{
    SndCompleteProc done;
    u_long u_data;
    int which, x;

    if (gCommBusy && snd_GotReturns()) {
        if (gLoadingFromFS) {
            if (gLoadCB) {
                gLoadCB(gSyncBuffer[1], gLoadUserData);
            }
            gLoadCB = NULL;
            gLoadingFromFS = 0;
        } else {
            which = gCommandFillBuffer != 1;
            for (x = 0; x < gSndCommandBuffePtr[which]->num_commands; x++) {
                done = gSndCommandReturnDefPtr[which][x].done;
                if (gSndCommandReturnDefPtr[which][x].done) {
                    u_data = gSndCommandReturnDefPtr[which][x].u_data;
                    done(gReturnValuesPtr[which][x + 1], u_data);
                }
            }
        }
    }

    if (gLoadBusy) {
        FlushCache(0);
        if (gLoadReturnValue[0] != -1) {
            if (gLoadReturnDef.done) {
                u_data = gLoadReturnDef.u_data;
                done = gLoadReturnDef.done;
                gLoadReturnDef.done = NULL;
                gLoadReturnDef.u_data = 0;
                done(gLoadReturnValue[0], u_data);
            }
            gLoadBusy = 0;
            gLoadReturnValue[0] = 0;
        }
    }

    if (!gCommBusy && gSndCommandBuffePtr[gCommandFillBuffer]->num_commands && !gCaching) {
        snd_SendCurrentBatch();
    }

    if (gSSRead) {
        snd_StreamSafeCdSync(1);
        if (gSSReadDone) {
            gSSRead = 0;
            gSSReadDone = 0;
            if (gCdCallback) {
                gCdCallback(1);
            }
        }
    }

    if (gCommBusy || gLoadBusy) {
        return 1;
    }

    return 0;
}

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d060);

INCLUDE_ASM(const s32, "P2/989snd", snd_GotReturns__Fv);
#ifdef SKIP_ASM
// Rodata
int snd_GotReturns(void)
{
    FlushCache(0);
    if (gCommBusy == NULL) {
        return 1;
    }

    if (sceSifCheckStatRpc(&gSLClientData.rpcd)) {
        return 0;
    }

    if (*gCommBusy == -1 && (gCommBusy[gAwaitingInts + 1] == -1)) {
        gCommBusy = NULL;
        return 1;
    } else {
        printf("989snd.c: Sif says RPC isn\'t busy, but we still don\'t have returns from the  IOP!\n");
        return 0;
    }

    return 1;
}
#endif

void snd_PrepareReturnBuffer(u_int* buffer, int num_ints)
{
    gAwaitingInts = num_ints;
    gCommBusy = buffer;
    buffer[num_ints + 1] = 0;
    buffer[0] = 0;
}

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d138);

INCLUDE_ASM(const s32, "P2/989snd", snd_BankLoadByLoc);
#ifdef SKIP_ASM
SoundBankPtr snd_BankLoadByLoc(int loc, int offset)
{
    gUnkBankLoadError = 0;
    if (gLoadBusy) {
        printf("snd_BankLoadByLoc: Load already in progress!\n");
        return NULL;
    }

    if (snd_StreamSafeCdSync(1) == 1) {
        printf("snd_BankLoadByLoc: CD BUSY!\n");
        return NULL;
    }

    gLoadReturnValue[0] = 0xffffffff;
    gLoadParams[0] = loc;
    gLoadParams[1] = offset;
    while (sceSifCheckStatRpc(&gSLClientLoaderData.rpcd)) {
        printf("989snd.c: RPC collision!\n");
        snd_FlushSoundCommands();
        FlushCache(0);
    }

    if (sceSifCallRpc(&gSLClientLoaderData, 3, 1, gLoadParams, 8, gLoadReturnValue, 4, NULL, NULL) < 0) {
        printf("989snd.c: RPC call has failed inside snd_BankLoadByLoc\n");
        gUnkBankLoadError = 0x106;
        return NULL;
    }

    while ((SoundBankPtr)gLoadReturnValue[0] == (SoundBankPtr)0xffffffff) {
        FlushCache(0);
    }

    return (SoundBankPtr)gLoadReturnValue[0];
}
#endif

INCLUDE_ASM(const s32, "P2/989snd", snd_BankLoadByLoc_CB);
#ifdef SKIP_ASM
void snd_BankLoadByLoc_CB(int loc, int offset, SndCompleteProc cb, u_long u_data)
{
    gUnkBankLoadError = 0;

    if (gLoadBusy) {
        printf("snd_BankLoadByLoc: Load already in progress!\n");
        return;
    }

    if (snd_StreamSafeCdSync(1) == 1) {
        printf("snd_BankLoadByLoc: CD BUSY!\n");
        return;
    }

    gLoadReturnValue[0] = 0xffffffff;
    gLoadParams[0] = loc;
    gLoadParams[1] = offset;
    gLoadReturnDef.done = cb;
    gLoadReturnDef.u_data = u_data;

    while (sceSifCheckStatRpc(&gSLClientLoaderData.rpcd)) {
        printf("989snd.c: RPC collision!\n");
        snd_FlushSoundCommands();
        FlushCache(0);
    }

    gLoadBusy = 1;
    sceSifCallRpc(&gSLClientLoaderData, 3, 1, gLoadParams, 8, gLoadReturnValue, 4, NULL, NULL);
}
#endif

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d3e8);

void snd_ResolveBankXREFS(void)
{
    snd_SendIOPCommandNoWait(8, 0, NULL, NULL, 0);
}

void snd_UnloadBank(SoundBankPtr bank)
{
    int data[1];

    data[0] = (int)bank;

    snd_SendIOPCommandNoWait(6, 4, (char*)data, NULL, 0);
}

void snd_SetMasterVolume(int which, int vol)
{
    int data[2];

    data[0] = which;
    data[1] = vol;

    snd_SendIOPCommandNoWait(9, 8, (char*)data, NULL, 0);
}

int snd_GetMasterVolume(int which)
{
    int data[1];

    data[0] = which;

    return snd_SendIOPCommandAndWait(10, 4, (char*)data);
}

void snd_SetPlaybackMode(int mode)
{
    int data[1];

    data[0] = mode;

    snd_SendIOPCommandNoWait(0xb, 4, (char*)data, NULL, 0);
}

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d510);

void snd_SetMixerMode(int channel_mode, int reverb_mode)

{
    int data[2];

    data[0] = channel_mode;
    data[1] = reverb_mode;

    snd_SendIOPCommandNoWait(0xd, 8, (char*)data, NULL, 0);
}

void snd_SetGroupVoiceRange(int group, int min, int max)
{
    int data[3];

    data[0] = group;
    data[1] = min;
    data[2] = max;

    snd_SendIOPCommandNoWait(0x4e, 0xc, (char*)data, NULL, 0);
}

u_int snd_PlaySoundVolPanPMPB(SoundBankPtr bank, int sound, int vol, int pan, int pitch_mod, int bend)
{
    int data[6];

    data[0] = (int)bank;
    data[1] = sound;
    data[2] = vol;
    data[3] = pan;
    data[4] = pitch_mod;
    data[5] = bend;

    return snd_SendIOPCommandAndWait(0x11, 0x18, (char*)data);
}

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d5d8);

void snd_StopSound(u_int handle)
{
    int data[1];

    data[0] = handle;

    snd_SendIOPCommandNoWait(0x15, 4, (char*)data, NULL, 0);
}

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d630);

void snd_PauseSound(u_int handle)
{
    int data[1];

    data[0] = handle;

    snd_SendIOPCommandNoWait(0x13, 4, (char*)data, NULL, 0);
}

void snd_ContinueSound(u_int handle)
{
    int data[1];

    data[0] = handle;

    snd_SendIOPCommandNoWait(0x14, 4, (char*)data, NULL, 0);
}

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d6a0);

void snd_PauseAllSoundsInGroup(u_int groups)

{
    int data[1];

    data[0] = groups;

    snd_SendIOPCommandNoWait(0x16, 4, (char*)data, NULL, 0);
}

void snd_ContinueAllSoundsInGroup(u_int groups)

{
    int data[1];

    data[0] = groups;

    snd_SendIOPCommandNoWait(0x17, 4, (char*)data, NULL, 0);
}

u_int snd_SoundIsStillPlaying(u_int handle)
{
    u_int data[1];

    data[0] = handle;

    return snd_SendIOPCommandAndWait(0x19, 4, (char*)data);
}

void snd_SoundIsStillPlaying_CB(u_int handle, SndCompleteProc cb, u_long user_data)
{
    int data[1];

    data[0] = handle;

    snd_SendIOPCommandNoWait(0x19, 4, (char*)data, cb, user_data);
}

int snd_IsSoundALooper(SoundBankPtr bank, u_int sound)
{
    int data[2];

    data[0] = (int)bank;
    data[1] = sound;

    return snd_SendIOPCommandAndWait(0x1a, 8, (char*)data);
}

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d790);

void snd_SetSoundVolPan(u_int handle, int vol, int pan)
{
    int data[3];

    data[0] = handle;
    data[1] = vol;
    data[2] = pan;

    snd_SendIOPCommandNoWait(0x1b, 0xc, (char*)data, NULL, 0);
}

int snd_GetSoundOriginalPitch(SoundBankPtr bank, int index)
{
    int data[2];

    data[0] = (int)bank;
    data[1] = index;

    return snd_SendIOPCommandAndWait(0x1c, 8, (char*)data);
}

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d808);

void snd_SetSoundPitch(u_int handle, int pitch)
{
    int data[2];

    data[0] = handle;
    data[1] = pitch;

    snd_SendIOPCommandNoWait(0x1e, 8, (char*)data, NULL, 0);
}

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d848);

void snd_AutoVol(u_int handle, int vol, int delta_time, int delta_from)
{
    int data[4];

    data[0] = handle;
    data[1] = vol;
    data[2] = delta_time;
    data[3] = delta_from;

    snd_SendIOPCommandNoWait(0x22, 0x10, (char*)data, NULL, 0);
}

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d8a0);

void snd_SetMIDIRegister(u_int handle, int reg, int value)
{
    int data[3];

    data[0] = handle;
    data[1] = reg;
    data[2] = value;

    snd_SendIOPCommandNoWait(0x29, 0xc, (char*)data, NULL, 0);
}

int snd_GetMIDIRegister(u_int handle, int reg)
{
    int data[2];

    data[0] = handle;
    data[1] = reg;

    return snd_SendIOPCommandAndWait(0x28, 8, (char*)data);
}

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d920);

void snd_SetGlobalExcite(int value)
{
    int data[1];

    data[0] = value;

    snd_SendIOPCommandNoWait(0x27, 4, (char*)data, NULL, 0);
}

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d958);

INCLUDE_ASM(const s32, "P2/989snd", snd_SendIOPCommandAndWait__FiiPc);
#ifdef SKIP_ASM
u_int snd_SendIOPCommandAndWait(int command, int data_used, char* in_data)
{
    u_int ret_val;
    int x;

    for (x = 0; x < data_used; x++) {
        gSyncSendBuffer[x] = in_data[x];
    }

    while (gCommBusy) {
        snd_FlushSoundCommands();
        FlushCache(0);
    }

    snd_PrepareReturnBuffer(gSyncBuffer, 1);
    while (sceSifCheckStatRpc(&gSLClientData.rpcd)) {
        printf("989nsd.c: RPC collision!\n");
        snd_FlushSoundCommands();
        FlushCache(0);
    }

    if (data_used) {
        sceSifCallRpc(&gSLClientData, command, 1, gSyncSendBuffer, data_used, gSyncBuffer, 0xc, NULL, NULL);
    } else {
        sceSifCallRpc(&gSLClientData, command, 1, NULL, 0, gSyncBuffer, 0xc, NULL, NULL);
    }

    while (!snd_GotReturns())
        ;

    ret_val = gSyncBuffer[1];

    if (gSndCommandBuffePtr[gCommandFillBuffer]->num_commands && !gCaching) {
        snd_SendCurrentBatch();
    }

    return ret_val;
}
#endif

INCLUDE_ASM(const s32, "P2/989snd", snd_SendIOPCommandNoWait__FiiPcPFiUl_vUl);
#ifdef SKIP_ASM
void snd_SendIOPCommandNoWait(int command, int data_used, char* in_data, SndCompleteProc done, u_long u_data)
{
    int x, was_caching = 0, y;
    char* msg;
    int msg_size;

    if (!gCaching && !gCommBusy && !data_used && !done) {
        snd_PrepareReturnBuffer(gSyncBuffer, 1);

        while (sceSifCheckStatRpc(&gSLClientData.rpcd)) {
            printf("989snd.c: RPC collision!\n");
            snd_FlushSoundCommands();
            FlushCache(0);
        }

        sceSifCallRpc(&gSLClientData, command, 1, NULL, 0, gSyncBuffer, 0xc, NULL, NULL);
        return;
    }

    y = 0;

    msg_size = data_used + 4;
    if (msg_size % 4) {
        msg_size = ((data_used) - ((msg_size % 4) - 8));
    }

    while (gSndCommandBuffePtr[gCommandFillBuffer]->num_commands == 256 || gCommandBuffeBytesAvail[gCommandFillBuffer] < msg_size) {
        if (gCaching != 0) {
            gCaching = 0;
            was_caching = 1;
        }
        snd_FlushSoundCommands();
        if (y == 1) {
            printf("snd_SendIOPCommandNoWait: BUFFER %d FULL(%d)! Sound stalled waiting for IOP coma nds to finish!\n", gCommandFillBuffer, gSndCommandBuffePtr[gCommandFillBuffer]->num_commands);
        }
        y++;
    }

    if (y) {
        printf("snd_SendIOPCommandNoWait: continueing (%d).\n", y);
    }

    if (was_caching) {
        gCaching = 1;
    }

    msg = gSndCommandBuffePtr[gCommandFillBuffer]->buf + 0xffc - gCommandBuffeBytesAvail[gCommandFillBuffer];
    *((short*)(msg)) = command;
    msg += 2;
    *((short*)(msg)) = data_used;
    msg += 2;

    for (x = 0; x < data_used; x++) {
        msg[x] = in_data[x];
    }

    gCommandBuffeBytesAvail[gCommandFillBuffer] -= msg_size;
    gSndCommandReturnDefPtr[gCommandFillBuffer][gSndCommandBuffePtr[gCommandFillBuffer]->num_commands].done = done;
    gSndCommandReturnDefPtr[gCommandFillBuffer][gSndCommandBuffePtr[gCommandFillBuffer]->num_commands].u_data = u_data;
    snd_PostMessage();
}
#endif

void snd_PostMessage(void)
{
    gSndCommandBuffePtr[gCommandFillBuffer]->num_commands = gSndCommandBuffePtr[gCommandFillBuffer]->num_commands + 1;
    snd_FlushSoundCommands();
}

INCLUDE_ASM(const s32, "P2/989snd", snd_SendCurrentBatch__Fv);
#ifdef SKIP_ASM
void snd_SendCurrentBatch(void)
{
    snd_PrepareReturnBuffer(gReturnValuesPtr[gCommandFillBuffer],
        gSndCommandBuffePtr[gCommandFillBuffer]->num_commands);

    while (sceSifCheckStatRpc(&gSLClientData.rpcd)) {
        printf("989snd.c: RPC collision!\n");
        FlushCache(0);
    }

    sceSifCallRpc(&gSLClientData, 0x4d, 1, gSndCommandBuffePtr[gCommandFillBuffer],
        0x1000 - gCommandBuffeBytesAvail[gCommandFillBuffer],
        gReturnValuesPtr[gCommandFillBuffer],
        gSndCommandBuffePtr[gCommandFillBuffer]->num_commands * 4 + 8, NULL, NULL);

    gCommandFillBuffer = gCommandFillBuffer != 1;

    gSndCommandBuffePtr[gCommandFillBuffer]->num_commands = 0;
    gCommandBuffeBytesAvail[gCommandFillBuffer] = 0xffc;
}
#endif

int snd_InitVAGStreamingEx(int num_channels, int buffer_size, unsigned int read_mode, int enable_streamsafe_from_ee)
{
    int data[4];

    if (gStreamingInited == 1) {
        return 0;
    }

    if (gLoadBusy) {
        while (snd_FlushSoundCommands())
            ;
    }

    snd_StreamSafeCdSync(0);
    data[0] = num_channels;
    data[1] = buffer_size;
    data[2] = read_mode;
    data[3] = enable_streamsafe_from_ee;

    gStreamingInited = snd_SendIOPCommandAndWait(0x2a, 0x10, (char*)data);
    return gStreamingInited;
}

void snd_StopAllStreams(void)
{
    snd_SendIOPCommandNoWait(0x34, 0, NULL, NULL, 0);
}

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011e040);

u_int snd_PlayVAGStreamByLoc(int loc1, int loc2, int offset1, int offset2, int vol, int pan, int vol_group, u_int queue, u_int flags)
{
    int data[7];

    data[0] = loc1;
    data[1] = loc2;
    data[2] = vol << 0x10 | offset1 & 0xffffU;
    data[3] = pan << 0x10 | offset2 & 0xffffU;
    data[4] = vol_group;
    data[5] = queue;
    data[6] = flags;

    return snd_SendIOPCommandAndWait(0x2c, 0x1c, (char*)data);
}

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011e0a8);

void snd_ContinueVAGStream(u_int stream)
{
    int data[1];

    data[0] = stream;

    snd_SendIOPCommandNoWait(0x2e, 4, (char*)data, NULL, 0);
}

void snd_IsVAGStreamBuffered_CB(u_int stream, SndCompleteProc cb, u_long user_data)
{
    u_int data[1];

    data[0] = stream;

    snd_SendIOPCommandNoWait(0x4f, 4, (char*)data, cb, user_data);
}

int snd_StreamSafeCheckCDIdle(int block_ee_iop)
{
    int data[1];

    data[0] = block_ee_iop;

    return snd_SendIOPCommandAndWait(0x36, 4, (char*)data);
}

int snd_StreamSafeCdRead(u_int lbn, u_int sectors, void* buf, sceCdRMode* mode)
{
    int data[3];

    if (gStreamingInited == 0) {
        return sceCdRead(lbn, sectors, buf, mode);
    }

    if (snd_StreamSafeCdSync(1) == 1) {
        return 0;
    }

    WRITE_ONCE(gStats.cd_busy, 1);
    WRITE_ONCE(gStats.cd_error, 0);

    data[0] = lbn;
    data[1] = sectors;
    data[2] = (int)buf;

    snd_SendIOPCommandNoWait(0x38, 0xc, (char*)data, NULL, 0);

    gSSReadDone = 0;
    gSSRead = 1;

    return 1;
}

int snd_StreamSafeCdSync(int mode)
{
    if (gStreamingInited == 0) {
        return sceCdSync(mode);
    }

    FlushCache(0);
    gSSReadDone = !READ_ONCE(gStats.cd_busy);
    if (gSSReadDone != 1) {
        if (mode == 1) {
            return 1;
        }

        while (!gSSReadDone) {
            snd_FlushSoundCommands();
            FlushCache(0);
            gSSReadDone = !READ_ONCE(gStats.cd_busy);
        }
    }

    return 0;
}

int snd_StreamSafeCdBreak(void)
{
    if (gStreamingInited == 0) {
        return sceCdBreak();
    }

    snd_SendIOPCommandNoWait(0x37, 0, NULL, NULL, 0);
    return 1;
}

int snd_StreamSafeCdGetError(void)
{
    if (!gStreamingInited) {
        return sceCdGetError();
    }

    return ((volatile SndSystemStatus*)&gStats)->cd_error;
}

void snd_SetReverbType(int core, int type)
{
    int data[2];

    data[0] = core;
    data[1] = type;

    snd_SendIOPCommandNoWait(0xe, 8, (char*)data, NULL, 0);
}

void snd_SetReverbDepth(int core, int left, int right)
{
    int data[3];

    data[0] = core;
    data[1] = left;
    data[2] = right;

    snd_SendIOPCommandNoWait(0xf, 0xc, (char*)data, NULL, 0);
}

void snd_PreAllocReverbWorkArea(int core, int type)
{
    int data[2];

    data[0] = core;
    data[1] = type;

    snd_SendIOPCommandNoWait(0x51, 8, (char*)data, NULL, 0);
}

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011e3d8);

int snd_InitMovieSound(int sizeOfIOPBuffer, int volumeLevel, int panCenter, int volumeGroup, int type)
{
    int data[5];

    data[0] = sizeOfIOPBuffer;
    data[1] = volumeLevel;
    data[2] = panCenter;
    data[3] = volumeGroup;
    data[4] = type;

    return snd_SendIOPCommandAndWait(0x3b, 0x14, (char*)data);
}

void snd_ResetMovieSound(void)
{
    snd_SendIOPCommandAndWait(0x3d, 0, NULL);
}

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011e488);

void snd_CloseMovieSound(void)
{
    snd_SendIOPCommandAndWait(0x3c, 0, NULL);
}

void snd_StartMovieSound(int iopBuffer, int iopBufferSize, int iopPausePosition, u_int sr, int ch)
{
    int data[5];

    data[0] = iopBuffer;
    data[1] = iopBufferSize;
    data[2] = iopPausePosition;
    data[3] = sr;
    data[4] = ch;

    snd_SendIOPCommandAndWait(0x3e, 0x14, (char*)data);
}

int snd_GetTransStatus()
{
    return snd_SendIOPCommandAndWait(0x40, 0, NULL);
}

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011e520);

INCLUDE_ASM(const s32, "P2/989snd", snd_GetDopplerPitchMod);
#ifdef SKIP_ASM
// matches, TU padding problem
int snd_GetDopplerPitchMod(int approaching_mph)
{
    return (approaching_mph * 0x5f4) / 0x2e5;
}
#endif
