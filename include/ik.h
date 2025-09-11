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
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct IKH : public SO
{
    // ...
};

/**
 * @brief Unknown.
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
