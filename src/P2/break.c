#include <break.h>

INCLUDE_ASM(const s32, "P2/break", InitBrk__FP3BRK);

INCLUDE_ASM(const s32, "P2/break", LoadBrkFromBrx__FP3BRKP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/break", CloneBrk__FP3BRKT0);

INCLUDE_ASM(const s32, "P2/break", PostBrkLoad__FP3BRK);

INCLUDE_ASM(const s32, "P2/break", PostBrkLoadCallbackHookup__FP3BRK5MSGIDPv);

INCLUDE_ASM(const s32, "P2/break", UpdateBrk__FP3BRKf);

INCLUDE_ASM(const s32, "P2/break", FAbsorbBrkWkr__FP3BRKP3WKR);

INCLUDE_ASM(const s32, "P2/break", BreakBrk__FP3BRK);

INCLUDE_ASM(const s32, "P2/break", SetBrkBroken__FP3BRKi);

INCLUDE_ASM(const s32, "P2/break", SetBrkExclude__FP3BRK3OID);

INCLUDE_ASM(const s32, "P2/break", SetBrkRemain__FP3BRK3OID);

INCLUDE_ASM(const s32, "P2/break", SetBrkFixed__FP3BRK3OID);

INCLUDE_ASM(const s32, "P2/break", SetBrkRemainFixed__FP3BRK3OID);

INCLUDE_ASM(const s32, "P2/break", SetBrkOnPlayer__FP3BRKi);

void GetBrkOnPlayer(BRK *pbrk, int *pfBreakOnPlayer)
{
    *pfBreakOnPlayer = STRUCT_OFFSET(pbrk, 0x63c, int) & 1;
}

INCLUDE_ASM(const s32, "P2/break", SetBrkOnBomb__FP3BRKi);

void GetBrkOnBomb(BRK *pbrk, int *pfBreakOnBomb)
{
    *pfBreakOnBomb = (STRUCT_OFFSET(pbrk, 0x63c, int) >> 2) & 1;
}

INCLUDE_ASM(const s32, "P2/break", AddBrkTouchObject__FP3BRK3OID);

INCLUDE_ASM(const s32, "P2/break", AddBrkTouchClass__FP3BRK3CID);

INCLUDE_ASM(const s32, "P2/break", FUN_0013DAB8);

SFX *PsfxEnsureBrk(BRK *pbrk, ENSK ensk)
{
    if(!STRUCT_OFFSET(pbrk, 0x6b4, SFX *))
    {
        NewSfx(&STRUCT_OFFSET(pbrk, 0x6b4, SFX *));
    }
    
    return STRUCT_OFFSET(pbrk, 0x6b4, SFX *);
}

INCLUDE_ASM(const s32, "P2/break", FCheckBrkTouchObject__FP3BRKP2SO);

INCLUDE_ASM(const s32, "P2/break", UpdateBrkp__FP4BRKPf);

INCLUDE_ASM(const s32, "P2/break", HandleBrkpMessage__FP4BRKP5MSGIDPv);

INCLUDE_ASM(const s32, "P2/break", FIgnoreBrkpIntersection__FP4BRKPP2SO);

INCLUDE_ASM(const s32, "P2/break", SetBrkpBrkps__FP4BRKP5BRKPS);

void InitBreak(BREAK *pbreak)
{
    InitBrk((BRK *)pbreak);
    STRUCT_OFFSET(pbreak, 0x63c, int) = 5;
    STRUCT_OFFSET(pbreak, 0x698, int) = -1;
}

INCLUDE_ASM(const s32, "P2/break", InitFragile__FP7FRAGILE);

INCLUDE_ASM(const s32, "P2/break", AdjustFragileNewXp__FP7FRAGILEP2XPi);

INCLUDE_ASM(const s32, "P2/break", AdjustZapbreakNewXp__FP8ZAPBREAKP2XPi);

INCLUDE_ASM(const s32, "P2/break", UpdateZapbreak__FP8ZAPBREAKf);
