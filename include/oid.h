/**
 * @file oid.h
 *
 * @brief Object IDs.
 */
#ifndef OID_H
#define OID_H

#include "common.h"

/**
 * @brief Object ID.
 */
enum OID
{
    OID_Nil = -1,
    OID_Unknown = 0x0,
    OID__MERGED_STATICS = 0x1,
    OID__VISIBILITY_MAP = 0x2,
    OID__WORLD = 0x3,
    OID__CAMERA = 0x4,
    OID_jt = 0x5,
    OID_bentley = 0x6,
    OID_murray = 0x7,

    // ...

    OID_shd_stock_shadow = 0x2c,

    // ...

    OID_EF = 0xEF,

    // ...

    OID_rat = 0x269,

    // ...

    OID_16A = 0x16A,
    OID_16B = 0x16B,
    OID_16C = 0x16C,
    OID_16D = 0x16D,

    // ...

    OID_state_ubb_round_2 = 0x2da,
    OID_state_ubb_round_3 = 0x2db,

    // ...

    OID_state_ubb_dunk = 0x2e0,

    // ...
};

#endif // OID_H
