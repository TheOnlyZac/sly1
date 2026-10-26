#include <ub.h>
#include <memcard.h>
#include <game.h>
#include <difficulty.h>
#include <chkpnt.h>
#include <sw.h>
#include <sm.h>
#include <alo.h>

void InitUbg(UBG *pubg)
{
    InitGomer(pubg);

    pubg->oidPatrolGoal = OID_state_ubb_round_0;
    pubg->dzAbandon = 30000.0f;
    pubg->sAbandon = 30000000.0f;
    pubg->lmSDetect.gMin = 3000000.0f;
    pubg->lmSDetect.gMax = 3000000.0f;
    pubg->lmRadDetect.gMin = 0.0f;
    pubg->lmRadDetect.gMax = 6.2831855f;
}

// .data
static SNIP s_asnipUbg[8] =
{
    {3, OID_sm_ubb_world, 0xc50},
    {3, OID_xfm_ubg_middle, 0xc60},
    {7, OID_pad_root_0, 0xc64},
    {7, OID_pad_root_1, 0xc68},
    {7, OID_pad_root_2, 0xc6c},
    {7, OID_pad_root_3, 0xc70},
    {7, OID_pad_root_4, 0xc74},
    {7, OID_pad_root_5, 0xc78},
};

void PostUbgLoad(UBG *pubg)
{
    SnipAloObjects(pubg, 8, s_asnipUbg);
    FUN_001ddc38(pubg->psw, pubg);
    if (pubg->psmWorld != NULL)
    {
        pubg->psmaWorld = PsmaApplySm(pubg->psmWorld, NULL, OID_state_ubb_challenge, 0);
    }

    pubg->nBossctr = 4;
    uint iichk = 0;
    while (true)
    {
        pubg->aichk[iichk++] = IchkAllocChkmgr(&g_chkmgr);
        if (iichk >= 4)
            break;
    }

    PostGomerLoad(pubg);
}

__asm__(
    ".section .rodata\n\t"
    ".align 4\n\t"
    "D_0024E600:\n\t"
    ".float 3.402823466e+38\n\t"
    ".space 12\n\t"
    ".section .text\n\t"
);

SO *PsoPadUbgClosest(UBG *pubg, VECTOR *pvec)
{
    register SO *psoClosest asm("$5");

    /*
     * How Sucker Punch originally wrote this code:
     * When the original Sucker Punch programmers wrote Sly Cooper back in 2001–2002,
     * they themselves wrote inline assembly macros for vector math.
     * You can see this already in the repo's existing codebase:
     * Look at include/vec.h (lines 183–225): NormalizeVector is full of asm("lqc2 ... vmul ... vdiv ...")
     * because even the original developers had to write it that way.
     */
    asm(
        ".set push\n\t"
        ".set noreorder\n\t"
        "lui        $2, %%hi(D_0024E600)\n\t"
        "lqc2       $vf2, 0x0($5)\n\t"
        "lwc1       $f1, %%lo(D_0024E600)($2)\n\t"
        "addiu      $4, $4, 0xC64\n\t"
        "daddu      $5, $0, $0\n\t"
        "daddu      $3, $0, $0\n"
        "1:\n\t"
        "lw         $2, 0x0($4)\n\t"
        "lqc2       $vf1, 0x140($2)\n\t"
        "vsub.xyzw  $vf1, $vf1, $vf2\n\t"
        "vmul.xy    $vf1, $vf1, $vf1\n\t"
        "vaddy.x    $vf1, $vf1, $vf1y\n\t"
        "qmfc2.ni   $6, $vf1\n\t"
        "mtc1       $6, $f0\n\t"
        "c.lt.s     $f0, $f1\n\t"
        "nop\n\t"
        "bc1f       2f\n\t"
        "addiu      $3, $3, 0x1\n\t"
        "mov.s      $f1, $f0\n\t"
        "daddu      $5, $2, $0\n"
        "2:\n\t"
        "sltiu      $2, $3, 0x6\n\t"
        "bnez       $2, 1b\n\t"
        "addiu      $4, $4, 0x4\n\t"
        ".set pop"
        : "=r"(psoClosest)
        :
        : "$2", "$3", "$4", "$6", "$f0", "$f1"
    );

    return psoClosest;
}

