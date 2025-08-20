#include <memory.h>
#include <thread.h>
#include <sce/memset.h>

/**
 * @todo Change these to static when possible.
 */
extern int s_pvGlobalMac;
extern int s_pvWorldMin;
extern int s_pvWorldMac;
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
    
    void *pv = (void *)s_pvGlobalMac;
    s_pvGlobalMac += (cb + 0x0f) & -0x10;
    s_pvWorldMin = s_pvWorldMac = s_pvGlobalMac;
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
    void *pvSw = (void *)s_pvWorldMac;
    s_pvWorldMac += (cb + 0x0f) & -0x10;
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

void CopyAqw(void *pvDst, void *pvSrc, int cqw)
{
    u128 *dst = (u128 *)pvDst;
    u128 *src = (u128 *)pvSrc;
    
    int remainder = cqw & 0x03;
    int nQWords = cqw - remainder;
    
    int processed = 0;
    while(processed < remainder)
    {
        *dst++ = *src++;
        processed++;
    }
    
    processed = 0;
    while(processed < nQWords)
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
        
        processed += 4;
    }
}

void CopyAb(void *pvDst, void *pvSrc, uint cb)
{
    // Do a byte copy, if not word aligned.
    if(((uint)pvDst | (uint)pvSrc | cb) & 0x03)
    {
        u8 *dst = (u8 *)pvDst;
        u8 *src = (u8 *)pvSrc;
        for(uint i = 0; i < cb; i++)
        {
            *dst++ = *src++;
        }
        
        return;
    }
    
    // Copy 4 uints at a time, if aligned properly.
    if(((uint)pvDst | (uint)pvSrc | cb) & 0x0f)
    {
        uint *dst = (uint *)pvDst;
        uint *src = (uint *)pvSrc;
        
        int remainder = (cb >> 2) & 0x03;
        int nWords = (cb >> 2) - remainder;
        
        int processed = 0;
        while(processed < remainder)
        {
            *dst++ = *src++;
            processed++;
        }
        
        // TODO: This part might be possible to clean up,
        // but I wasn't able to. -545u
        processed = 0;
        while(processed < nWords)
        {
            uint w0 = src[0];
            uint w1 = src[1];
            uint w2 = src[2];
            uint w3 = src[3];
            src += 4;
            
            dst[0] = w0;
            dst[1] = w1;
            dst[2] = w2;
            dst[3] = w3;
            dst += 4;
            
            processed += 4;
        }
        
        return;
    }
    
    // Use CopyAqw, if fully 16-byte aligned.
    CopyAqw(pvDst, pvSrc, cb >> 4);
}