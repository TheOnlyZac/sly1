#include <sound.h>
#include <989snd.h>
#include <sce/memset.h>
#include <sw.h>
#include <po.h>
#include <cm.h>
#include <cplcy.h>
#include <dl.h>
#include <slotheap.h>
#include <memory.h>
#include <game.h>
#include <cat.h>

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

extern float D_00274838[11][4]; // temp
extern float D_00274758[11][4]; // default mvgk rvols (guess)


extern uint D_00274728; // music sfx handle (guess)
extern uint D_0027472C; // vag handle (guess)
extern int D_00274730;
extern int D_00274744;
extern int D_00274748;
extern int D_0027474C; // AMB serial counter (guess)
extern float D_00274750;
extern int D_00274754;
extern int D_00245020[][2]; // sfxid -> bank table (guess)
extern int D_00274720;
extern int D_00274724;
extern uint D_0027473C;
extern int D_00274734;
extern DLI *s_pdliFirst; // Global iterator list (defined in dl.c).
extern int D_002748EC;
extern AMB *D_002748E8;
extern LM D_00274820;
extern LM D_00274828;
extern int D_00274808[];
extern void *D_006047B0[];
extern int D_006047D0[];




/**
 * @brief Advance a DL iterator and return the element it was on.
 * @note Name is a guess.
 */
static inline void *PvNextDli(DLI *pdli)
{
    void *pv = *pdli->m_ppv;
    pdli->m_ppv = (void **)((char *)pv + pdli->m_ibDle);
    return pv;
}

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

void *SbpEnsureBank(SFXID sfxid)
{
    return SbpEnsureBank(D_00245020[sfxid][0]);
}

void NewSfx(SFX **ppsfx)
{
    *ppsfx = (SFX *)PvAllocSwClearImpl(sizeof(SFX));
    (*ppsfx)->sfxid = (SFXID)-1;
    (*ppsfx)->sStart = 3000.0f;
    (*ppsfx)->sFull = 300.0f;
    (*ppsfx)->uVol = 1.0f;
    (*ppsfx)->uPitch = 0.0f;
    (*ppsfx)->pamb = 0;
    (*ppsfx)->lmRepeat.gMin = -1.0f;
    (*ppsfx)->uDoppler = 0.0f;
}

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

void RefreshPambVolPan(AMB *pamb)
{
    int vol = (int)(pamb->volAttenuated * 1024.0f);
    float pan = pamb->pan;
    int ipan;
    if (pan > 0.0f)
        ipan = (int)((pan + 2.0f) * 179.5f) - 0x167;
    else
        ipan = (int)((pan + 2.0f) * 179.5f);
    snd_SetSoundVolPan(pamb->sfxh, vol, ipan);
}

void StartAloSound(ALO *palo, AMB **ppamb, float sStart, float sFull)
{
    AMB *pamb;
    int fLocal = 0;
    if (!ppamb)
    {
        fLocal = 1;
        ppamb = &pamb;
    }
    StartSound(SFXID_UnkNeg2, ppamb, palo, 0, sStart, sFull, 1.0f, 0.0f, 0.0f, 0, 0);
    if (*ppamb)
    {
        RefreshPambVolPan(*ppamb);
        if (fLocal)
            DropPamb(ppamb);
    }
}

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

void KillExcitement()
{
    DL *pdl = &g_psw->dlExc;
    DLI dli;
    dli.m_pdl = pdl;
    dli.m_ppv = (void **)pdl;
    dli.m_ibDle = pdl->ibDle;
    dli.m_pdliNext = s_pdliFirst;
    s_pdliFirst = &dli;
    for (void *pv = PvNextDli(&dli); pv; pv = PvNextDli(&dli))
        RemoveExc((EXC *)pv);
    snd_SetGlobalExcite(0x14);
    D_002748EC = 0;
    s_pdliFirst = dli.m_pdliNext;
    g_iexcHyst = 0;
    D_00274734 = 0;
}

/**
 * @todo ~84% matched (6 differing lines of 37): clamp uses movn with swapped operands instead of movz.
 */
INCLUDE_ASM("asm/nonmatchings/P2/sound", PexcSetExcitement__Fi);
#ifdef SKIP_ASM
EXC *PexcSetExcitement(int iexc)
{
    bool fEmpty = FIsDlEmpty(&g_psw->dlExc);
    EXC *pexc = PexcAlloc();
    int lim = 0x6B;
    int iexcNew;
    if (iexc < -20)
        iexcNew = -20;
    else
        iexcNew = (lim < iexc) ? lim : iexc;
    if (pexc)
    {
        pexc->iexc = iexcNew;
        int iexcCur = D_00274734;
        if (iexcCur < iexcNew || fEmpty)
        {
            D_00274734 = iexcNew;
            g_iexcHyst = iexcCur;
        }
    }
    return pexc;
}
#endif // SKIP_ASM

