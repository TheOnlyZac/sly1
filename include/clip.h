/**
 * @file clip.h
 */
#ifndef CLIP_H
#define CLIP_H

#include "common.h"
#include <geom.h>
#include <bsp.h>
#include <vec.h>
#include <so.h>

typedef int GRFHTL;

/**
 * @brief Unknown.
 * @todo Based on the may prototype,
 * so this can be incorrect.
 */
struct MAA
{
    float u;
    int iu;
    undefined1 unk[8];
    VECTOR pos;
    VECTOR normal;
};

SO *PsoHitTestLineObjects(GRFHTL grfhtl, VECTOR *ppos0, VECTOR *ppos1, int cpso, SO **apso, LSG *plsgBest);

int ClsgClipEdgeToObject(SO *pso, VECTOR *ppos0, VECTOR *ppos1, int clsgMax, LSG *alsg);

int ClsgClipEdgeToObjectPruned(SO *pso, BSP *pbspPruned, VECTOR *ppos0, VECTOR *ppos1, int clsgMax, LSG *alsg);

int ClsgClipCylinderToObject(SO *pso, VECTOR *ppos0, VECTOR *ppos1, float sRadius, int clsgMax, LSG *alsg);

int ClsgClipLineToSphere(VECTOR *pposSphere, float sRadius, VECTOR *ppos0, VECTOR *ppos1, int clsgMax, LSG *alsg);

int ClsgClipEdgeToSphere(VECTOR *pposSphere, float sRadius, VECTOR *ppos0, VECTOR *ppos1, int clsgMax, LSG *alsg);

int ClsgClipCylinderToSphere(VECTOR *pposSphere, float sRadiusSphere, VECTOR *ppos0, VECTOR *ppos1, float sRadiusCylinder, int clsgMax, LSG *alsg);

int ClsgClipEdgeToCylinder(VECTOR *pposCylinder0, VECTOR *pposCylinder1, float sRadiusCylinder, VECTOR *pposEdge0, VECTOR *pposEdge1, int clsgMax, LSG *alsg);

int SgnCompareMaa(MAA *pmaa1, MAA *pmaa2);

int ClsgMergeAlsg(int clsg, LSG *alsg);

int ClsgClipCylinderToBsp(BSPC *pbspc, GEOM *pgeom, VECTOR *ppos0, VECTOR *ppos1, float sRadiusCylinder, int clsgMax, LSG *alsg);

#endif // CLIP_H
