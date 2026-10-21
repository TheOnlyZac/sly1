#include <sb.h>
#include <asega.h>
#include <memcard.h>
#include <game.h>
#include <sw.h>
#include <ui.h>

#include <screen.h>
#include <emitter.h>
#include <jt.h>

extern VECTOR g_normalX;

void PostSbgLoad(SBG *psbg)
{
    PostStepguardLoad(psbg);
    FUN_001ddc38(psbg->psw,  psbg);
}

int FUN_001a9928(SBG *psbg)
{
    if (IsSwHandsOff(psbg->psw) == 0) 
    {
        return STRUCT_OFFSET(psbg, 0xC24, int);
    }
    return 0;
}

void UpdateSbgGoal(SBG *psbg, int fEnter)
{
    int vectorCheck;

    UpdateStepguardGoal(psbg, fEnter);
    if (STRUCT_OFFSET(psbg, 0x724, SGS) == SGS_Stun) 
    {
        typedef int (*VFn)(SBG*);
        vectorCheck = STRUCT_OFFSET(STRUCT_OFFSET(psbg, 0x0, SBG *), 0x198, VFn)(psbg);
        if (vectorCheck != 0) 
        {
            SetStepguardGoal(psbg, &STRUCT_OFFSET(vectorCheck, 0x140, VECTOR));
        }
    }
}

void UpdateSbgSgs(SBG *psbg)
{
    UpdateStepguardSgs(psbg);

    if (STRUCT_OFFSET(psbg, 0x724, SGS) == SGS_Stun)
    {
        LookStepguardAtGoal(psbg);
    }
}

void OnSbgEnteringSgs(SBG *psbg, SGS sgs, ASEG *paseg)
{
    OnStepguardEnteringSgs(psbg, sgs, paseg);
    if (STRUCT_OFFSET(psbg, 0x724, int) == 0xB) 
    {
        DefeatBossFromWorld(GAMEWORLD_Snow);
        FUN_0018c7f8(&g_save);
    }
}

void UpdateSbg(SBG *psbg, float dt)
{
    UpdateStepguard(psbg, dt);
    ASEGA *pasega = STRUCT_OFFSET(psbg, 0xC20, ASEGA *);
    if (pasega != 0 && STRUCT_OFFSET(pasega, 0x18, float) == 0.0f) 
    {
        RetractAsega(pasega);
        STRUCT_OFFSET(psbg, 0xC20, ASEGA *) = 0;
    }
}

void FUN_001a9a98()
{
    if (FUN_001e9970() != 0) 
    {
        g_unkblot7.pvtblot->pfnShowBlot(&g_unkblot7);
        return;
    }
    g_unkblot7.pvtblot->pfnHideBlot(&g_unkblot7);
}

int FAbsorbSbgWkr(SBG *psbg, WKR *pwkr)
{
    if (STRUCT_OFFSET(psbg, 0xC14, ASEG *) != NULL && (pwkr->grfic & 0x20) != 0)
    {
        STRUCT_OFFSET(psbg, 0xC10, int)++;
        FUN_001ac060(&g_unkblot7);

        EXPLSO explso;

        asm volatile (
            ".set push\n"
            ".set noreorder\n"
            ".set noat\n"
            "lw      $2, 0xB00(%0)\n"
            "beqz    $2, 3f\n"
            "lui     $2, %%hi(g_normalX)\n"
            "lqc2    $vf3, 0x30(%1)\n"
            "vmul.xyz $vf1, $vf3, $vf3\n"
            "vaddw.x $vf2, $vf0, $vf0w\n"
            "vadday.x ACC, $vf1, $vf1y\n"
            "vmaddz.x $vf1, $vf2, $vf1z\n"
            "lui     $1, (0x38D1B717 >> 16)\n"
            "ori     $1, $1, (0x38D1B717 & 0xFFFF)\n"
            "mtc1    $1, $f1\n"
            ".word   0x4A0103BD\n"
            "vwaitq\n"
            "vaddq.x $vf1, $vf0, Q\n"
            "lq      $4, 0x20(%1)\n"
            "qmfc2.ni $3, $vf1\n"
            "addiu   $2, $2, %%lo(g_normalX)\n"
            "mtc1    $3, $f0\n"
            "lq      $2, 0x0($2)\n"
            "c.lt.s  $f0, $f1\n"
            "addiu   $3, $0, 0x6\n"
            "sq      $4, 0x20($sp)\n"
            "bc1f    1f\n"
            "sw      $3, 0x0($sp)\n"
            "b       2f\n"
            "qmtc2.ni $2, $vf1\n"
            "1:\n"
            "vdiv    Q, $vf0w, $vf1x\n"
            "vwaitq\n"
            "vmulq.xyzw $vf1, $vf3, Q\n"
            "2:\n"
            "sqc2    $vf1, 0x10($sp)\n"
            "lw      $4, 0xB00(%0)\n"
            "lw      $3, 0x0($4)\n"
            "lw      $2, 0x7C($3)\n"
            "jalr    $2\n"
            "move    $5, $sp\n"
            "3:\n"
            ".set pop\n"
            :
            : "r"(psbg), "r"(pwkr)
            : "$1", "$2", "$3", "$4", "$5", "$f0", "$f1", "memory"
        );

        ASEG *paseg;
        if ((pwkr->grftak & 2) != 0)
        {
            paseg = (g_pjt != NULL && STRUCT_OFFSET(g_pjt, 0x223C, int) != 4 && STRUCT_OFFSET(g_pjt, 0x223C, int) != 6)
                ? STRUCT_OFFSET(psbg, 0xC18, ASEG *)
                : STRUCT_OFFSET(psbg, 0xC14, ASEG *);
        }
        else if ((pwkr->grftak & 4) != 0)
        {
            paseg = STRUCT_OFFSET(psbg, 0xC1C, ASEG *);
        }
        else
        {
            paseg = STRUCT_OFFSET(psbg, 0xC14, ASEG *);
        }

        ApplyAsegCur(paseg, (ALO *)psbg, 0.0f, 1.0f, (GRFAPL)1, &STRUCT_OFFSET(psbg, 0xC20, ASEGA *));

        pwkr->grfic &= ~0x20;
    }

    return FAbsorbStepguardWkr(psbg, pwkr);
}

void FUN_001a9c58(SBG *psbg, int a, int b, int c)
{
    STRUCT_OFFSET(psbg, 0xC14, int) = a;
    STRUCT_OFFSET(psbg, 0xC18, int) = b;
    STRUCT_OFFSET(psbg, 0xC1C, int) = c;
}
