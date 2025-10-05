/**
 * @file target.h
 */
#ifndef TARGET_H
#define TARGET_H

#include "common.h"
#include <dl.h>
#include <xform.h>

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
    undefined4 unk0;
    undefined4 unk1;
    undefined4 unk2;
};

void StartupTarget();

void ResetTargetList();

void InitTarget(TARGET *ptarget);

void OnTargetAdd(TARGET *ptarget);

void OnTargetRemove(TARGET *ptarget);

void CloneTarget(TARGET *ptarget, TARGET *ptargetBase);

#endif // TARGET_H
