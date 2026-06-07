#include <frzg.h>

INCLUDE_ASM("asm/nonmatchings/P2/frzg", PostFrzgLoad__FP4FRZG);

void AddFrzgObject(FRZG *pfrzg, OID oid)
{
    int coid = pfrzg->coid;
    pfrzg->aoid[coid] = oid;
    pfrzg->coid = coid + 1;
}
