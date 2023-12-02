/**
 * @file chkpnt.h
 *
 * @brief Declarations for the checkpoint system.
*/
#ifndef CHKPNT_H
#define CHKPNT_H

#include <util.h>
#include <game.h>
#include <vec.h>

/**
 * @brief Checkpoint
*/
struct CHKPNT
{
};

/**
 * @brief Checkpoint Manager
*/
struct CHKMGR
{
	int cbitChk;
	int unk_0x8;
	int padding[128];
	int fChkDirty;
	VECTOR posVolChkpnt;
	int csSaved[129]; // type may be wrong
	OID unk_oid_0x424;
	OID unk_oid_0x428;
	int fCheckpoint;
};

/**
 * @brief Resets the checkpoint manager.
 *
 * @param pchkmgr Pointer to the checkpoint manager.
*/
void ResetChkmgrCheckpoints(CHKMGR* pchkmgr);

#endif // CHKPNT_H
