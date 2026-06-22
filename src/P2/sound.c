#include <sound.h>
#include <989snd.h>
#include <sce/memset.h>
#include <sw.h>
#include <po.h>
#include <game.h>
#include <memory.h>
#include <cplcy.h>
#include <sdk/ee/eekernel.h>

extern uchar D_00604790[]; // temp

/**
 * @brief Media volume float.
 * @todo Does this even exist?
 */
struct MVG
{
    float vol; // Current volume
    MVGK mvgk; // Media volume float kind
    undefined4 unk2;
    undefined4 unk3;
};

extern float D_00274838[10][4]; // temp

void UnloadMusic()
{
    extern u_int D_0027473C;
    extern u_int D_00274728;
    extern int D_00274720;

    if (D_0027473C != 0)
    {
        if (D_00274728 != 0)
            snd_StopSound(D_00274728);
        snd_UnloadBank((SoundBankPtr)D_0027473C);
        while (snd_FlushSoundCommands()) {}
        D_0027473C = 0;
    }
    D_00274720 = 0;
    D_00274728 = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", SbpEnsureBank__Fi);

extern int D_00245020[][2];
void SbpEnsureBank(SFXID sfxid)
{
    SbpEnsureBank(D_00245020[sfxid][0]);
}

void NewSfx(SFX **ppsfx)
{
    *ppsfx = (SFX *)PvAllocSwClearImpl(sizeof(SFX));
    (*ppsfx)->sfxid = (SFXID)-1;
    (*ppsfx)->sStart = 3000.0f;
    (*ppsfx)->sFull = 300.0f;
    (*ppsfx)->uVol = 1.0f;
    (*ppsfx)->uPitch = 0.0f;
    (*ppsfx)->pamb = NULL;
    (*ppsfx)->lmRepeat.gMin = -1.0f;
    (*ppsfx)->uDoppler = 0.0f;
}

extern int D_006047B0[];
extern int D_006047D0[];

int FContinuousSound(SFXID sfxid)
{
    if (D_006047B0[D_00245020[sfxid][0]] == 0)
    {
        SbpEnsureBank(sfxid);
    }
    return D_006047D0[sfxid];
}

extern int D_00274730;
extern "C" void FUN_001BE5D8(void)
{
    D_00274730 = 0;
}

extern u_int D_00274744;
int SetVagUnpaused()
{
    return D_00274744;
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", PreloadVag__FPc2FK);

extern u_int D_00274744;
void StopVag();
extern "C" void FUN_001be708(void)
{
    D_00274744 = 0;
    StopVag();
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", PreloadVag1);

extern u_int D_00274744;
extern u_int D_0027472C;
extern int D_00274730;
int FPauseForVag()
{
    if (D_00274744 != 0)
    {
        return 0;
    }
    u_int handle = D_0027472C;
    if (handle != 0)
    {
        if (D_00274730 != 0)
        {
            return 1;
        }
        snd_ContinueVAGStream(handle);
    }
    return 0;
}

void RefreshPambVolPan(AMB *pamb)
{
    int vol = (int)(STRUCT_OFFSET(pamb, 0x50, float) * 1024.0f);
    float pan = STRUCT_OFFSET(pamb, 0x54, float);
    int panOut;
    if (0.0f < pan)
        panOut = (int)((pan + 2.0f) * 179.5f) - 359;
    else
        panOut = (int)((pan + 2.0f) * 179.5f);
    snd_SetSoundVolPan(pamb->sfxh, vol, panOut);
}

void RefreshPambVolPan(AMB *pamb);
void DropPamb(AMB **ppamb);

extern "C" void FUN_001be8f8(ALO *palo, AMB **ppamb, float sStart, float sFull)
{
    AMB *pambLocal;
    int fLocal = 0;

    if (ppamb == NULL)
    {
        fLocal = 1;
        ppamb = &pambLocal;
    }

    StartSound((SFXID)-2, ppamb, palo, NULL, sStart, sFull, 1.0f, 0.0f, 0.0f, NULL, NULL);

    if (*ppamb != NULL)
    {
        RefreshPambVolPan(*ppamb);
        if (fLocal)
        {
            DropPamb(ppamb);
        }
    }
}

extern u_int D_0027472C;
int FVagPlaying()
{
    return D_0027472C != 0;
}

JUNK_WORD(0x0080102D);

void StopVag()
{
    if (D_00274744 == 0)
    {
        if (D_0027472C != 0)
        {
            snd_StopSound(D_0027472C);
            while (snd_SoundIsStillPlaying(D_0027472C))
            {
                int i = 0x4E1F;
                do
                {
                    i--;
                } while (i >= 0);
            }
            D_0027472C = 0;
            D_00274730 = 0;
        }
    }
}

extern u_int D_0027472C;
void PauseVag()
{
    u_int handle = D_0027472C;
    if (handle != 0)
    {
        snd_PauseSound(handle);
    }
}

extern u_int D_0027472C;
void ContinueVag()
{
    u_int handle = D_0027472C;
    if (handle != 0)
    {
        snd_ContinueSound(handle);
    }
}

extern int D_00274720;
extern u_int D_00274728;
void KillMusic()
{
    if (D_00274720 == 3)
    {
        snd_StopSound(D_00274728);
        D_00274728 = 0;
        D_00274720 = 2;
    }
}

extern int D_00274720;
extern int D_00274724;
extern u_int D_0027473C;
void PreloadMusidSongComplete(u_int handle, u_long unused)
{
    D_0027473C = handle;
    if (handle != 0)
    {
        snd_ResolveBankXREFS();
        D_00274720 = 2;
    }
    else
    {
        D_00274724 = 0;
        D_00274720 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", PreloadMusidSong__F5MUSID);

enum MUSID {};
void PreloadMusidSong(MUSID musid);

void StartMusidSong(MUSID musid)
{
    extern int D_00274720;
    extern u_int D_00274728;
    extern u_int D_0027473C;

    PreloadMusidSong(musid);
    if (musid != 0)
    {
        while (snd_FlushSoundCommands() != 0)
        {
            if (D_00274720 != 1)
                break;
            FlushCache(0);
        }
        if (D_00274720 == 2)
        {
            u_int handle = snd_PlaySoundVolPanPMPB((SoundBankPtr)D_0027473C, 0, 0x400, -1, 0, 0);
            D_00274728 = handle;
            if (handle != 0)
                D_00274720 = 3;
        }
    }
}

void PauseMusic()
{
    SetMvgkRvol(2, MVGK_Music, 0.0f);
}

void ContinueMusic()
{
    SetMvgkRvol(2, MVGK_Music, 1.0f);
}

extern u_int D_00274728;
void SfxhMusicUnknown1()
{
    snd_PauseSound(D_00274728);
}

extern u_int D_00274728;
void SfxhMusicUnknown2()
{
    snd_ContinueSound(D_00274728);
}

EXC *PexcAlloc()
{
    EXC *pexc = (EXC *)PvAllocSlotheapUnsafe(&STRUCT_OFFSET(g_psw, 0x1bb8, SLOTHEAP));
    if (pexc != 0)
    {
        memset(pexc, 0, sizeof(EXC));
        AppendDlEntry(&STRUCT_OFFSET(g_psw, 0x1bc4, DL), pexc);
    }
    return pexc;
}

void RemoveExc(EXC *pexc)
{
    RemoveDlEntry(&STRUCT_OFFSET(g_psw, 0x1bc4, DL), pexc);
    FreeSlotheapPv(&STRUCT_OFFSET(g_psw, 0x1bb8, SLOTHEAP), pexc);
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", KillExcitement__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/sound", PexcSetExcitement__Fi);

INCLUDE_ASM("asm/nonmatchings/P2/sound", SetIexcCurHigh__FP3EXC);

extern int D_00274734;
extern int D_002748EC;
void SetIexcCurHigh(EXC *pexc);

void UnsetExcitement(EXC *pexc)
{
    if (pexc != 0)
    {
        int iexc = pexc->iexc;
        RemoveExc(pexc);
        if (iexc == D_00274734)
        {
            SetIexcCurHigh(pexc);
            int iexcCur = D_00274734;
            if (iexcCur >= 0)
                D_002748EC = 0;
            g_iexcHyst = iexcCur;
            snd_SetGlobalExcite(iexcCur + 0x14);
            SetMvgkRvol(7, MVGK_Music, 1.0f);
            g_iexcHyst = -0x64;
        }
    }
}

extern int D_00274734;
void SetIexcCurHigh(EXC *pexc);

void UnsetExcitementHyst(EXC *pexc)
{
    if (pexc != 0)
    {
        int iexc = pexc->iexc;
        RemoveExc(pexc);
        if (iexc == D_00274734)
        {
            g_iexcHyst = iexc;
            SetIexcCurHigh(pexc);
        }
    }
}

void StartupSound()
{
    memset(D_00604790, 0, 0x1c);
    snd_StartSoundSystem();
    SbpEnsureBank(0);
    snd_InitVAGStreamingEx(1, 0x2000, 1, 1);
    snd_SetGlobalExcite(0x14);
    MvgkUnknown2();
    snd_SetMixerMode(0, 1);
    snd_SetGroupVoiceRange(0, 0, 0x2f);
    snd_SetGroupVoiceRange(1, 0x18, 0x2f);
    snd_SetGroupVoiceRange(3, 0x18, 0x2f);
    snd_SetGroupVoiceRange(2, 0x18, 0x2f);
    snd_PreAllocReverbWorkArea(2, 4);
}

JUNK_NOP();
JUNK_ADDIU(10);

extern int D_00274748;
int FAmbientsPaused()
{
    return D_00274748;
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", CalculateVolPan__FfP6VECTORPfT2fff);

INCLUDE_ASM("asm/nonmatchings/P2/sound", FUN_001BF2E0);

INCLUDE_ASM("asm/nonmatchings/P2/sound", FUN_001BF398);

INCLUDE_ASM("asm/nonmatchings/P2/sound", PposEar__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/sound", SetDoppler__FP3AMB);

INCLUDE_ASM("asm/nonmatchings/P2/sound", PfneardistGet__Fv);

VECTOR *PposEar();
typedef float (*PFNSDIST)(VECTOR *, VECTOR *);
PFNSDIST PfneardistGet();
float SDistEar(VECTOR *pvec)
{
    VECTOR *pposEar = PposEar();
    return PfneardistGet()(pposEar, pvec);
}

void CalculateVolPan(float dist, VECTOR *pvec, float *pa, float *pb, float a, float b, float c);

void CalculateDistVolPan(VECTOR *pvec, float *pa, float *pb, float a, float b, float c)
{
    if (pvec)
    {
        CalculateVolPan(SDistEar(pvec), pvec, pa, pb, a, b, c);
    }
    else
    {
        *pa = a;
        *pb = 0;
    }
}

AMB *PambAlloc()
{
    AMB *pamb = (AMB *)PvAllocSlotheapUnsafe(&STRUCT_OFFSET(g_psw, 0x1ba0, SLOTHEAP));
    if (pamb != 0)
    {
        memset(pamb, 0, 0x90);
        AppendDlEntry(&STRUCT_OFFSET(g_psw, 0x1bac, DL), pamb);
    }
    return pamb;
}

void DropPamb(AMB **ppamb)
{
    (*ppamb)->ppamb = NULL;
    *ppamb = NULL;
}

void RemoveAmb(AMB *pamb)
{
    if (pamb->ppamb != NULL)
    {
        *pamb->ppamb = NULL;
    }
    pamb->iSerial = -1;
    RemoveDlEntry(&STRUCT_OFFSET(g_psw, 0x1bac, DL), pamb);
    FreeSlotheapPv(&STRUCT_OFFSET(g_psw, 0x1ba0, SLOTHEAP), pamb);
}

void RemoveAmb(AMB *pamb);

void StopSound(AMB *pamb, int msRampdown)
{
    if (pamb != 0)
    {
        if (msRampdown == 0)
            snd_StopSound(pamb->sfxh);
        else
            snd_AutoVol(pamb->sfxh, -4, (int)((float)msRampdown * 0.24000001f), 2);
        RemoveAmb(pamb);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", SetPambFrq__FP3AMBf);

void RefreshPambVolPan(AMB *pamb);

void SetPambVol(AMB *pamb, float uVolAtSource)
{
    if (pamb != 0)
    {
        float ratio = uVolAtSource / pamb->uVolAtSource;
        pamb->uVolAtSource = uVolAtSource;
        STRUCT_OFFSET(pamb, 0x50, float) *= ratio; // real volAttenuated (compiled AMB layout is shifted -8 here; named field at 0x50 is frq)
        RefreshPambVolPan(pamb);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", FillPamb__FP3AMBPP3AMBiP3ALOP6VECTORfffffP2LMT10_);

INCLUDE_ASM("asm/nonmatchings/P2/sound", ActivatePamb__FP3AMB5SFXID);

INCLUDE_ASM("asm/nonmatchings/P2/sound", ScheduleNextIntermittentSound__FP3AMB);

INCLUDE_ASM("asm/nonmatchings/P2/sound", StartSound__F5SFXIDPP3AMBP3ALOP6VECTORfffffP2LMT9);

extern "C" void FUN_001BFFC8(int err, u_long user_data)
{
    if (err == 0)
    {
        int iSerial = (int)(user_data >> 32);
        AMB *pamb = (AMB *)(user_data & 0xFFFFFFFF);
        if (pamb->iSerial == iSerial)
        {
            STRUCT_OFFSET(pamb, 0x48, int) = 1; // fStopped (real offset; compiled AMB::fStopped lands at 0x44)
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", HandleWipeHandleWipeVolumes__FifVolumes);

INCLUDE_ASM("asm/nonmatchings/P2/sound", UpdateSounds__Fv);

void SetMvgkUvol(float uvol)
{
    snd_SetMasterVolume(8, (int)(uvol * 1024.0f));
}

void MvgkUnknown1(MVGK mvgk)
{
    float v = 1.0f;
    for (int i = 0; i < 11; ++i)
    {
        v *= D_00274838[i][mvgk];
    }

    float one = 1.0f;
    float zero = 0.0f;
    if (v < zero)
    {
        v = zero;
    }
    else if (v > one)
    {
        v = one;
    }
    
    snd_SetMasterVolume(mvgk, (int)(v * 1024.0f));
}

void SetMvgkRvol(int channel, MVGK mvgk, float rvol)
{
    D_00274838[channel][mvgk] = rvol;
    MvgkUnknown1(mvgk);
}

extern float D_00274758[10][4];
void MvgkUnknown3(int fMute);
void MvgkUnknown4(int mode);
void MvgkUnknown2()
{
    CopyAb(D_00274838, D_00274758, 0xB0);
    SetMvgkUvol(1.0f);
    for (int i = 0; i < 4; ++i)
    {
        MvgkUnknown1((MVGK)i);
    }
    MvgkUnknown3(STRUCT_OFFSET(g_pgsCur, 0x19EC, int) & 0x80);
    MvgkUnknown4(STRUCT_OFFSET(g_pgsCur, 0x19EC, int) & 0x40);
}

void MvgkUnknown3(int fMute)
{
    float rvol = 1.0f;
    if (fMute != 0)
    {
        rvol = 0.0f;
    }
    SetMvgkRvol(3, MVGK_Music, rvol);
}

void MvgkUnknown4(int mode)
{
    snd_SetPlaybackMode(mode != 0);
}

/**
 * @todo Figure out func_001c0cb0, and use enum values for params where applicable.
 */
void KillSoundSystem()
{
    snd_StopAllStreams();
    KillSounds(0);
    KillExcitement();
    FUN_001c0cb0();
    while (snd_FlushSoundCommands()) {}
    snd_StreamSafeCheckCDIdle(1);
    snd_StreamSafeCdSync(0);
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", KillSounds__Fi);

enum REVERBK {};
extern int D_00274808[];

void PushSwReverb(SW *psw, REVERBK reverb, int depth)
{
    if ((unsigned)STRUCT_OFFSET(psw, 0x2348, int) < 4)
    {
        snd_SetReverbType(2, D_00274808[reverb]);
        snd_SetReverbDepth(2, depth, depth);
        STRUCT_OFFSET((char *)psw + (STRUCT_OFFSET(psw, 0x2348, int) << 3), 0x2328, int) = reverb;
        STRUCT_OFFSET((char *)psw + (STRUCT_OFFSET(psw, 0x2348, int) << 3), 0x232c, int) = depth;
        STRUCT_OFFSET(psw, 0x2348, int) = STRUCT_OFFSET(psw, 0x2348, int) + 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", PopSwReverb__FP2SW);

void SetSwDefaultReverb(SW *psw, REVERBK reverb, const int depth)
{
    snd_SetReverbType(2, D_00274808[reverb]);
    snd_SetReverbDepth(2, depth, depth);
    STRUCT_OFFSET(psw, 0x2328, int) = reverb;
    STRUCT_OFFSET(psw, 0x232c, int) = depth;
    STRUCT_OFFSET(psw, 0x2348, int) = 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", FUN_001C0A50);

struct SW;

extern "C" void FUN_001C0AB8(SW *psw, float *pg)
{
    int c = STRUCT_OFFSET(psw, 0x1D80, int); // count of intermittent-sound entries (array of 0x14-byte entries at 0x1D84)
    if (c != 0)
    {
        char *pisnd = (char *)psw + (c * 0x14 + 0x1D70); // last entry: 0x1D84 + (c-1)*0x14
        STRUCT_OFFSET(pisnd, 0xC, float) = 8000.0f - pg[1] * 50.0f;  // lmRepDist.gMin
        STRUCT_OFFSET(pisnd, 0x10, float) = 8000.0f - pg[0] * 50.0f; // lmRepDist.gMax
    }
}

struct SW;

extern "C" void FUN_001C0B08(SW *psw, LM *plm)
{
    int c = STRUCT_OFFSET(psw, 0x1D80, int); // count of intermittent-sound entries (array of 0x14-byte entries at 0x1D84)
    if (c != 0)
    {
        char *pisnd = (char *)psw + (c * 0x14 + 0x1D70); // last entry: 0x1D84 + (c-1)*0x14
        STRUCT_OFFSET(pisnd, 0x4, LM) = *plm; // lmRepeat (unaligned 8-byte struct copy: ldl/ldr + sdl/sdr)
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", StartSwIntermittentSounds__FP2SW);

// TODO: Verify signature.
extern int D_006053E0[];
extern u_int D_00274728;
extern "C" void SetAMRegister__FiUc(int n, int bReg)
{
    if (bReg != D_006053E0[n])
    {
        D_006053E0[n] = bReg;
        snd_SetMIDIRegister(D_00274728, n, bReg);
    }
}

extern int D_006053E0[];
int GetAMRegister(int reg)
{
    return D_006053E0[reg];
}

extern int D_006053E0[];
extern u_int D_00274728;
void UpdateAMRegister(int reg, int value)
{
    D_006053E0[reg] = snd_GetMIDIRegister(D_00274728, reg);
}

void FUN_001c0cb0()
{
    for (int i = 0; i < 8; i++)
    {
        SetAMRegister__FiUc(i, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", HsNextFootFall__Fv);

extern int D_002748EC;
int HsNextFootFall();

void NextSneakyFootstep()
{
    if (D_002748EC != 0)
    {
        int hs = HsNextFootFall();
        StartSound((SFXID)0x77, NULL, NULL, NULL, 0.0f, 0.0f, 0.5f, hs * 0.083333336f, 0.0f, NULL, NULL);
    }
}
