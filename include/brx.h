/**
 * @file brx.h
 *
 * @brief Binary Resource Archive.
 */
#ifndef BRX_H
#define BRX_H

#include "common.h"
#include <sw.h>

/**
 * @brief Builds the eopids array.
 */
void StartupBrx();

// ...

/**
 * @brief Creates a new PLO from the given parameters.
 *
 * @param cid Class ID.
 * @param psw Pointer to the SW object.
 * @param paloParent Pointer to the parent ALO object.
 * @param oid Object ID.
 * @param isplice Splice index.
 *
 * @return Pointer to the new SW object.
 */
SW* PloNew(CID cid, SW* psw, ALO* paloParent, OID oid, int isplice);

 // ...

/**
 * @brief Loads the options from a BRX file.
 *
 * @param pvStruct Pointer to the structure to load options into.
 * @param pbis Pointer to the binary input stream.
 */
void LoadOptionsFromBrx(void *pvStruct, CBinaryInputStream *pbis);

// ...

/**
 * @brief Get the PLO index from a stock OID.
 *
 * @param oid The OID to get the index of.
 *
 * @return The level object index.
 */
uint IploFromStockOid(int oid);

#endif // BRX_H
