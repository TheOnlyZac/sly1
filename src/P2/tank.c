#include <tank.h>

INCLUDE_ASM(const s32, "P2/tank", InitTank__FP4TANK);

INCLUDE_ASM(const s32, "P2/tank", PostTankLoad__FP4TANK);

INCLUDE_ASM(const s32, "P2/tank", UpdateTank__FP4TANKf);

INCLUDE_ASM(const s32, "P2/tank", FUN_001deb30);

void UseTankCharm(TANK *ptank)
{
    UsePoCharm(ptank);
    SetTankTanks(ptank, TANKS_Active);
}

INCLUDE_ASM(const s32, "P2/tank", UpdateTankActive__FP4TANKP3JOYf);

INCLUDE_ASM(const s32, "P2/tank", OnTankActive__FP4TANKiP2PO);

INCLUDE_ASM(const s32, "P2/tank", RenderTankAll__FP4TANKP2CMP2RO);

INCLUDE_ASM(const s32, "P2/tank", ImpactTank__FP4TANKi);

INCLUDE_ASM(const s32, "P2/tank", FInvulnerableTank__FP4TANK3ZPK);

INCLUDE_ASM(const s32, "P2/tank", ApplyTankThrow__FP4TANKP2PO);

INCLUDE_ASM(const s32, "P2/tank", FTakeTankDamage__FP4TANKP3ZPR);

INCLUDE_ASM(const s32, "P2/tank", FUN_001dfa10);

INCLUDE_ASM(const s32, "P2/tank", AdjustTankNewXp__FP4TANKP2XPi);

INCLUDE_ASM(const s32, "P2/tank", HandleTankMessage__FP4TANK5MSGIDPv);

INCLUDE_ASM(const s32, "P2/tank", JthsCurrentTank__FP4TANK);

INCLUDE_ASM(const s32, "P2/tank", SetTankTanks__FP4TANK5TANKS);
