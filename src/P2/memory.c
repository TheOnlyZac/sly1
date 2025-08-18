#include <memory.h>
#include <thread.h>
#include <sce/memset.h>

extern int g_swAllocBase;
extern int g_swAllocPtr;
extern int g_stackAllocPtr;
extern CRITSECT g_stackAllocCritSect;
extern int g_stackAllocDepth;
extern int g_stackAllocStack[];

INCLUDE_ASM(const s32, "P2/memory", PvAllocGlobalImpl__Fi);
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

/**
 * @todo 99.50% matching. Only a register mismatch.
 * https://decomp.me/scratch/It1kw
 */
INCLUDE_ASM(const s32, "P2/memory", PvAllocSwImpl__Fi);
#ifdef SKIP_ASM
void *PvAllocSwImpl(int cb)
{
    if(cb == 0)
    {
        return nullptr;
    }
    
    CheckForOutOfMemory();
    g_swAllocPtr += (cb + 0x0f) & -0x10;
    return (void *)g_swAllocPtr;
}
#endif

void FreeSw()
{
    g_swAllocPtr = g_swAllocBase;
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
    EnterCritSect(&g_stackAllocCritSect);
    g_stackAllocStack[++g_stackAllocDepth] = g_stackAllocPtr;
}

void *PvAllocStackImpl(int cb)
{
    if(cb == 0)
    {
        return nullptr;
    }
    
    CheckForOutOfMemory();
    g_stackAllocPtr -= (cb + 0x0f) & -0x10;
    return (void *)g_stackAllocPtr;
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
    g_stackAllocPtr = g_stackAllocStack[g_stackAllocDepth--];
    LeaveCritSect(&g_stackAllocCritSect);
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

INCLUDE_ASM(const s32, "P2/memory", CopyAqw__FPvT0i);

INCLUDE_ASM(const s32, "P2/memory", CopyAb__FPvT0Ui);
