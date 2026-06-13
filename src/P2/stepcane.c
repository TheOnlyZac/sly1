#include <stepcane.h>
#include <math.h>
#include <rchm.h>

INCLUDE_ASM("asm/nonmatchings/P2/stepcane", SetJtJtcs__FP2JT4JTCS);

INCLUDE_ASM("asm/nonmatchings/P2/stepcane", UpdateJtCane__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/stepcane", UpdateJtActiveCane__FP2JTP3JOY);

INCLUDE_ASM("asm/nonmatchings/P2/stepcane", ChooseJtAttackTarget__FP2JTiP6VECTORffPP6TARGETT2);

INCLUDE_ASM("asm/nonmatchings/P2/stepcane", ChooseJtSweepTarget__FP2JTP2BLP6ASEGBL);

void ChooseJtRushTarget(JT *pjt)
{
    extern VECTOR D_00274BF0;
    VECTOR dposProj;
    TARGET *ptarget;

    ChooseJtAttackTarget(pjt, 8, &D_00274BF0, 0.25f, 1.0f, &ptarget, &dposProj);
    STRUCT_OFFSET(pjt, 0x2204, int) = 0;
    STRUCT_OFFSET(pjt, 0x2200, TARGET *) = ptarget;
    STRUCT_OFFSET(pjt, 0x2208, int) = 0;
    if (ptarget != NULL)
    {
        STRUCT_OFFSET(pjt, 0x638, float) = atan2f(dposProj.y, dposProj.x);
        FixStepAngularVelocity((STEP *)pjt);
    }
}

void ChooseJtSmashTarget(JT *pjt)
{
    extern VECTOR D_00274C00;
    VECTOR dposProj;
    TARGET *ptarget;

    ChooseJtAttackTarget(pjt, 4, &D_00274C00, 0.25f, 3.15f, &ptarget, &dposProj);
    STRUCT_OFFSET(pjt, 0x2204, int) = 0;
    STRUCT_OFFSET(pjt, 0x2200, TARGET *) = ptarget;
    STRUCT_OFFSET(pjt, 0x2208, int) = 0;
    if (ptarget != NULL)
    {
        STRUCT_OFFSET(pjt, 0x638, float) = atan2f(dposProj.y, dposProj.x);
        FixStepAngularVelocity((STEP *)pjt);
    }
}
