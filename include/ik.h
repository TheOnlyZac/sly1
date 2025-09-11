/**
 * @file ik.h
 */
#ifndef IK_H
#define IK_H

#include "common.h"
#include <alo.h>
#include <so.h>
#include <cm.h>

// Forward.
struct RO;

/**
 * @class IK_HANDLE
 * @brief Inverse kinematics handle.
 * @todo Implement the struct.
 */
struct IKH : public SO
{
    // ...
};

/**
 * @class LIGHTWEIGHT_IK_HAN
 * @brief Lightweight(?) inverse kinematics handle.
 * @todo Implement the struct.
 */
struct LIKH : public ALO
{
    // ...
};

void RenderIkhSelf(IKH *pikh, CM pcm, RO *pro);

void RenderLikhSelf(LIKH *plikh, CM *pcm, RO *pro);

void SolveAloIK(ALO *palo);

#endif // IK_H
