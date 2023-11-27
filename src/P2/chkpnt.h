#pragma once
#include <util.h>
#include <game.h>
#include <vec.h>

struct CHKPNT
{
};

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

void ResetChkmgrCheckpoints(CHKMGR* pchkmgr);
