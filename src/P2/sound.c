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
#include <sdk/ee/eekernel.h>
#include <sdk/libcdvd.h>

extern void *D_00604790[]; // loaded sound bank table (guess)
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
extern int D_00274740; // current bank index (guess)
extern int D_00274748;
extern int D_0027474C; // AMB serial counter (guess)
extern float D_00274750;
extern int D_00274754;
extern int D_00274830; // footfall state (guess)
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
extern int D_006047B0[]; // bank looper scan done flags (guess)
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

/**
 * @brief Decode the file location (sector and size) of a catalog entry into a CFileLocation.
 * @return Nonzero if the entry exists and has a size. (Name is a guess.)
 */
static inline int FFillFcl(CFileLocation *pfl, void *pent)
{
    if (!pent)
        return 0;
    uint cb = STRUCT_OFFSET(pent, 4, uint) ^ STRUCT_OFFSET(pent, 0x1C, uint);
    uint isector = STRUCT_OFFSET(pent, 0, uint) ^ STRUCT_OFFSET(pent, 0x14, uint);
    pfl->m_fcl.cb = cb;
    pfl->m_fcl.isector = isector;
    return cb != 0;
}

/**
 * @brief Compare two catalog entries by their decoded key. (Name is a guess.)
 */
static inline int FEqualKey(void *entry, void *key)
{
    if (entry == key)
        return 1;
    if (entry == 0 || key == 0)
        return 0;
    return (((STRUCT_OFFSET(entry, 0x8, int) ^ STRUCT_OFFSET(entry, 0x18, int)) ^
             (STRUCT_OFFSET(key, 0x8, int) ^ STRUCT_OFFSET(key, 0x18, int)))) == 0;
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

/**
 * @todo ~50% matched (81 differing lines of 165): same control flow, but the original recomputes the D_00604790 address at each use (no CSE) and keeps different registers.
 */
INCLUDE_ASM("asm/nonmatchings/P2/sound", SbpEnsureBank__Fi);
#ifdef SKIP_ASM
extern int D_00244F40[];
extern int D_00246838[];
void *SbpEnsureBank(int bank)
{
    if (bank == D_00274740)
        return D_00604790[bank];
    if (bank == 0)
    {
        if (D_00604790[0])
            return D_00604790[0];
    }
    else
    {
        UnloadMusic();
        if (D_00274740 >= 0)
        {
            if (D_00604790[D_00274740])
            {
                snd_UnloadBank((SoundBankPtr)D_00604790[D_00274740]);
                while (snd_FlushSoundCommands()) {}
                D_00604790[D_00274740] = 0;
                snd_ResolveBankXREFS();
            }
        }
        D_00274740 = bank;
    }
    CFileLocation fl;
    if (FFillFcl(&fl, &D_00244F40[bank * 8]))
    {
        while (sceCdDiskReady(0) != 2) {}
        snd_StreamSafeCdSync(0);
        void *pbnk = snd_BankLoadByLoc(fl.m_fcl.isector, 0);
        D_00604790[bank] = pbnk;
        if (pbnk)
        {
            snd_ResolveBankXREFS();
            if (!D_006047B0[bank])
            {
                D_006047B0[bank] = 1;
                for (int i = 0; i < 0x303; i++)
                {
                    if (D_00245020[i][0] == bank)
                    {
                        int fLoop = 0;
                        if (snd_IsSoundALooper(pbnk, D_00245020[i][1]) || D_00246838[i])
                            fLoop = 1;
                        D_006047D0[i] = fLoop;
                    }
                }
            }
        }
    }
    return D_00604790[bank];
}
#endif // SKIP_ASM

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

void PreloadVag(char *pch, FK fk)
{
    if (D_00274744)
        return;
    if (!pch)
        return;
    if (FVagPlaying())
        StopVag();
    CFileLocation fl;
    if (!FFillFcl(&fl, pch))
        return;
    u_int h = snd_PlayVAGStreamByLoc(fl.m_fcl.isector, 0, 0, 0, 0x400, 0, 2, 0, 0);
    if (h)
    {
        D_0027472C = h;
        D_00274744 = 1;
        D_00274730 = 0;
        SetMvgkRvol(8, MVGK_Music, 0.5f);
        SetMvgkRvol(8, MVGK_Effects, 0.5f);
        SetMvgkRvol(8, (MVGK)3, 0.5f);
    }
}

void FUN_001be708()
{
    D_00274744 = 0;
    StopVag();
}

extern "C" void PreloadVag1(void *pent)
{
    if (D_00274744)
        return;
    if (FVagPlaying())
        StopVag();
    CFileLocation fl;
    if (FFillFcl(&fl, pent))
    {
        u_int h = snd_PlayVAGStreamByLoc(fl.m_fcl.isector, 0, 0, 0, 0x400, 0, 2, 0, 1);
        if (h)
        {
            D_0027472C = h;
            D_00274730 = 1;
            snd_IsVAGStreamBuffered_CB(h, (SndCompleteProc)FUN_001BE5D8, (u_long)h);
        }
    }
}

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

/**
 * @todo ~87% matched (5 differing lines of 37): the delay loop is [addiu; nop; nop*5; bgez; addiu(delay)] in the original, i.e. the decrement sits in the branch delay slot and the nop count differs; no variant reproduced it.
 */
INCLUDE_ASM("asm/nonmatchings/P2/sound", StopVag__Fv);
#ifdef SKIP_ASM
void StopVag()
{
    if (!D_00274744 && D_0027472C)
    {
        snd_StopSound(D_0027472C);
        while (snd_SoundIsStillPlaying(D_0027472C))
        {
            for (int i = 19999; i >= 0; i--)
            {
                asm("nop;nop;nop;nop;nop;nop");
            }
        }
        D_0027472C = 0;
        D_00274730 = 0;
    }
}
#endif // SKIP_ASM

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

void PreloadMusidSong(MUSID musid)
{
    if (!musid)
    {
        KillMusic();
        return;
    }
    int fSame = FEqualKey((void *)musid, (void *)D_00274724);
    if (fSame && D_00274720)
        return;
    while (snd_FlushSoundCommands() && D_00274720 == 1)
        FlushCache(0);
    UnloadMusic();
    D_00274724 = (int)musid;
    CFileLocation fl;
    if (FFillFcl(&fl, (void *)musid))
    {
        D_00274720 = 1;
        snd_StreamSafeCdSync(0);
        snd_BankLoadByLoc_CB(fl.m_fcl.isector, 0, (SndCompleteProc)PreloadMusidSongComplete, 0);
    }
}

void StartMusidSong(MUSID musid)
{
    PreloadMusidSong(musid);
    if (musid)
    {
        while (snd_FlushSoundCommands() && D_00274720 == 1)
            FlushCache(0);
        if (D_00274720 == 2)
        {
            u_int h = snd_PlaySoundVolPanPMPB((SoundBankPtr)D_0027473C, 0, 0x400, -1, 0, 0);
            D_00274728 = h;
            if (h)
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

/**
 * @todo ~45% matched (29 differing lines of 56): VU0 inline asm with fake register dependencies; the scalar constants and the g_pcm load are scheduled differently and ppos is copied to another register.
 */
INCLUDE_ASM("asm/nonmatchings/P2/sound", CalculateVolPan__FfP6VECTORPfT2fff);
#ifdef SKIP_ASM
void CalculateVolPan(float sDist, VECTOR *ppos, float *puVol, float *pPan, float uVol, float sStart, float sFull)
{
    if (ppos)
    {
        if (sStart < sDist)
        {
            float zero = 0.0f;
            *pPan = zero;
            *puVol = zero;
            return;
        }
        if (sFull < sDist)
        {
            VECTOR d;
            int a1, a2, a3, a4, a5, a6, a7;
            float num = sStart - sDist;
            float den = sStart - sFull;
            float k = 0.7f;
            float one = 1.0f;
            int dot;
            asm("lqc2 $vf2,0(%1)" : "=r"(a1) : "r"(ppos));
            asm("lqc2 $vf1,%1\n\tvsub.xyzw $vf2,$vf2,$vf1" : "=r"(a2) : "m"(STRUCT_OFFSET(g_pcm, 0x40, VECTOR)), "r"(a1));
            asm("vmul.xyz $vf1,$vf2,$vf2\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf3,$vf1z\n\tsqc2 $vf2,%1\n\t.word 0x4A0103BD\n\tvwaitq\n\tvaddq.x $vf1,$vf0,Q" : "=r"(a3), "=m"(d), "+f"(num) : "r"(a2));
            float t = num / den;
            asm("vdiv Q,$vf0w,$vf1x\n\tvwaitq\n\tvmulq.xyzw $vf1,$vf2,Q\n\tsqc2 $vf1,%1\n\tlqc2 $vf2,%2\n\tvmul.xyz $vf1,$vf1,$vf2\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf3,$vf1z" : "=r"(a4), "=m"(d) : "m"(STRUCT_OFFSET(g_pcm, 0x90, VECTOR)), "r"(a3), "f"(t));
            float oneMinusT = one - t;
            float vol = uVol * t;
            asm("qmfc2.ni %0,$vf1" : "=r"(dot) : "r"(a4));
            float dotf;
            asm("mtc1 %1,%0" : "=f"(dotf) : "r"(dot));
            *pPan = -dotf * k * oneMinusT;
            *puVol = vol;
            return;
        }
    }
    *puVol = uVol;
    *pPan = 0.0f;
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/sound", FUN_001BF2E0);
#ifdef SKIP_ASM
// @todo not attempted: VU0 code (see the asm), needs inline asm with fake register dependencies like CalculateVolPan.
#endif // SKIP_ASM

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
#ifdef SKIP_ASM
// @todo not attempted: VU0 code (see the asm), needs inline asm with fake register dependencies like CalculateVolPan.
#endif // SKIP_ASM

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
    pamb->cTick = NRandInRange(0, 3);
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

/**
 * @todo ~10% matched (64 differing lines of 57): the original builds the vector in a 128 bit register (mfc1, pextlw, pcpyld, qmtc2, sqc2 to pos and two stack copies); plain struct code uses ldl/ldr copies instead.
 */
INCLUDE_ASM("asm/nonmatchings/P2/sound", ScheduleNextIntermittentSound__FP3AMB);
#ifdef SKIP_ASM
void ScheduleNextIntermittentSound(AMB *pamb)
{
    pamb->tNext = g_clock.t + GRandInRange(pamb->lmRepeat.gMin, pamb->lmRepeat.gMax);
    if (!pamb->palo)
    {
        float rad = GRandInRange(0.0f, 6.2831855f);
        float sDist = GRandInRange(pamb->lmRepDist.gMin, pamb->lmRepDist.gMax);
        VECTOR v;
        v.x = cosf(rad) * sDist;
        v.y = sinf(rad) * sDist;
        v.z = 0.0f;
        v.gUnused = 0.0f;
        pamb->pos = v;
        VECTOR *pposEar = PposEar();
        asm("lqc2 $vf2,%1\n\tlqc2 $vf1,%2\n\tvadd.xyzw $vf1,$vf1,$vf2\n\tsqc2 $vf1,%0" : "=m"(pamb->pos) : "m"(*pposEar), "m"(v));
    }
}
#endif // SKIP_ASM

void StartSound(SFXID sfxid, AMB **ppamb, ALO *palo, VECTOR *ppos, float sStart, float sFull, float uVolAtSource, float frq, float uDoppler, LM *plmRepeat, LM *plmRepDist)
{
    if (sfxid == (SFXID)-1)
        return;
    int fContinuous;
    if (sfxid != SFXID_UnkNeg2)
    {
        int ibank = D_00245020[sfxid][0];
        if (ibank > 0 && ibank != STRUCT_OFFSET(g_psw, 0x1D70, int))
            return;
        fContinuous = FContinuousSound(sfxid);
    }
    else
    {
        fContinuous = 0;
    }
    AMB *pamb = 0;
    if (ppos || palo || ppamb)
    {
        if (!fContinuous && (!plmRepeat || plmRepeat->gMin < 0.0f))
        {
            AMB amb;
            FillPamb(&amb, ppamb, 0, palo, ppos, sStart, sFull, uVolAtSource, frq, uDoppler, 0, 0);
            if (amb.volAttenuated != 0.0f)
            {
                pamb = PambAlloc();
                if (pamb)
                {
                    amb.dle = pamb->dle;
                    *pamb = amb;
                }
            }
            else if (sfxid == SFXID_UnkNeg2)
            {
                snd_SetSoundVolPan(D_0027472C, 0, 0);
            }
            if (ppamb)
                *ppamb = pamb;
        }
        else
        {
            pamb = PambAlloc();
            if (!pamb)
                return;
            FillPamb(pamb, ppamb, fContinuous, palo, ppos, sStart, sFull, uVolAtSource, frq, uDoppler, plmRepeat, plmRepDist);
        }
        if (!pamb)
            return;
        if (0.0f <= pamb->lmRepeat.gMin)
        {
            ScheduleNextIntermittentSound(pamb);
            pamb->tNext = g_clock.t + GRandInRange(0.0f, pamb->lmRepeat.gMin);
        }
        ActivatePamb(pamb, sfxid);
    }
    else
    {
        void *pbnk = SbpEnsureBank(sfxid);
        snd_PlaySoundVolPanPMPB(pbnk, D_00245020[sfxid][1], (int)(uVolAtSource * 1024.0f), 0, (int)(frq * 1524.0f), 0);
    }
}

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

void UpdateSounds()
{
    if (FAmbientsPaused())
        return;
    // Register pins are a hack to force the original register assignment.
    register VECTOR *pposEar asm("$20") = PposEar();
    register PFNEARDIST pfneardist asm("$21") = PfneardistGet();
    DL *pdl = &g_psw->dlAmb;
    DLI dli;
    dli.m_pdl = pdl;
    dli.m_ppv = (void **)pdl;
    dli.m_ibDle = pdl->ibDle;
    dli.m_pdliNext = s_pdliFirst;
    s_pdliFirst = &dli;
    if (D_0027472C && !snd_SoundIsStillPlaying(D_0027472C))
    {
        if (D_00274744)
        {
            SetMvgkRvol(8, MVGK_Music, 1.0f);
            SetMvgkRvol(8, MVGK_Effects, 1.0f);
            SetMvgkRvol(8, (MVGK)3, 1.0f);
        }
        D_0027472C = 0;
        D_00274744 = 0;
        D_00274730 = 0;
    }
    if (g_iexcHyst != -100)
    {
        int iexcCur = D_00274734;
        int fRise = g_iexcHyst < iexcCur;
        if (iexcCur > 0 && fRise)
        {
            snd_SetGlobalExcite(iexcCur + 20);
            g_iexcHyst = D_00274734;
            SetMvgkRvol(7, MVGK_Music, 1.0f);
            D_002748EC = 0;
        }
        else if (--D_00274754 < 0)
        {
            int iexcHyst = g_iexcHyst;
            int iexcNew = (D_00274734 < iexcHyst) ? iexcHyst - 1 : iexcHyst + 1;
            D_002748EC = (uint)iexcNew >> 31;
            g_iexcHyst = iexcNew;
            snd_SetGlobalExcite(iexcNew + 20);
            if (g_iexcHyst < 0)
            {
                float t = (float)g_iexcHyst * -0.05f;
                float zero = 0.0f;
                float one = 1.0f;
                float tc;
                if (t < zero)
                    tc = zero;
                else if (t > one)
                    tc = one;
                else
                    tc = t;
                float a = tc * 0.6666667f;
                SetMvgkRvol(7, MVGK_Music, (1.0f - tc) + a);
            }
            D_00274754 += 3;
        }
        if (fRise ? !(g_iexcHyst < D_00274734) : !(g_iexcHyst > D_00274734))
        {
            D_002748EC = (uint)g_iexcHyst >> 31;
            snd_SetGlobalExcite(D_00274734 + 20);
            g_iexcHyst = -100;
        }
    }
    for (void *pv = PvNextDli(&dli); pv; pv = PvNextDli(&dli))
    {
        AMB *pamb = (AMB *)pv;
        if (pamb->palo && !FIsLoInWorld(pamb->palo))
        {
            StopSound(pamb, 0);
            continue;
        }
        if (!pamb->fOutOfRange)
        {
            if (pamb->fStopped)
            {
                if (0.0f <= pamb->lmRepeat.gMin)
                {
                    pamb->sfxh = 0;
                }
                else
                {
                    if (pamb->palo)
                        pamb->palo->pvtlo->pfnSendLoMessage(pamb->palo, (MSGID)9, pamb);
                    if (!pamb->fContinuous)
                    {
                        StopSound(pamb, 0);
                        continue;
                    }
                    snd_StopSound(pamb->sfxh);
                    pamb->sfxh = 0;
                }
                pamb->fStopped = 0;
                pamb->fOutOfRange = 1;
                continue;
            }
            int n = (pamb->cTick + 1) % 4;
            pamb->cTick = n;
            if ((uchar)n == 0)
                snd_SoundIsStillPlaying_CB(pamb->sfxh, AmbCompleteProc, (u_long)pamb | ((u_long)pamb->iSerial << 32));
        }
        if (0.0f <= pamb->lmRepeat.gMin)
        {
            if (g_clock.t < pamb->tNext)
            {
                if (pamb->fOutOfRange)
                    continue;
            }
            else
            {
                ScheduleNextIntermittentSound(pamb);
                if (pamb->fOutOfRange)
                {
                    float tNow = g_clock.t;
                    if (tNow - D_00274750 < 1.0f)
                        continue;
                    D_00274750 = tNow;
                }
            }
        }
        if (!pamb->fAttached)
            continue;
        VECTOR *ppos = pamb->palo ? &STRUCT_OFFSET(pamb->palo, 0x140, VECTOR) : &pamb->pos;
        float sDist = pfneardist(pposEar, ppos);
        if (pamb->sStart < sDist)
        {
            if (0.0f <= pamb->lmRepeat.gMin)
                continue;
            if (pamb->fOutOfRange)
                continue;
            if (pamb->fContinuous || 0.0f < pamb->tNext)
            {
                snd_StopSound(pamb->sfxh);
                pamb->sfxh = 0;
                pamb->fOutOfRange = 1;
            }
            else
            {
                StopSound(pamb, 0);
            }
        }
        else
        {
            CalculateVolPan(sDist, ppos, &pamb->volAttenuated, &pamb->pan, pamb->uVolAtSource, pamb->sStart, pamb->sFull);
            if (pamb->fOutOfRange && pamb->sfxid != SFXID_UnkNeg2)
            {
                pamb->sfxh = snd_PlaySoundVolPanPMPB(pamb->bnk, D_00245020[pamb->sfxid][1], 0, 0, 0, 0);
                pamb->fOutOfRange = 0;
            }
            SetDoppler(pamb);
            SetPambFrq(pamb, pamb->frq);
            RefreshPambVolPan(pamb);
        }
    }
    snd_FlushSoundCommands();
    s_pdliFirst = dli.m_pdliNext;
}

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

int HsNextFootFall()
{
    int aiStep[42] = {-5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, 1, -5, -5, -5, -5, 1, 1, -5, -5, -5, 1, 1, 1, -5, -5, 1, 1, 1, 1, -5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int aiRow[25] = {6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0};
    int n = NRandInRange(0, 5);
    int r = aiRow[D_00274830 + 12] * 24;
    D_00274830 += *(int *)((char *)aiStep + (n * 4 + r));
    return D_00274830;
}

void NextSneakyFootstep()
{
    if (D_002748EC)
    {
        int hs = HsNextFootFall();
        StartSound((SFXID)0x77, 0, 0, 0, 0.0f, 0.0f, 0.5f, (float)hs * 0.083333336f, 0.0f, 0, 0);
    }
}

// FLT_MAX. Probably owned by spire (its rodata starts at 0x14e3b4, used by InitSpire); defined here only so the
// raw rodata blob after sound's rodata starts 8 byte aligned like in the original.
extern const float DAT_0024d3b4 = 3.4028235e38f;
