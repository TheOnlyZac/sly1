/**
 * @file transition.h
 *
 * @brief Declarations for the transition system.
*/
#ifndef TRANSITION_H
#define TRANSITION_H

#include <bis.h>
#include <brx.h>
#include <cat.h>
#include <game.h>
#include <gs.h>
#include <difficulty.h>
#include <clock.h>
#include <joy.h>
#include <phasemem.h>
#include <prog.h>
#include <sound.h>
#include <sw.h>
#include <iostream>

typedef int GRFTRANS;

/**
 * @brief Transition data
 *
 * Responsible for holding data bout a level transition.
*/
struct TRANS
{
    uint32_t fSet;
    struct LevelTableStruct *pchzWorld; // Current file thats loading struct
    OID oidWarp; // Checkpoint Warps
    OID trans_mod_flags;
    GRFTRANS grftrans; // Lost all lives flags
};

/**
 * @brief Transition Flags
*/
enum FTRANS {
    GRFTRANS_None = 0,
    FTRANS_Checkpoint = 1,
    FTRANS_RetryWorld = 2,
    FTRANS_ClearGame = 4,
    FTRANS_SameWorld = 8,
    FTRANS_ShowLives = 16
};

/**
 * @brief Level Table Struct
 *
 * Holds data about the level file.
 *
 * @note Name is not official.
*/
struct LevelTableStruct
{
    CFileLocation fileLocation; /* Ciphers for lsn and size */
    uint32_t search_val;
    uint32_t for_lsn;
    uint32_t search_cipher; /* Cipher for search val */
    uint32_t for_size;
    uint32_t level_id; /* Level ID */
    uint32_t level_name;  /* Pointer to level name string */
    FLS tasks;         /* Tasks to complete (visited, key, vault, mts) */
};

/**
 * @brief Transition
*/
class CTransition
{
protected:
    char *m_pchzWorld;      // This is the ptr to enc level sector offset and size in memory
    OID   m_oidWarp;        // Which checkpoint you spawn at when you start a level
    OID   m_oidWarpContext;

public:
    GRFTRANS grftrans;       // Flags that affect level loading, one of them checks if you lost all lives when you die.
    char m_achzWorldCur[64]; // File description contents.
    int  m_fPending;         // Basically like a level pending flag.

    // Reloads the current level. The value of FTRANS affects the load.
    void ResetWorld(FTRANS ftrans);

    // Sets the conditions on the level if you died or loading a level
    void Set(char *pchzWorld, OID oidWarp, OID oidWarpContext, GRFTRANS grftrans);

    // Executes the conditions from CTransition::Set by setting some engine vaules to default and loading the level file
    void Execute();
};

// Global variables
static CTransition g_transition; // Current transition

#endif // TRANSITION_H
