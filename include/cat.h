/**
 * @file cat.h
 *
 * @brief Catalog.
 */
#ifndef CAT_H
#define CAT_H

#include "common.h"

/**
 * @brief Related to file location.
 */
struct FCL
{
    uint isector;
    uint cb;
};

/**
 * @brief File location.
 */
class CFileLocation
{
public:
    FCL fcl; // File sector and size.
};

#endif // CAT_H
