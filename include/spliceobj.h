/**
 * @file spliceobj.h
 *
 * @brief Splice objects.
 */
#ifndef SPLICEOBJ_H
#define SPLICEOBJ_H

#include "common.h"
#include <splice/ref.h>
#include <basic.h>
#include <brx.h>

typedef void (*PFNGET)(OTYP);

EOPID *PeopidFind(BASIC *pbasic, int optid);

CRef RefGetObjectList(BASIC *pbasic, OTYP otyp, PFNGET pfnget);

CRef RefGetPeopid(BASIC *pbasic, EOPID *peopid);

int FAppendSpliceListElement(void *pvstate, void *pvdata);

int FSpliceListElementExists(void *pvstate, void *pvdata);

CRef RefSetPvsFromSplice(int cref, CRef *aref, OTYP *aotyp, void **apv);

CRef RefSetArgListFromPvs(int cargs, OTYP *aotyp, void **apv);

CRef RefSetPeopid(BASIC *pbasic, EOPID *peopid, CRef *prefValue);

CRef RefGetOption(BASIC *pbasic, int optid);

CRef RefSetOption(BASIC *pbasic, int optid, CRef *prefValue);

CRef RefAddOption(BASIC *pbasic, int optid, CRef *prefValue);

CRef RefEnsureOption(BASIC *pbasic, int optid, CRef *prefValue);

CRef RefSetArgsFromSplice(int cref, CRef *aref, OTYP *aotyp);

#endif // SPLICEOBJ_H
