#pragma once
#include <bis.h>
#include <cat.h>
#include <game.h>
#include <gs.h>
#include <difficulty.h>
#include <iostream>

typedef int GRFTRANS;

struct TRANS
{
    uint32_t fSet;
	struct LevelTableStruct* pchzWorld; // Current file thats loading struct
    OID oidWarp; // Checkpoint Warps
    OID trans_mod_flags;
    GRFTRANS grftrans; // Lost all lives flags 
};

struct lsn_and_unk_ciphers_t
{
    uint32_t lsn_enc;
    uint32_t size_enc;
};

struct LevelTableStruct
{
    struct lsn_and_unk_ciphers_t lsn_and_size_ciphers; /* Ciphers for lsn and size */
    uint32_t search_val;
    uint32_t field_0xc;
    uint32_t field_0x10;
    uint32_t for_lsn;
    uint32_t search_cipher; /* Cipher for search val */
    uint32_t for_size;
    uint32_t level_id; /* Level ID */
    void* level_name; /* Pointer to name string */
    enum FLS tasks; /* Tasks to complete (visited, key, vault, mts) */
};

class CTransition
{
protected:
    char* m_pchzWorld; // This is the ptr to enc level sector offset and size in memory
    OID m_oidWarp; // Which checkpoint you spawn at when you start a level
    OID m_oidWarpContext;

public:
    GRFTRANS grftrans; // Flags that affect level loading, one of them checks if you lost all lives when you die
    char m_achzWorldCur[64]; // File description contents
    int m_fPending; // Moves the camera to level origin if you set it manually

    // Sets the conditions on the level if you died or loading a level
    void Set(char* pchzWorld, OID oidWarp, OID oidWarpContext, GRFTRANS grftrans);

    // Executes the conditions from CTransition::Set by setting some engine vaules to default and loading the level file
    void Execute();
};
