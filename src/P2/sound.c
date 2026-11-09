#include <sound.h>
#include <989snd.h>
#include <sce/memset.h>
#include <sw.h>
#include <po.h>
#include <cm.h>
#include <dl.h>
#include <slotheap.h>

extern uchar D_00604790[]; // temp
extern int D_006053E0[];

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


extern uint D_00274728; // music sfx handle (guess)
extern uint D_0027472C; // vag handle (guess)
extern int D_00274730;
extern int D_00274744;
extern int D_00274748;
extern int D_00245020[][2]; // sfxid -> bank table (guess)
extern int D_00274720;
extern int D_00274724;
extern uint D_0027473C;
extern int D_00274734;
extern int D_002748EC;
extern int D_00274808[];
extern void *D_006047B0[];
extern int D_006047D0[];




void UnloadMusic()
{
    if (D_0027473C)
    {
        if (D_00274728)
            snd_StopSound(D_00274728);
        snd_UnloadBank((SoundBankPtr)D_0027473C);
        while (snd_FlushSoundCommands()) {}
        D_0027473C = 0;
    }
    D_00274720 = 0;
    D_00274728 = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", SbpEnsureBank__Fi);

void SbpEnsureBank(SFXID sfxid)
{
    SbpEnsureBank(D_00245020[sfxid][0]);
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", NewSfx__FPP3SFX);

int FContinuousSound(SFXID sfxid)
{
    if (!D_006047B0[D_00245020[sfxid][0]])
        SbpEnsureBank(sfxid);
    return D_006047D0[sfxid];
}

void FUN_001BE5D8()
{
    D_00274730 = 0;
}

int SetVagUnpaused()
{
    return D_00274744;
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", PreloadVag__FPc2FK);

void FUN_001be708()
{
    D_00274744 = 0;
    StopVag();
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", PreloadVag1);

int FPauseForVag()
{
    if (D_00274744)
        return 0;
    if (D_0027472C)
    {
        if (D_00274730)
            return 1;
        snd_ContinueVAGStream(D_0027472C);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", RefreshPambVolPan__FP3AMB);

INCLUDE_ASM("asm/nonmatchings/P2/sound", FUN_001be8f8);

int FVagPlaying()
{
    return D_0027472C != 0;
}

JUNK_WORD(0x0080102D);

INCLUDE_ASM("asm/nonmatchings/P2/sound", StopVag__Fv);

void PauseVag()
{
    if (D_0027472C)
        snd_PauseSound(D_0027472C);
}

void ContinueVag()
{
    if (D_0027472C)
        snd_ContinueSound(D_0027472C);
}

void KillMusic()
{
    if (D_00274720 == 3)
    {
        snd_StopSound(D_00274728);
        D_00274728 = 0;
        D_00274720 = 2;
    }
}

void PreloadMusidSongComplete(uint handle, unsigned long userData)
{
    D_0027473C = handle;
    if (handle)
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

INCLUDE_ASM("asm/nonmatchings/P2/sound", StartMusidSong__F5MUSID);

void PauseMusic()
{
    SetMvgkRvol(2, MVGK_Music, 0.0f);
}

void ContinueMusic()
{
    SetMvgkRvol(2, MVGK_Music, 1.0f);
}

void SfxhMusicUnknown1()
{
    snd_PauseSound(D_00274728);
}

void SfxhMusicUnknown2()
{
    snd_ContinueSound(D_00274728);
}

EXC *PexcAlloc()
{
    EXC *pexc = (EXC *)PvAllocSlotheapUnsafe(&g_psw->slotheapExc);
    if (pexc)
    {
        memset(pexc, 0, sizeof(EXC));
        AppendDlEntry(&g_psw->dlExc, pexc);
    }
    return pexc;
}

void RemoveExc(EXC *pexc)
{
    RemoveDlEntry(&g_psw->dlExc, pexc);
    FreeSlotheapPv(&g_psw->slotheapExc, pexc);
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", KillExcitement__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/sound", PexcSetExcitement__Fi);

INCLUDE_ASM("asm/nonmatchings/P2/sound", SetIexcCurHigh__FP3EXC);

INCLUDE_ASM("asm/nonmatchings/P2/sound", UnsetExcitement__FP3EXC);

void UnsetExcitementHyst(EXC *pexc)
{
    if (pexc)
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

int FAmbientsPaused()
{
    return D_00274748;
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", CalculateVolPan__FfP6VECTORPfT2fff);

INCLUDE_ASM("asm/nonmatchings/P2/sound", FUN_001BF2E0);

INCLUDE_ASM("asm/nonmatchings/P2/sound", FUN_001BF398);

VECTOR *PposEar()
{
    PO *ppo = PpoCur();
    VECTOR *ppos;
    typedef int (*PFN)(PO *);
    if (ppo && ((PFN *)STRUCT_OFFSET(ppo, 0, void *))[0x138 / 4](ppo))
        ppos = &STRUCT_OFFSET(ppo, 0x140, VECTOR);
    else
        ppos = &STRUCT_OFFSET(g_pcm, 0x40, VECTOR);
    return ppos;
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", SetDoppler__FP3AMB);

INCLUDE_ASM("asm/nonmatchings/P2/sound", PfneardistGet__Fv);

float SDistEar(VECTOR *ppos)
{
    VECTOR *pposEar = PposEar();
    return PfneardistGet()(pposEar, ppos);
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", CalculateDistVolPan__FP6VECTORPfT1fff);

AMB *PambAlloc()
{
    AMB *pamb = (AMB *)PvAllocSlotheapUnsafe(&g_psw->slotheapAmb);
    if (pamb)
    {
        memset(pamb, 0, sizeof(AMB));
        AppendDlEntry(&g_psw->dlAmb, pamb);
    }
    return pamb;
}

void DropPamb(AMB **ppamb)
{
    (*ppamb)->ppamb = 0;
    *ppamb = 0;
}

void RemoveAmb(AMB *pamb)
{
    if (pamb->ppamb)
        *pamb->ppamb = 0;
    pamb->iSerial = -1;
    RemoveDlEntry(&g_psw->dlAmb, pamb);
    FreeSlotheapPv(&g_psw->slotheapAmb, pamb);
}

void StopSound(AMB *pamb, int msRampdown)
{
    if (pamb)
    {
        if (msRampdown == 0)
            snd_StopSound(pamb->sfxh);
        else
            snd_AutoVol(pamb->sfxh, -4, (int)((float)msRampdown * 0.24000001f), 2);
        RemoveAmb(pamb);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", SetPambFrq__FP3AMBf);

void SetPambVol(AMB *pamb, float uVolAtSource)
{
    if (pamb)
    {
        pamb->volAttenuated *= uVolAtSource / pamb->uVolAtSource;
        pamb->uVolAtSource = uVolAtSource;
        RefreshPambVolPan(pamb);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", FillPamb__FP3AMBPP3AMBiP3ALOP6VECTORfffffP2LMT10_);

INCLUDE_ASM("asm/nonmatchings/P2/sound", ActivatePamb__FP3AMB5SFXID);

INCLUDE_ASM("asm/nonmatchings/P2/sound", ScheduleNextIntermittentSound__FP3AMB);

INCLUDE_ASM("asm/nonmatchings/P2/sound", StartSound__F5SFXIDPP3AMBP3ALOP6VECTORfffffP2LMT9);

INCLUDE_ASM("asm/nonmatchings/P2/sound", FUN_001BFFC8);

void HandleWipeVolumes(int fMusic, float vol)
{
    SetMvgkRvol(6, MVGK_Effects, vol);
    SetMvgkRvol(6, (MVGK)2, vol);
    SetMvgkRvol(6, (MVGK)3, vol);
    if (fMusic)
        SetMvgkRvol(6, MVGK_Music, vol);
}

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

INCLUDE_ASM("asm/nonmatchings/P2/sound", MvgkUnknown2__Fv);

void MvgkUnknown3(int mute)
{
    SetMvgkRvol(3, MVGK_Music, mute ? 0.0f : 1.0f);
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

void PushSwReverb(SW *psw, REVERBK reverbk, const int depth)
{
    if ((uint)psw->cswrev < 4)
    {
        snd_SetReverbType(2, D_00274808[reverbk]);
        snd_SetReverbDepth(2, depth, depth);
        psw->aswrev[psw->cswrev].reverbk = reverbk;
        psw->aswrev[psw->cswrev].depth = depth;
        psw->cswrev++;
    }
}

void PopSwReverb(SW *psw)
{
    if (psw->cswrev >= 2)
    {
        psw->cswrev--;
        snd_SetReverbType(2, D_00274808[psw->aswrev[psw->cswrev - 1].reverbk]);
        int depth = psw->aswrev[psw->cswrev - 1].depth;
        snd_SetReverbDepth(2, depth, depth);
    }
}

void SetSwDefaultReverb(SW *psw, REVERBK reverbk, const int depth)
{
    snd_SetReverbType(2, D_00274808[reverbk]);
    snd_SetReverbDepth(2, depth, depth);
    psw->aswrev[0].reverbk = reverbk;
    psw->aswrev[0].depth = depth;
    psw->cswrev = 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", FUN_001C0A50);

INCLUDE_ASM("asm/nonmatchings/P2/sound", FUN_001C0AB8);

INCLUDE_ASM("asm/nonmatchings/P2/sound", FUN_001C0B08);

INCLUDE_ASM("asm/nonmatchings/P2/sound", StartSwIntermittentSounds__FP2SW);

// TODO: Verify signature.
/**
 * @todo 94% matched: the original does not zero-extend (andi 0xff) the uchar argument.
 */
INCLUDE_ASM("asm/nonmatchings/P2/sound", SetAMRegister__FiUc);
#ifdef SKIP_ASM
void SetAMRegister(int reg, uchar value)
{
    if ((int)value != D_006053E0[reg])
    {
        D_006053E0[reg] = (int)value;
        snd_SetMIDIRegister(D_00274728, reg, (int)value);
    }
}
#endif // SKIP_ASM

int GetAMRegister(int reg) 
{
    return D_006053E0[reg];
}

void UpdateAMRegister(int reg, int value)
{
    D_006053E0[reg] = snd_GetMIDIRegister(D_00274728, reg);
}

void FUN_001c0cb0()
{
    for (int i = 0; i < 8; ++i)
        SetAMRegister(i, 0);
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", HsNextFootFall__Fv);

void NextSneakyFootstep()
{
    if (D_002748EC)
    {
        int hs = HsNextFootFall();
        StartSound((SFXID)0x77, 0, 0, 0, 0.0f, 0.0f, 0.5f, (float)hs * 0.083333336f, 0.0f, 0, 0);
    }
}
