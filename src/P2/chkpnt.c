#include <chkpnt.h>

INCLUDE_ASM(const s32, "P2/chkpnt", ResetChkmgrCheckpoints__FP6CHKMGR);

INCLUDE_ASM(const s32, "P2/chkpnt", SaveChkmgrCheckpoint__FP6CHKMGR3OIDT1);

INCLUDE_ASM(const s32, "P2/chkpnt", ReturnChkmgrToCheckpoint__FP6CHKMGR);

INCLUDE_ASM(const s32, "P2/chkpnt", RestoreChkmgrFromCheckpoint__FP6CHKMGR);

int IchkAllocChkmgr(CHKMGR *pchkmgr)
{
    pchkmgr->cbitChk = pchkmgr->cbitChk + 1;
    return pchkmgr->cbitChk;
}

INCLUDE_ASM(const s32, "P2/chkpnt", FGetChkmgrIchk__FP6CHKMGRi);

INCLUDE_ASM(const s32, "P2/chkpnt", SetChkmgrIchk__FP6CHKMGRi);

INCLUDE_ASM(const s32, "P2/chkpnt", ClearChkmgrIchk__FP6CHKMGRi);

INCLUDE_ASM(const s32, "P2/chkpnt", LoadVolFromBrx__FP3VOLP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/chkpnt", FCheckVolPoint__FP3VOLP6VECTOR);

INCLUDE_ASM(const s32, "P2/chkpnt", InitChkpnt__FP6CHKPNT);

INCLUDE_ASM(const s32, "P2/chkpnt", LoadChkpntFromBrx__FP6CHKPNTP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/chkpnt", BindChkpnt__FP6CHKPNT);

INCLUDE_ASM(const s32, "P2/chkpnt", PostChkpntLoad__FP6CHKPNT);

INCLUDE_ASM(const s32, "P2/chkpnt", CloneChkpnt__FP6CHKPNTT0);

INCLUDE_ASM(const s32, "P2/chkpnt", UpdateChkpnt__FP6CHKPNTf);

INCLUDE_ASM(const s32, "P2/chkpnt", FUN_001417f0);

INCLUDE_ASM(const s32, "P2/chkpnt", TriggerChkpnt__FP6CHKPNT);
INCLUDE_ASM(const s32, "P2/chkpnt", func_001419A0);
INCLUDE_ASM(const s32, "P2/chkpnt", func_001419C0);
INCLUDE_ASM(const s32, "P2/chkpnt", func_001419E0);
