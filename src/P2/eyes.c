#include <eyes.h>
#include <shdanim.h>
#include <shd.h>
#include <util.h>

void InitEyes(EYES *peyes, SAAF *psaaf)
{
    InitSaa(peyes, psaaf);
    peyes->unk2 = STRUCT_OFFSET(peyes, 0x10, int);
    peyes->oid = (OID)*(short *)&psaaf->dframe;
    *(float *)&peyes->unk[0] = psaaf->dtLoopMin;
    *(float *)&peyes->unk[1] = psaaf->dtLoopMax;
    *(float *)&peyes->unk[2] = psaaf->dtPauseMin;
    *(float *)&peyes->unk[3] = psaaf->dtPauseMax;
}

void PostEyesLoad(EYES *peyes)
{
    SHD *pshd;
    int sCur;
    int sShd;

    PostSaaLoad((SAA *)peyes);

    pshd = PshdFindShader(peyes->oid);
    peyes->pshd = pshd;
    if (pshd != NULL)
    {
        if (STRUCT_OFFSET(pshd, 0x24, SAA *) == NULL)
        {
            if (STRUCT_OFFSET(peyes->sai.pshd, 0x24, SAA *) == (SAA *)peyes)
            {
                STRUCT_OFFSET(pshd, 0x24, SAA *) = (SAA *)peyes;
            }
        }
    }

    sCur = 0;
    if (peyes->sai.pshd != NULL)
    {
        sCur = STRUCT_OFFSET(peyes->sai.pshd, 0x20, int);
    }
    sShd = 0;
    if (peyes->pshd != NULL)
    {
        sShd = STRUCT_OFFSET(peyes->pshd, 0x20, int);
    }

    peyes->eyess = EYESS_Nil;
    STRUCT_OFFSET(peyes, 0x5C, int) = (sShd < sCur) ? sCur : sShd;
    SetEyesEyess(peyes, EYESS_Open);
}

void SetEyesEyess(EYES *peyes, EYESS eyess)
{
    if (peyes->eyess == eyess)
        return;

    switch (eyess)
    {
    case EYESS_Open:
    {
        int c = STRUCT_OFFSET(peyes, 0x5C, int);
        STRUCT_OFFSET(peyes, 0x70, float) = (float)(c - 1) * STRUCT_OFFSET(peyes, 0x74, float);
        STRUCT_OFFSET(peyes, 0x6C, float) =
            (float)(c * 2) * (1.0f - STRUCT_OFFSET(peyes, 0x74, float)) /
            STRUCT_OFFSET(peyes, 0x2C, float);
        if (GRandInRange(0.0f, 1.0f) < STRUCT_OFFSET(peyes, 0x38, float))
            STRUCT_OFFSET(peyes, 0x68, float) = 0.0f;
        else
            STRUCT_OFFSET(peyes, 0x68, float) =
                GRandInRange(STRUCT_OFFSET(peyes, 0x30, float), STRUCT_OFFSET(peyes, 0x34, float));
        break;
    }
    case EYESS_Closing:
        break;
    case EYESS_Closed:
    {
        int c = STRUCT_OFFSET(peyes, 0x5C, int);
        if ((int)STRUCT_OFFSET(peyes, 0x70, float) != c - 1)
            STRUCT_OFFSET(peyes, 0x70, float) = (float)(c - 1);
        break;
    }
    case EYESS_Opening:
        break;
    }

    peyes->eyess = eyess;
    STRUCT_OFFSET(peyes, 0x64, float) = g_clock.t;
}

INCLUDE_ASM("asm/nonmatchings/P2/eyes", UpdateEyes__FP4EYESf);

void SetEyesClosed(EYES *peyes, float uClosed)
{
    STRUCT_OFFSET(peyes, 0x74, float) = uClosed;

    if (1.0f <= uClosed)
    {
        SetEyesEyess(peyes, EYESS_Closed);
    }
    else
    {
        peyes->eyess = EYESS_Nil;
        SetEyesEyess(peyes, EYESS_Open);
    }

    SetSaiIframe((SAI *)((uint8_t *)peyes + 0x10), (int)STRUCT_OFFSET(peyes, 0x70, float));
    SetSaiIframe((SAI *)((uint8_t *)peyes + 0x40), (int)STRUCT_OFFSET(peyes, 0x70, float));
}

INCLUDE_ASM("asm/nonmatchings/P2/eyes", PsaiFromEyesShd__FP4EYESP3SHD);
