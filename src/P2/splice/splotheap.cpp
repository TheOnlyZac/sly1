#include <splice/splotheap.h>
#include <sce/memset.h>
#include <splice/gc.h>
#include <memory.h>

/**
 * @todo 94.76% match.
 * https://decomp.me/scratch/3gv6F
 */
INCLUDE_ASM("asm/nonmatchings/P2/splice/splotheap", Startup__10CSplotheapii);
#ifdef SKIP_ASM
void CSplotheap::Startup(int cb, int c)
{
    m_c = c;
    m_cb = cb + 8;
    m_ab = (byte *)PvAllocSwImpl(m_cb * m_c);

    SPLOT *psplotCurr = PsplotLookup(0);
    for (int i = 1; i < c; i++)
    {
        SPLOT *psplotPrev = psplotCurr;
        psplotCurr = PsplotLookup(i);
        psplotPrev->psplotNext = psplotCurr;
    }

    psplotCurr->psplotNext = NULL;

    m_psplotAlloc = NULL;
    m_psplotRecyclable = NULL;
}
#endif // SKIP_ASM

void CSplotheap::Shutdown()
{
    return;
}

void *CSplotheap::PvAllocUnsafe()
{
    if (!m_psplotFree)
    {
        g_gc.Collect();
    }

    SPLOT *psplot = m_psplotFree;
    if (psplot)
    {
        m_psplotFree = psplot->psplotNext;
        psplot->psplotNext = m_psplotAlloc;
        m_psplotAlloc = psplot;
        return PvFromPsplot(psplot);
    }

    return NULL;
}

void *CSplotheap::PvAllocClear()
{
    void *pv = PvAllocUnsafe();
    memset(pv, 0, m_cb - sizeof(SPLOT));
    return pv;
}

SPLOT *CSplotheap::PsplotLookup(int i)
{
    return (SPLOT *)(m_ab + i * m_cb);
}

void CSplotheap::UpdateRecyclable()
{
    m_psplotRecyclable = m_psplotAlloc;
}

void CSplotheap::UnmarkAll()
{
    SPLOT *psplot = m_psplotAlloc;
    while (psplot)
    {
        psplot->fAlive = 0;
        psplot = psplot->psplotNext;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/splotheap", FreeGarbage__10CSplotheap);

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
    return !psplot->fAlive;
}

void MarkPvAlive(void *pv)
{
    SPLOT *psplot = PsplotFromPv(pv);
    psplot->fAlive = 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/splotheap", FUN_0011C418__FPvT0P6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/splotheap", FUN_0011C498__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/splice/splotheap", FUN_0011C4E8);
