/**
 * @file splice/method.h
 */
#ifndef SPLICE_METHOD_H
#define SPLICE_METHOD_H

#include "common.h"

struct BASIC;
class CRef;

/**
 * @class CMethod
 */
class CMethod
{
public:
    BASIC *m_pbasic;
    CRef (*m_pfnthunk)(BASIC *, int, CRef *);
    int m_crefReq;
};

CMethod* PmethodNew();

#endif // SPLICE_METHOD_H
