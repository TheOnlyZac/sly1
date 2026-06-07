#include <smartguard.h>
#include <freeze.h>
#include <sound.h>

INCLUDE_ASM("asm/nonmatchings/P2/smartguard", InitSmartguard__FP10SMARTGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/smartguard", PostSmartguardLoadFlashlight__FP10SMARTGUARD);

void UseSmartguardFlashlightTarget(SMARTGUARD *psmartguard, SGS sgs, OID oidTarget)
{
    FValidSgs(sgs);
    SGFT *mpsgssgft = &STRUCT_OFFSET(psmartguard, 0xc38, SGFT); // psmartguard->mpsgssgft[sgs]
    mpsgssgft[sgs].oidTarget = oidTarget;
}

void FUN_001B7100(SMARTGUARD *p, int val)
{
    int c = STRUCT_OFFSET(p, 0xcd4, int);
    if ((unsigned int)c < 4)
    {
        long long *a = &STRUCT_OFFSET(p, 0xcd8, long long);
        *(int *)&a[c] = val;
        STRUCT_OFFSET(p, 0xcd4, int) = c + 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/smartguard", PostSmartguardLoad__FP10SMARTGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/smartguard", FFilterSmartguardDetect__FP10SMARTGUARDP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/smartguard", FDetectSmartguard__FP10SMARTGUARD);

void UpdateSmartguard(SMARTGUARD *psmartguard, float dt)
{
    UpdateStepguard(psmartguard, dt);
    UpdateSmartguardFlashlight(psmartguard);
}

INCLUDE_ASM("asm/nonmatchings/P2/smartguard", UpdateSmartguardFlashlight__FP10SMARTGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/smartguard", OnSmartguardEnteringSgs__FP10SMARTGUARD3SGSP4ASEG);

INCLUDE_ASM("asm/nonmatchings/P2/smartguard", FCanSmartguardAttack__FP10SMARTGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/smartguard", SgasGetSmartguard__FP10SMARTGUARD);

void HandleSmartguardMessage(SMARTGUARD *psmartguard, MSGID msgid, void *pv)
{
    HandleStepguardMessage(psmartguard, msgid, pv);

    // psmartguard->pasegaSgs
    if (msgid == MSGID_asega_wrapped && (ASEGA *)pv == STRUCT_OFFSET(psmartguard, 0x7e0, ASEGA *))
    {
        STRUCT_OFFSET(psmartguard, 0xcc4, int)++; // psmartguard->cidleSearch
    }
}

void FreezeSmartguard(SMARTGUARD *psmartguard, int fFreeze)
{
    FreezeSo(psmartguard, fFreeze);

    if (fFreeze)
    {
        // psmartguard->pexcSneak
        UnsetExcitement(STRUCT_OFFSET(psmartguard, 0xcc0, EXC *));
        STRUCT_OFFSET(psmartguard, 0xcc0, EXC *) = NULL;
    }
}
