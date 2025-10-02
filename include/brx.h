/**
 * @file brx.h
 *
 * @brief Binary Resource Archive.
 */
#ifndef BRX_H
#define BRX_H

#include "common.h"
#include <sw.h>

typedef int GRFEOPID;

/**
 * @brief Object Type?
 * @todo Populate the enum with values from the prototype.
 */
enum OTYP
{
    OTYP_Nil = -1
};

/**
 * @brief Optional Data?
 */
struct OPTDAT
{
    undefined4 unknown1;
    undefined4 unknown2[2];
    undefined4 unknown3;
    undefined4 unknown4;
    undefined4 unknown5;
};

/**
 * @brief Unknown.
 */
struct EOPID
{
    OTYP otyp;
    GRFEOPID grfeopid;
    OPTDAT optdat;
};

/**
 * @brief Builds the eopids array.
 */
void StartupBrx();

/**
 * @brief Creates a new LO from the given parameters.
 *
 * @param cid Class ID.
 * @param psw Pointer to the SW object.
 * @param paloParent Pointer to the parent ALO object.
 * @param oid Object ID.
 * @param isplice Splice index.
 *
 * @return Pointer to the new LO object.
 */
LO *PloNew(CID cid, SW *psw, ALO *paloParent, OID oid, int isplice);

/**
 * @brief TODO.
 */
void LoadOptionFromBrx(void *pvStruct, EOPID *peopid, CBinaryInputStream *pbis);

/**
 * @brief Loads the options from a BRX file.
 *
 * @param pvStruct Pointer to the structure to load options into.
 * @param pbis Pointer to the binary input stream.
 */
void LoadOptionsFromBrx(void *pvStruct, CBinaryInputStream *pbis);

/**
 * @brief Get the PLO index from a stock OID.
 *
 * @param oid The OID to get the index of.
 *
 * @return The level object index.
 */
uint IploFromStockOid(int oid);

/**
 * @brief TODO.
 */
void LoadSwObjectsFromBrx(SW *psw, ALO *paloParent, CBinaryInputStream *pbis);

/**
 * @brief TODO.
 */
void SetLoDefaults(LO *plo);

#endif // BRX_H
