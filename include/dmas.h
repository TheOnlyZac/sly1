/**
 * @file dmas.h
 *
 * @brief Direct memory access.
 */
#ifndef DMAS_H
#define DMAS_H

#include <sce/libdma.h>
#include <sdk/ee/eekernel.h>
#include "common.h"
#include <shd.h>

extern sceDmaChan *g_pdcVif0;
extern sceDmaChan *g_pdcVif1;
extern sceDmaChan *g_pdcGif;
extern sceDmaChan *g_pdcFromSpr;
extern sceDmaChan *g_pdcToSpr;

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
