/**
 * @file find.h
 *
 * @brief Find objects in the SW.
 */
#ifndef FIND_H
#define FIND_H

#include "common.h"
#include <alo.h>
#include <sw.h>
#include <cid.h>
#include <so.h>

/**
 * @brief Gets the DL for the SW object with the given OID.
 *
 * @param psw The SW object.
 * @param oid The OID of the object.
 *
 * @return The DL for the object, or NULL if the object was not found.
 */
DL *PdlFromSwOid(SW *psw, OID oid);

void MatchSwObject(LO *ploMatch, int grffsoMask, int fIncludeRemoved, int fProxyMatch, LO *ploContext, int cploMax, int *pcploMatch, LO **aplo, int *pcpaloBest);

int CploFindSwObjects(SW *psw, int grffso, OID oid, LO *ploContext, int cploMax, LO **aplo);

LO *PloFindSwObject(SW *psw, int grffso, OID oid, LO *ploContext);

LO *PloFindSwNearest(SW *psw, OID oid, LO *ploContext);

LO *PloFindSwChild(SW *psw, OID oid, ALO *paloAncestor);

/**
 * @brief Checks if the given CID is derived from another.
 *
 * @param cid The CID to check.
 * @param cidAncestor The CID to check against.
 *
 * @retval 1 if the CID is derived from the ancestor.
 * @retval 0 if the CID is not derived from the ancestor.
 */
int FIsCidDerivedFrom(int cid, int cidAncestor);

int CploFindSwObjectsByClass(SW *psw, int grffso, CID cid, LO *ploContext, int cploMax, LO **aplo);

LO *PloFindSwObjectByClass(SW *psw, int grffso, CID cid, LO *ploContext);

/**
 * @brief Finds the common parent of two LOs.
 *
 * @param plo The first LO.
 * @param ploOther The second LO.
 *
 * @return The common parent of the two LOs.
 */
ALO *PaloFindLoCommonParent(LO *plo, LO *ploOther);

extern void** g_mpcidpvt;

#endif // FIND_H
