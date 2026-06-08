#include <dartgun.h>
#include <jt.h>

void InitDartgun(DARTGUN *pdartgun)
{
    InitBreak((BREAK *)pdartgun);
    STRUCT_OFFSET(pdartgun, 0x6c0, OID) = OID_Nil; // pdartgun->oidDart
}

INCLUDE_ASM("asm/nonmatchings/P2/dartgun", HandleDartgunMessage__FP7DARTGUN5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/dartgun", BindDartgun__FP7DARTGUN);

extern "C" {
void FUN_0014f900(DARTGUN* pdartgun)
{
    if (g_pjt != NULL)
    {
        STRUCT_OFFSET(pdartgun, 0x6dc, int) = STRUCT_OFFSET(g_pjt, 0x24f8, int);
    }
}
}

INCLUDE_ASM("asm/nonmatchings/P2/dartgun", PostDartgunLoad__FP7DARTGUN);

INCLUDE_ASM("asm/nonmatchings/P2/dartgun", UpdateDartgun__FP7DARTGUNf);

int FIgnoreDartgunIntersection(DARTGUN *pdartgun, SO *psoOther)
{
    if (FIsBasicDerivedFrom(psoOther, CID_RAT))
    {
        if (STRUCT_OFFSET(psoOther, 0x588, SO *) == (SO *)pdartgun)
            return 1;
    }

    return FIgnoreSoIntersection((SO *)pdartgun, psoOther);
}

INCLUDE_ASM("asm/nonmatchings/P2/dartgun", BreakDartgun__FP7DARTGUN);

void SetDartgunGoalState(DARTGUN *pdartgun, OID oidStateGoal)
{
    OID oidCur;

    GetSmaGoal(STRUCT_OFFSET(pdartgun, 0x740, SMA *), &oidCur);
    if (oidCur == OID_Nil)
        GetSmaCur(STRUCT_OFFSET(pdartgun, 0x740, SMA *), &oidCur);

    if (oidStateGoal == oidCur)
        return;

    if (oidCur == (OID)0x2B7)
    {
        STRUCT_OFFSET(STRUCT_OFFSET(STRUCT_OFFSET(pdartgun, 0x734, char *), 0x200, char *), 0x4C, int) = 0;
    }

    if (oidStateGoal < (OID)0x2BA)
    {
        if (oidStateGoal >= (OID)0x2B8)
        {
            STRUCT_OFFSET(STRUCT_OFFSET(STRUCT_OFFSET(pdartgun, 0x734, char *), 0x200, char *), 0x1C, int) = (oidStateGoal == (OID)0x2B9);
            if ((unsigned int)(oidCur - 0x2BA) >= 2)
                STRUCT_OFFSET(pdartgun, 0x6D8, int) = 0;
        }
    }

    SetSmaGoal(STRUCT_OFFSET(pdartgun, 0x740, SMA *), oidStateGoal);
}

INCLUDE_ASM("asm/nonmatchings/P2/dartgun", TrackDartgun__FP7DARTGUNP3OID);

INCLUDE_ASM("asm/nonmatchings/P2/dartgun", FPrepareDartgunToFire__FP7DARTGUN);

INCLUDE_ASM("asm/nonmatchings/P2/dartgun", FireDartgun__FP7DARTGUN);

INCLUDE_ASM("asm/nonmatchings/P2/dartgun", AgeDartgunStuckDart__FP7DARTGUN);

INCLUDE_ASM("asm/nonmatchings/P2/dartgun", PratGetDartgunRatTarget__FP7DARTGUN);

/**
 * @todo Cleanup once struct is implemented.
 */
void AddDartgunRatTarget(DARTGUN *pdartgun, OID oid)
{
    if (STRUCT_OFFSET(pdartgun, 0x744, uint) >= 8)
    {
        return;
    }

    // pdartgun->aoidRatTarget[pdartgun->coidRatTarget++] = oid;
    OID *aoidRatTarget = &STRUCT_OFFSET(pdartgun, 0x748, OID);
    aoidRatTarget[STRUCT_OFFSET(pdartgun, 0x744, uint)++] = oid;
}

void StartDartgunTargetAreaChange(DARTGUN *pdartgun)
{
    STRUCT_OFFSET(pdartgun, 0x78c, int) = 0; // pdartgun->cpratInTargetArea
    STRUCT_OFFSET(pdartgun, 0x7b0, int) = 0; // pdartgun->fJtInTargetArea
}

INCLUDE_ASM("asm/nonmatchings/P2/dartgun", AddDartgunTargetAreaTarget__FP7DARTGUNP3ALO);
