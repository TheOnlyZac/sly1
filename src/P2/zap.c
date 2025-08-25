#include <zap.h>

INCLUDE_ASM(const s32, "P2/zap", InitTzp__FP3TZP);

INCLUDE_ASM(const s32, "P2/zap", FUN_001f4f70);

INCLUDE_ASM(const s32, "P2/zap", PostTzpLoad__FP3TZP);

INCLUDE_ASM(const s32, "P2/zap", FUN_001f5008);

INCLUDE_ASM(const s32, "P2/zap", CloneTzp__FP3TZPT0eTzp);

INCLUDE_ASM(const s32, "P2/zap", FUN_001f51c8);

INCLUDE_ASM(const s32, "P2/zap", FInflictTzpZap__FP3TZPP2XPP3ZPR);
INCLUDE_ASM(const s32, "P2/zap", func_001F5208);

/**
 * @todo This matches but what does it actually do?
 */
void PzpdEnsureTzp(TZP *ptzp, ENSK ensk)
{
    STRUCT_OFFSET(ptzp, 0x5e4, int) = 0;
}

INCLUDE_ASM(const s32, "P2/zap", InitVolzp__FP5VOLZP);

INCLUDE_ASM(const s32, "P2/zap", UpdateVolzp__FP5VOLZPf);

void InitZpd(ZPD *pzpd, SO *pso)
{
    pzpd->pso = pso;
    pzpd->zpk = ZPK_Blunt;
    pzpd->dzThrow = 150.0f;
}

INCLUDE_ASM(const s32, "P2/zap", PostZpdLoad__FP3ZPD);

INCLUDE_ASM(const s32, "P2/zap", ApplyZpdThrow__FP3ZPDP2PO);

INCLUDE_ASM(const s32, "P2/zap", InflictZpdZap__FP3ZPDP2XPP3ZPR);
INCLUDE_ASM(const s32, "P2/zap", func_001F5840);

INCLUDE_ASM(const s32, "P2/zap", AddZpdZapLo__FP3ZPDP2LO);

INCLUDE_ASM(const s32, "P2/zap", RemoveZpdZapLo__FP3ZPDP2LO);
