#include <memory.h>
#include <thread.h>
#include <sce/memset.h>

/**
 * @todo Change these to static when possible.
 */
extern void *s_pvGlobalMin;
extern void *s_pvGlobalMac;
extern void *s_pvWorldMin;
extern void *s_pvWorldMac;
extern void *s_pvStackMin;
extern void *s_pvStackMac;
extern CRITSECT s_critsectStack;
extern int s_ipvStackCur;
extern void *s_apvStackMin[50];

extern void *g_pvHeapMin;
extern void *g_pvHeapMax;
extern int D_0064C70F;

void StartupMemMgr()
{
    void *end = (void *)((int)&D_0064C70F & ~0x0f);

    g_pvHeapMin = end;
    g_pvHeapMax = (void *)0x02000000;

    s_pvGlobalMin = s_pvGlobalMac = s_pvWorldMin = s_pvWorldMac = end;

    s_pvStackMin = s_pvStackMac = (void *)0x02000000;
    s_ipvStackCur = -1;

    InitCritSect(&s_critsectStack);
}

void *PvAllocGlobalImpl(int cb)
{
    if (cb == 0)
    {
        return 0;
    }

    void *pv = (void *)s_pvGlobalMac;
    (byte *)s_pvGlobalMac += (cb + 0x0f) & -0x10;
    s_pvWorldMin = s_pvWorldMac = s_pvGlobalMac;
    return pv;
}

JUNK_NOP();
JUNK_WORD(0xACC20004);

#ifdef DEBUG
/**
 * @todo Implement debugging function (low-priority).
 */
void HardLockError()
{
}
#endif

void CheckForOutOfMemory()
{
    return;
}

void *PvAllocSwImpl(int cb)
{
    if (cb == 0)
    {
        return NULL;
    }

    CheckForOutOfMemory();
    void *pvSw = (void *)s_pvWorldMac;
    (byte *)s_pvWorldMac += (cb + 0x0f) & -0x10;
    return pvSw;
}

void FreeSw()
{
    s_pvWorldMac = s_pvWorldMin;
}

void *PvAllocSwCopyImpl(int cb, void *pvBase)
{
    void *pvDst = PvAllocSwImpl(cb);
    if (pvDst)
    {
        CopyAb(pvDst, pvBase, cb);
    }

    return pvDst;
}

void *PvAllocSwClearImpl(int cb)
{
    void *pvBlock = PvAllocSwImpl(cb);
    if (pvBlock)
    {
        memset(pvBlock, 0, cb);
    }

    return pvBlock;
}

void InitStackImpl()
{
    EnterCritSect(&s_critsectStack);
    s_apvStackMin[++s_ipvStackCur] = s_pvStackMin;
}

void *PvAllocStackImpl(int cb)
{
    if (cb == 0)
    {
        return NULL;
    }

    CheckForOutOfMemory();
    (byte *)s_pvStackMin -= (cb + 0x0f) & -0x10;
    return (void *)s_pvStackMin;
}

void *PvAllocStackClearImpl(int cb)
{
    void *pvBlock = PvAllocStackImpl(cb);
    if (pvBlock)
    {
        memset(pvBlock, 0, cb);
    }

    return pvBlock;
}

void FreeStackImpl()
{
    s_pvStackMin = s_apvStackMin[s_ipvStackCur--];
    LeaveCritSect(&s_critsectStack);
}

void *malloc(uint __size)
{
    return NULL;
}

void *_malloc_r(_reent *pre, uint __size)
{
    return NULL;
}

void free(void *pv)
{
    return;
}

void *__builtin_new(unsigned int cb)
{
    return PvAllocSwClearImpl(cb);
}

void __builtin_delete()
{
    return;
}

void CopyAqw(void *pvDst, void *pvSrc, int cqw)
{
    qword *pqwdst = (qword *)pvDst;
    qword *pqwsrc = (qword *)pvSrc;

    int cRemain = cqw & 0x03;
    int cBulk = cqw - cRemain;

    int i = 0;
    for (; i < cRemain; i++)
    {
        *pqwdst++ = *pqwsrc++;
    }

    i = 0;
    for (; i < cBulk; i += 4)
    {
        qword qw0 = pqwsrc[0];
        qword qw1 = pqwsrc[1];
        qword qw2 = pqwsrc[2];
        qword qw3 = pqwsrc[3];
        pqwsrc += 4;

        pqwdst[0] = qw0;
        pqwdst[1] = qw1;
        pqwdst[2] = qw2;
        pqwdst[3] = qw3;
        pqwdst += 4;
    }
}

void CopyAb(void *pvDst, void *pvSrc, uint cb)
{
    // Do a byte copy, if not word aligned.
    if (((uint)pvDst | (uint)pvSrc | cb) & 0x03)
    {
        uchar *pbDst = (uchar *)pvDst;
        uchar *pbSrc = (uchar *)pvSrc;
        for (uint i = 0; i < cb; i++)
        {
            *pbDst++ = *pbSrc++;
        }

        return;
    }

    // Copy 4 uints at a time, if aligned properly.
    if (((uint)pvDst | (uint)pvSrc | cb) & 0x0f)
    {
        uint *puDst = (uint *)pvDst;
        uint *puSrc = (uint *)pvSrc;

        int cRemain = (cb / sizeof(uint)) & 0x03;
        int cBluk = (cb / sizeof(uint)) - cRemain;

        int i = 0;
        for (; i < cRemain; i++)
        {
            *puDst++ = *puSrc++;
        }

        i = 0;
        for (; i < cBluk; i += 4)
        {
            uint w0 = puSrc[0];
            uint w1 = puSrc[1];
            uint w2 = puSrc[2];
            uint w3 = puSrc[3];
            puSrc += 4;

            puDst[0] = w0;
            puDst[1] = w1;
            puDst[2] = w2;
            puDst[3] = w3;
            puDst += 4;
        }

        return;
    }

    // Use CopyAqw, if fully 16-byte aligned.
    CopyAqw(pvDst, pvSrc, cb >> 4);
}
