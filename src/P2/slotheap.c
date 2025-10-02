#include <slotheap.h>
#include <memory.h>
#include <sce/memset.h>

void _InitSlotheap(SLOTHEAP *pslotheap, int cb, int c)
{
    byte *pbBase = pslotheap->ab;
    pslotheap->cb = cb;
    pslotheap->pslotFree = (SLOT *)pbBase;

    for (int i = 1; i < c; i++)
    {
        SLOT *pslotPrev = (SLOT *)pbBase;
        pbBase = &pslotheap->ab[i * pslotheap->cb];
        pslotPrev->pslotNext = (SLOT *)pbBase;
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

JUNK_NOP();
JUNK_ADDIU(40);

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
    if (!pv)
    {
        return;
    }

    SLOT *pslot = (SLOT *)pv;
    pslot->pslotNext = pslotheap->pslotFree;
    pslotheap->pslotFree = pslot;
}

JUNK_NOP();
JUNK_WORD(0x00E0102D);
