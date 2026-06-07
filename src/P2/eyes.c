#include <eyes.h>
#include <shdanim.h>

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

INCLUDE_ASM("asm/nonmatchings/P2/eyes", PostEyesLoad__FP4EYES);

INCLUDE_ASM("asm/nonmatchings/P2/eyes", SetEyesEyess__FP4EYES5EYESS);

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
