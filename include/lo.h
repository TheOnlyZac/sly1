/**
 * @file lo.h
 *
 * @brief Level objects.
 */
#ifndef LO_H
#define LO_H

#include "common.h"
#include <basic.h>
#include <dl.h>
#include <sw.h>
#include <alo.h>
#include <splice/frame.h>

// todo Find where this struct should be implemented.
struct MQ;

enum OID
{
	OID_Unknown = 0x0,
	OID__MERGED_STATICS = 0x1,
	OID__VISIBILITY_MAP = 0x2,
	OID__WORLD = 0x3,
	OID__CAMERA = 0x4,
	OID_jt = 0x5,
	OID_bentley = 0x6,
	OID_murray = 0x7,

    // ...

    OID_rat = 0x269

    // ...
};

struct LO : public BASIC
{
    OID oid;
    DLE dleOid;
    SW *psw;
    ALO *paloParent;
    DLE dleChild;
    LO *ploCidNext;
    MQ *pmqFirst;
    char *pchzName;
    CFrame *pframe;
    ulong dtickPerf;
};

#endif // LO_H
