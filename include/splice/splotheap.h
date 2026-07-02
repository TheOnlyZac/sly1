/**
 * @file splice/splotheap.h
 */
#ifndef SPLICE_SPLOTHEAP_H
#define SPLICE_SPLOTHEAP_H

#include "common.h"

typedef void (*PFNDELETE)(void *);

struct SPLOT
{
    SPLOT *psplotNext;
    int fAlive;
};

class CSplotheap
{
private:
    int m_cb;
    int m_c;
    byte *m_ab;
    SPLOT *m_psplotFree;
    SPLOT *m_psplotAlloc;
    SPLOT *m_psplotRecyclable;

public:
    PFNDELETE m_pfndelete;

    void Startup(int cb, int c);
    void Shutdown();
    void *PvAllocUnsafe();
    void *PvAllocClear();
    SPLOT *PsplotLookup(int i);
    void UpdateRecyclable();
    void UnmarkAll();
    void FreeGarbage();
};

extern CSplotheap g_splotheapPair;
extern CSplotheap g_splotheapFrame;
extern CSplotheap g_splotheapUnk1;
extern CSplotheap g_splotheapProc;
extern CSplotheap g_splotheapMethod;

// Sidebag binding-node helpers: allocate a node {int n; CRef ref; pNext}
// from g_splotheapUnk1, and recursively clone a node list.
class CFrame;
void *FUN_0011C498();
void FUN_0011C418(void *psbbFrom, void *psbbTo, CFrame *pframe);

static void *PvFromPsplot(SPLOT *psplot);
static SPLOT *PsplotFromPv(void *pv);
bool FIsPvGarbage(void *pv);
void MarkPvAlive(void *pv);

#endif // SPLICE_SPLOTHEAP_H