void SetIexcCurHigh(EXC *pexc)
{
    DL *pdl = &g_psw->dlExc;
    DLI dli;
    dli.m_pdl = pdl;
    dli.m_ppv = (void **)pdl;
    dli.m_ibDle = pdl->ibDle;
    dli.m_pdliNext = s_pdliFirst;
    s_pdliFirst = &dli;
    if (FIsDlEmpty(pdl))
    {
        D_00274734 = 0;
    }
    else
    {
        D_00274734 = -20;
        for (void *pv = PvNextDli(&dli); pv; pv = PvNextDli(&dli))
        {
            int iexc = ((EXC *)pv)->iexc;
            if (D_00274734 < iexc)
                D_00274734 = iexc;
        }
    }
    s_pdliFirst = dli.m_pdliNext;
}

void UnsetExcitement(EXC *pexc)
{
    if (pexc)
    {
        int iexc = pexc->iexc;
        RemoveExc(pexc);
        if (iexc == D_00274734)
        {
            SetIexcCurHigh(pexc);
            if (D_00274734 >= 0)
                D_002748EC = 0;
            g_iexcHyst = D_00274734;
            snd_SetGlobalExcite(D_00274734 + 0x14);
            SetMvgkRvol(7, MVGK_Music, 1.0f);
            g_iexcHyst = -100;
        }
    }
}

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

extern "C" float FUN_001BF398(VECTOR *pposA, VECTOR *pposB)
{
    float r;
    asm("lqc2 $vf1,%1\n\tlqc2 $vf2,%2\n\tvsub.xyzw $vf1,$vf1,$vf2\n\tvmul.xyz $vf1,$vf1,$vf1\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf3,$vf1z\n\t.word 0x4A0103BD\n\tvwaitq\n\tvaddq.x $vf1,$vf0,Q\n\tqmfc2.ni $2,$vf1\n\tmtc1 $2,%0" : "=f"(r) : "m"(*pposA), "m"(*pposB) : "$2");
    return r;
}

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

PFNEARDIST PfneardistGet()
{
    if (FActiveCplcy(&g_pcm->cplook))
    {
        int lookk = LookkCurCplook(&g_pcm->cplook);
        if (lookk >= 3)
            return FUN_001BF398;
        if (lookk > 0)
            return FUN_001BF2E0;
    }
    return FUN_001BF398;
}

float SDistEar(VECTOR *ppos)
{
    VECTOR *pposEar = PposEar();
    return PfneardistGet()(pposEar, ppos);
}

void CalculateDistVolPan(VECTOR *ppos, float *puVol, float *pPan, float uVol, float sStart, float sFull)
{
    if (ppos)
    {
        CalculateVolPan(SDistEar(ppos), ppos, puVol, pPan, uVol, sStart, sFull);
    }
    else
    {
        *puVol = uVol;
        *pPan = 0.0f;
    }
}

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

void SetPambFrq(AMB *pamb, float frq)
{
    if (pamb)
    {
        if (frq != pamb->frq || (pamb->palo && 0.0001f < pamb->rDoppler))
        {
            pamb->frq = frq;
            if (!pamb->fPitchOrig)
            {
                pamb->ptchOrig = snd_GetSoundOriginalPitch(pamb->bnk, D_00245020[pamb->sfxid][1]);
                pamb->fPitchOrig = 1;
            }
            int ptch = pamb->ptchOrig + (int)(pamb->frq * 1524.0f) + pamb->dnDoppler;
            int hi = 0x7FFF;
            int ptchNew;
            if (ptch < -0x8000)
                ptchNew = -0x8000;
            else
                ptchNew = (hi < ptch) ? hi : ptch;
            ptch = ptchNew;
            snd_SetSoundPitch(pamb->sfxh, ptch);
        }
    }
}

void SetPambVol(AMB *pamb, float uVolAtSource)
{
    if (pamb)
    {
        pamb->volAttenuated *= uVolAtSource / pamb->uVolAtSource;
        pamb->uVolAtSource = uVolAtSource;
        RefreshPambVolPan(pamb);
    }
}

void FillPamb(AMB *pamb, AMB **ppamb, int fContinuous, ALO *palo, VECTOR *ppos, float sStart, float sFull, float uVolAtSource, float frq, float uDoppler, LM *plmRepeat, LM *plmRepDist)
{
    DLE dle = pamb->dle;
    memset(pamb, 0, sizeof(AMB));
    pamb->dle = dle;
    if (palo)
        ppos = &STRUCT_OFFSET(palo, 0x140, VECTOR);
    pamb->ppamb = ppamb;
    if (ppamb)
        *ppamb = pamb;
    pamb->frq = frq;
    pamb->rDoppler = uDoppler;
    pamb->fContinuous = fContinuous;
    pamb->palo = palo;
    pamb->sStart = sStart;
    pamb->sFull = sFull;
    pamb->uVolAtSource = uVolAtSource;
    pamb->fStopped = 0;
    pamb->iSerial = D_0027474C++;
    STRUCT_OFFSET(pamb, 0x4c, uchar) = NRandInRange(0, 3);
    if (plmRepeat)
        pamb->lmRepeat = *plmRepeat;
    else
        pamb->lmRepeat.gMin = -1.0f;
    if (plmRepDist)
        pamb->lmRepDist = *plmRepDist;
    else
        pamb->lmRepDist.gMin = -1.0f;
    if (ppos)
        STRUCT_OFFSET(&pamb->pos, 0, qword) = STRUCT_OFFSET(ppos, 0, qword);
    pamb->fAttached = ppos != 0 || pamb->lmRepeat.gMin >= 0.0f;
    CalculateDistVolPan(ppos, &pamb->volAttenuated, &pamb->pan, uVolAtSource, sStart, sFull);
    SetDoppler(pamb);
}

