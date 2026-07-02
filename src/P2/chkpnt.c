#include <chkpnt.h>
#include <sce/memset.h>
#include <tn.h>
#include <brx.h>
#include <so.h>
#include <joy.h>
#include <rumble.h>
#include <po.h>
#include <wipe.h>

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
#ifdef SKIP_ASM
void SaveChkmgrCheckpoint(CHKMGR *pchkmgr, OID oidWarp, OID oidWarpContext)
{
    STRUCT_OFFSET(pchkmgr, 0x20C, int) = 0;
    memcpy((char *)pchkmgr + 0x220, &pchkmgr->abitChk, 0x204);
    STRUCT_OFFSET(pchkmgr, 0x42c, int) = 1;
    STRUCT_OFFSET(pchkmgr, 0x424, int) = oidWarp;
    STRUCT_OFFSET(pchkmgr, 0x428, int) = oidWarpContext;
}
#endif // SKIP_ASM

void ReturnChkmgrToCheckpoint(CHKMGR *pchkmgr)
{
    TRANS trans;
    trans.fSet = 1;
    trans.pchzWorld = (LevelTableStruct *)g_transition.m_achzWorldCur;
    if (STRUCT_OFFSET(pchkmgr, 0x42c, int))
    {
        trans.oidWarp = (OID)STRUCT_OFFSET(pchkmgr, 0x424, int);
        trans.oidWarpContet = (OID)STRUCT_OFFSET(pchkmgr, 0x428, int);
        trans.grftrans = 0x11;
    }
    else
    {
        trans.oidWarp = OID_Nil;
        trans.oidWarpContet = OID_Nil;
        trans.grftrans = 0x10;
    }
    ActivateWipe(&g_wipe, &trans, (WIPEK)1);
}

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
#ifdef SKIP_ASM
void CloneChkpnt(CHKPNT *pchkpnt, CHKPNT *pchkpntBase)
{
    int i = 0;
    LO *plo0 = STRUCT_OFFSET(pchkpnt, 0x5B4, LO *);
    LO *plo1 = STRUCT_OFFSET(pchkpnt, 0x5B0, LO *);

    CloneSo((SO *)pchkpnt, (SO *)pchkpntBase);

    STRUCT_OFFSET(pchkpnt, 0x5B0, LO *) = plo1;
    STRUCT_OFFSET(pchkpnt, 0x5B4, LO *) = plo0;

    if (STRUCT_OFFSET(pchkpnt, 0x564, int) > 0)
    {
        LO **a = &STRUCT_OFFSET(pchkpnt, 0x568, LO *);
        do
        {
            *a = PloCloneLo(*a, STRUCT_OFFSET(pchkpnt, 0x14, SW *), (ALO *)pchkpnt);
            i++;
            a++;
        } while (i < STRUCT_OFFSET(pchkpnt, 0x564, int));
    }

    if (STRUCT_OFFSET(pchkpnt, 0x58C, int) > 0)
    {
        int j = 0;
        LO **a = &STRUCT_OFFSET(pchkpnt, 0x590, LO *);
        do
        {
            *a = PloCloneLo(*a, STRUCT_OFFSET(pchkpnt, 0x14, SW *), (ALO *)pchkpnt);
            j++;
            a++;
        } while (j < STRUCT_OFFSET(pchkpnt, 0x58C, int));
    }
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/chkpnt", UpdateChkpnt__FP6CHKPNTf);

extern void TriggerJoyRumbleRumk(JOY *pjoy, RUMK rumk, float dt);

int FUN_001417f0(CHKPNT *pchkpnt, WKR *pwkr)
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

void FUN_001419A0(CHKPNT *pchkpnt, int n)
{
    int c = STRUCT_OFFSET(pchkpnt, 0x578, int);
    int *a = &STRUCT_OFFSET(pchkpnt, 0x57c, int);
    a[c] = n;
    STRUCT_OFFSET(pchkpnt, 0x578, int) = c + 1;
}

void FUN_001419C0(CHKPNT *pchkpnt, int n)
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
