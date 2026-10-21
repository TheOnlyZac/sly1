#include <eyes.h>
#include <shdanim.h>

void InitEyes(EYES *peyes, SAAF *psaaf)
{
    InitSaa(peyes, psaaf);
    peyes->saiOther.grfsai = peyes->sai.grfsai;
    peyes->oidOther = (OID)psaaf->eyesf.oidOther;
    peyes->dtBlink = psaaf->eyesf.dtBlink;
    peyes->dtOpenMin = psaaf->eyesf.dtOpenMin;
    peyes->dtOpenMax = psaaf->eyesf.dtOpenMax;
    peyes->uDoubleBlink = psaaf->eyesf.uDoubleBlink;
}

void PostEyesLoad(EYES *peyes)
{
    PostSaaLoad(peyes);

    peyes->saiOther.pshd = PshdFindShader(peyes->oidOther);
    if (peyes->saiOther.pshd && !peyes->saiOther.pshd->psaa && peyes->sai.pshd->psaa == peyes)
    {
        peyes->saiOther.pshd->psaa = peyes;
    }

    int cframe = peyes->sai.pshd ? peyes->sai.pshd->cframe : 0;
    int cframeOther = peyes->saiOther.pshd ? peyes->saiOther.pshd->cframe : 0;
    if (cframe <= cframeOther)
    {
        cframe = cframeOther;
    }

    peyes->eyess = EYESS_Nil;
    peyes->cframe = cframe;
    SetEyesEyess(peyes, EYESS_Open);
}

void SetEyesEyess(EYES *peyes, EYESS eyess)
{
    if (peyes->eyess == eyess)
    {
        return;
    }

    switch (eyess)
    {
        case EYESS_Open:
        {
            peyes->gframe = (float)(peyes->cframe - 1) * peyes->uClosed;
            peyes->sviframe = ((float)(peyes->cframe * 2) * (1.0f - peyes->uClosed)) / peyes->dtBlink;

            if (peyes->uDoubleBlink > GRandInRange(0.0f, 1.0f))
            {
                peyes->dtOpen = 0.0f;
            }
            else
            {
                peyes->dtOpen = GRandInRange(peyes->dtOpenMin, peyes->dtOpenMax);
            }
            break;
        }
        case EYESS_Closing:
        {
            break;
        }
        case EYESS_Closed:
        {
            int cframe = peyes->cframe - 1;
            if ((int)peyes->gframe != cframe)
            {
                peyes->gframe = (float)cframe;
            }
            break;
        }
    }

    peyes->eyess = eyess;
    peyes->tEyess = g_clock.t;
}

void UpdateEyes(EYES *peyes, float dt)
{
    if (peyes->cframe <= 1)
    {
        return;
    }

    EYESS eyess = peyes->eyess;
    switch (eyess)
    {
        case EYESS_Open:
        {
            if (peyes->dtOpen <= g_clock.t - peyes->tEyess)
            {
                eyess = EYESS_Closing;
            }
            break;
        }
        case EYESS_Closing:
        {
            peyes->gframe += peyes->sviframe * dt;

            if (peyes->cframe <= peyes->gframe)
            {
                peyes->gframe -= peyes->sviframe * dt;
                eyess = ((int)peyes->gframe == peyes->cframe - 1) ? EYESS_Closed : EYESS_Opening;
            }
            break;
        }
        case EYESS_Closed:
        {
            if (peyes->uClosed < 1.0f)
            {
                eyess = EYESS_Opening;
            }
            break;
        }
        case EYESS_Opening:
        {
            peyes->gframe -= peyes->sviframe * dt;

            if (peyes->gframe <= (float)peyes->cframe * peyes->uClosed)
            {
                eyess = EYESS_Open;
            }
            break;
        }
    }

    SetEyesEyess(peyes, eyess);
    SetSaiIframe(&peyes->sai, (int)peyes->gframe);
    SetSaiIframe(&peyes->saiOther, (int)peyes->gframe);
}

void SetEyesClosed(EYES *peyes, float uClosed)
{
    peyes->uClosed = uClosed;

    if (uClosed >= 1.0f)
    {
        SetEyesEyess(peyes, EYESS_Closed);
    }
    else
    {
        peyes->eyess = EYESS_Nil;
        SetEyesEyess(peyes, EYESS_Open);
    }

    SetSaiIframe(&peyes->sai, (int)peyes->gframe);
    SetSaiIframe(&peyes->saiOther, (int)peyes->gframe);
}

SAI *PsaiFromEyesShd(EYES *peyes, SHD *pshd)
{
    SAI *psai = PsaiFromSaaShd(peyes, pshd);
    if (!psai)
    {
        psai = &peyes->saiOther;
        if (pshd->oid != peyes->oidOther)
        {
            psai = NULL;
        }
    }

    return psai;
}