void ActivatePamb(AMB *pamb, SFXID sfxid)
{
    void *pbnk;
    int isnd;
    if (sfxid != SFXID_UnkNeg2)
    {
        pbnk = SbpEnsureBank(sfxid);
        isnd = D_00245020[sfxid][1];
        pamb->bnk = pbnk;
    }
    pamb->sfxid = sfxid;
    pamb->tStarted = g_clock.t;
    if (sfxid == SFXID_UnkNeg2)
    {
        pamb->sfxh = D_0027472C;
        pamb->fOutOfRange = 0;
    }
    else if (pamb->volAttenuated != 0.0f && pamb->lmRepeat.gMin < 0.0f)
    {
        pamb->sfxh = snd_PlaySoundVolPanPMPB(pbnk, isnd, 0, 0, 0, 0);
        pamb->fOutOfRange = 0;
        SetDoppler(pamb);
        SetPambFrq(pamb, pamb->frq);
        RefreshPambVolPan(pamb);
    }
    else
    {
        pamb->sfxh = 0;
        pamb->fOutOfRange = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sound", ScheduleNextIntermittentSound__FP3AMB);

INCLUDE_ASM("asm/nonmatchings/P2/sound", StartSound__F5SFXIDPP3AMBP3ALOP6VECTORfffffP2LMT9);

void AmbCompleteProc(int result, unsigned long userData)
{
    if (result == 0)
    {
        AMB *pamb = (AMB *)(userData & 0xFFFFFFFF);
        int iSerial = (int)((long)userData >> 32);
        if (pamb->iSerial == iSerial)
            pamb->fStopped = 1;
    }
}

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

void MvgkUnknown2()
{
    CopyAb(D_00274838, D_00274758, 0xB0);
    SetMvgkUvol(1.0f);
    for (int i = 0; i < 4; i++)
        MvgkUnknown1((MVGK)i);
    MvgkUnknown3(g_pgsCur->grfgs & 0x80);
    MvgkUnknown4(g_pgsCur->grfgs & 0x40);
}

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

void KillSounds(int msRampdown)
{
    if (g_psw)
    {
        DL *pdl = &g_psw->dlAmb;
        DLI dli;
        dli.m_pdl = pdl;
        dli.m_ppv = (void **)pdl;
        dli.m_ibDle = pdl->ibDle;
        dli.m_pdliNext = s_pdliFirst;
        s_pdliFirst = &dli;
        for (void *pv = PvNextDli(&dli); pv; pv = PvNextDli(&dli))
            StopSound((AMB *)pv, msRampdown);
        s_pdliFirst = dli.m_pdliNext;
    }
    snd_FlushSoundCommands();
}

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

void AddSwIntermittentSound(SW *psw, SFXID sfxid)
{
    if (psw->cswsi < 16)
    {
        SWSI *pswsi = &psw->aswsi[psw->cswsi];
        pswsi->sfxid = sfxid;
        pswsi->lmRepeat = D_00274820;
        pswsi->lmRepDist = D_00274828;
        psw->cswsi++;
    }
}

void SetSwIntermittentDist(SW *psw, LM *plm)
{
    if (psw->cswsi)
    {
        SWSI *pswsi = &psw->aswsi[psw->cswsi - 1];
        pswsi->lmRepDist.gMin = 8000.0f - plm->gMax * 50.0f;
        pswsi->lmRepDist.gMax = 8000.0f - plm->gMin * 50.0f;
    }
}

void SetSwIntermittentRepeat(SW *psw, LM *plm)
{
    if (psw->cswsi)
    {
        SWSI *pswsi = &psw->aswsi[psw->cswsi - 1];
        pswsi->lmRepeat = *plm;
    }
}

void StartSwIntermittentSounds(SW *psw)
{
    for (int i = 0; i < psw->cswsi; ++i)
    {
        StartSound((SFXID)psw->aswsi[i].sfxid, &D_002748E8, 0, 0, 8000.0f, 3000.0f, 1.0f, 0.0f, 0.0f, &psw->aswsi[i].lmRepeat, &psw->aswsi[i].lmRepDist);
    }
}

// TODO: Verify signature.
// The original does not zero-extend the uchar argument, which only compiles
// with an int parameter and an asm label carrying the real (uchar) mangled name.
void SetAMRegister_impl(int reg, int value) asm("SetAMRegister__FiUc");
void SetAMRegister_impl(int reg, int value)
{
    if (value != D_006053E0[reg])
    {
        D_006053E0[reg] = value;
        snd_SetMIDIRegister(D_00274728, reg, value);
    }
}

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
