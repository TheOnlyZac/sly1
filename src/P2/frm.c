#include <frm.h>
#include <phasemem.h>
#include <sdk/ee/eekernel.h>

INCLUDE_ASM("asm/nonmatchings/P2/frm", VU1_Interrupt__Fi);

INCLUDE_ASM("asm/nonmatchings/P2/frm", StartupFrame__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/frm", OpenFrame__Fv);
#ifdef SKIP_ASM
/**
 * @todo 11.12% matched.
 * Missing some global data definitions.
 */
void OpenFrame()
{
	SetPhase(PHASE_Main);
	//WaitSema(DAT_002623b4);

	// int i = g_ifrmMax * 72;
	// g_ifrmMax += 1;

	// ...

	// ClearPendingFrame(g_pfrmOpen);

	// ...
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/frm", EnsureVu1Code__FP4VIFSPvT1);

INCLUDE_ASM("asm/nonmatchings/P2/frm", FinalizeFrameGifs__FP4GIFSPiPP2QW);

INCLUDE_ASM("asm/nonmatchings/P2/frm", FUN_0015ebf0);

INCLUDE_ASM("asm/nonmatchings/P2/frm", CloseFrame__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/frm", PrepareGsForFrameRender__FP3FRM);

INCLUDE_ASM("asm/nonmatchings/P2/frm", check_anticrack_antigrab__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/frm", FrameRenderLoop__FPv);

INCLUDE_ASM("asm/nonmatchings/P2/frm", RenderFrame__FP3FRMi);

INCLUDE_ASM("asm/nonmatchings/P2/frm", ClearPendingFrame__FP3FRM);

INCLUDE_ASM("asm/nonmatchings/P2/frm", FlushFrames__Fi);

INCLUDE_ASM("asm/nonmatchings/P2/frm", BlendPrevFrame__Fv);

/**
 * @note These are automatically generated static initalization functions.
 * Once the appropriate functions are matched these can be removed.
 */
INCLUDE_ASM("asm/nonmatchings/P2/frm", func_0015F618);
INCLUDE_ASM("asm/nonmatchings/P2/frm", func_0015F658);
