#include <geom.h>

void InitGeom(GEOM *pgeom)
{
    pgeom->cpos = 0;
    pgeom->apos = 0;

    pgeom->csurf = 0;
    pgeom->asurf = 0;

    pgeom->cedge = 0;
    pgeom->aedge = 0;
}

INCLUDE_ASM(const s32, "P2/geom", CloneGeom__FP4GEOMP7MATRIX4T0);

INCLUDE_ASM(const s32, "P2/geom", FUN_00161028);
