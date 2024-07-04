/**
 * @file lo.h
 *
 * @brief Level objects.
 */
#ifndef LO_H
#define LO_H

#include "common.h"
#include <oid.h>
#include <basic.h>
#include <dl.h>
#include <sw.h>
#include <splice/frame.h>
#include <mq.h>

struct ALO; // Forward declaration.

/**
 * @brief "LO"
 */
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
