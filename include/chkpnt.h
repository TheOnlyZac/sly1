/**
 * @file chkpnt.h
 *
 * @brief Checkpoint system.
 */
#ifndef CHKPNT_H
#define CHKPNT_H

#include "common.h"
#include <vec.h>
#include <vol.h>
#include <bis.h>

/**
 * @brief Checkpoint.
 *
 * @todo Define struct.
 */
struct CHKPNT : public ALO
{
	// ...
};

/**
 * @brief Checkpoint Manager.
 *
 * @todo Fill in missing fields.
 */
struct CHKMGR
{
    int unknown_0x0;
	int cbitChk; // Count of values in abitChk.
	int *abitChk; // Unknown, name/type may be wrong.
	int padding[128]; // Temporary padding
	int fChkDirty;
	VECTOR posVolChkpnt;
	int csSaved[129]; // type may be wrong
	OID unk_oid_0x424;
	OID unk_oid_0x428;
	int fCheckpoint;
};
extern CHKMGR g_chkmgr;

void ResetChkmgrCheckpoints(CHKMGR *pchkmgr);

void SaveChkmgrCheckpoint(CHKMGR *pchkmgr, OID oidWarp, OID oidWarpContext);

void ReturnChkmgrToCheckpoint(CHKMGR *pchkmgr);

void RestoreChkmgrFromCheckpoint(CHKMGR *pchkmgr);

int IchkAllocChkmgr(CHKMGR *pchkmgr);

int FGetChkmgrIchk(CHKMGR *pchkmgr, int ichk);

void SetChkmgrIchk(CHKMGR *pchkmgr, int ichk);

void ClearChkmgrIchk(CHKMGR *pchkmgr, int ichk);

void LoadVolFromBrx(VOL *pvol, CBinaryInputStream *pbis);

int FCheckVolPoint(VOL *pvol, VECTOR *ppos);

void InitChkpnt(CHKPNT *pchkpnt);

void LoadChkpntFromBrx(CHKPNT *pchkpnt, CBinaryInputStream *pbis);

void BindChkpnt(CHKPNT *pchkpnt);

void PostChkpntLoad(CHKPNT *pchkpnt);

void CloneChkpnt(CHKPNT *pchkpnt, CHKPNT *pchkpntBase);

void UpdateChkpnt(CHKPNT *pchkpnt, float dt);

// ? tbd
void FUN_001417f0();

void TriggerChkpnt(CHKPNT *pchkpnt);

#endif /* CHKPNT_H */
