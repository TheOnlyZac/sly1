#include "brx.h"

SW* PloNew(CID cid, SW* csw, ALO* paloParent, OID oid, int isplice)
{
	// This is here temporarily
	SW* temp = csw;
	return temp;
}

int IploFromStockOid(int oid)
{
	uint uVar1;

	uVar1 = oid - 0xc;
	if (0x1c < uVar1)
		uVar1 = 0xffffffff;

	return uVar1;
}
