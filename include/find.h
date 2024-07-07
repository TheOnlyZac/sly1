/**
 * @file find.h
 */
#ifndef FIND_H
#define FIND_H

#include "common.h"
#include <alo.h>
#include <sw.h>
#include <cid.h>

DL *PdlFromSwOid(SW *psw, OID oid);

void MatchSwObject(LO *ploMatch, int grffsoMask, int fIncludeRemoved, int fProxyMatch, LO *ploContext, int cploMax, int *pcploMatch, LO **aplo, int *pcpaloBest);

int CploFindSwObjects(SW *psw, int grffso, OID oid, LO *ploContext, int cploMax, LO **aplo);

LO *PloFindSwObject(SW *psw, int grffso, OID oid, LO *ploContext);

LO *PloFindSwNearest(SW *psw, OID oid, LO *ploContext);

LO *PloFindSwChild(SW *psw, OID oid, ALO *paloAncestor);

int FIsCidDerivedFrom(int cid, int cidAncestor);

int CploFindSwObjectsByClass(SW *psw, int grffso, CID cid, LO *ploContext, int cploMax, LO **aplo);

LO *PloFindSwObjectByClass(SW *psw, int grffso, CID cid, LO *ploContext);

ALO *PaloFindLoCommonParent(LO *plo, LO *ploOther);

#endif // FIND_H
