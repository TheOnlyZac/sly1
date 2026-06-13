#include <dartgun.h>
#include <jt.h>
#include <clock.h>
#include <lookat.h>
#include <dart.h>
#include <dl.h>
#include <find.h>

void InitDartgun(DARTGUN *pdartgun)
{
    InitBreak((BREAK *)pdartgun);
    STRUCT_OFFSET(pdartgun, 0x6c0, OID) = OID_Nil; // pdartgun->oidDart
}

void HandleDartgunMessage(DARTGUN *pdartgun, MSGID msgid, void *pv)
{
    OID oid;
    ALO *palo;

    HandleAloMessage((ALO *)pdartgun, msgid, pv);

    if (msgid != (MSGID)0x14)
        return;

    if (pv != STRUCT_OFFSET(pdartgun, 0x740, void *))
        return;

    GetSmaGoal((SMA *)pv, &oid);
    if (oid != (OID)0x2B7)
        return;

    if (STRUCT_OFFSET(pdartgun, 0x680, int) != 0)
    {
        RetractSma(STRUCT_OFFSET(pdartgun, 0x740, SMA *));
        STRUCT_OFFSET(pdartgun, 0x740, int) = 0;
    }
    else
    {
        STRUCT_OFFSET(STRUCT_OFFSET(STRUCT_OFFSET(pdartgun, 0x734, char *), 0x200, char *), 0x4C, int) = 1;
        STRUCT_OFFSET(STRUCT_OFFSET(STRUCT_OFFSET(pdartgun, 0x734, char *), 0x200, char *), 0x1C, int) = 0;

        palo = STRUCT_OFFSET(pdartgun, 0x734, ALO *);
        (*(void (**)(ALO *, void *))((char *)palo->pvtlo + 0x84))(palo, (char *)palo + 0x190);
        palo = STRUCT_OFFSET(pdartgun, 0x734, ALO *);
        (*(void (**)(ALO *, void *))((char *)palo->pvtlo + 0x88))(palo, (char *)palo + 0x1A0);
        palo = STRUCT_OFFSET(pdartgun, 0x738, ALO *);
        (*(void (**)(ALO *, void *))((char *)palo->pvtlo + 0x88))(palo, (char *)palo + 0x1A0);
    }
}

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

void BreakDartgun(DARTGUN *pdartgun)
{
    OID oidCur;
    ALO *palo;
    SMA *psma;

    palo = STRUCT_OFFSET(pdartgun, 0x6c8, ALO *);
    if (palo != NULL)
    {
        (*(void (**)(ALO *, int))((char *)palo->pvtlo + 0x64))(palo, 0);
        palo = STRUCT_OFFSET(pdartgun, 0x6c8, ALO *);
        (*(void (**)(ALO *))((char *)palo->pvtlo + 0x1c))(palo);
    }

    psma = STRUCT_OFFSET(pdartgun, 0x740, SMA *);
    if (psma != NULL)
    {
        SeekSma(psma, (OID)0x2B7);
        GetSmaCur(STRUCT_OFFSET(pdartgun, 0x740, SMA *), &oidCur);
        if (oidCur == (OID)0x2B7)
        {
            RetractSma(STRUCT_OFFSET(pdartgun, 0x740, SMA *));
            STRUCT_OFFSET(pdartgun, 0x740, int) = 0;
        }
    }

    palo = STRUCT_OFFSET(STRUCT_OFFSET(pdartgun, 0x734, char *), 0x200, ALO *);
    (*(void (**)(ALO *, int))((char *)palo->pvtlo + 0x8))(palo, 7);

    BreakBrk((BRK *)pdartgun);
}

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

void TrackDartgun(DARTGUN *pdartgun, OID *poidStateGoal)
{
    extern VECTOR D_00248D30;

    if (*poidStateGoal == (OID)0x2B8)
    {
        STRUCT_OFFSET(STRUCT_OFFSET(STRUCT_OFFSET(pdartgun, 0x734, char *), 0x200, char *), 0x1C, int) = 0;
        if (STRUCT_OFFSET(pdartgun, 0x6D0, float) < g_clock.t - STRUCT_OFFSET(pdartgun, 0x6D8, float))
        {
            if (FPrepareDartgunToFire(pdartgun))
                *poidStateGoal = (OID)0x2BA;
        }
    }
    else
    {
        LO *plo = STRUCT_OFFSET(pdartgun, 0x6E0, LO *);
        if (plo == NULL || FIsLoInWorld(plo) == 0 ||
            STRUCT_OFFSET(STRUCT_OFFSET(pdartgun, 0x6E0, SO *), 0x550, int) == 3 ||
            STRUCT_OFFSET(STRUCT_OFFSET(pdartgun, 0x6E0, SO *), 0x550, int) == 4)
        {
            STRUCT_OFFSET(pdartgun, 0x6E0, RAT *) = PratGetDartgunRatTarget(pdartgun);
        }

        if (STRUCT_OFFSET(pdartgun, 0x6E0, RAT *) != NULL)
        {
            SetActlaTarget((ACTLA *)STRUCT_OFFSET(STRUCT_OFFSET(pdartgun, 0x734, char *), 0x200, char *),
                           (ALO *)STRUCT_OFFSET(pdartgun, 0x6E0, ALO *), &D_00248D30);
            if (STRUCT_OFFSET(pdartgun, 0x6D0, float) < g_clock.t - STRUCT_OFFSET(pdartgun, 0x6D8, float))
            {
                if (FPrepareDartgunToFire(pdartgun))
                    *poidStateGoal = (OID)0x2BB;
            }
        }
    }
}

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
