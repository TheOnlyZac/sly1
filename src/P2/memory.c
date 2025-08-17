#include <memory.h>
#include <sce/memset.h>

INCLUDE_ASM(const s32, "P2/memory", PvAllocGlobalImpl__Fi);

INCLUDE_ASM(const s32, "P2/memory", func_0018D4F0);

/**
 * @todo Rename function.
 */
void func_0018D4F8()
{
    return;
}

INCLUDE_ASM(const s32, "P2/memory", PvAllocSwImpl__FUi);

INCLUDE_ASM(const s32, "P2/memory", func_0018D550);

void *PvAllocSwCopyImpl(uint cb, void *pvSrc)
{
    void *pvDst = PvAllocSwImpl(cb);
    if (pvDst)
    {
        CopyAb(pvDst, pvSrc, cb);
    }
    
    return pvDst;
}

void *PvAllocSwClearImpl(uint cb)
{
    void *pvBlock = PvAllocSwImpl(cb);
    if(pvBlock)
    {
        memset(pvBlock, 0, cb);
    }
    
    return pvBlock;
}

INCLUDE_ASM(const s32, "P2/memory", func_0018D608);

INCLUDE_ASM(const s32, "P2/memory", func_0018D658);

INCLUDE_ASM(const s32, "P2/memory", func_0018D6A8);

INCLUDE_ASM(const s32, "P2/memory", func_0018D6F0);

INCLUDE_ASM(const s32, "P2/memory", func_0018D740);

INCLUDE_ASM(const s32, "P2/memory", func_0018D748);

/**
 * @todo Rename function.
 */
void func_0018D750()
{
    return;
}

/**
 * @todo Rename function.
 */
void *func_0018D758(uint cb)
{
    return PvAllocSwClearImpl(cb);
}

void __builtin_delete()
{
    return;
}

INCLUDE_ASM(const s32, "P2/memory", func_0018D780);

INCLUDE_ASM(const s32, "P2/memory", CopyAb__FPvT0Ui);
