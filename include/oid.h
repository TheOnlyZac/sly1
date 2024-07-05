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
enum OID {
    OID_Unknown = 0x0,
    OID__MERGED_STATICS = 0x1,
    OID__VISIBILITY_MAP = 0x2,
    OID__WORLD = 0x3,
    OID__CAMERA = 0x4,
    OID_jt = 0x5,
    OID_bentley = 0x6,
    OID_murray = 0x7,

    // ...

    OID_rat = 0x269

    // ...
};


#endif // OID_H
