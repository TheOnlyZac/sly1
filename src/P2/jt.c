#include <jt.h>
#include <alo.h>
#include <po.h>
#include <steppower.h>
#include <game.h>

INCLUDE_ASM("asm/nonmatchings/P2/jt", InitJt__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", LoadJtFromBrx__FP2JTP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/jt", PostJtLoad__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", PresetJtAccelBase);

INCLUDE_ASM("asm/nonmatchings/P2/jt", PresetJtAccel__FP2JTf);

INCLUDE_ASM("asm/nonmatchings/P2/jt", AdjustJtNewXp__FP2JTP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/jt", AdjustJtDz__FP2JTiP2DZif);

INCLUDE_ASM("asm/nonmatchings/P2/jt", HandleJtGrfjtsc);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtInternalXps__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", FCheckJtXpBase__FP2JTP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/jt", AdjustJtXpVelocity__FP2JTP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/jt", HandleJtMessage__FP2JT5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/jt", FTurnJtToTarget__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtBalance__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", RebuildJtXmg__FP2JTP3ALOfT1P6ACTADJP3XMG);

INCLUDE_ASM("asm/nonmatchings/P2/jt", FMatchJtXmg__FP2JTP3XMGP6ACTADJ);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtStand__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", ThrowJt__FP2JTP6VECTORff);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UnhookJt__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", CalculateJtToolSpin__FP2JTfP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/jt", RenderJtAll__FP2JTP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/jt", FUN_00172530);

INCLUDE_ASM("asm/nonmatchings/P2/jt", FUN_001725e0);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtTool__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", FUN_00172898);

void UpdateJtPosWorldPrev(JT *pjt)
{
    UpdateSoPosWorldPrev(pjt);
    STRUCT_OFFSET(pjt, 0x21cc, int) = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", FUN_00172b08);

void UpdateJtBounds(JT *pjt)
{
    int i;
    UpdateSoBounds(pjt);
    for (i = 0; i < STRUCT_OFFSET(pjt, 0x21cc, int); i++)
    {
        ExtendSoBounds(pjt, &STRUCT_OFFSET(pjt, 0x21d0 + i * 0x10, VECTOR), STRUCT_OFFSET(pjt, 0x2420, float));
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", PsoGetJtEffect__FP2JTPi);

INCLUDE_ASM("asm/nonmatchings/P2/jt", AddJtCustomXps__FP2JTP2SOiP3BSPT3PP2XP);

CT CtTorqueJt(JT *pjt)
{
    if (pjt->jts == JTS_Zap || pjt->jts == (JTS)13)
    {
        return CT_Free;
    }
    return CT_Locked;
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", FUN_00172ee0);

INCLUDE_ASM("asm/nonmatchings/P2/jt", GetJtCpdefiFlatten__FP2JTP6CPDEFI);

void FUN_00173708(JT *pjt, int fActive, PO *ppoOther)
{
    OnPoActive(pjt, fActive, ppoOther);
    SetFsp((FSP)(fActive ? g_pgsCur->fspLast : -1));
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", FUN_00173750);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtActive__FP2JTP3JOYf);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJt__FP2JTf);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtDrive__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", ChooseJtPhys__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", EnableJtActadj__FP2JTi);

INCLUDE_ASM("asm/nonmatchings/P2/jt", SetJtJts__FP2JT3JTS4JTBS);

void ProfileJt(JT *pjt, int fProfile)
{
    return;
}

void SetJtPuppet(JT *pjt, ASEGA *pasega)
{
    SetJtJts(pjt, pasega ? JTS_Peek : JTS_Stand, JTBS_Nil);
}

void FUN_00177828(JT *pjt, int n)
{
    STRUCT_OFFSET(pjt, 0x2bd8, int) = n;
    STRUCT_OFFSET(pjt, 0x4b8, int) = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", PaloAbsorbWkr__FP3WKRiPP3ALO);

int NCmpWkr(WKR *pwkr0, WKR *pwkr1)
{
    return pwkr0->gSort > pwkr1->gSort ? 1 : -1;
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtEffect__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", FIsJtSoundBase__FP2JT);

void CollectJtPrize(JT *pjt, PCK pck, ALO *paloOther)
{
    CollectPoPrize(pjt, pck, paloOther);
    switch (pck)
    {
    case PCK_Key:
        SetJtJts(pjt, JTS_Rush, JTBS_Rush_Attack);
        break;
    case PCK_Gold:
        SetJtJts(pjt, JTS_Rush, JTBS_Rush_Bounce);
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", GetJtDiapi__FP2JTP6DIALOGP5DIAPI);

INCLUDE_ASM("asm/nonmatchings/P2/jt", PlayJtDialog__FP2JTP6DIALOG);
