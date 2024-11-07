/**
 * @file splice/proc.h
 */
#ifndef SPLICE_PROC_H
#define SPLICE_PROC_H

#include "common.h"

class CFrame;
class CPair;

/**
 * @class CProc
 *
 * @todo Fill in class.
 */
class CProc
{
private:
    CFrame* m_pframe;
    CPair* m_ppair;
    int m_crefReq;
    int m_fVarArg;
    CPair* m_ppairCodeExpr;

public:
    void CloneTo(CProc* pprocClone, CFrame* pframeClone);
};

static CProc* PprocNew(void);

#endif // SPLICE_PROC_H
