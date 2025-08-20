#include <memory.h>
#include <thread.h>
#include <sce/memset.h>

/**
 * @todo Change these to static when possible.
 */
extern int s_pvGlobalMax;
extern int s_pvWorldMin;
extern int s_pvWorldMax;
extern int s_pvStackMin;
extern CRITSECT s_critsectStack;
extern int s_ipvStackCur;
extern int s_apvStackMin[];

void *PvAllocGlobalImpl(int cb)
{
    if(cb == 0)
    {
        return 0;
    }
    
    void *pv = (void *)s_pvGlobalMax;
    s_pvGlobalMax += (cb + 0x0f) & -0x10;
    s_pvWorldMin = s_pvWorldMax = s_pvGlobalMax;
    return pv;
}

INCLUDE_ASM(const s32, "P2/memory", LAB_0018D4F0);

#ifdef PROTO
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
    if(cb == 0)
    {
        return nullptr;
    }

    CheckForOutOfMemory();
    void *pvSw = (void *)s_pvWorldMax;
    s_pvWorldMax += (cb + 0x0f) & -0x10;
    return pvSw;
}

void FreeSw()
{
    s_pvWorldMax = s_pvWorldMin;
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
    if(pvBlock)
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
    if(cb == 0)
    {
        return nullptr;
    }

    CheckForOutOfMemory();
    s_pvStackMin -= (cb + 0x0f) & -0x10;
    return (void *)s_pvStackMin;
}

void *PvAllocStackClearImpl(int cb)
{
    void *pvBlock = PvAllocStackImpl(cb);
    if(pvBlock)
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
    return (void *)0x0;
}

void *_malloc_r(_reent *pre, uint __size)
{
    return (void *)0x0;
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

/**
 * @todo 99.35% matching. Incorrect registers.
 * https://decomp.me/scratch/6YrJZ
 */
INCLUDE_ASM(const s32, "P2/memory", CopyAqw__FPvT0i);
#ifdef SKIP_ASM
void CopyAqw(void *pvDst, void *pvSrc, int cqw)
{
    int remainder = cqw & 0x03;
    int bulkCount = cqw - remainder;

    u128 *dst = (u128 *)pvDst;
    u128 *src = (u128 *)pvSrc;

    for(int i = 0; i < remainder; i++)
    {
        *dst++ = *src++;
    }

    for(int i = 0; i < bulkCount; i += 4)
    {
        u128 qw0 = src[0];
        u128 qw1 = src[1];
        u128 qw2 = src[2];
        u128 qw3 = src[3];
        src += 4;

        dst[0] = qw0;
        dst[1] = qw1;
        dst[2] = qw2;
        dst[3] = qw3;
        dst += 4;
    }
}
#endif

INCLUDE_ASM(const s32, "P2/memory", CopyAb__FPvT0Ui);
