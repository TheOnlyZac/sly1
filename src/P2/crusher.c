#include <crusher.h>
#include <sm.h>
#include <oid.h>
#include <po.h>

/**
 * @todo Rename.
 */
extern int DAT_0027c008;

void OnCrfodAdd(CRFOD *pcrfod)
{
    OnStepguardAdd(pcrfod);
    AppendDlEntry(&pcrfod->psw->dlCrfod, pcrfod);
}

void OnCrfodRemove(CRFOD *pcrfod)
{
    OnStepguardRemove(pcrfod);
    RemoveDlEntry(&pcrfod->psw->dlCrfod, pcrfod);
}

void CloneCrfod(CRFOD *pcrfod, CRFOD *pcrfodBase)
{
    DLE dleCrfod = STRUCT_OFFSET(pcrfod, 0xc10, DLE);
    CloneStepguard(pcrfod, pcrfodBase);
    STRUCT_OFFSET(pcrfod, 0xc10, DLE) = dleCrfod;
}

void InitCrfodb(CRFODB *pcrfodb)
{
    InitStepguard(pcrfodb);
    STRUCT_OFFSET(pcrfodb, 0xc24, int) = 1;
    DAT_0027c008 = 0;
}

void PostCrfodbLoad(CRFODB *pcrfodb)
{
    PostStepguardLoad(pcrfodb);
    STRUCT_OFFSET(pcrfodb, 0xc2c, int) = DAT_0027c008++;
}

void CalcHeadingVector(float rad, VECTOR *pvector)
{
    CalculateSinCos(rad, &pvector->y, (float *)pvector);
    pvector->z = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/P2/crusher", UpdateCrfodbGoal__FP6CRFODBi);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FDetectCrfodb__FP6CRFODB);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FAbsorbCrfodbWkr__FP6CRFODBP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014bd38);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", SgsNextCrfodkAI__FP6CRFODK);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FDetectCrfodk__FP6CRFODK);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FAbsorbCrfodkWkr__FP6CRFODKP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014bf88);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", InitCrbrain__FP7CRBRAIN);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", post_load_crbrain);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014c2f0);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014c5e8);

extern void *D_0027C00C;
void FUN_0014c668(void *pv, int tnt)
{
    if (tnt == 1)
    {
        OID oidGoal;
        OID oidCur;

        GetSmaGoal(STRUCT_OFFSET(D_0027C00C, 0x42c, SMA *), &oidGoal);
        GetSmaCur(STRUCT_OFFSET(D_0027C00C, 0x42c, SMA *), &oidCur);

        if (oidGoal != (OID)0x3fe && oidCur != (OID)0x3fe)
        {
            SetSmaGoal(STRUCT_OFFSET(D_0027C00C, 0x42c, SMA *), (OID)0x3ff);
            FUN_0014c5e8(D_0027C00C);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/crusher", update_crbrain);
#ifdef SKIP_ASM
extern "C" void update_crbrain(CRBRAIN *p, float dt)
{
    OID oid;

    UpdateAlo(p, dt);
    GetSmaCur(STRUCT_OFFSET(p, 0x42c, SMA *), &oid);

    if (oid == (OID)0x3fd)
    {
        CLOCK *pclock = &g_clock;

        if (STRUCT_OFFSET(p, 0x45c, float) < pclock->t)
            FUN_0014c858(p);

        if (STRUCT_OFFSET(p, 0x460, float) < pclock->t)
            FUN_0014cba8(p);

        PO *ppo = PpoCur();
        void *pvt = STRUCT_OFFSET(ppo, 0x0, void *);
        void (*pfn)(PO *) = (void (*)(PO *))STRUCT_OFFSET(pvt, 0x144, void *);
        pfn(ppo);
    }
}
#endif // SKIP_ASM

extern int FUN_001e9970();
extern BLOT g_unkblot1;
extern BLOT g_unkblot9;

void FUN_0014c788(void *pv)
{
    OID oid;
    int fShow;

    GetSmaCur(STRUCT_OFFSET(pv, 0x42c, SMA *), &oid);

    fShow = 0;
    if (oid == (OID)0x3fd)
    {
        fShow = FUN_001e9970();
    }

    if (fShow)
    {
        g_unkblot1.pvtblot->pfnShowBlot(&g_unkblot1);
        g_unkblot9.pvtblot->pfnShowBlot(&g_unkblot9);
    }
    else
    {
        g_unkblot1.pvtblot->pfnHideBlot(&g_unkblot1);
        g_unkblot9.pvtblot->pfnHideBlot(&g_unkblot9);
    }
}

void *FUN_0014c820(void *p)
{
    int idx = STRUCT_OFFSET(p, 0x690, int);
    return (uint8_t *)p + (idx * 0xB0 + 0x480);
}

void FUN_0014c838(void *p, int value)
{
    int n = STRUCT_OFFSET(p, 0x2dc, int);
    STRUCT_OFFSET(p, 0x2dc, int) = n + 1;
    STRUCT_OFFSET((uint8_t *)p + n * 0x14, 0x2e0, int) = value;
}

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014c858);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014cba8);

void FUN_0014cd70(void *p)
{
    int n;

    if (STRUCT_OFFSET(p, 0x458, int) == STRUCT_OFFSET(p, 0x450, int))
    {
        float g = GRandInRange(STRUCT_OFFSET(p, 0x43c, float), STRUCT_OFFSET(p, 0x440, float));
        STRUCT_OFFSET(p, 0x45c, float) = g_clock.t + g;
    }

    n = STRUCT_OFFSET(p, 0x458, int);
    STRUCT_OFFSET(p, 0x458, int) = n - 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014cdc8);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", handle_crbrain_message);
