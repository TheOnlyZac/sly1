#include <ub.h>

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

INCLUDE_ASM("asm/nonmatchings/P2/ub", PostUbgLoad__FP3UBG);

INCLUDE_ASM("asm/nonmatchings/P2/ub", PsoPadUbgClosest__FP3UBGP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/ub", OnUbgEnteringSgs__FP3UBG3SGSP4ASEG);

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

INCLUDE_ASM("asm/nonmatchings/P2/ub", UpdateUbgGoal__FP3UBGi);

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

INCLUDE_ASM("asm/nonmatchings/P2/ub", FUN_001e8fe8);

int FIgnoreUbgIntersection(UBG *pubg, SO *psoOther)
{
    for (uint i = 0; i < 6; i++)
    {
        if ((SO *)psoOther->paloRoot == pubg->apsoPads[i])
            return 0;
    }

    return FIgnoreStepguardIntersection(pubg, psoOther);
}
