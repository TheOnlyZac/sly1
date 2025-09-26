#include <pzo.h>
#include <find.h>

INCLUDE_ASM("asm/nonmatchings/P2/pzo", InitSprize__FP6SPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", LoadSprizeFromBrx__FP6SPRIZEP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", BindSprize__FP6SPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", PostSprizeLoad__FP6SPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", UpdateSprize__FP6SPRIZEf);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", CollectSprize__FP6SPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", EmitSprizeExplosion__FP6SPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", PcsFromSprize__FP6SPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", AddSprizeAseg__FP6SPRIZE3OID);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", HandleSprizeMessage__FP6SPRIZE5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", FIgnoreSprizeIntersection__FP6SPRIZEP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", FUN_00199000);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", InitScprize__FP7SCPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", CloneScprize__FP7SCPRIZET0);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", PcsFromScprize__FP7SCPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", CollectScprize__FP7SCPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", LoadLockFromBrx__FP4LOCKP18CBinaryInputStream);
#ifdef SKIP_ASM
/**
 * @todo 95.80% matched. s_asnip may not be defined correctly.
 */
void LoadLockFromBrx(LOCK *plock, CBinaryInputStream *pbis)
{
    static SNIP *s_asnip;
    LoadAloFromBrx(plock, pbis);
    SnipAloObjects(plock, 1, s_asnip);
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/pzo", PostLockLoad__FP4LOCK);
#ifdef SKIP_ASM
/**
 * @todo 95.00% matched. s_asnip may not be defined correctly.
 */
void PostLockLoad(LOCK *plock)
{
    static SNIP *s_asnip;
    PostAloLoad(plock);
    SnipAloObjects(plock, 1, s_asnip);
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/pzo", LoadLockgFromBrx__FP5LOCKGP18CBinaryInputStream);
#ifdef SKIP_ASM
/**
 * @todo 95.00% matched. s_asnip may not be defined correctly.
 */
void LoadLockgFromBrx(LOCKG *plockg, CBinaryInputStream *pbis)
{
    LoadAloFromBrx(plockg, pbis);
    // SnipAloObjects(plockg, 1, PostLockgLoad);
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/pzo", PostLockgLoad__FP5LOCKG);
#ifdef SKIP_ASM
/**
 * @todo 63.40% matched.
 */
void PostLockgLoad(LOCKG *plockg)
{
    PostAloLoad(plockg);

    int count;
    SW *psw = plockg->psw;
    LO **aplo = STRUCT_OFFSET(plockg, 0x304, LO **);
    count = CploFindSwObjectsByClass(psw, 1, (CID)0x5C, (LO *)plockg, 8, aplo);
    STRUCT_OFFSET(plockg, 0x300, uint) = count;

    count = STRUCT_OFFSET(plockg, 0x2DC, uint);
    if (count > 0) {
        LO **aploIn = STRUCT_OFFSET(plockg, 0x2E0, LO **);
        LO **aploOut = STRUCT_OFFSET(plockg, 0x304, LO **);
        for (int i = 0; i < count; i++) {
            LO *plo = PloFindSwObject(psw, 4, STRUCT_OFFSET(aploIn, i * 4, OID), (LO *)plockg);
            if (plo) {
                uint curCount = STRUCT_OFFSET(plockg, 0x300, uint);
                if (curCount < 8) {
                    aploOut[curCount] = plo;
                    curCount++;
                    STRUCT_OFFSET(plockg, 0x300, uint) = curCount;
                }
            }
        }
    }

    int mask = STRUCT_OFFSET(plockg, 0x2D0, int);
    int goalStart = 0x22E;
    int goalEnd = 0x22F;
    if ((STRUCT_OFFSET(g_pwsCur, 0x448, int) & mask))
        goalStart = goalEnd;

    SMA *psma;
    count = STRUCT_OFFSET(plockg, 0x300, uint);
    if (count > 0) {
        ALO **aploState = STRUCT_OFFSET(plockg, 0x304, ALO **);
        for (int i = 0; i < count; i++) {
            ALO *paloChild = aploState[i];
            psma = PsmaApplySm(STRUCT_OFFSET(paloChild, 0x2D0, SM *), paloChild, (OID)-1, 0);
            STRUCT_OFFSET(paloChild, 0x2D4, SMA *) = psma;
            SetSmaGoal(psma, (OID)goalStart);
        }
    }

    psma = PsmaApplySm(STRUCT_OFFSET(plockg, 0x2D4, SM *), (ALO *)plockg, OID_Nil, 0);
    STRUCT_OFFSET(plockg, 0x2D8, SMA *) = psma;
    SetSmaGoal(psma, (OID)goalStart);
}
#endif

void SetLockgIndex(LOCKG *plockg, int ifws)
{
    STRUCT_OFFSET(plockg, 0x2D0, int) = 1 << ++ifws;
}

/**
 * @note Will stop matching if ALO or LOCKG fields are changed.
 */
void AddLockgLock(LOCKG *plockg, OID oidLock)
{
    uint ccur = plockg->coidLock;
    if (ccur >= 8)
        return;

    plockg->aoidLock[ccur] = oidLock;
    plockg->coidLock = ++ccur;
}

INCLUDE_ASM("asm/nonmatchings/P2/pzo", TriggerLockg__FP5LOCKG);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", InitClue__FP4CLUE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", LoadClueFromBrx__FP4CLUEP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", CloneClue__FP4CLUET0);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", PostClueLoad__FP4CLUE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", UpdateClue);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", OnClueSmack__FP4CLUE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", CollectClue__FP4CLUE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", BreakClue__FP4CLUE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", CollectClueSilent__FP4CLUE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", FUN_00199c10);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", ImpactClue__FP4CLUEi);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", FAbsorbClueWkr__FP4CLUEP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", RenderClueAll__FP4CLUEP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", CollectAllClues__Fi);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", SetGrfvault__Fi);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", FUN_0019a000);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", FUN_0019a088);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", FUN_0019a0f0);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", InitVault__FP5VAULT);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", PostTmblLoad__FP4TMBL3OID);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", PostVaultLoad__FP5VAULT);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", OnVaultActive__FP5VAULTiP2PO);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", UpdateVaultActive__FP5VAULTP3JOYf);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", HandleVaultMessage__FP5VAULT5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", AddVaultGoadDialog__FP5VAULT5GOADK3OID);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", OpenVault__FP5VAULT);
