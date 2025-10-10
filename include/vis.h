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
 * @class VISMAP
 * @brief Visibility map.
 */
struct VISMAP : public LO
{
    /* 0x30 */ int cvbsp;
    /* 0x34 */ VBSP *avbsp;
    /* 0x3c */ int cgrfzon;
    /* 0x40 */ GRFZON *agrfzonOneHop;
};

void InitVismap(VISMAP *pvismap);

void LoadVismapFromBrx(VISMAP *pvismap, CBinaryInputStream *pbis);

GRFZON GrfzonOneHop(VISMAP *pvismap, VBSP *pvbsp);

void ClipVbspSphereOneHop(VISMAP *pvismap, VBSP *pvbsp, VU_VECTOR pos, float sRadius, GRFZON *pgrfzon);

void ClipVismapSphereOneHop(VISMAP *pvismap, VECTOR *ppos, float sRadius, GRFZON *pgrfzon);

void ClipVismapPointNoHop(VISMAP *pvismap, VECTOR *ppos, GRFZON *pgrfzon);

#endif // VIS_H
