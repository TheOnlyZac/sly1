#include <splice/splotheap.h>
#include <sce/memset.h>
#include <splice/gc.h>
#include <memory.h>

// Forward declarations.
static void *PvFromPsplot(SPLOT *psplot);
static SPLOT *PsplotFromPv(void *pv);

void CSplotheap::Startup(int cb, int c)
{
    m_c = c;
    m_cb = cb + 8;
    m_ab = (byte *)PvAllocSwImpl(m_cb * m_c);

    SPLOT *psplotCurr = PsplotLookup(0);
    m_psplotFree = psplotCurr;
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
#ifdef SKIP_ASM
/**
 * @todo 86.67% match.
 */
void CSplotheap::FreeGarbage()
{
    SPLOT *pSplot = m_psplotAlloc;
    SPLOT *pPrev = (SPLOT *)&m_psplotAlloc;
    SPLOT *pBoundary;

    if (pSplot)
    {
        SPLOT *pRecyclable = m_psplotRecyclable;
        pBoundary = pPrev;

        if (pSplot != pRecyclable)
        {
            pPrev = pSplot;
            pSplot = pSplot->psplotNext;

            while (pSplot && pSplot != pRecyclable)
            {
                pBoundary = pPrev;

                if (pSplot != pRecyclable)
                {
                    break;
                }

                pPrev = pSplot;
            }
        }
    }
    else
    {
        pBoundary = pPrev;
    }

    pSplot = pBoundary->psplotNext;
    while (pSplot)
    {
        if (pSplot->fAlive)
        {
            pPrev = pSplot;
            pSplot = pSplot->psplotNext;
            continue;
        }

        pPrev->psplotNext = pSplot->psplotNext;
        pSplot->psplotNext = m_psplotFree;
        m_psplotFree = pSplot;

        if (m_pfndelete)
        {
            m_pfndelete(PvFromPsplot(pSplot));
        }

        pSplot = pPrev->psplotNext;
    }

    m_psplotRecyclable = pBoundary->psplotNext;
}
#endif // SKIP_ASM

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
