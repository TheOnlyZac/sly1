/**
 * @file po.h
 *
 * @brief Player object(?).
 */
#ifndef PO_H
#define PO_H

#include "common.h"
#include <so.h>

/**
 * @brief Player object.
 *
 * @todo Implement struct fields.
 */
struct PO : public SO
{
    // ...
};

/**
 * @brief Gets a pointer to the current PO.
 */
PO *PpoCur();

#endif // PO_H
