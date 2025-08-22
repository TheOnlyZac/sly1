#include <xform.h>
#include <sw.h>

INCLUDE_ASM(const s32, "P2/xform2", LoadWarpFromBrx__FP4WARPP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/xform2", CloneWarp__FP4WARPT0);

INCLUDE_ASM(const s32, "P2/xform2", PostWarpLoad__FP4WARP);

INCLUDE_ASM(const s32, "P2/xform2", TriggerWarp__FP4WARP);

INCLUDE_ASM(const s32, "P2/xform2", SetWarpRsmg__FP4WARPi3OIDN22);

INCLUDE_ASM(const s32, "P2/xform2", func_001F4308);

INCLUDE_ASM(const s32, "P2/xform2", TeleportSwPlayer__FP2SW3OIDT1);

INCLUDE_ASM(const s32, "P2/xform2", PexitDefault__Fv);

INCLUDE_ASM(const s32, "P2/xform2", TriggerDefaultExit__Fi5WIPEK);

INCLUDE_ASM(const s32, "P2/xform2", LoadExitFromBrx__FP4EXITP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/xform2", PostExitLoad__FP4EXIT);

INCLUDE_ASM(const s32, "P2/xform2", SetExitExits__FP4EXIT5EXITS);
#ifdef SKIP_ASM
/**
 * @todo 97.74% matched.
 * https://decomp.me/scratch/t75bf
 */
void SetExitExits(EXIT *pexit, EXITS exits)
{
    if (exits == pexit->exits) {
        return;
    }

    if (pexit->exits == EXITS_Totals && exits != EXITS_Exiting) {
        BLOT *totals = (BLOT *)&g_totals;
        g_totals.pvttotals->pfnHideBlot(totals);
    }

    if (exits != EXITS_Exiting) {
        pexit->exits = exits;
        pexit->tExits = g_clock.t;
        return;
    }

    // Read the 64-bit value from offset 0x2c8
    uint64_t uVar1 = STRUCT_OFFSET(pexit, 0x2c8, uint64_t);

    // Apply bitwise mask and OR operation
    uVar1 = (uVar1 & ~0x30100000000ULL) | (0x8000ULL << 0x19);

    // Store back the modified value
    STRUCT_OFFSET(pexit, 0x2c8, uint64_t) = uVar1;

    IncrementSwHandsOff(pexit->psw);

    pexit->exits = exits;
    pexit->tExits = g_clock.t;
}
#endif // SKIP_ASM

INCLUDE_ASM(const s32, "P2/xform2", TriggerExit__FP4EXIT);

INCLUDE_ASM(const s32, "P2/xform2", WipeExit__FP4EXIT);

INCLUDE_ASM(const s32, "P2/xform2", UpdateExit__FfP4EXIT);

INCLUDE_ASM(const s32, "P2/xform2", InitCamera__FP6CAMERA);

INCLUDE_ASM(const s32, "P2/xform2", PostCameraLoad__FP6CAMERA);

INCLUDE_ASM(const s32, "P2/xform2", EnableCamera__FP6CAMERA);
