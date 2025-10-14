#include <render.h>

extern int s_fFBCleared;
extern int s_fZBCleared;
extern int s_fCameraGlobals;
extern int s_fRenderGlobals;

INCLUDE_ASM("asm/nonmatchings/P2/render", SubmitRpl__FP3RPL);

INCLUDE_ASM("asm/nonmatchings/P2/render", NCmpPrplReverseZ__FPP3RPLT0);
#ifdef SKIP_ASM
/**
 * @todo 100% match, if the struct is exactly 8 bytes long.
 * Once the struct is fully implemented this code needs to be changed to account for that.
 * https://decomp.me/scratch/4xKRS
 */
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

    return (plhs - prhs) >> 0x04;
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/render", CprplPartitionArpl__FiP3RPLPP3RPL);

INCLUDE_ASM("asm/nonmatchings/P2/render", RenderSw__FP2SWP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/render", EnsureRenderGlobals__Fv);

void EnsureCameraGlobals()
{
    if (s_fCameraGlobals == 0)
    {
        s_fCameraGlobals = 1;
        DrawCm(g_pcm);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/render", EnsureScreenCleared__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/render", SetupRpDynamicTexture__FP3RPL);

INCLUDE_ASM("asm/nonmatchings/P2/render", SetupRpBackground__FP3RPL);

INCLUDE_ASM("asm/nonmatchings/P2/render", SetupRpBlotContext__FP3RPL);

INCLUDE_ASM("asm/nonmatchings/P2/render", SetupRpGlob__FP3RPL);

INCLUDE_ASM("asm/nonmatchings/P2/render", SetupRpBlip__FP3RPL);

INCLUDE_ASM("asm/nonmatchings/P2/render", SetupRpWorldMap__FP3RPL);

INCLUDE_ASM("asm/nonmatchings/P2/render", DrawSw__FP2SWP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/render", FillScreenRect__FiiiiffffP4GIFS);

INCLUDE_ASM("asm/nonmatchings/P2/render", StartupRender__Fv);
