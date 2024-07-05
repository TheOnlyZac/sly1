/**
 * @file xform.h
 *
 * @brief Transform.
 */
#ifndef XFORM_H
#define XFORM_H

#include "common.h"
#include <alo.h>
#include <vec.h>
#include <mat.h>
#include <dl.h>

// Forward declarations
struct XFM;
struct EXPL;
struct EXPLG;
struct EXPLO;
struct EXPLS;
struct EXPLSO;
struct EXPLSTE;
struct TARGET;
struct PNT;
struct CAMERA;

/**
 * @brief Transform.
 */
struct XFM : public LO
{
    VECTOR posLocal;
    MATRIX3 matLocal;
};

struct EXPL : public XFM
{
    // ...
};

struct EXPLG : public EXPL
{
    // ...
};

struct EXPLO : public EXPL
{
    // ...
};

struct EXPLS : public EXPLO
{
    // ...
};

struct EXPLSO
{
    // ...
};

struct EXPLSTE
{
    // ...
};

struct TARGET : public XFM
{
    DLE dleTarget;
    int grftak;
    float sRadiusTarget;
    int fHitTest;
    undefined4 unk0;
    undefined4 unk1;
    undefined4 unk2;
};

/**
 * @brief Point.
 */
struct PNT : public LO
{
    VECTOR posLocal;
};

/**
 * @brief Camera.
 *
 * @note Not the same as the game camera CM. More research needed.
 * Might be in the wrong header.
 */
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
