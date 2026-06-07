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

INCLUDE_ASM("asm/nonmatchings/P2/eyes", SetEyesClosed__FP4EYESf);

INCLUDE_ASM("asm/nonmatchings/P2/eyes", PsaiFromEyesShd__FP4EYESP3SHD);
