/**
 * @file actseg.h
 *
 * @brief Declarations for actor segments.
*/
#ifndef ACTSEG_H
#define ACTSEG_H

#include <vec.h>
#include <util.h>

/**
 * @brief Unknown, needs more research
*/
struct ACTLA
{
    int fUseTarget;
    struct ALO_conflict* paloTarget;
    struct VECTOR posTargetLocal;
    float sIgnore;
    int nPriorityEnabled;
    int nPriorityDisabled;
    int fPaused;
    struct CLQ clqPanToPan;
    struct LM lmPan;
    struct CLQ clqTiltToTilt;
    struct LM lmTilt;
};

#endif // ACTSEG_H
