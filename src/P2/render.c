#include <render.h>
#include <vifs.h>
#include <frm.h>
#include <phasemem.h>

extern VECTOR g_vecScreenMultiply;
extern VECTOR g_vecScreenAdd;
extern RPL *g_prplCur;
extern QW g_qwGifClipFan;

// TODO: Change to static when possible.
extern RPL s_arplSetup[18];
extern int s_fFBCleared;
extern int s_fZBCleared;
extern int s_fCameraGlobals;
extern int s_fRenderGlobals;

// TODO: Figure out where these should be defined at.
extern void *VU1_GlobMpg;
extern void *VU1_GlobMpgEnd;
extern void *VU1_BlipMpg;
extern void *VU1_BlipMpgEnd;
extern QW g_aqwGifsClearAll[44];
extern QW g_aqwGifsClearZB[44];
extern int g_iqwBase;
extern PHASEMEM g_phasemem;

INCLUDE_ASM("asm/nonmatchings/P2/render", SubmitRpl__FP3RPL);

int NCmpPrplReverseZ(RPL **pprpl1, RPL **pprpl2)
{
    RPL *plhs = *pprpl1;
    RPL *prhs = *pprpl2;

    if (prhs->z < plhs->z)
    {
        return -1;
    }
    if (plhs->z < prhs->z)
    {
        return 1;
    }

    return (plhs - prhs);
}

INCLUDE_ASM("asm/nonmatchings/P2/render", CprplPartitionArpl__FiP3RPLPP3RPL);

INCLUDE_ASM("asm/nonmatchings/P2/render", RenderSw__FP2SWP2CM);

void EnsureRenderGlobals()
{
    if (s_fRenderGlobals == 0)
    {
        s_fRenderGlobals = 1;
        g_vifs.AddDmaCnt();
        g_vifs.AddVifBaseOffset(0, 0);
        g_vifs.AddVifUnpack(UPK_V3_32, 1, &g_vecScreenMultiply, 0);
        g_vifs.AddVifUnpack(UPK_V3_32, 1, &g_vecScreenAdd, 1);
        g_vifs.AddVifUnpack(UPK_V4_32, 1, &g_qwGifClipFan, 0xc);
        g_vifs.AddVifUnpack(UPK_V2_32, 1, &g_psw->lsmDefault, 3);
        g_vifs.EndDmaCnt();
    }
}

void EnsureCameraGlobals()
{
    if (s_fCameraGlobals == 0)
    {
        s_fCameraGlobals = 1;
        DrawCm(g_pcm);
    }
}

/**
 * @todo 95.71% match. Missing two instructions.
 */
INCLUDE_ASM("asm/nonmatchings/P2/render", EnsureScreenCleared__Fv);
#ifdef SKIP_ASM
void EnsureScreenCleared()
{
    if (!s_fFBCleared)
    {
        g_vifs.AddDmaCnt();
        g_vifs.AddVifDirect(0x2c, g_aqwGifsClearAll, 0);
        g_vifs.EndDmaCnt();
        s_fZBCleared = 1;
        s_fFBCleared = 1;
    }
    else if (!s_fZBCleared)
    {
        g_vifs.AddDmaCnt();
        g_vifs.AddVifFlush();
        g_vifs.AddVifDirect(0x2c, g_aqwGifsClearZB, 0);
        g_vifs.EndDmaCnt();
        s_fZBCleared = 1;
    }
}
#endif // SKIP_ASM

void SetupRpDynamicTexture(RPL *prpl)
{
    EnsureVu1Code(&g_vifs, &VU1_GlobMpg, &VU1_GlobMpgEnd);
}

void SetupRpBackground(RPL *prpl)
{
    EnsureRenderGlobals();
    EnsureCameraGlobals();
    EnsureVu1Code(&g_vifs, &VU1_GlobMpg, &VU1_GlobMpgEnd);
    s_fFBCleared = 1;
    g_pfrmOpen->fBackgroundUploadRequired = 1;
    g_vifs.AddDmaCnt();
    g_vifs.AddVifFlusha();
    g_vifs.EndDmaCnt();
}

