#include <missile.h>
#include <asega.h>

void InitMissile(MISSILE *pmissile)
{
    InitBomb(pmissile);
    STRUCT_OFFSET(pmissile, 0x6b8, int) = 1; // pmissile->fFollowTrajectory
}

INCLUDE_ASM("asm/nonmatchings/P2/missile", LoadMissileFromBrx__FP7MISSILEP18CBinaryInputStream);

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

extern "C" void FUN_0018dd50(void * p, int val)
{
    int c = STRUCT_OFFSET(p, 0x6bc, int);
    if ((unsigned int)c < 4)
    {
        int *a = &STRUCT_OFFSET(p, 0x6c0, int);
        a[c] = val;
        STRUCT_OFFSET(p, 0x6bc, int) = c + 1;
    }
}

extern "C" void FUN_0018dd78(void * p, int val)
{
    int c = STRUCT_OFFSET(p, 0x6d0, int);
    if ((unsigned int)c < 4)
    {
        int *a = &STRUCT_OFFSET(p, 0x6d4, int);
        a[c] = val;
        STRUCT_OFFSET(p, 0x6d0, int) = c + 1;
    }
}

extern qword D_00248D30;

void InitAccmiss(ACCMISS *paccmiss)
{
    InitMissile(paccmiss);
    *(qword *)((char *)paccmiss + 0x350) = D_00248D30;
}

INCLUDE_ASM("asm/nonmatchings/P2/missile", FireAccmiss__FP7ACCMISSP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/missile", PresetAccmissAccel__FP7ACCMISSf);

INCLUDE_ASM("asm/nonmatchings/P2/missile", FireSplmiss__FP7SPLMISSP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/missile", ProjectSplmissTransform__FP7SPLMISSfi);
