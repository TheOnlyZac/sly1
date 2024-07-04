/**
 * @file dl.h
 */
#ifndef DL_H
#define DL_H

#include "common.h"
#include <oid.h>

/**
 * @brief Unknown.
 */
struct DL
{
    undefined4 unk_1;
    undefined4 unk_2;
    int ibDle;
};

/**
 * Unknown.
 */
struct DLE
{
    undefined4 unk_1;
    undefined4 unk_2;
};

/**
 * @brief Unknown.
 */
struct DLI
{
    DL *m_pdl;
    void **m_ppv;
    int m_ibDle;
    DLI *m_pdliNext;
};

/**
 * @brief Unknown.
 */
struct DLIM
{
    // ...
};

/**
 * @brief Unknown.
 */
struct DLR
{
    OID oidChild;
    DLR *pdlrNext;
};

#endif // DL_H
