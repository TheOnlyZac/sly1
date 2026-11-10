#include <suv.h>
#include <clock.h>
#include <find.h>
#include <sm.h>
#include <ui.h>

struct SUVRACE // guess, only the vtable and the counter at 0x27c are known
{
    void *pvt;
    char pad[0x278];
    int c;
};

struct UNKBLOT // guess, only the vtable and the pointers at 0x264 and 0x268 are known
{
    void *pvt;
    char pad[0x260];
    void *pv0;
    void *pv1;
};

#define VCALL(pobj, off) (*(void (**)(void *))(*(int *)(pobj) + (off)))(pobj)

extern char D_00275290[];
extern char D_00275250[];

void InitSuv(SUV *psuv)
{
    InitPo(psuv);
    STRUCT_OFFSET(psuv, 0x614, float) = 50.0f;
    STRUCT_OFFSET(psuv, 0x610, float) = 50.0f;
    STRUCT_OFFSET(psuv, 0x618, float) = 3000.0f;
    STRUCT_OFFSET(psuv, 0x61c, float) = 1300.0f;
    STRUCT_OFFSET(psuv, 0x868, float) = 2.0f;
    STRUCT_OFFSET(psuv, 0xb04, int) = 3;
    STRUCT_OFFSET(psuv, 0x620, qword) = *(qword *)D_00275290;
    CopyAb(&STRUCT_OFFSET(psuv, 0x630, char), D_00275250, 0x40);
    ResetSuv(psuv);
}

INCLUDE_ASM("asm/nonmatchings/P2/suv", PostSuvLoad__FP3SUV);

INCLUDE_ASM("asm/nonmatchings/P2/suv", PresetSuvAccel__FP3SUVf);

/**
 * @todo 16 differing lines of 79: float register allocation (g and gBest swapped) and hoisted constant load.
 */
INCLUDE_ASM("asm/nonmatchings/P2/suv", GExcludeAlm__FiP2LMf);
#ifdef SKIP_ASM
extern float D_0024DC94;

float GExcludeAlm(int clm, LM *alm, float g)
{
    float gBest, dgBest;
    gBest = dgBest = D_0024DC94;
    if (!FCheckAlm(clm, alm, g))
    {
        return g;
    }
    for (int i = 0; i < clm; i++)
    {
        LM *plm = &alm[i];
        float dg = ABS(g - plm->gMin);
        if (dg < dgBest)
        {
            if (!FCheckAlm(clm, alm, plm->gMin))
            {
                gBest = plm->gMin;
                dgBest = dg;
            }
        }
        dg = ABS(g - plm->gMax);
        if (dg < dgBest)
        {
            if (!FCheckAlm(clm, alm, plm->gMax))
            {
                gBest = plm->gMax;
                dgBest = dg;
            }
        }
    }
    return gBest;
}
#endif

extern SMP D_00275490;
extern float D_002754A0[2];

void UpdateSuvBalance(SUV *psuv)
{
    if (psuv != PpoCur())
    {
        STRUCT_OFFSET(psuv, 0x85c, float) = GSmooth(STRUCT_OFFSET(psuv, 0x85c, float), STRUCT_OFFSET(psuv, 0x860, float), g_clock.dt, &D_00275490, 0);
        if (g_clock.t < STRUCT_OFFSET(psuv, 0x864, float))
        {
        }
        else
        {
            int n = (STRUCT_OFFSET(psuv, 0xb00, int) - 1) * 3 + STRUCT_OFFSET(STRUCT_OFFSET(psuv, 0xaf8, SUVFEAT *), 0xc, int);
            float x = n * 0.1f;
            float lo = 0.0f, hi = 1.0f;
            float xc;
            if (x < lo)
                xc = lo;
            else if (x > hi)
                xc = hi;
            else
                xc = x;
            float v = GEvaluateClq(&STRUCT_OFFSET(psuv, 0x670, CLQ), xc);
            float vlo = STRUCT_OFFSET(psuv, 0x680, float), vhi = STRUCT_OFFSET(psuv, 0x684, float);
            float vc;
            if (v < vlo)
                vc = vlo;
            else if (v > vhi)
                vc = vhi;
            else
                vc = v;
            STRUCT_OFFSET(psuv, 0x860, float) = vc;
            STRUCT_OFFSET(psuv, 0x860, float) += GRandInRange(-0.05f, 0.05f);
            STRUCT_OFFSET(psuv, 0x864, float) = g_clock.t + GRandInRange(D_002754A0[0], D_002754A0[1]);
        }
    }
}

