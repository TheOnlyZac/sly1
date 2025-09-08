/**
 * @file dmas.h
 *
 * @brief Direct memory access.
 */
#ifndef DMAS_H
#define DMAS_H

#include "common.h"
#include <sce/libdma.h>
#include <sdk/ee/eekernel.h>
#include <vec.h>

extern sceDmaChan *g_pdcVif0;
extern sceDmaChan *g_pdcVif1;
extern sceDmaChan *g_pdcGif;
extern sceDmaChan *g_pdcFromSpr;
extern sceDmaChan *g_pdcToSpr;

/**
 * @brief Union for 16-byte aligned data.
 */
union QW
{
    VECTOR vec;
    VECTOR4 vec4;
    ulong ull;
    ulong aul[2];
    uint aun[4];
    ushort aus[8];
    uchar ab[16];
    long ll;
    long al[2];
    int an[4];
    short as[8];
    float ag[4];
};

class DMAS
{
public:
    uchar* m_pbMax;
    uchar* m_ab;
    QW* m_pqwCnt;
    uchar* m_pb;
    int m_fPad;
    int m_fEndPrim;
    //byte padding[0x450];

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

void StartupDma();

#endif // DMAS_H
