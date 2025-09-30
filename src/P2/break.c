#include <break.h>
#include <chkpnt.h>

INCLUDE_ASM("asm/nonmatchings/P2/break", InitBrk__FP3BRK);

INCLUDE_ASM("asm/nonmatchings/P2/break", LoadBrkFromBrx__FP3BRKP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/break", CloneBrk__FP3BRKT0);

void PostBrkLoad(BRK *pbrk)
{
    PostAloLoad((ALO *)pbrk);
    PostSwCallback(pbrk->psw, PostBrkLoadCallbackHookup, pbrk, MSGID_callback, nullptr);
}

INCLUDE_ASM("asm/nonmatchings/P2/break", PostBrkLoadCallbackHookup__FP3BRK5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/break", UpdateBrk__FP3BRKf);

INCLUDE_ASM("asm/nonmatchings/P2/break", FAbsorbBrkWkr__FP3BRKP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/break", BreakBrk__FP3BRK);

void SetBrkBroken(BRK *pbrk, int fBroken)
{
    STRUCT_OFFSET(pbrk, 0x680, int) = fBroken; // pbrk->fBroken

    if (fBroken != 0)
    {
        SetChkmgrIchk(&g_chkmgr, STRUCT_OFFSET(pbrk, 0x688, int)); // pbrk->ichkBroken
    }
    else
    {
        ClearChkmgrIchk(&g_chkmgr, STRUCT_OFFSET(pbrk, 0x688, int)); // pbrk->ichkBroken
    }
}

void SetBrkExclude(BRK *pbrk, OID oid)
{
    if (STRUCT_OFFSET(pbrk, 0x550, uint) >= 0x10)
        return;

    (&STRUCT_OFFSET(pbrk, 0x554, BRP))[STRUCT_OFFSET(pbrk, 0x550, uint)].oid = oid;
    (&STRUCT_OFFSET(pbrk, 0x554, BRP))[STRUCT_OFFSET(pbrk, 0x550, uint)].brpt = BRPT_Disappear;
    STRUCT_OFFSET(pbrk, 0x550, uint)++;
}

void SetBrkRemain(BRK *pbrk, OID oid)
{
    if (STRUCT_OFFSET(pbrk, 0x550, uint) >= 0x10)
        return;

    (&STRUCT_OFFSET(pbrk, 0x554, BRP))[STRUCT_OFFSET(pbrk, 0x550, uint)].oid = oid;
    (&STRUCT_OFFSET(pbrk, 0x554, BRP))[STRUCT_OFFSET(pbrk, 0x550, uint)].brpt = BRPT_Remain;
    STRUCT_OFFSET(pbrk, 0x550, uint)++;
}

void SetBrkFixed(BRK *pbrk, OID oid)
{
    if (STRUCT_OFFSET(pbrk, 0x550, uint) >= 0x10)
        return;

    (&STRUCT_OFFSET(pbrk, 0x554, BRP))[STRUCT_OFFSET(pbrk, 0x550, uint)].oid = oid;
    (&STRUCT_OFFSET(pbrk, 0x554, BRP))[STRUCT_OFFSET(pbrk, 0x550, uint)].brpt = BRPT_Fixed;
    STRUCT_OFFSET(pbrk, 0x550, uint)++;
}

void SetBrkRemainFixed(BRK *pbrk, OID oid)
{
    if (STRUCT_OFFSET(pbrk, 0x550, uint) >= 0x10)
        return;

    (&STRUCT_OFFSET(pbrk, 0x554, BRP))[STRUCT_OFFSET(pbrk, 0x550, uint)].oid = oid;
    (&STRUCT_OFFSET(pbrk, 0x554, BRP))[STRUCT_OFFSET(pbrk, 0x550, uint)].brpt = BRPT_RemainFixed;
    STRUCT_OFFSET(pbrk, 0x550, uint)++;
}

INCLUDE_ASM("asm/nonmatchings/P2/break", SetBrkOnPlayer__FP3BRKi);

void GetBrkOnPlayer(BRK *pbrk, int *pfBreakOnPlayer)
{
    // pbrk->grfbrk
    *pfBreakOnPlayer = STRUCT_OFFSET(pbrk, 0x63c, int) & 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/break", SetBrkOnBomb__FP3BRKi);

void GetBrkOnBomb(BRK *pbrk, int *pfBreakOnBomb)
{
    // pbrk->grfbrk
    *pfBreakOnBomb = (STRUCT_OFFSET(pbrk, 0x63c, int) >> 2) & 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/break", AddBrkTouchObject__FP3BRK3OID);

INCLUDE_ASM("asm/nonmatchings/P2/break", AddBrkTouchClass__FP3BRK3CID);

INCLUDE_ASM("asm/nonmatchings/P2/break", FUN_0013DAB8);

SFX *PsfxEnsureBrk(BRK *pbrk, ENSK ensk)
{
    // pbrk->psfxBreak
    if (!STRUCT_OFFSET(pbrk, 0x6b4, SFX *))
    {
        NewSfx(&STRUCT_OFFSET(pbrk, 0x6b4, SFX *));
    }
    
    return STRUCT_OFFSET(pbrk, 0x6b4, SFX *);
}

INCLUDE_ASM("asm/nonmatchings/P2/break", FCheckBrkTouchObject__FP3BRKP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/break", UpdateBrkp__FP4BRKPf);

INCLUDE_ASM("asm/nonmatchings/P2/break", HandleBrkpMessage__FP4BRKP5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/break", FIgnoreBrkpIntersection__FP4BRKPP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/break", SetBrkpBrkps__FP4BRKP5BRKPS);

void InitBreak(BREAK *pbreak)
{
    InitBrk(pbreak);
    STRUCT_OFFSET(pbreak, 0x63c, int) = 5;
    STRUCT_OFFSET(pbreak, 0x698, int) = -1;
}

INCLUDE_ASM("asm/nonmatchings/P2/break", InitFragile__FP7FRAGILE);

INCLUDE_ASM("asm/nonmatchings/P2/break", AdjustFragileNewXp__FP7FRAGILEP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/break", AdjustZapbreakNewXp__FP8ZAPBREAKP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/break", UpdateZapbreak__FP8ZAPBREAKf);
