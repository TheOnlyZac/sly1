#include <geom.h>

void InitGeom(GEOM *pgeom)
{
    pgeom->cpos = 0;
    pgeom->apos = (VECTOR *)nullptr;

    pgeom->csurf = 0;
    pgeom->asurf = (SURF *)nullptr;

    pgeom->cedge = 0;
    pgeom->aedge = (EDGE *)nullptr;
}

INCLUDE_ASM("asm/nonmatchings/P2/geom", CloneGeom__FP4GEOMP7MATRIX4T0);

INCLUDE_ASM("asm/nonmatchings/P2/geom", FUN_00161028);
