/**
 * @file cat.h
 *
 * @brief WAL catalog.
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
 * @brief File Key.
 *
 * Used to identify the file type.
 */
enum FK
{
    FK_Nil = -1,
    FK_BrxWorld = 0,   // Level File
    FK_IcoIcon = 1,    // Icon File
    FK_BnkEffects = 2, // Sound Effect File
    FK_BnkMusic = 3,   // Music File
    FK_VagDialog = 4,  // Dialog File
    FK_VagAnimation = 5,
    FK_PssMovie = 6, // Video File
    FK_Max = 7
};

/**
 * @brief WAL Entry.
 *
 * Stores the file key and file location & size.
 */
struct WALE
{
    char *pchzKey;    // File Name used for searching for file to load
    struct FCL *pfcl; // File location and size.
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
