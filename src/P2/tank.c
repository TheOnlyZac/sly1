#include <tank.h>
#include <po.h>
#include <mat.h>
#include <math.h>

extern qword D_00275740;

void InitTank(TANK *ptank)
{
    InitStep((STEP *)ptank);

    float rad = atan2f(STRUCT_OFFSET(ptank, 0xD4, float), STRUCT_OFFSET(ptank, 0xD0, float));
    STRUCT_OFFSET(ptank, 0x638, float) = rad;
    LoadRotateMatrixRad(rad, &g_normalZ, (MATRIX3 *)((uint8_t *)ptank + 0x660));

    STRUCT_OFFSET(ptank, 0x720, int) = -1;
    STRUCT_OFFSET(ptank, 0x72C, float) = -10.0f;
    STRUCT_OFFSET(ptank, 0x6F0, qword) = D_00275740;
}

INCLUDE_ASM("asm/nonmatchings/P2/tank", PostTankLoad__FP4TANK);

INCLUDE_ASM("asm/nonmatchings/P2/tank", UpdateTank__FP4TANKf);

static inline VU_VECTOR VuVectorXyz(float x, float y, float z)
{
    VU_VECTOR v;
    qword tmp;
    asm("mfc1 %0, %2\n\tmfc1 %1, %3\n\tpextlw %0, %1, %0\n\tmfc1 %1, %4\n\tpcpyld %0, %1, %0"
        : "=r"(v.data), "=r"(tmp)
        : "f"(x), "f"(y), "f"(z));
    return v;
}

void FUN_001deb30(TANK *ptank)
{
    union
    {
        qword q;
        float af[4];
    } u;
    float radPanTarget;
    float radTiltTarget;
    float svTarget;

    CalculateAloDrive((ALO *)ptank, NULL, NULL, g_clock.dt,
                      STRUCT_OFFSET(ptank, 0x638, float),
                      &radPanTarget, &radTiltTarget, &svTarget);

    STRUCT_OFFSET(ptank, 0x638, float) = radPanTarget;
    LoadRotateMatrixPanTilt(radPanTarget, radTiltTarget,
                            (MATRIX3 *)((uint8_t *)ptank + 0x660));

    u.q = VuVectorXyz(-svTarget, 0.0f, 0.0f).data;
    STRUCT_OFFSET(ptank, 0x640, qword) = u.q;
}

void UseTankCharm(TANK *ptank)
{
    UsePoCharm(ptank);
    SetTankTanks(ptank, TANKS_Active);
}

INCLUDE_ASM("asm/nonmatchings/P2/tank", UpdateTankActive__FP4TANKP3JOYf);

void OnTankActive(TANK *ptank, int fActive, PO *ppoOther)
{
    OnPoActive(ptank, fActive, ppoOther);
    if (!fActive)
    {
        STRUCT_OFFSET(ptank, 0x728, int) = 0; // ptank->fFlash
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/tank", RenderTankAll__FP4TANKP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/tank", ImpactTank__FP4TANKi);

INCLUDE_ASM("asm/nonmatchings/P2/tank", FInvulnerableTank__FP4TANK3ZPK);

INCLUDE_ASM("asm/nonmatchings/P2/tank", ApplyTankThrow__FP4TANKP2PO);

INCLUDE_ASM("asm/nonmatchings/P2/tank", FTakeTankDamage__FP4TANKP3ZPR);

INCLUDE_ASM("asm/nonmatchings/P2/tank", FUN_001dfa10);

INCLUDE_ASM("asm/nonmatchings/P2/tank", AdjustTankNewXp__FP4TANKP2XPi);

#ifndef SKIP_ASM
INCLUDE_ASM("asm/nonmatchings/P2/tank", HandleTankMessage__FP4TANK5MSGIDPv);
#else
void HandleTankMessage(TANK *ptank, MSGID msgid, void *pv)
{
    OID oidCur;
    OID oidGoal;

    switch (msgid)
    {
    case (MSGID)0x14:
        if (pv == STRUCT_OFFSET(ptank, 0x75C, void *))
        {
            GetSmaCur((SMA *)pv, &oidCur);
            GetSmaGoal(STRUCT_OFFSET(ptank, 0x75C, SMA *), &oidGoal);
        }
        break;

    case (MSGID)0x13:
    {
        SMA *psma = STRUCT_OFFSET(ptank, 0x75C, SMA *);
        if (psma != NULL)
        {
            if (STRUCT_OFFSET(pv, 0x0, ASEGA *) == psma->pasegaCur)
            {
                int label = STRUCT_OFFSET(pv, 0x8, int);
                if (label != 0x15E)
                {
                    if (label == 0x15F)
                    {
                        STRUCT_OFFSET(ptank, 0x738, int) = 0;
                    }
                }
                else
                {
                    STRUCT_OFFSET(ptank, 0x738, int) = 1;
                }
            }
        }
        break;
    }
    }

    HandlePoMessage(ptank, msgid, pv);
}
#endif

JTHS JthsCurrentTank(TANK *ptank)
{
    return (JTHS)(STRUCT_OFFSET(ptank, 0x728, int) != 0); // ptank->fFlash
}

INCLUDE_ASM("asm/nonmatchings/P2/tank", SetTankTanks__FP4TANK5TANKS);
