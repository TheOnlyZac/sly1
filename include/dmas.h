/**
 * @file dmas.h
 */
#ifndef DMAS_H
#define DMAS_H

#include "common.h"
#include <shd.h>
#include <sce/dma.h>
#include <sce/kernel.h>

class DMAS
{
    uchar* m_pbMax;
    uchar* m_ab;
    QW* m_pqwCnt;
    uchar* m_pb;
    int m_fPad;
    int m_fEndPrim;

public:
    DMAS();

    void Clear();
    void Reset();
    void AllocGlobal(int);
    void AllocSw(int, int);
    void AllocStack(int);
    void AllocStatic(int, QW*);
    void Detach(int*, QW**);
    void DetachCopySw(int*, QW**, QW*, int);
    void Send(sceDmaChan* chan);
    void AddDmaCnt();
    void AddDmaRefs(int, QW*);
    void AddDmaCall(QW*);
    void AddDmaRet();
    void AddDmaBulk(int, QW*);
    void AddDmaEnd();
    void EndDmaCnt();

    virtual void EndPrim();
};

static void StartupDma();

#endif // DMAS_H