void SetupRpBlotContext(RPL *prpl)
{
    EnsureRenderGlobals();
    EnsureScreenCleared();
    EnsureVu1Code(&g_vifs, &VU1_GlobMpg, &VU1_GlobMpgEnd);
    s_fCameraGlobals = 0;
}

void SetupRpGlob(RPL *prpl)
{
    EnsureRenderGlobals();
    EnsureCameraGlobals();
    EnsureScreenCleared();
    EnsureVu1Code(&g_vifs, &VU1_GlobMpg, &VU1_GlobMpgEnd);
}

void SetupRpBlip(RPL *prpl)
{
    EnsureRenderGlobals();
    EnsureCameraGlobals();
    EnsureScreenCleared();
    EnsureVu1Code(&g_vifs, &VU1_BlipMpg, &VU1_BlipMpgEnd);
}

INCLUDE_ASM("asm/nonmatchings/P2/render", SetupRpWorldMap__FP3RPL);

void DrawSw(SW *psw, CM *pcm)
{
    PrepareSwLightsForDraw(psw);

    s_fFBCleared = 0;
    s_fZBCleared = 0;
    s_fCameraGlobals = 0;
    s_fRenderGlobals = 0;
    g_iqwBase = 0x214;

    // TODO: The order of the fields in PHASEMEM_MAIN is probably wrong? This works for now.
    RPL *aprpl[1042];
    int cprpl = CprplPartitionArpl((g_prplCur - (RPL *)&g_phasemem), (RPL *)&g_phasemem, aprpl);

    g_vifs.m_fCheckCnt = 1;
    g_vifs.EndDmaCnt();

    for (int i = 0; i < cprpl; i++)
    {
        aprpl[i]->pfnDraw(aprpl[i]);
    }

    g_vifs.AddDmaCnt();

    if (cprpl == 0)
    {
        g_vifs.AddVifDirect(0x2c, g_aqwGifsClearAll, 0);
    }

    g_prplCur = NULL;
}

INCLUDE_ASM("asm/nonmatchings/P2/render", FillScreenRect__FiiiiffffP4GIFS);

/**
 * @todo 99.81% match. For some reason RPL 13 and RPL 15 are flipped in the target ASM.
 * Flipping them here makes messes with the other code.
 */
INCLUDE_ASM("asm/nonmatchings/P2/render", StartupRender__Fv);
#ifdef SKIP_ASM
void StartupRender()
{
    GIFS gifs;
    gifs.AllocStatic(1, &g_qwGifClipFan);
    // TODO: Figure out what these magic numbers mean.
    gifs.AddPrimBulk(0x7d, 0, 3, 0x412, NULL);

    s_arplSetup[0].pfnDraw = SetupRpDynamicTexture;
    s_arplSetup[1].pfnDraw = SetupRpBackground;
    s_arplSetup[2].pfnDraw = SetupRpBlotContext;
    s_arplSetup[3].pfnDraw = SetupRpGlob;
    s_arplSetup[4].pfnDraw = SetupRpGlob;
    s_arplSetup[5].pfnDraw = SetupRpBlip;
    s_arplSetup[6].pfnDraw = SetupRpGlob;
    s_arplSetup[7].pfnDraw = SetupRpGlob;
    s_arplSetup[8].pfnDraw = SetupRpGlob;
    s_arplSetup[9].pfnDraw = SetupRpBlip;
    s_arplSetup[10].pfnDraw = SetupRpGlob;
    s_arplSetup[11].pfnDraw = SetupRpGlob;
    s_arplSetup[12].pfnDraw = SetupRpGlob;
    s_arplSetup[13].pfnDraw = SetupRpGlob;
    s_arplSetup[14].pfnDraw = SetupRpBlip;
    s_arplSetup[15].pfnDraw = SetupRpBlip;
    s_arplSetup[16].pfnDraw = SetupRpGlob;
    s_arplSetup[17].pfnDraw = SetupRpWorldMap;

    for (int i = 0; i < 18; i++)
    {
        s_arplSetup[i].rp = RP_Nil;
    }
}
#endif // SKIP_ASM
