/**
 * @file cat.h
 *
 * @brief Catalog.
 */
#ifndef CAT_H
#define CAT_H

#include "common.h"

struct FCL
{
    uint isector;
    uint cb;
};

class CFileLocation
{
public:
    FCL fcl;
};

#endif // CAT_H
