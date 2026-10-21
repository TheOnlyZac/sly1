#include <missile.h>
#include <asega.h>

// .data
static SNIP s_asnipMissile[1] =
{
    {2, OID_aseg_missile_fire, 0x6b0}
};

float DT_MissilePredictMax = 0.5f;

void InitMissile(MISSILE *pmissile)
{
    InitBomb(pmissile);
    STRUCT_OFFSET(pmissile, 0x6b8, int) = 1; // pmissile->fFollowTrajectory
}

void LoadMissileFromBrx(MISSILE *pmissile, CBinaryInputStream *pbis)
{
    LoadBombFromBrx(pmissile, pbis);
    SnipAloObjects(pmissile, 1, s_asnipMissile);
    STRUCT_OFFSET(pmissile, 0x2c8, ulong) &= 0xfffffcffffffffff;
    STRUCT_OFFSET(pmissile, 0x2c8, ulong) |= 0x10000000000;
}

void OnMissileRemove(MISSILE *pmissile)
{
    OnSoRemove(pmissile);
    if (STRUCT_OFFSET(pmissile, 0x6b4, ASEGA *)) // pmissile->pasegaCur
    {
        RetractAsega(STRUCT_OFFSET(pmissile, 0x6b4, ASEGA *));
        STRUCT_OFFSET(pmissile, 0x6b4, ASEGA *) = NULL; // pmissile->pasegaCur
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/missile", ProjectMissileTransform__FP7MISSILEfi);

INCLUDE_ASM("asm/nonmatchings/P2/missile", FireMissile__FP7MISSILEP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/missile", RenderMissileAll__FP7MISSILEP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/missile", FUN_0018dc88);

INCLUDE_ASM("asm/nonmatchings/P2/missile", FUN_0018dd50);

INCLUDE_ASM("asm/nonmatchings/P2/missile", FUN_0018dd78);

INCLUDE_ASM("asm/nonmatchings/P2/missile", InitAccmiss__FP7ACCMISS);

INCLUDE_ASM("asm/nonmatchings/P2/missile", FireAccmiss__FP7ACCMISSP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/missile", PresetAccmissAccel__FP7ACCMISSf);

INCLUDE_ASM("asm/nonmatchings/P2/missile", FireSplmiss__FP7SPLMISSP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/missile", ProjectSplmissTransform__FP7SPLMISSfi);
