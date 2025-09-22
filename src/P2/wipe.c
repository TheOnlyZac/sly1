#include <wipe.h>

void InitWipe(WIPE *pwipe)
{
    pwipe->wipes = WIPES_Nil;
    SetWipeWipes(pwipe, WIPES_Idle);
}

INCLUDE_ASM("asm/nonmatchings/P2/wipe", UpdateWipe__FP4WIPEP3JOY);

INCLUDE_ASM("asm/nonmatchings/P2/wipe", DrawWipe__FP4WIPE);

INCLUDE_ASM("asm/nonmatchings/P2/wipe", ActivateWipe__FP4WIPEP5TRANS5WIPEK);

INCLUDE_ASM("asm/nonmatchings/P2/wipe", SetWipeButtonTrans__FP4WIPEP5TRANS5WIPEK);

INCLUDE_ASM("asm/nonmatchings/P2/wipe", FCatchWipeButtonTrans__FP4WIPEP3JOY5WIPES);

JUNK_WORD(0x00A0102D);

INCLUDE_ASM("asm/nonmatchings/P2/wipe", SetWipeWipes__FP4WIPE5WIPES);

void WipeToWorldWarp(const void *pchzWorld, OID oidWarp, WIPEK wipek)
{
    TRANS trans;
    trans.fSet = 1;
    trans.grftrans = 0;
    trans.pchzWorld = (LevelTableStruct *)pchzWorld;
    trans.oidWarp = oidWarp;
    ActivateWipe(&g_wipe, &trans, wipek);
}
