/**
 * @file vis.h
 *
 * @brief Visibility map.
 */
#ifndef VIS_H
#define VIS_H

#include "common.h"
#include <bsp.h>
#include <bis.h>
#include <vec.h>
#include <lo.h>

typedef int GRFZON;

/**
 * @brief Visibility map.
 */
struct VISMAP : public LO
{
    int cvbsp;
    VBSP *avbsp;
    int cgrfzon;
    GRFZON *agrfzonOneHop;
};

void InitVismap(VISMAP *pvismap);

void LoadVismapFromBrx(VISMAP *pvismap, CBinaryInputStream *pbis);

GRFZON GrfzonOneHop(VISMAP *pvismap, VBSP *pvbsp);

void ClipVbspSphereOneHop(VISMAP *pvismap, VBSP *pvbsp, VU_VECTOR pos, float sRadius, GRFZON *pgrfzon);

void ClipVismapSphereOneHop(VISMAP *pvismap, VECTOR *ppos, float sRadius, GRFZON *pgrfzon);

void ClipVismapPointNoHop(VISMAP *pvismap, VECTOR *ppos, GRFZON *pgrfzon);

#endif // VIS_H