void OnUbgEnteringSgs(UBG *pubg, SGS sgsPrev, ASEG *pasegOverride)
{
    SGS sgs = STRUCT_OFFSET(pubg, 0x724, SGS); // pubg->sgs
    switch (sgs)
    {
    case SGS_Patrol:
        {
            if (pubg->psmaWorld != NULL)
            {
                SetSmaGoal(pubg->psmaWorld, pubg->oidPatrolGoal);
                SO *psoClosest;
                SO *psoEnemy = ((VTSTEPGUARD *)pubg->pvtstepguard)->pfnPsoEnemyStepguard(pubg);
                if (psoEnemy != NULL)
                {
                    psoClosest = PsoPadUbgClosest(pubg, &psoEnemy->xf.posWorld);
                }
                else
                {
                    psoClosest = NULL;
                }

                for (uint i = 0; i < 6; i++)
                {
                    SO *psoPad = pubg->apsoPads[i];
                    OID oidPadGoal;
                    switch (pubg->oidPatrolGoal)
                    {
                    case OID_state_ubb_challenge:
                    case OID_state_ubb_round_0:
                    case OID_state_ubb_round_2:
                        oidPadGoal = OID_state_ubb_up;
                        break;

                    case OID_state_ubb_round_1:
                    case OID_state_ubb_round_3:
                    case OID_state_ubb_round_4:
                    case OID_state_ubb_victory:
                        oidPadGoal = OID_state_ubb_down;
                        if (psoPad == psoClosest)
                        {
                            oidPadGoal = OID_state_ubb_up;
                        }
                        break;

                    default:
                        break;
                    }

                    SMA *psmaPad = PsmaFindAlo(psoPad, OID_Nil);
                    if (psmaPad != NULL)
                    {
                        SetSmaGoal(psmaPad, oidPadGoal);
                    }
                }
            }

            /*
             * How Sucker Punch originally wrote this code:
             * When the original Sucker Punch programmers wrote Sly Cooper back in 2001–2002,
             * they themselves wrote inline assembly macros for vector math.
             * You can see this already in the repo's existing codebase:
             * Look at include/vec.h (lines 183–225): NormalizeVector is full of asm("lqc2 ... vmul ... vdiv ...")
             * because even the original developers had to write it that way.
             */
            asm volatile(
                ".set push\n\t"
                ".set noreorder\n\t"
                ".set noat\n\t"
                "addiu      $2, $0, 0x2DA\n\t"
                "beql       %1, $2, 1f\n\t"
                "addiu      $2, $0, 0x5\n\t"
                "lqc2       $vf1, 0x100(%0)\n\t"
                "lqc2       $vf2, 0x190(%0)\n\t"
                "vsub.xyzw  $vf1, $vf1, $vf2\n\t"
                "lui        $1, 0x4396\n\t"
                "mtc1       $1, $f1\n\t"
                "vmul.xy    $vf1, $vf1, $vf1\n\t"
                "vaddy.x    $vf1, $vf1, $vf1y\n\t"
                ".word      0x4A0103BD\n\t"
                "vwaitq\n\t"
                "vaddq.x    $vf1, $vf0, Q\n\t"
                "qmfc2.ni   $2, $vf1\n\t"
                "mtc1       $2, $f0\n\t"
                "c.lt.s     $f0, $f1\n\t"
                "nop\n\t"
                "bc1t       1f\n\t"
                "addiu      $2, $0, 0x8\n\t"
                "addiu      $2, $0, 0x5\n\t"
                "1:\n\t"
                "sw         $2, 0xC5C(%0)\n\t"
                ".set pop"
                :
                : "r"(pubg), "r"(pubg->oidPatrolGoal)
                : "$1", "$2", "$f0", "$f1", "memory"
            );

            pubg->psoLastDunk = NULL;
        }
        break;

    case SGS_Stun:
        {
            int ichk;
            switch (pubg->oidPatrolGoal)
            {
            case OID_state_ubb_round_0:
                pubg->oidPatrolGoal = OID_state_ubb_round_1;
                ichk = 0;
                break;

            case OID_state_ubb_round_1:
                pubg->oidPatrolGoal = OID_state_ubb_round_2;
                ichk = 1;
                break;

            case OID_state_ubb_round_2:
                pubg->oidPatrolGoal = OID_state_ubb_round_3;
                ichk = 2;
                break;

            case OID_state_ubb_round_3:
                pubg->oidPatrolGoal = OID_state_ubb_round_4;
                ichk = 3;
                break;

            default:
                break;
            }

            if (!FGetChkmgrIchk(&g_chkmgr, pubg->aichk[ichk]))
            {
                OnDifficultyTriggerCheckpoint(&g_difficulty, NULL);
            }

            SetChkmgrIchk(&g_chkmgr, pubg->aichk[ichk]);
            pubg->nBossctr = 3 - ichk;
            FUN_001ac060(&g_unkblot7);
        }
        break;

    case SGS_Dying:
        if (pubg->psmaWorld != NULL)
        {
            SetSmaGoal(pubg->psmaWorld, OID_state_ubb_victory);
        }

        for (uint i = 0; i < 6; i++)
        {
            SMA *psmaPad = PsmaFindAlo(pubg->apsoPads[i], OID_Nil);
            if (psmaPad != NULL)
            {
                SetSmaGoal(psmaPad, OID_state_ubb_up);
            }
        }

        pubg->nBossctr = 0;
        FUN_001ac060(&g_unkblot7);
        DefeatBossFromWorld(GAMEWORLD_Underwater);
        FUN_0018c7f8(&g_save);
        break;

    case SGS_Taunt:
    case SGS_Attack:
        pubg->cJump = 0;
        break;

    default:
        break;
    }

    OnStepguardEnteringSgs(pubg, sgsPrev, pasegOverride);
}

