#include <slotheap.h>
#include <memory.h>
#include <sce/memset.h>

void _InitSlotheap(SLOTHEAP *pslotheap, int cb, int c)
{
    byte *pbBase = pslotheap->ab;
    pslotheap->cb = cb;
    pslotheap->pslotFree = (SLOT *)pbBase;

    int i = 1;
    while (i < c)
    {
        SLOT *pslotPrev = (SLOT *)pbBase;
        pbBase = &pslotheap->ab[i * pslotheap->cb];
        pslotPrev->pslotNext = (SLOT *)pbBase;
        i++;
    }

    ((SLOT *)pbBase)->pslotNext = (SLOT *)nullptr;
}

void CreateSlotheapSw(SLOTHEAP *pslotheap, int cb, int c)
{
    cb = (cb + 7) & -8;
    pslotheap->ab = (byte *)PvAllocSwImpl(cb * c);
    _InitSlotheap(pslotheap, cb, c);
}

void CreateSlotheapSwAlign64(SLOTHEAP *pslotheap, int cb, int c)
{
    byte *pb = (byte *)PvAllocSwImpl(cb * c + 0x30);
    pslotheap->ab = (byte *)(((int)pb + 0x3f) & -0x40);
    _InitSlotheap(pslotheap, cb, c);
}

INCLUDE_ASM("asm/nonmatchings/P2/slotheap", junk_001B5E98);

void *PvAllocSlotheapUnsafe(SLOTHEAP *pslotheap)
{
    SLOT *pslotFree = pslotheap->pslotFree;
    if (pslotFree)
    {
        pslotheap->pslotFree = pslotFree->pslotNext;
    }

    return pslotFree;
}

void *PvAllocSlotheapImpl(SLOTHEAP *pslotheap)
{
    return PvAllocSlotheapUnsafe(pslotheap);
}

void *PvAllocSlotheapClearImpl(SLOTHEAP *pslotheap)
{
    void *pv = PvAllocSlotheapUnsafe(pslotheap);
    memset(pv, 0, pslotheap->cb);
    return pv;
}

void FreeSlotheapPv(SLOTHEAP *pslotheap, void *pv)
{
    if (pv)
    {
        SLOT *pslot = (SLOT *)pv;
        pslot->pslotNext = pslotheap->pslotFree;
        pslotheap->pslotFree = pslot;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/slotheap", junk_001B5F48);
