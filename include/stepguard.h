/**
 * @file stepguard.h
 */
#ifndef STEPGUARD_H
#define STEPGUARD_H

#include "common.h"
#include <step.h>

struct STEPGUARD : public STEP
{
    // ...
};

void InitStepguard(STEPGUARD *pstepguard);

// ...

#endif // STEPGUARD_H
