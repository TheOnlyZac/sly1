/**
 * @file xform.h
 */
#ifndef XFORM_H
#define XFORM_H

#include "common.h"
#include <lo.h>
#include <vec.h>
#include <mat.h>

struct XFM : public LO
{
    VECTOR posLocal;
    MATRIX3 matLocal;
};

#endif // XFORM_H
