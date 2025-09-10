/**
 * @file geom.h
 *
 * @brief Geometry.
 */
#ifndef GEOM_H
#define GEOM_H

#include <vec.h>
#include <mat.h>

/**
 * @todo Define struct
 */
struct TBSP;

/**
 * @brief Edge in a geometry.
 */
struct EDGE
{
    ushort aipos[2];
    ushort aisurf[2];
    EDGE *pedgeNext;
    EDGE *pedgeOtherNext;
};

/**
 * @brief Unknown.
 */
struct SUR
{
    int cb;
    void *pvSrc;
    void *pvDst;
    int cvtx;
};

/**
 * @brief Unknown.
 */
struct SURF
{
    VECTOR normal;
    float gDot;
    EDGE *pedge;
    EDGE *pedgeOther;
    short grfsurf;
    short ipos;
};

/**
 * @brief Unknown.
 */
struct TSURF
{
    float gDot;
    undefined4 unk1;
    undefined4 unk2;
    undefined4 unk3;
    VECTOR normal;
};

/**
 * @brief Geometry.
 */
struct GEOM
{
    float sRadius;

    int cpos;
    VECTOR *apos;

    int csurf;
    SURF *asurf;

    int cedge;
    EDGE *aedge;

    int *mpiposiiedgeMac;
    int *aiedge;
    VECTOR *mpisurfposCenter;
    float *mpisurfsRadius;
};

/**
 * @brief Initializes the geometry struct.
 */
void InitGeom(GEOM *pgeom);

/**
 * @brief Clones the geometry struct.
 */
void CloneGeom(GEOM *pgeomSrc, MATRIX4 *pdmat, GEOM *pgeomDst);

#endif // GEOM_H
