#include <mb.h>

extern SNIP s_asnipLoadMbg[2];

void InitMbg(MBG *pmbg)
{
    InitStepguard(pmbg);
    STRUCT_OFFSET(pmbg, 0xe3c, int) = -1;
}

void LoadMbgFromBrx(MBG *pmbg, CBinaryInputStream *pbis)
{
    LoadStepguardFromBrx(pmbg, pbis);
    SnipAloObjects(pmbg, 2, s_asnipLoadMbg);
}

INCLUDE_ASM("asm/nonmatchings/P2/mb", PostMbgLoad__FP3MBG);

INCLUDE_ASM("asm/nonmatchings/P2/mb", FUN_0018a510);

INCLUDE_ASM("asm/nonmatchings/P2/mb", FUN_0018a628);

INCLUDE_ASM("asm/nonmatchings/P2/mb", PsoHitTestCylinderObjects__FiP6VECTORT1fiPP2SOP3LSG);

INCLUDE_ASM("asm/nonmatchings/P2/mb", FFilterMbgAttackObjects__FP3MBGP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/mb", FObstructedMbg__FP3MBGP6VECTORT1);

INCLUDE_ASM("asm/nonmatchings/P2/mb", FCanMbgAttack__FP3MBG);

INCLUDE_ASM("asm/nonmatchings/P2/mb", FDetectMbg__FP3MBG);

INCLUDE_ASM("asm/nonmatchings/P2/mb", FUN_0018ab88__Fi);

INCLUDE_ASM("asm/nonmatchings/P2/mb", FUN_0018abf0__Fi);

INCLUDE_ASM("asm/nonmatchings/P2/mb", FUN_0018ac58__Fi);

void UpdateMbg(MBG *pmbg, float dt)
{
    UpdateStepguard(pmbg, dt);
}

INCLUDE_ASM("asm/nonmatchings/P2/mb", FUN_0018acf0);

INCLUDE_ASM("asm/nonmatchings/P2/mb", UpdateMbgGoal__FP3MBGi);

INCLUDE_ASM("asm/nonmatchings/P2/mb", UpdateMbgSgs__FP3MBG);

INCLUDE_ASM("asm/nonmatchings/P2/mb", OnMgExitingSgs__FP3MBG3SGS);

INCLUDE_ASM("asm/nonmatchings/P2/mb", HandleMbgMessage__FP3MBG5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/mb", FUN_0018b460);