float DsGetTrackRelative(float a, float b, float c)
{
    float d = b - c;
    if (d > a * 0.5f)
    {
        d -= a;
    }
    else if (d < a * -0.5f)
    {
        d += a;
    }
    return d;
}

int FIsSuvAheadOf(SUV *psuv, SUV *psuvOther)
{
    int d = STRUCT_OFFSET(psuv, 0xb00, int) - STRUCT_OFFSET(psuvOther, 0xb00, int);
    if (d > 0)
        return 1;
    if (d < 0)
        return 0;
    d = STRUCT_OFFSET(STRUCT_OFFSET(psuv, 0xaf8, SUVFEAT *), 0xc, int) - STRUCT_OFFSET(STRUCT_OFFSET(psuvOther, 0xaf8, SUVFEAT *), 0xc, int);
    if (d > 0)
        return 1;
    if (d < 0)
        return 0;
    float dsRel = DsGetTrackRelative(STRUCT_OFFSET(psuv, 0x834, float), STRUCT_OFFSET(psuv, 0x83c, float), STRUCT_OFFSET(psuvOther, 0x83c, float));
    return dsRel > 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/P2/suv", UpdateSuvLine__FP3SUVPi);

INCLUDE_ASM("asm/nonmatchings/P2/suv", UpdateSuvHeading__FP3SUV);

/**
 * @todo 6 differing lines of 45: loop counter increment and sltiu get scheduled earlier than the target.
 */
INCLUDE_ASM("asm/nonmatchings/P2/suv", UpdateSuvWheels__FP3SUV);
#ifdef SKIP_ASM
extern SMP D_002754E8;
extern float D_002754F8;
extern float D_002754F4;

void UpdateSuvWheels(SUV *psuv)
{
    unsigned int i;
    float rad = atan2f(STRUCT_OFFSET(psuv, 0xd4, float), STRUCT_OFFSET(psuv, 0xd0, float));
    float radDiff = RadNormalize(STRUCT_OFFSET(psuv, 0x694, float) - rad);
    float lim = GLimitAbs(D_002754F8 * radDiff, D_002754F4);
    STRUCT_OFFSET(psuv, 0x69c, float) = RadSmooth(STRUCT_OFFSET(psuv, 0x69c, float), lim, g_clock.dt, &D_002754E8, 0);
    char *pw;
    for (i = 0, pw = &STRUCT_OFFSET(psuv, 0x6b0, char); i < 4;)
    {
        float d = (int)i < 2 ? STRUCT_OFFSET(psuv, 0x610, float) : STRUCT_OFFSET(psuv, 0x614, float);
        STRUCT_OFFSET(pw, 0x50, float) = STRUCT_OFFSET(psuv, 0x698, float) / d;
        i++;
        pw += 0x60;
    }
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/suv", UpdateSuvExpls__FP3SUV);

void BoostSuv(SUV *psuv)
{
    STRUCT_OFFSET(psuv, 0x854, float) = g_clock.t;
    STRUCT_OFFSET(psuv, 0x858, int)--;
    LO *palo = STRUCT_OFFSET(psuv, 0xb14, LO *);
    if (palo)
    {
        palo->pvtlo->pfnAddLo(palo);
    }
}

/**
 * @todo 24 differing lines of 96: bit test is folded to srav and andi 1, and loop constants are numbered differently.
 */
INCLUDE_ASM("asm/nonmatchings/P2/suv", FUN_001d9338__FP3SUV);
#ifdef SKIP_ASM
struct SUVLS // guess, view of LS fields at 0x70 and 0x74
{
    char pad[0x70];
    int c;
    unsigned char ab[16];
};

void FUN_001d9338(SUV *psuv)
{
    float x = ((STRUCT_OFFSET(psuv, 0xb00, int) - 1) * 3 + STRUCT_OFFSET(STRUCT_OFFSET(psuv, 0xaf8, SUVFEAT *), 0xc, int)) * 0.1f;
    float lo = 0.0f, hi = 1.0f;
    float xc;
    if (x < lo)
        xc = lo;
    else if (x > hi)
        xc = hi;
    else
        xc = x;
    int i = STRUCT_OFFSET(psuv, 0xb0c, int) - STRUCT_OFFSET(psuv, 0xb08, int);
    if (i < 3 || (((SUVLS *)g_plsCur)->ab[i / 8] & (1 << (i & 7))))
    {
        OnDifficultyPlayerDeath(xc, &g_difficulty);
    }
    for (; i >= 0; i--)
    {
        SUVLS *pls = (SUVLS *)g_plsCur;
        int m = 1 << (i & 7);
        if (!(pls->ab[i / 8] & m))
        {
            pls->ab[i / 8] |= m;
            pls->c++;
        }
    }
}
#endif

/**
 * @todo 67 differing lines of 140: target hoists the constants 1, -1, 0x42f, 0x430 into saved registers.
 */
INCLUDE_ASM("asm/nonmatchings/P2/suv", UpdateSuvVolumes__FP3SUVi);
#ifdef SKIP_ASM
void UpdateSuvVolumes(SUV *psuv, int fUnused)
{
    int i;
    SUVFEAT *pfeat;
    for (i = 0, pfeat = &STRUCT_OFFSET(psuv, 0x874, SUVFEAT); i < STRUCT_OFFSET(psuv, 0x870, int); i++, pfeat++)
    {
        int fIn = FCheckVolPoint(pfeat->pvol, &STRUCT_OFFSET(psuv, 0x100, VECTOR));
        if (fIn != pfeat->unk8)
        {
            int kind = pfeat->fActive;
            pfeat->unk8 = fIn;
            switch (kind)
            {
            case 0:
                if (fIn != 0 && pfeat->pfeatNext == STRUCT_OFFSET(psuv, 0xaf8, SUVFEAT *))
                {
                    STRUCT_OFFSET(psuv, 0xaf8, SUVFEAT *) = pfeat;
                    if (pfeat == STRUCT_OFFSET(psuv, 0xaf4, SUVFEAT *))
                    {
                        int n = STRUCT_OFFSET(psuv, 0xb00, int) + 1;
                        STRUCT_OFFSET(psuv, 0xb00, int) = n;
                        if (STRUCT_OFFSET(psuv, 0xb04, int) < n)
                        {
                            LO *plo = PloFindSwObject(STRUCT_OFFSET(psuv, 0x14, SW *), 4, (OID)0x42c, psuv);
                            SMA *psma = STRUCT_OFFSET(plo, 0x48, SMA *);
                            OID oid;
                            GetSmaGoal(psma, &oid);
                            if (oid == -1)
                            {
                                GetSmaCur(psma, &oid);
                            }
                            if (psuv == PpoCur())
                            {
                                STRUCT_OFFSET(psuv, 0xb00, int) = STRUCT_OFFSET(psuv, 0xb04, int);
                            }
                            switch (oid)
                            {
                            case 0x42f:
                                if (psuv == PpoCur())
                                {
                                    SetSmaGoal(psma, (OID)0x432);
                                    OnDifficultyCollectKey(&g_difficulty);
                                }
                                else
                                {
                                    SetSmaGoal(psma, (OID)0x430);
                                }
                                break;
                            case 0x430:
                                if (psuv == PpoCur())
                                {
                                    SetSmaGoal(psma, (OID)0x431);
                                    FUN_001d9338(psuv);
                                }
                                break;
                            }
                        }
                    }
                }
                break;
            case 1:
                if (fIn == 0)
                    STRUCT_OFFSET(psuv, 0xafc, SUVFEAT *) = 0;
                else
                    STRUCT_OFFSET(psuv, 0xafc, SUVFEAT *) = pfeat;
                break;
            }
        }
    }
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/suv", UpdateSuvSounds__FP3SUVf);

INCLUDE_ASM("asm/nonmatchings/P2/suv", UpdateSuvPuncher__FP3SUV);

void UpdateSuv(SUV *psuv, float dt)
{
    int fNoXps = 0;
    UpdatePo(psuv, dt);
    switch (STRUCT_OFFSET(psuv, 0xb34, int))
    {
    case 0:
        STRUCT_OFFSET(psuv, 0x698, float) = 0.0f;
        break;
    case 1:
        UpdateSuvBalance(psuv);
        UpdateSuvLine(psuv, &fNoXps);
        UpdateSuvHeading(psuv);
        break;
    case 2:
        break;
    }
    UpdateSuvSounds(psuv, dt);
    UpdateSuvWheels(psuv);
    UpdateSuvExpls(psuv);
    UpdateSuvVolumes(psuv, fNoXps);
    UpdateSuvPuncher(psuv);
    if (STRUCT_OFFSET(psuv, 0xf8, float) > 0.5f)
    {
        STRUCT_OFFSET(psuv, 0x850, float) = g_clock.t;
    }
    if (STRUCT_OFFSET(psuv, 0xb34, int) != 0)
    {
        ResolveAlo(psuv);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/suv", UpdateSuvActive__FP3SUVP3JOYf);

extern UNKBLOT g_unkblot2;
extern UNKBLOT g_unkblot3;
extern UNKBLOT g_unkblot4;
extern SUVRACE D_00272430;
extern SUVRACE D_002726B0;

void FUN_001da170(SUV *psuv)
{
    int f1 = 0;
    int f2 = 0;
    switch (STRUCT_OFFSET(psuv, 0xb30, int))
    {
    case 0:
    {
        LO *plo = PloFindSwObject(STRUCT_OFFSET(psuv, 0x14, SW *), 5, (OID)0x42c, 0);
        if (plo)
        {
            SMA *psma = STRUCT_OFFSET(plo, 0x48, SMA *);
            OID oid;
            GetSmaGoal(psma, &oid);
            int n = oid;
            if (n == -1)
            {
                GetSmaCur(psma, &oid);
                n = oid;
            }
            if (n < 0x431)
            {
                if (n >= 0x42f)
                {
                    f1 = (int)FUN_001e9970();
                }
            }
        }
        break;
    }
    case 1:
        f2 = (int)FUN_001e9970();
        break;
    }
    if (f1)
    {
        VCALL(&g_unkblot3, 0x38);
        VCALL(&g_unkblot2, 0x38);
        VCALL(&g_unkblot4, 0x38);
    }
    else
    {
        VCALL(&g_unkblot3, 0x3c);
        VCALL(&g_unkblot2, 0x3c);
        VCALL(&g_unkblot4, 0x3c);
    }
    if (f2)
    {
        VCALL(&D_00272430, 0x38);
        VCALL(&D_002726B0, 0x38);
    }
    else
    {
        VCALL(&D_00272430, 0x3c);
        VCALL(&D_002726B0, 0x3c);
    }
}

void UpdateSuvInternalXps(SUV *psuv)
{
    STRUCT_OFFSET(psuv, 0x6a0, int)++;
}

INCLUDE_ASM("asm/nonmatchings/P2/suv", AddSuvCustomXps__FP3SUVP2SOiP3BSPT3PP2XP);

INCLUDE_ASM("asm/nonmatchings/P2/suv", AdjustSuvNewXp__FP3SUVP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/suv", UpdateSuvInfluences__FP3SUVP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/suv", RenderSuvSelf__FP3SUVP2CMP2RO);

void UpdateSuvBounds(SUV *psuv)
{
    unsigned int i;
    UpdateSoBounds(psuv);
    for (i = 0; i < 4; i++)
    {
        void *pv = STRUCT_OFFSET(psuv, 0x6b0 + i * 0x60, void *);
        if (pv)
        {
            VECTOR pos;
            STRUCT_OFFSET(&pos, 0, qword) = STRUCT_OFFSET(pv, 0x190, qword);
            ConvertAloPos(psuv, 0, &pos, &pos);
            ExtendSoBounds(psuv, &pos, (int)i < 2 ? STRUCT_OFFSET(psuv, 0x610, float) : STRUCT_OFFSET(psuv, 0x614, float));
        }
    }
}

void CollectSuvPrize(SUV *psuv, PCK pck, ALO *palo)
{
    void *pstepguard = STRUCT_OFFSET(psuv, 0xb78, void *);
    if (pstepguard)
    {
        SetStepguardPatrolAnimation((STEPGUARD *)pstepguard, 0);
        pstepguard = STRUCT_OFFSET(psuv, 0xb78, void *);
        (*(void (**)(void *, PCK, ALO *))(*(int *)pstepguard + 0x148))(pstepguard, pck, palo);
    }
    else
    {
        CollectPoPrize(psuv, pck, palo);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/suv", UpdateSuvShapes__FP3SUV);

void UpdateSuvXfWorld(SUV *psuv)
{
    UpdateSoXfWorld(psuv);
    UpdateSuvShapes(psuv);
}

void GetSuvCpdefi(SUV *psuv, float dt, CPDEFI *pcpdefi)
{
    GetSoCpdefi(psuv, dt, pcpdefi);
}

extern UNKBLOT g_unkblot2;
extern UNKBLOT g_unkblot3;
extern UNKBLOT g_unkblot4;

void OnSuvActive(SUV *psuv, int fActive, PO *ppoOther)
{
    OnPoActive(psuv, fActive, ppoOther);
    if (fActive)
    {
        g_unkblot3.pv0 = &STRUCT_OFFSET(psuv, 0x858, char);
        g_unkblot2.pv0 = &STRUCT_OFFSET(psuv, 0xb00, char);
        g_unkblot2.pv1 = &STRUCT_OFFSET(psuv, 0xb04, char);
        g_unkblot4.pv0 = &STRUCT_OFFSET(psuv, 0xb08, char);
        g_unkblot4.pv1 = &STRUCT_OFFSET(psuv, 0xb0c, char);
        FUN_001ddc38(STRUCT_OFFSET(psuv, 0x14, SW *), psuv);
    }
    else if (STRUCT_OFFSET(psuv, 0xb34, SUVS) == 2)
    {
        SetSuvSuvs(psuv, (SUVS)0);
    }
}

extern SUVRACE D_00272430;
extern SUVRACE D_002726B0;
extern int D_002751D4;

void HandleSuvMessage(SUV *psuv, MSGID msgid, void *pv)
{
    HandlePoMessage(psuv, msgid, pv);
    if (msgid == MSGID_break_break)
    {
        if (STRUCT_OFFSET(pv, 8, int) == 0x426)
        {
            SUVRACE *psr0 = &D_00272430;
            int c = D_002751D4;
            if (psr0->c < c)
            {
                SUVRACE *psr1 = &D_002726B0;
                if (psr1->c < c)
                {
                    if (STRUCT_OFFSET(STRUCT_OFFSET(pv, 0x6cc, void *), 0x50, SUV *) == psuv)
                        psr0->c++;
                    else
                        psr1->c++;
                }
            }
        }
    }
}

void SetSuvTrack(SUV *psuv, SHAPE *pshape)
{
    VECTOR pos;
    int i;
    STRUCT_OFFSET(psuv, 0x830, SHAPE *) = pshape;
    CRV *pcrv = pshape->pcrv;
    if (pcrv->pvtcrv->pfnFindCrvClosestPointAll)
    {
        pcrv->pvtcrv->pfnFindCrvClosestPointAll(pcrv, &STRUCT_OFFSET(psuv, 0x100, VECTOR), 0, 0, 0, &STRUCT_OFFSET(psuv, 0x838, float), 0);
    }
    UpdateSuvShapes(psuv);
    STRUCT_OFFSET(psuv, 0x844, float) = STRUCT_OFFSET(psuv, 0x840, float);
    pcrv = STRUCT_OFFSET(psuv, 0x830, SHAPE *)->pcrv;
    STRUCT_OFFSET(psuv, 0x834, float) = pcrv->pvtcrv->pfnSMaxCrv(pcrv);
    for (i = 0; i < STRUCT_OFFSET(psuv, 0x870, int); i++)
    {
        SUVFEAT *pfeat = &(&STRUCT_OFFSET(psuv, 0x874, SUVFEAT))[i];
        if (pfeat->fActive == 0)
        {
            GetXfmPos(pfeat->pvol, &pos);
            pcrv = STRUCT_OFFSET(psuv, 0x830, SHAPE *)->pcrv;
            if (pcrv->pvtcrv->pfnFindCrvClosestPointAll)
            {
                pcrv->pvtcrv->pfnFindCrvClosestPointAll(pcrv, &pos, 0, 0, 0, 0, &pfeat->s);
            }
        }
    }
}

void SetSuvLine(SUV *psuv, SHAPE *pshape)
{
    VECTOR pos;
    STRUCT_OFFSET(psuv, 0x848, SHAPE *) = pshape;
    CRV *pcrv = pshape->pcrv;
    if (pcrv->pvtcrv->pfnFindCrvClosestPointAll)
    {
        pcrv->pvtcrv->pfnFindCrvClosestPointAll(pcrv, &STRUCT_OFFSET(psuv, 0x100, VECTOR), 0, &pos, 0, &STRUCT_OFFSET(psuv, 0x84c, float), 0);
    }
}

void AddSuvCheckPoint(SUV *psuv, VOL *pvol)
{
    if (pvol)
    {
        unsigned int n = STRUCT_OFFSET(psuv, 0x870, unsigned int);
        if (n < 16)
        {
            VECTOR pos;
            SUVFEAT *pfeat = &STRUCT_OFFSET(psuv, 0x874, SUVFEAT) + n;
            STRUCT_OFFSET(psuv, 0x870, unsigned int) = n + 1;
            pfeat->pvol = pvol;
            pfeat->fActive = 0;
            if (STRUCT_OFFSET(psuv, 0xaf4, SUVFEAT *) == 0)
            {
                STRUCT_OFFSET(psuv, 0xaf8, SUVFEAT *) = pfeat;
                STRUCT_OFFSET(psuv, 0xaf4, SUVFEAT *) = pfeat;
                pfeat->pfeatNext = pfeat;
            }
            else
            {
                pfeat->pfeatNext = STRUCT_OFFSET(psuv, 0xaf4, SUVFEAT *)->pfeatNext;
                STRUCT_OFFSET(psuv, 0xaf4, SUVFEAT *)->pfeatNext = pfeat;
                pfeat->iOrder = pfeat->pfeatNext->iOrder + 1;
            }
            if (STRUCT_OFFSET(psuv, 0x830, SHAPE *))
            {
                GetXfmPos(pvol, &pos);
                CRV *pcrv = STRUCT_OFFSET(psuv, 0x830, SHAPE *)->pcrv;
                if (pcrv->pvtcrv->pfnFindCrvClosestPointAll)
                {
                    pcrv->pvtcrv->pfnFindCrvClosestPointAll(pcrv, &pos, 0, 0, 0, 0, &pfeat->s);
                }
            }
        }
    }
}

/**
 * @todo 2 differing lines of 26: store order of the last field (pexpl) is wrong; all 720 statement orders tried.
 */
INCLUDE_ASM("asm/nonmatchings/P2/suv", AddSuvFeature__FP3SUVP3VOLffP4EXPLT4);
#ifdef SKIP_ASM
void AddSuvFeature(SUV *psuv, VOL *pvol, float a, float b, EXPL *pexpl, EXPL *pexpl2)
{
    if (pvol)
    {
        unsigned int n = STRUCT_OFFSET(psuv, 0x870, unsigned int);
        if (n < 16)
        {
            SUVFEAT *pfeat = &STRUCT_OFFSET(psuv, 0x874, SUVFEAT)+ n;
            STRUCT_OFFSET(psuv, 0x870, unsigned int) = n + 1;
            pfeat->pexpl2 = pexpl2;
            pfeat->pvol = pvol;
            pfeat->b = b;
            pfeat->fActive = 1;
            pfeat->a = a;
            pfeat->pexpl = pexpl;
        }
    }
}
#endif

void SetSuvSuvs(SUV *psuv, SUVS suvs)
{
    if (suvs != STRUCT_OFFSET(psuv, 0xb34, SUVS))
    {
        STRUCT_OFFSET(psuv, 0xb34, SUVS) = suvs;
        STRUCT_OFFSET(psuv, 0xb38, float) = g_clock.t;
        if (suvs == 2)
        {
            if (psuv != PpoCur())
            {
                SwitchToPo(psuv);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/suv", ResetSuv__FP3SUV);

JUNK_ADDIU(10);
JUNK_WORD(0x7C450000);
JUNK_WORD(0x48220800);

INCLUDE_ASM("asm/nonmatchings/P2/suv", VecCombo__FG8VU_FLOATG9VU_VECTORT0T1);
