#include <mb.h>
#include <stepguard.h>
#include <memory.h>
#include <memcard.h>
#include <game.h>
#include <screen.h>

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

SGS FUN_0018abf0(int param)
{
    STEPGUARD *pstepguard = (STEPGUARD *)param;
    OID oid;

    if (STRUCT_OFFSET(pstepguard, 0x724, int) == 4)
    {
        GetSmaCur((SMA *)STRUCT_OFFSET(pstepguard, 0xE10, int), &oid);
        if (oid == (OID)0x438)
        {
            if (SggsGetStepguard(pstepguard) == 0)
            {
                return (SGS)2;
            }
        }
    }

    return SgsNextStepguardAI(pstepguard);
}

INCLUDE_ASM("asm/nonmatchings/P2/mb", FUN_0018ac58__Fi);

void UpdateMbg(MBG *pmbg, float dt)
{
    UpdateStepguard(pmbg, dt);
}

INCLUDE_ASM("asm/nonmatchings/P2/mb", FUN_0018acf0);

INCLUDE_ASM("asm/nonmatchings/P2/mb", UpdateMbgGoal__FP3MBGi);

INCLUDE_ASM("asm/nonmatchings/P2/mb", UpdateMbgSgs__FP3MBG);

void OnMgExitingSgs(MBG *pmbg, SGS sgs)
{
    OnStepguardExitingSgs(pmbg, sgs);
    
    int field_0x724 = STRUCT_OFFSET(pmbg, 0x724, int);
    if (field_0x724 == 0x10)
    {
        int field_0xE3C = STRUCT_OFFSET(pmbg, 0xE3C, int);
        if (field_0xE3C != -1)
        {
            int field_0xE10 = STRUCT_OFFSET(pmbg, 0xE10, int);
            SetSmaGoal((SMA *)field_0xE10, (OID)field_0xE3C);
            STRUCT_OFFSET(pmbg, 0xE3C, int) = -1;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/mb", HandleMbgMessage__FP3MBG5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/mb", FUN_0018b460);
