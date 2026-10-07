#include <fader.h>
#include <alo.h>
#include <sw.h>

void UpdateFader(FADER *pfader, float dt)
{
    if (pfader->duAlpha != 0.0f && !FIsLoInWorld(pfader->palo))
    {
        RemoveFader(pfader);
        return;
    }

    float uAlphaPrev = pfader->uAlpha;
    pfader->uAlpha += pfader->duAlpha * dt;

    if (pfader->uAlpha <= 0.0f && uAlphaPrev > 0.0f)
    {
        pfader->palo->pvtlo->pfnRemoveLo(pfader->palo);
        RemoveFader(pfader);
    }
    else if (pfader->uAlpha >= 1.0f && uAlphaPrev < 1.0f)
    {
        RemoveFader(pfader);
    }
}

FADER *PfaderNew(ALO *palo)
{
    FADER *pfader = (FADER *)PvAllocSlotheapClearImpl(&g_psw->slotheapFader);
    pfader->palo = palo;

    if (palo->fRealClock != 0)
    {
        AppendDlEntry(&g_psw->dlRealClockFader, pfader);
    }
    else
    {
        AppendDlEntry(&g_psw->dlFader, pfader);
    }

    return pfader;
}

void RemoveFader(FADER *pfader)
{
    if (pfader->palo->fRealClock != 0)
    {
        RemoveDlEntry(&g_psw->dlRealClockFader, pfader);
    }
    else
    {
        RemoveDlEntry(&g_psw->dlFader, pfader);
    }

    pfader->palo->pfader = NULL;
    FreeSlotheapPv(&g_psw->slotheapFader, pfader);
}
