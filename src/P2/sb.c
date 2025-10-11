#include <sb.h>

INCLUDE_ASM("asm/nonmatchings/P2/sb", PostSbgLoad__FP3SBG);

INCLUDE_ASM("asm/nonmatchings/P2/sb", FUN_001a9928__FP3SBG);

INCLUDE_ASM("asm/nonmatchings/P2/sb", UpdateSbgGoal__FP3SBGi);

void UpdateSbgSgs(SBG *psbg)
{
    UpdateStepguardSgs(psbg);

    // TODO: This might be an enum?
    if (STRUCT_OFFSET(psbg, 0x724, int) == 0x10)
    {
        LookStepguardAtGoal(psbg);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sb", OnSbgEnteringSgs__FP3SBG3SGSP4ASEG);

INCLUDE_ASM("asm/nonmatchings/P2/sb", UpdateSbg__FP3SBGf);

INCLUDE_ASM("asm/nonmatchings/P2/sb", FUN_001a9a98);

INCLUDE_ASM("asm/nonmatchings/P2/sb", FAbsorbSbgWkr__FP3SBGP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/sb", FUN_001a9c58);
