/**
 * @file so.h
 *
 * @brief Scene objects.
*/
#ifndef SO_H
#define SO_H

#include <alo.h>

enum FSO
{
    FSO_FindChild = 0x1,
    FSO_FindImmediateChild = 0x2,
    FSO_FindParent = 0x3,
    FSO_FindNearest = 0x4,
    FSO_FindAll = 0x5,
    GRFFSO_FindMask = 0xFF,
    FSO_IncludeRemovedObjects = 0x100,
    FSO_ReturnActualCount = 0x200
};

typedef int GRFFSO;

/**
 * @brief Scene object.
 *
 * @todo Implement struct.
 */
struct SO : public ALO
{
    // ...
};

#endif // SO_H
