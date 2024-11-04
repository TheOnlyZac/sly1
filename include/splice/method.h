/**
 * @file splice/method.h
 */
#ifndef SPLICE_METHOD_H
#define SPLICE_METHOD_H

#include "common.h"

struct BASIC;

/**
 * @class CMethod
 */
class CMethod
{
    BASIC* m_pbasic;
    void* m_pfnthunk; //todo: fix type?
    int m_crefReq;
};

static CMethod* PMethodNew();

#endif // SPLICE_METHOD_H
