#pragma once

#include <util.h>
#include <game.h>

typedef struct VTCHKPNT;
struct CHKPNT
{
	struct VTCHKPNT* pvtchkpnt;
};

typedef struct VTCHKMGR;
struct CHKMGR
{
	struct VTCHKMTR* pvtchkmgr;
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

void ResetChkmgrCheckpoints(CHKMGR* pchkmgr);
