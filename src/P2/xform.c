#include <xform.h>
#include <sw.h>

INCLUDE_ASM("asm/nonmatchings/P2/xform", InitXfm__FP3XFM);

INCLUDE_ASM("asm/nonmatchings/P2/xform", LoadXfmFromBrx__FP3XFMP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/xform", SetXfmParent__FP3XFMP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/xform", ApplyXfmProxy__FP3XFMP5PROXY);

INCLUDE_ASM("asm/nonmatchings/P2/xform", ConvertXfmLocalToWorld__FP3XFMP6VECTORT1);

INCLUDE_ASM("asm/nonmatchings/P2/xform", GetXfmPos__FP3XFMP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/xform", GetXfmMat__FP3XFMP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/xform", PwarpFromOid__F3OIDT0);

INCLUDE_ASM("asm/nonmatchings/P2/xform", LoadWarpFromBrx__FP4WARPP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/xform", CloneWarp__FP4WARPT0);

INCLUDE_ASM("asm/nonmatchings/P2/xform", PostWarpLoad__FP4WARP);

INCLUDE_ASM("asm/nonmatchings/P2/xform", TriggerWarp__FP4WARP);

INCLUDE_ASM("asm/nonmatchings/P2/xform", SetWarpRsmg__FP4WARPi3OIDN22);

INCLUDE_ASM("asm/nonmatchings/P2/xform", FUN_001F4308);

INCLUDE_ASM("asm/nonmatchings/P2/xform", TeleportSwPlayer__FP2SW3OIDT1);

INCLUDE_ASM("asm/nonmatchings/P2/xform", PexitDefault__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/xform", TriggerDefaultExit__Fi5WIPEK);

INCLUDE_ASM("asm/nonmatchings/P2/xform", LoadExitFromBrx__FP4EXITP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/xform", PostExitLoad__FP4EXIT);

INCLUDE_ASM("asm/nonmatchings/P2/xform", SetExitExits__FP4EXIT5EXITS);
#ifdef SKIP_ASM
/**
 * @todo 97.74% matched.
 * https://decomp.me/scratch/t75bf
 */
void SetExitExits(EXIT *pexit, EXITS exits)
{
    if (exits == pexit->exits)
    {
        return;
    }

    if (pexit->exits == EXITS_Totals && exits != EXITS_Exiting)
    {
        BLOT *totals = (BLOT *)&g_totals;
        g_totals.pvttotals->pfnHideBlot(totals);
    }

    if (exits != EXITS_Exiting)
    {
        pexit->exits = exits;
        pexit->tExits = g_clock.t;
        return;
    }

    // Read the 64-bit value from offset 0x2c8
    ulong uVar1 = STRUCT_OFFSET(pexit, 0x2c8, ulong);

    // Apply bitwise mask and OR operation
    uVar1 = (uVar1 & ~0x30100000000ULL) | (0x8000ULL << 0x19);

    // Store back the modified value
    STRUCT_OFFSET(pexit, 0x2c8, ulong) = uVar1;

    IncrementSwHandsOff(pexit->psw);

    pexit->exits = exits;
    pexit->tExits = g_clock.t;
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/xform", TriggerExit__FP4EXIT);

INCLUDE_ASM("asm/nonmatchings/P2/xform", WipeExit__FP4EXIT);

INCLUDE_ASM("asm/nonmatchings/P2/xform", UpdateExit__FfP4EXIT);

INCLUDE_ASM("asm/nonmatchings/P2/xform", InitCamera__FP6CAMERA);

INCLUDE_ASM("asm/nonmatchings/P2/xform", PostCameraLoad__FP6CAMERA);

INCLUDE_ASM("asm/nonmatchings/P2/xform", EnableCamera__FP6CAMERA);
