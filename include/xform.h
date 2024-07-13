/**
 * @file xform.h
 */
#ifndef XFORM_H
#define XFORM_H

#include "common.h"
#include <alo.h>
#include <vec.h>
#include <mat.h>
#include <oid.h>

struct XFM : public LO
{
    VECTOR posLocal;
    MATRIX3 matLocal;
};

struct PNT : public LO
{
    VECTOR posLocal;
};

struct CAMERA : public ALO
{
    OID oidTarget;
    PNT *ppntTarget;
    ALO *paloTarget;
    undefined4 unk_1;
    VECTOR posEye;
    VECTOR vecView;
    VECTOR vecUp;
    int fSetCplcy;
    undefined4 unk_2;
    undefined4 unk_3;
    undefined4 unk_4;
};

#endif // XFORM_H
