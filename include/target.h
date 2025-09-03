/**
 * @file target.h
 */
#ifndef TARGET_H
#define TARGET_H

#include <dl.h>
#include <xform.h>

/**
 * @brief Target.
 */
struct TARGET : public XFM
{
    DLE dleTarget;
    int grftak;
    float sRadiusTarget;
    int fHitTest;
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
