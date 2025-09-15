#include <chkpnt.h>
#include <sce/memset.h>

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", ResetChkmgrCheckpoints__FP6CHKMGR);
#ifdef SKIP_ASM
/**
 * @brief Resets the checkpoints on the checkpoint manager.
 *
 * @param pchkmgr Pointer to the checkpoint manager.
 *
 * @todo 67.19% matched.
 */
void ResetChkmgrCheckpoints(CHKMGR *pchkmgr)
{
	pchkmgr->cbitChk = 0;
	pchkmgr->unk_0x8 = 0;

	memset(STRUCT_OFFSET(pchkmgr, 0xc, void *), 0, 0x200);
	pchkmgr->fChkDirty = 0;

	float temp_should_be_global_var = 0.0f;
	pchkmgr->posVolChkpnt.x = temp_should_be_global_var;
	pchkmgr->posVolChkpnt.z = temp_should_be_global_var;
	pchkmgr->posVolChkpnt.x = temp_should_be_global_var;
	pchkmgr->posVolChkpnt.x = (float)((int)temp_should_be_global_var >> 0x1f);

	memset(pchkmgr->csSaved, 0, 0x20c);
	pchkmgr->fCheckpoint = 0;

	pchkmgr->unk_oid_0x424 = (OID)0xFFFFFFFF;
	pchkmgr->unk_oid_0x428 = (OID)0xFFFFFFFF;
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", SaveChkmgrCheckpoint__FP6CHKMGR3OIDT1);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", ReturnChkmgrToCheckpoint__FP6CHKMGR);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", RestoreChkmgrFromCheckpoint__FP6CHKMGR);

int IchkAllocChkmgr(CHKMGR *pchkmgr)
{
    return ++pchkmgr->cbitChk;
}

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", FGetChkmgrIchk__FP6CHKMGRi);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", SetChkmgrIchk__FP6CHKMGRi);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", ClearChkmgrIchk__FP6CHKMGRi);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", LoadVolFromBrx__FP3VOLP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", FCheckVolPoint__FP3VOLP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", InitChkpnt__FP6CHKPNT);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", LoadChkpntFromBrx__FP6CHKPNTP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", BindChkpnt__FP6CHKPNT);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", PostChkpntLoad__FP6CHKPNT);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", CloneChkpnt__FP6CHKPNTT0);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", UpdateChkpnt__FP6CHKPNTf);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", FUN_001417f0);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", TriggerChkpnt__FP6CHKPNT);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", FUN_001419A0);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", FUN_001419C0);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", FUN_001419E0);
