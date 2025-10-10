#include <bomb.h>
#include <memory.h>
#include <emitter.h>

INCLUDE_ASM("asm/nonmatchings/P2/bomb", InitBomb__FP4BOMB);

void LoadBombFromBrx(BOMB *pbomb, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(pbomb, pbis);
    // pbomb->pexpl
    InferExpl(&STRUCT_OFFSET(pbomb, 0x5bc, EXPL *), pbomb);
}

void CloneBomb(BOMB *pbomb, BOMB *pbombBase)
{
    CloneSo(pbomb, pbombBase);

    // pbombBase->psfxDet
    if (STRUCT_OFFSET(pbombBase, 0x680, SFX *))
    {
        // pbomb->psfxDet & pbombBase->psfxDet
        STRUCT_OFFSET(pbomb, 0x680, SFX *) = (SFX *)PvAllocSwCopyImpl(0x24, STRUCT_OFFSET(pbombBase, 0x680, SFX *));
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/bomb", PostBombLoad__FP4BOMB);

INCLUDE_ASM("asm/nonmatchings/P2/bomb", HandleBombMessage__FP4BOMB5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/bomb", UpdateBomb__FP4BOMBf);

INCLUDE_ASM("asm/nonmatchings/P2/bomb", FUN_0013b828);

INCLUDE_ASM("asm/nonmatchings/P2/bomb", FUN_0013b9d8);

INCLUDE_ASM("asm/nonmatchings/P2/bomb", FUN_0013ba70);

INCLUDE_ASM("asm/nonmatchings/P2/bomb", FAbsorbBombWkr__FP4BOMBP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/bomb", FUN_0013bc80);

void PrimeBomb(BOMB *pbomb, float dt)
{
    // pbomb->tDetonate
    STRUCT_OFFSET(pbomb, 0x554, float) = g_clock.t + dt;
}

INCLUDE_ASM("asm/nonmatchings/P2/bomb", ApplyBombThrow__FP4BOMBP2PO);

INCLUDE_ASM("asm/nonmatchings/P2/bomb", DetonateBomb__FP4BOMB);

INCLUDE_ASM("asm/nonmatchings/P2/bomb", PsfxEnsureBomb__FP4BOMB4ENSK);
