#include <splice/splotheap.h>

INCLUDE_ASM(const s32, "P2/splice/splotheap", Startup__10CSplotheapii);

void CSplotheap::Shutdown()
{
    return;
}

INCLUDE_ASM(const s32, "P2/splice/splotheap", PvAllocUnsafe__10CSplotheap);

INCLUDE_ASM(const s32, "P2/splice/splotheap", PvAllocClear__10CSplotheap);

INCLUDE_ASM(const s32, "P2/splice/splotheap", PsplotLookup__10CSplotheapi);

void CSplotheap::UpdateRecyclable()
{
    m_psplotRecyclable = m_psplotAlloc;
}

void CSplotheap::UnmarkAll()
{
    SPLOT *psplot = m_psplotAlloc;
    while (psplot != nullptr)
    {
        psplot->fAlive = 0;
        psplot = psplot->psplotNext;
    }
}

INCLUDE_ASM(const s32, "P2/splice/splotheap", FreeGarbage__10CSplotheap);

static void *PvFromPsplot(SPLOT *psplot)
{
    return (byte *)psplot + sizeof(SPLOT);
}

static SPLOT *PsplotFromPv(void *pv)
{
    return (SPLOT *)((byte *)pv - sizeof(SPLOT));
}

bool FIsPvGarbage(void *pv)
{
    SPLOT *psplot = PsplotFromPv(pv);
    return psplot->fAlive == 0;
}

void MarkPvAlive(void *pv)
{
    SPLOT *psplot = PsplotFromPv(pv);
    psplot->fAlive = 1;
}

INCLUDE_ASM(const s32, "P2/splice/splotheap", func_0011C418);

INCLUDE_ASM(const s32, "P2/splice/splotheap", func_0011C498);

INCLUDE_ASM(const s32, "P2/splice/splotheap", func_0011C4E8);
