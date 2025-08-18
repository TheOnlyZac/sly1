#include <memory.h>
#include <sce/memset.h>

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

void CheckForOutOfMemory() {
    return;
}

INCLUDE_ASM(const s32, "P2/memory", PvAllocSwImpl__Fi);

INCLUDE_ASM(const s32, "P2/memory", FreeSw__Fv);

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

INCLUDE_ASM(const s32, "P2/memory", InitStackImpl__Fv);

INCLUDE_ASM(const s32, "P2/memory", PvAllocStackImpl__Fi);

void *PvAllocStackClearImpl(int cb)
{
    void *pvBlock = PvAllocStackImpl(cb);
    if(pvBlock)
    {
        memset(pvBlock, 0, cb);
    }

    return pvBlock;
}

INCLUDE_ASM(const s32, "P2/memory", FreeStackImpl__Fv);

void *malloc(uint __size)
{
    return (void *)0x0;
}

void *_malloc_r(_reent *pre, uint __size)
{
    return (void *)0x0;
}

void free(void *pv) {
    return;
}

void *__builtin_new(unsigned int cb)
{
    return PvAllocSwClearImpl(cb);
}

void __builtin_delete() {
    return;
}

INCLUDE_ASM(const s32, "P2/memory", CopyAqw__FPvT0i);

INCLUDE_ASM(const s32, "P2/memory", CopyAb__FPvT0Ui);
