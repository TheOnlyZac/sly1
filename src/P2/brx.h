/**
 * @file brx.h
 *
 * @brief Declarations for interaction with binary resource archives.
*/
#include <alo.h>
#include <game.h>
#include <sw.h>

/**
 * @brief Creates a new level object from a CID, SW, ALO, OID, and splice index.
 *
 * @param cid The CID of the LO.
 * @param csw The SW of the LO.
 * @param paloParent The ALO of the LO.
 * @param oid The OID of the LO.
 * @param isplice The splice index of the LO.
 *
 * @return Pointer to the new object.
*/
SW* PloNew(CID cid, SW* csw, ALO* paloParent, OID oid, int isplice);

/**
 * @brief Gets the level object index from a stock OID.
 *
 * @param oid The stock OID.
 *
 * @return The level object index.
*/
int IploFromStockOid(int oid);
