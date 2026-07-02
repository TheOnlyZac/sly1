#include <ub.h>

INCLUDE_ASM("asm/nonmatchings/P2/ub", InitUbg__FP3UBG);

#ifndef SKIP_ASM
INCLUDE_ASM("asm/nonmatchings/P2/ub", PostUbgLoad__FP3UBG);
#else
extern SNIP D_00275B60;
void FUN_001ddc38(void *pv, void *pvBlot);

void PostUbgLoad(UBG *pubg)
{
    SnipAloObjects((ALO *)pubg, 8, &D_00275B60);
    FUN_001ddc38(STRUCT_OFFSET(pubg, 0x14, void *), pubg);

    if (STRUCT_OFFSET(pubg, 0xC50, void *) != NULL)
    {
        STRUCT_OFFSET(pubg, 0xC54, SMA *) =
            PsmaApplySm(STRUCT_OFFSET(pubg, 0xC50, SM *), NULL, (OID)0x2D7, 0);
    }

    STRUCT_OFFSET(pubg, 0xC90, int) = 4;

    int *pichk = &STRUCT_OFFSET(pubg, 0xC80, int);
    int i = 0;
    do
    {
        *pichk = IchkAllocChkmgr(&g_chkmgr);
        i++;
        pichk++;
    } while ((uint)i < 4);

    PostGomerLoad(pubg);
}
#endif

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
    // pubg->fAbandonExternal
    if (STRUCT_OFFSET(pubg, 0xc40, int) != 0)
        return 0;

    // pubg->cJump
    return (STRUCT_OFFSET(pubg, 0xc5c, int)) != 0;
}

int FCanUbgAttack(UBG *pubg)
{
    // pubg->oidPatrolGoal
    if(STRUCT_OFFSET(pubg, 0xc58, OID) != OID_state_ubb_round_3)
        return 0;

    // pubg->cJump
    if(STRUCT_OFFSET(pubg, 0xc5c, int) == 5 || STRUCT_OFFSET(pubg, 0xc5c, int) == 0)
        return 0;

    return 1;
}

void DoUbgFreefallJump(UBG *pubg)
{
    // pubg->oidPatrolGoal
    if (STRUCT_OFFSET(pubg, 0xc58, OID) != OID_state_ubb_round_2)
    {
        // pubg->cJump
        int cJump = STRUCT_OFFSET(pubg, 0xc5c, int) - 1;
        if (cJump < 1) cJump = 0;
        STRUCT_OFFSET(pubg, 0xc5c, int) = cJump;
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
        // pubg->apsoPads
        SO **apsoPads = &STRUCT_OFFSET(pubg, 0xc64, SO *);
        if ((SO *)psoOther->paloRoot == apsoPads[i])
            return 0;
    }

    return FIgnoreStepguardIntersection(pubg, psoOther);
}
