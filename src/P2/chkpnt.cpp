#include <chkpnt.h>

#include <cstring>

void ResetChkmgrCheckpoints(CHKMGR* pchkmgr)
{
	pchkmgr->cbitChk = 0;
	pchkmgr->unk_0x8 = 0;

	std::memset(pchkmgr->padding, 0, 0x200);
	pchkmgr->fChkDirty = 0;

	float temp_should_be_global_var = 0.0f;
	pchkmgr->posVolChkpnt.x = temp_should_be_global_var;
	pchkmgr->posVolChkpnt.z = temp_should_be_global_var;
	pchkmgr->posVolChkpnt.x = temp_should_be_global_var;
	pchkmgr->posVolChkpnt.x = (float)((int)temp_should_be_global_var >> 0x1f);

	std::memset(pchkmgr->csSaved, 0, 0x20c);
	pchkmgr->fCheckpoint = 0;

	pchkmgr->unk_oid_0x424 = (OID)0xFFFFFFFF;
	pchkmgr->unk_oid_0x428 = (OID)0xFFFFFFFF;
}
