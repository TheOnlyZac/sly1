#include <chkpnt.h>
#include <sce/memset.h>
#include <tn.h>
#include <brx.h>
#include <so.h>
#include <joy.h>
#include <rumble.h>
#include <po.h>

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

void RestoreChkmgrFromCheckpoint(CHKMGR *pchkmgr)
{
    pchkmgr->cbitChk = 0;
    memcpy(&pchkmgr->abitChk, (char *)pchkmgr + 0x220, 0x204);
    pchkmgr->fChkDirty = 0;
}

int IchkAllocChkmgr(CHKMGR *pchkmgr)
{
    return ++pchkmgr->cbitChk;
}

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", FGetChkmgrIchk__FP6CHKMGRi);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", SetChkmgrIchk__FP6CHKMGRi);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", ClearChkmgrIchk__FP6CHKMGRi);

void LoadVolFromBrx(VOL *pvol, CBinaryInputStream *pbis)
{
    pbis->ReadMatrix((MATRIX3 *)((uint8_t *)pvol + 0x50));
    pbis->ReadVector((VECTOR *)((uint8_t *)pvol + 0x40));
    LoadTbspFromBrx(pbis,
                    &STRUCT_OFFSET(pvol, 0x80, int),
                    &STRUCT_OFFSET(pvol, 0x84, TSURF *),
                    &STRUCT_OFFSET(pvol, 0x88, int),
                    &STRUCT_OFFSET(pvol, 0x8c, TBSP *));
    LoadOptionsFromBrx(pvol, pbis);
}

extern int ConvertXfmLocalToWorld(XFM *pxfm, VECTOR *pposWorld, VECTOR *pposLocal);

int FCheckVolPoint(VOL *pvol, VECTOR *ppos)
{
    VECTOR posLocal;

    ConvertXfmLocalToWorld(pvol, ppos, &posLocal);
    return FCheckTbspPoint(STRUCT_OFFSET(pvol, 0x8c, TBSP *), &posLocal);
}

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", InitChkpnt__FP6CHKPNT);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", LoadChkpntFromBrx__FP6CHKPNTP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", BindChkpnt__FP6CHKPNT);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", PostChkpntLoad__FP6CHKPNT);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", CloneChkpnt__FP6CHKPNTT0);

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", UpdateChkpnt__FP6CHKPNTf);

extern void TriggerJoyRumbleRumk(JOY *pjoy, RUMK rumk, float dt);

extern "C" int FUN_001417f0(CHKPNT *pchkpnt, WKR *pwkr)
{
    if ((PO *)pwkr->ploSource == PpoCur())
    {
        if (!(pwkr->grftak & 0x10))
            TriggerJoyRumbleRumk(&g_joy, RUMK_MediumThrob, 0.2f);
        TriggerChkpnt(pchkpnt);
        return 1;
    }

    return FAbsorbSoWkr((SO *)pchkpnt, pwkr);
}

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", TriggerChkpnt__FP6CHKPNT);

extern "C" void FUN_001419A0(CHKPNT *pchkpnt, int n)
{
    int c = STRUCT_OFFSET(pchkpnt, 0x578, int);
    int *a = &STRUCT_OFFSET(pchkpnt, 0x57c, int);
    a[c] = n;
    STRUCT_OFFSET(pchkpnt, 0x578, int) = c + 1;
}

extern "C" void FUN_001419C0(CHKPNT *pchkpnt, int n)
{
    int c = STRUCT_OFFSET(pchkpnt, 0x550, int);
    int *a = &STRUCT_OFFSET(pchkpnt, 0x554, int);
    a[c] = n;
    STRUCT_OFFSET(pchkpnt, 0x550, int) = c + 1;
}

void FUN_001419E0(int *param_1, int param_2)
{
    param_1[0x168] = param_2;
}
