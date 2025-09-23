/**
 * @file stepact.h
 */
#ifndef STEPACT_H
#define STEPACT_H

#include "common.h"
#include <act.h>

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct ACTADD : public ACT
{
    // ...
};

void GetActaddPositionGoal(ACTADD *pactadd, float dtOffset, VECTOR *ppos, VECTOR *pv);
void GetActaddRotationGoal(ACTADD *pactadd, float dtOffset, MATRIX3 *pmat, VECTOR *pw);

#endif // STEPACT_H
