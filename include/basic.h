/**
 * @file basic.h
 *
 * @brief Basic object.
 */
#ifndef BASIC_H
#define BASIC_H

#include "common.h"
#include <splice/sidebag.h>

/**
 * @brief Basic object.
 *
 * Base class for most objects.
 *
 * @todo Declare virtual methods.
 */
struct BASIC
{
    int field_0x0; // placeholder for vtable
    CSidebag *psidebag;
};

#endif // BASIC_H
