#include <suv.h>
#include <clock.h>

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

INCLUDE_ASM("asm/nonmatchings/P2/suv", GExcludeAlm__FiP2LMf);
#ifdef SKIP_ASM
extern float D_0024DC94;

float GExcludeAlm(int clm, LM *alm, float g)
{
    float gBest;
    float dgBest;
    if (!FCheckAlm(clm, alm, g))
    {
        return g;
    }
    dgBest = D_0024DC94;
    gBest = dgBest;
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

INCLUDE_ASM("asm/nonmatchings/P2/suv", UpdateSuvBalance__FP3SUV);

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

INCLUDE_ASM("asm/nonmatchings/P2/suv", FUN_001d9338);

INCLUDE_ASM("asm/nonmatchings/P2/suv", UpdateSuvVolumes__FP3SUVi);

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

INCLUDE_ASM("asm/nonmatchings/P2/suv", FUN_001da170);

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

struct UNKBLOT // guess, only the pointers at 0x264 and 0x268 are known
{
    char pad[0x264];
    void *pv0;
    void *pv1;
};
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

struct SUVRACE // guess, only the counter at 0x27c is known
{
    char pad[0x27c];
    int c;
};
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
