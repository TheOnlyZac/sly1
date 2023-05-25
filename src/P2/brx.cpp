#include "brx.h"

SW* PloNew(CID cid, SW* csw, ALO* paloParent, OID oid, int isplice)
{
	// This is here temporarily
	SW* temp = csw;
	return temp;
}

int IploFromStockOid(int oid)
{
	uint iplo;

	iplo = oid - 0xc;
	if (0x1c < iplo)
		iplo = 0xffffffff;

	return iplo;
}
