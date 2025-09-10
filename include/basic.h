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
 * @class BASIC
 * @brief Base object for most other kinds of objects.
 */
struct BASIC
{
    union {
        VTBASIC *pvtbasic;
        VTLO *pvtlo;
    };
    CSidebag *psidebag;
};

/**
 * @brief Check if the basic object is derived from the given class ID.
 *
 * @param pbasic The object.
 * @param cid The class ID to check.
 *
 * @retval 1 if the object is derived from the class.
 * @retval 0 if the object is not derived from the class.
 */
int FIsBasicDerivedFrom(BASIC *pbasic, CID cid);

/**
 * @brief Check if the basic has a sidebag, and if not, create one.
 *
 * @param pbasic The object.
 */
void EnsureBasicSidebag(BASIC *pbasic);

/**
 * @brief Get the basic object's CID.
 *
 * @param pbasic The object.
 * @param pcid Return CID.
 */
void GetBasicCid(BASIC *pbasic, CID *pcid);

#endif // BASIC_H
