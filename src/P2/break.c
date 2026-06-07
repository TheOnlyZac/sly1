#include <break.h>
#include <chkpnt.h>
#include <po.h>

INCLUDE_ASM("asm/nonmatchings/P2/break", InitBrk__FP3BRK);

INCLUDE_ASM("asm/nonmatchings/P2/break", LoadBrkFromBrx__FP3BRKP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/break", CloneBrk__FP3BRKT0);

void PostBrkLoad(BRK *pbrk)
{
    PostAloLoad((ALO *)pbrk);
    PostSwCallback(pbrk->psw, PostBrkLoadCallbackHookup, pbrk, MSGID_callback, NULL);
}

INCLUDE_ASM("asm/nonmatchings/P2/break", PostBrkLoadCallbackHookup__FP3BRK5MSGIDPv);

void UpdateBrk(BRK *pbrk, float dt)
{
    UpdateSo(pbrk, dt);

    if (STRUCT_OFFSET(pbrk, 0x678, int))
    {
        STRUCT_OFFSET(pbrk, 0x678, int) = 0;
        (*(void (**)(BRK *))((char *)pbrk->pvtlo + 0x130))(pbrk);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/break", FAbsorbBrkWkr__FP3BRKP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/break", BreakBrk__FP3BRK);

void SetBrkBroken(BRK *pbrk, int fBroken)
{
    STRUCT_OFFSET(pbrk, 0x680, int) = fBroken; // pbrk->fBroken

    if (fBroken)
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

void UpdateBrkp(BRKP *pbrkp, float dt)
{
    UpdateSo(pbrkp, dt);

    // TODO: Couldn't get the compiler to emit matching code without nesting the if's. Try to fix later?
    BRKPS brkps = STRUCT_OFFSET(pbrkp, 0x550, BRKPS); // pbrkp->brkps
    if (brkps != BRKPS_Idle)
    {
        if (brkps == BRKPS_Pending)
        {
            // pbrkp->cframeStatic, pbrkp->dtMaxLifetime, pbrkp->tBrkps
            if(STRUCT_OFFSET(pbrkp, 0x228, int) > 1 || STRUCT_OFFSET(pbrkp, 0x558, float) < g_clock.t - STRUCT_OFFSET(pbrkp, 0x554, float))
                brkps = BRKPS_Fading;
        }
    }

    SetBrkpBrkps(pbrkp, brkps);
}

void HandleBrkpMessage(BRKP *pbrkp, MSGID msgid, void *pv)
{
    HandleAloMessage((ALO *)pbrkp, msgid, pv);

    BRKP **apbrkp = (BRKP **)pv;
    if (msgid == MSGID_break_piece && apbrkp[1] == pbrkp)
    {
        SetBrkpBrkps(pbrkp, BRKPS_Pending);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/break", FIgnoreBrkpIntersection__FP4BRKPP2SO);

void SetBrkpBrkps(BRKP *pbrkp, BRKPS brkps)
{
    if (brkps == STRUCT_OFFSET(pbrkp, 0x550, BRKPS)) // pbrkp->brkps
    {
        return;
    }

    STRUCT_OFFSET(pbrkp, 0x550, BRKPS) = brkps; // pbrkp->brkps
    STRUCT_OFFSET(pbrkp, 0x554, float) = g_clock.t; // pbrkp->tBrkps

    if (brkps == 2)
    {
        FadeAloOut((ALO *)pbrkp, STRUCT_OFFSET(pbrkp, 0x55c, float));
    }
}

void InitBreak(BREAK *pbreak)
{
    InitBrk(pbreak);
    STRUCT_OFFSET(pbreak, 0x63c, int) = 5; // pbreak->grfbrk
    STRUCT_OFFSET(pbreak, 0x698, int) = -1; // pbreak->ccoin
}

void InitFragile(FRAGILE *pfragile)
{
    InitBrk(pfragile);
    STRUCT_OFFSET(pfragile, 0x63c, int) = 1; // pfragile->grfbrk
    STRUCT_OFFSET(pfragile, 0x6c0, float) = 1.0f;
    STRUCT_OFFSET(pfragile, 0x6c4, int) = -1;
    STRUCT_OFFSET(pfragile, 0x6c8, int) = -1;
}

INCLUDE_ASM("asm/nonmatchings/P2/break", AdjustFragileNewXp__FP7FRAGILEP2XPi);

void AdjustZapbreakNewXp(ZAPBREAK *pzapbreak, XP *pxp, int ixpd)
{
    AdjustFragileNewXp((FRAGILE *)pzapbreak, pxp, ixpd);
    if (STRUCT_OFFSET(pzapbreak, 0x680, int))
    {
        return;
    }

    PO *ppoBase = (PO *)pxp->axpd[1 - ixpd].psoRoot;
    if(FIsBasicDerivedFrom(ppoBase, CID_PO) && FCheckBrkTouchObject((BRK *)pzapbreak, ppoBase))
    {
        STRUCT_OFFSET(pzapbreak, 0x6d4, PO *) = ppoBase; // pzapbreak->ppoZap
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/break", UpdateZapbreak__FP8ZAPBREAKf);
