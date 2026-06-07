#include <pzo.h>
#include <find.h>
#include <game.h>
#include <so.h>
#include <jt.h>
#include <chkpnt.h>

void InitSprize(SPRIZE *psprize)
{
    InitSo(psprize);
    STRUCT_OFFSET(psprize, 0x554, int) = 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/pzo", LoadSprizeFromBrx__FP6SPRIZEP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", BindSprize__FP6SPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", PostSprizeLoad__FP6SPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", UpdateSprize__FP6SPRIZEf);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", CollectSprize__FP6SPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", EmitSprizeExplosion__FP6SPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", PcsFromSprize__FP6SPRIZE);

void AddSprizeAseg(SPRIZE * p, OID oidAseg)
{
    int c = STRUCT_OFFSET(p, 0x55c, int);
    OID *a = &STRUCT_OFFSET(p, 0x560, OID);
    a[c] = oidAseg;
    STRUCT_OFFSET(p, 0x55c, int) = c + 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/pzo", HandleSprizeMessage__FP6SPRIZE5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", FIgnoreSprizeIntersection__FP6SPRIZEP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", FUN_00199000);

void InitScprize(SCPRIZE *pscprize)
{
    InitSprize(pscprize);
    STRUCT_OFFSET(pscprize, 0x5a0, int) = IchkAllocChkmgr(&g_chkmgr);
}

void CloneScprize(SCPRIZE *pscprize, SCPRIZE *pscprizeBase)
{
    int ichk = STRUCT_OFFSET(pscprize, 0x5a0, int);
    CloneSo(pscprize, pscprizeBase);
    STRUCT_OFFSET(pscprize, 0x5a0, int) = ichk;
}

INCLUDE_ASM("asm/nonmatchings/P2/pzo", PcsFromScprize__FP7SCPRIZE);

void CollectScprize(SCPRIZE *pscprize)
{
    SetChkmgrIchk(&g_chkmgr, STRUCT_OFFSET(pscprize, 0x5a0, int));
    CollectSprize(pscprize);
}

extern SNIP D_0026A918;

void LoadLockFromBrx(LOCK *plock, CBinaryInputStream *pbis)
{
    LoadAloFromBrx(plock, pbis);
    SnipAloObjects(plock, 1, &D_0026A918);
}
extern SNIP D_0026A928;

void PostLockLoad(LOCK *plock)
{
    PostAloLoad(plock);
    SnipAloObjects(plock, 1, &D_0026A928);
}
extern SNIP D_0026A938;

void LoadLockgFromBrx(LOCKG *plockg, CBinaryInputStream *pbis)
{
    LoadAloFromBrx(plockg, pbis);
    SnipAloObjects(plockg, 1, &D_0026A938);
}
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

extern "C" void func_001781E0(JT *pjt, LOCKG *plockg);

void TriggerLockg(LOCKG *plockg)
{
    if (g_pjt)
        func_001781E0(g_pjt, plockg);
}

void InitClue(CLUE *pclue)
{
    SW *psw;
    int n;

    InitSprize(pclue);
    psw = pclue->psw;
    n = STRUCT_OFFSET(psw, 0x2300, int);
    STRUCT_OFFSET(pclue, 0x5a0, int) = n;
    STRUCT_OFFSET(psw, 0x2300, int) = n + 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/pzo", LoadClueFromBrx__FP4CLUEP18CBinaryInputStream);

void CloneClue(CLUE *pclue, CLUE *pclueBase)
{
    int n = STRUCT_OFFSET(pclue, 0x5a0, int);
    CloneSo(pclue, pclueBase);
    STRUCT_OFFSET(pclue, 0x5a0, int) = n;
}

INCLUDE_ASM("asm/nonmatchings/P2/pzo", PostClueLoad__FP4CLUE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", UpdateClue);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", OnClueSmack__FP4CLUE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", CollectClue__FP4CLUE);

void BreakClue(CLUE *pclue)
{
    ((void (*)(CLUE *))STRUCT_OFFSET(pclue->pvtlo, 0x134, void *))(pclue);
}

INCLUDE_ASM("asm/nonmatchings/P2/pzo", CollectClueSilent__FP4CLUE);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", FUN_00199c10);

void ImpactClue(CLUE *pclue, int fParentDirty)
{
    ImpactSo(pclue, fParentDirty);
}

INCLUDE_ASM("asm/nonmatchings/P2/pzo", FAbsorbClueWkr__FP4CLUEP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", RenderClueAll__FP4CLUEP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/pzo", CollectAllClues__Fi);

void SetGrfvault(int grfvault)
{
    g_pgsCur->grfvault = grfvault;
}

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
