#include <frm.h>
#include <gs.h>
#include <dmas.h>
#include <vifs.h>
#include <gifs.h>
#include <phasemem.h>
#include <sce/libdma.h>
#include <sdk/ee/eekernel.h>
#include <dl.h>

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

extern void *VU1_GlobMpg;
extern void *VU1_GlobMpgEnd;

INCLUDE_ASM("asm/nonmatchings/P2/frm", FinalizeFrameVifs__FP4VIFSPiPP2QW);
#ifdef SKIP_ASM
void FinalizeFrameVifs(VIFS *pvifs, int *pcqwVifs, QW **ppqwVifs)
{
    QW aqw[8];
    GIFS gifs = GIFS();

    gifs.AllocStatic(8, aqw);
    gifs.AddPrimPack(0, 1, 0x0e);
    gifs.PackAD(0x61, 0);
    gifs.AddPrimEnd();
    pvifs->AddVifFlush();
    pvifs->AddVifGifs(&gifs);
    EnsureVu1Code(pvifs, &VU1_GlobMpg, &VU1_GlobMpgEnd);
    pvifs->AddDmaEnd();
    pvifs->Detach(pcqwVifs, ppqwVifs);
}
#endif // SKIP_ASM

void FinalizeFrameGifs(GIFS *pgifs, int *pcqwGifs, QW **ppqwGifs)
{
    pgifs->AddPrimPack(0, 1, 0x0e);
    pgifs->PackAD(0x61, 0);
    pgifs->AddPrimEnd();
    pgifs->AddDmaEnd();
    pgifs->Detach(pcqwGifs, ppqwGifs);
}

extern "C" int SignalSema(int sid);

extern DL D_002622E0;
extern DL D_002622F0;
extern DL D_00262300;
extern int D_002622D0;
extern int D_002623B0;

void CloseFrame()
{
    FinalizeFrameVifs(&g_vifs, &g_pfrmOpen->cqwVifs, 0);
    FinalizeFrameGifs(&g_gifs, &g_pfrmOpen->cqwGifs, 0);

    STRUCT_OFFSET(g_pfrmOpen, 0x20, DL) = D_002622E0;
    ClearDl(&D_002622E0);

    STRUCT_OFFSET(g_pfrmOpen, 0x2C, DL) = D_002622F0;
    ClearDl(&D_002622F0);

    STRUCT_OFFSET(g_pfrmOpen, 0x38, DL) = D_00262300;
    ClearDl(&D_00262300);

    D_002622D0 = 0;
    g_pfrmOpen = 0;
    SignalSema(D_002623B0);
}

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

extern "C" unsigned int D_002C3B00[];
extern "C" unsigned int func_00100000[];
extern "C" char D_00148D74[];
extern "C" int D_00262310;

INCLUDE_ASM("asm/nonmatchings/P2/frm", check_anticrack_antigrab__Fv);
#ifdef SKIP_ASM
void check_anticrack_antigrab()
{
    unsigned int *pwTable = D_002C3B00;
    int cb = (int)D_00148D74;
    unsigned int crc = 0xFFFFFFFF;
    unsigned int *pw = func_00100000;

    while (cb > 0)
    {
        unsigned int w = *pw;
        cb -= 4;
        pw += 1;
        crc = pwTable[(crc ^ w) & 0xFF] ^ (crc >> 8);
        crc = pwTable[(crc ^ (w >> 8)) & 0xFF] ^ (crc >> 8);
        crc = pwTable[(crc ^ (w >> 16)) & 0xFF] ^ (crc >> 8);
        crc = pwTable[(crc ^ (w >> 24)) & 0xFF] ^ (crc >> 8);
    }

    if (crc != 0)
        D_00262310 = 1;
}
#endif // SKIP_ASM

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
extern "C" void func_0015F618(int, int);

extern "C" void func_0015F658(void)
{
    func_0015F618(1, 0xFFFF);
}
