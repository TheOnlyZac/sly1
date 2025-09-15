#include <frm.h>
#include <gs.h>
#include <dmas.h>
#include <vifs.h>
#include <gifs.h>
#include <phasemem.h>
#include <sce/libdma.h>
#include <sdk/ee/eekernel.h>

extern void *g_pvVu1Code;

// TODO: Should these be defined here?
extern SLI *g_psliCur;
extern QW *g_aqwGifsBackgroundUpload;

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

void EnsureVu1Code(VIFS *pvifs, void *pvStart, void *pvEnd)
{
    if (g_pvVu1Code != pvStart)
    {
        g_pvVu1Code = pvStart;
        uint cqw = (uint)((byte *)pvEnd - (byte *)pvStart + 0x0f) >> 0x04;
        pvifs->AddDmaRefs(cqw, (QW *)pvStart);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/frm", FinalizeFrameVifs__FP4VIFSPiPP2QW);

void FinalizeFrameGifs(GIFS *pgifs, int *pcqwGifs, QW **ppqwGifs)
{
    pgifs->AddPrimPack(0, 1, 0x0e);
    pgifs->PackAD(0x61, 0);
    pgifs->AddPrimEnd();
    pgifs->AddDmaEnd();
    pgifs->Detach(pcqwGifs, ppqwGifs);
}

INCLUDE_ASM("asm/nonmatchings/P2/frm", CloseFrame__Fv);

void PrepareGsForFrameRender(FRM *pfrm)
{
    g_psliCur = pfrm->asli;
    PropagateShaders(pfrm->grfzon);

    if (pfrm->fBackgroundUploadRequired && g_aqwGifsBackgroundUpload)
    {
        *((volatile uint *)0x10003010) = 4; // REG_GIF_MODE
        sceDmaSend(g_pdcGif, g_aqwGifsBackgroundUpload);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/frm", check_anticrack_antigrab__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/frm", FrameRenderLoop__FPv);

void RenderFrame(FRM *pfrm, int fRenderGifs)
{
    PrepareGsForFrameRender(pfrm);
    SendDmaSyncGsFinish(g_pdcVif1, pfrm->aqwVifs);
    if (fRenderGifs)
    {
        *((volatile uint *)0x10003010) = 0; // REG_GIF_MODE
        SendDmaSyncGsFinish(g_pdcGif, pfrm->aqwGifs);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/frm", ClearPendingFrame__FP3FRM);

INCLUDE_ASM("asm/nonmatchings/P2/frm", FlushFrames__Fi);

INCLUDE_ASM("asm/nonmatchings/P2/frm", BlendPrevFrame__Fv);

/**
 * @note These are automatically generated static initalization functions.
 * Once the appropriate functions are matched these can be removed.
 */
INCLUDE_ASM("asm/nonmatchings/P2/frm", func_0015F618);
INCLUDE_ASM("asm/nonmatchings/P2/frm", func_0015F658);
