/**
 * @file stepside.h
 */
#ifndef STEPSIDE_H
#define STEPSIDE_H

#include "common.h"
#include <stepcane.h>

// Forward.
struct JT;
struct ASEGBL;

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct BLSS : public BL
{
    // ...
};

void PostJtLoadSidestep(JT *pjt, BLSS *ablss, ASEGBL **ppasegbl);

void AdjustJtSidestep(JT *pjt, BLSS *ablss, ASEGBL *pasegbl);

void SetJtSidestepTarget(JT *pjt, BLSS *ablss, ASEGBL *pasegbl, float rad, float u);

#endif // STEPSIDE_H