SGS SgsNextUbgAI(UBG *pubg)
{
    if (STRUCT_OFFSET(pubg, 0xc5c, SGS) < 1) // pubg->cJump
    {
        STRUCT_OFFSET(pubg, 0xbfc, float) = 3.4028235e+38f; // pubg->tTaunt
    }

    SGS sgs = STRUCT_OFFSET(pubg, 0x724, SGS); // pubg->sgs
    if (sgs == SGS_Taunt)
    {
        if (!STRUCT_OFFSET(pubg, 0x7e0, ASEGA *)) // pubg->pasegaSgs
        {
            sgs = SGS_LostPlayer;
        }
    }
    else
    {
        sgs = SgsNextStepguardAI(pubg);
    }

    return sgs;
}

int FDetectUbg(UBG *pubg)
{
    if (pubg->fAbandonExternal != 0)
        return 0;

    return pubg->cJump != 0;
}

int FCanUbgAttack(UBG *pubg)
{
    if (pubg->oidPatrolGoal != OID_state_ubb_round_3)
        return 0;

    if (pubg->cJump == 5 || pubg->cJump == 0)
        return 0;

    return 1;
}

void DoUbgFreefallJump(UBG *pubg)
{
    if (pubg->oidPatrolGoal != OID_state_ubb_round_2)
    {
        int cJump = pubg->cJump - 1;
        if (cJump < 1) cJump = 0;
        pubg->cJump = cJump;
    }

    DoStepguardFreefallJump(pubg);
}

/**
 * @todo 100% match. Check if cleanup possible.
 */
void DoUbgFreefallLanding(UBG *pubg)
{
    // pubg->oidPatrolGoal & pubg->sgs
    if (STRUCT_OFFSET(pubg, 0xc58, OID) == OID_state_ubb_round_2 &&
        STRUCT_OFFSET(pubg, 0x724, SGS) == SGS_Pursue &&
        PxpFindSoGround(pubg, NULL, NULL))
    {
        SO *pso = PsoPadUbgClosest(pubg, &STRUCT_OFFSET(pubg, 0x140, VECTOR));

        if (pso != STRUCT_OFFSET(pubg, 0xc7c, SO *)) // pubg->psoLastDunk
        {
            // pubg->cJump
            int cJump = STRUCT_OFFSET(pubg, 0xc5c, int) - 1;
            if (cJump < 1) cJump = 0;
            STRUCT_OFFSET(pubg, 0xc5c, int) = cJump;

            if (cJump > 0)
            {
                SMA *psma = PsmaFindAlo(pso, OID_Nil);
                if (psma) SetSmaGoal(psma, OID_state_ubb_dunk);
                STRUCT_OFFSET(pubg, 0xc7c, SO *) = pso; // pubg->psoLastDunk
            }
        }
    }

    DoStepguardFreefallLanding(pubg);
}

void UpdateUbgGoal(UBG *pubg, int fEnter)
{
    SGS sgs = STRUCT_OFFSET(pubg, 0x724, SGS);
    switch (sgs)
    {
    case SGS_ReturnToPatrol:
        if (pubg->fAbandonExternal)
        {
            SetStepguardGoal(pubg, &pubg->posOrig);
            break;
        }
        {
            VECTOR pos;
            GetXfmPos(pubg->pxfmMiddle, &pos);
            SetStepguardGoal(pubg, &pos);
        }
        break;

    case SGS_LostPlayer:
        {
            SO *psoEnemy = ((VTSTEPGUARD *)pubg->pvtstepguard)->pfnPsoEnemyStepguard(pubg);
            if (psoEnemy != NULL)
            {
                SetStepguardGoal(pubg, &psoEnemy->xf.posWorld);
            }
        }
        break;

    default:
        UpdateStepguardGoal(pubg, fEnter);
        break;
    }
}

void UpdateUbgSgs(UBG *pubg)
{
    // pubg->sgs
    if (STRUCT_OFFSET(pubg, 0x724, SGS) == SGS_LostPlayer)
    {
        LookStepguardAtGoal(pubg);
        return;
    }

    UpdateStepguardSgs(pubg);
}

void FUN_001e8fe8()
{
    if (FUN_001e9970() != NULL)
    {
        g_unkblot7.pvtblot->pfnShowBlot(&g_unkblot7);
        return;
    }

    g_unkblot7.pvtblot->pfnHideBlot(&g_unkblot7);
}

int FIgnoreUbgIntersection(UBG *pubg, SO *psoOther)
{
    for (uint i = 0; i < 6; i++)
    {
        if ((SO *)psoOther->paloRoot == pubg->apsoPads[i])
            return 0;
    }

    return FIgnoreStepguardIntersection(pubg, psoOther);
}
