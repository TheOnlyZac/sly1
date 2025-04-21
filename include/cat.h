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
    FCL m_fcl; // File sector and size.

    // void Clear();
};

#endif // CAT_H
