#pragma once
#include <bis.h>
#include <cat.h>
#include <game.h>
#include <gs.h>
#include <difficulty.h>
#include <iostream>

typedef enum GRFTRANS;

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
    int m_fPending; // Moves the camera to level origin if you set it manually
    char* m_pchzWorld; // This is the ptr to enc level sector offset and size in memory
    OID m_oidWarp; // Which checkpoint you spawn at when you start a level
    OID m_oidWarpContext;

public:
    GRFTRANS grftrans; // Flags that affect level loading, one of them checks if you lost all lives when you die
    char m_achzWorldCur[64]; // File description contents

    // Sets the conditions on the level if you died or loading a level
    void Set(char* pchzWorld, OID oidWarp, OID oidWarpContext, GRFTRANS grftrans);

    // Bacially Executing those conditions from the set function in the Execute function and setting some engine vaules to default and loading the level file
	void Execute();
};
