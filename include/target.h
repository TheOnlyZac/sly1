/**
 * @file target.h
 */
#ifndef TARGET_H
#define TARGET_H

#include "common.h"
#include <xform.h>
#include <dl.h>

/**
 * @class TARGET
 * @brief Target point defined by a transform, radius, and some other data.
 */
struct TARGET : public XFM
{
    /* 0x80 */ DLE dleTarget;
    /* 0x88 */ int grftak;
    /* 0x8c */ float sRadiusTarget;
    /* 0x90 */ int fHitTest;
    /* 0x94 */ STRUCT_PADDING(3);
};

extern DL g_dlTarget;

void StartupTarget();

void ResetTargetList();

void InitTarget(TARGET *ptarget);

void OnTargetAdd(TARGET *ptarget);

void OnTargetRemove(TARGET *ptarget);

void CloneTarget(TARGET *ptarget, TARGET *ptargetBase);

#endif // TARGET_H
