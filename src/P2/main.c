#include "common.h"
#include <sdk/ee/eekernel.h>
#include <sce/libdma.h>
#include <mpeg.h>
#include <wipe.h>
#include <frm.h>
#include <joy.h>
#include <ui.h>
#include <save.h>
#include <clock.h>
#include <sw.h>
#include <cm.h>
#include <render.h>
#include <dmas.h>
#include <prog.h>
#include <phasemem.h>

extern void *D_00211E10;
extern void *D_00212110;
extern void *g_startupSampler[29];
extern int g_chpzArgs;
extern char **g_apchzArgs;

void Startup(); // Forward declaration

/**
 * @brief Main function.
 *
 * Invoked by the startup routine, starts the main game loop.
 *
 * @todo 80.99% matched
 * https://decomp.me/scratch/4XwiN
 */
INCLUDE_ASM(const s32, "P2/main", main);
#ifdef SKIP_ASM
int main(char **argv, int argc) {
    g_apchzArgs = argv;
    g_chpzArgs = argc;

    // These appear to be loaded into registers in the target assembly
    Startup();
    CMpeg* mpeg = &g_mpeg;

    while(true) {
        if (g_mpeg.oid_1 && g_pwipe->wipes != WIPES_WipingOut) {
            FlushFrames(1);
            mpeg->ExecuteOids();
        }

        if (g_transition.m_fPending) {
            FlushFrames(1);
            g_transition.Execute();
        }

        if (g_mpeg.oid_1 && g_pwipe->wipes != WIPES_WipingOut) {
            FlushFrames(1);
            mpeg->ExecuteOids();
        }

        UpdateJoy(&g_joy);
        UpdateCodes();
        UpdateSave(&g_save);
        UpdateUi(&g_ui);
        UpdateGameState(g_clock.dt);

        if (g_psw != nullptr) {
            SetupCm(g_pcm);
            OpenFrame();

            MarkClockTick(&g_clock);

            if (g_psw->pcbUpdate) {
                 g_psw->pcbUpdate(g_clock.dt);
            }

            RenderSw(g_psw, g_pcm);
            RenderUi();
            DrawSw(g_psw, g_pcm);
            DrawUi();
            CloseFrame();
        }

        g_cframe += 1;
    }
}
#endif

/**
 * @note This function isn't called but it is present immediately following main.
 */
INCLUDE_ASM(const s32, "P2/main", main_epilogue);

/**
 * @brief Starts up the VU0.
 */
void StartupVU0()
{
    g_pdcVif0->chcr.TTE = 1;
    FlushCache(0); /* XXX: bring in eekernel defs and use WRITEBACK_DCACHE */

    // Send VU0 init DMAtag
    sceDmaSend(g_pdcVif0, &D_00211E10); // D_00211E10 is start of .vutext
    sceDmaSync(g_pdcVif0, 0, 0);

    g_pdcVif0->chcr.TTE = 0;
}

/**
 * @brief Starts up the VU1.
 */
void StartupVU1(void)
{
    // Enable tag transfer
    g_pdcVif1->chcr.TTE = 1;
    FlushCache(0); /* XXX: bring in eekernel defs and use WRITEBACK_DCACHE */

    // Send initialization DMAtag and wait. Then, disable tag transfer again.
    sceDmaSend(g_pdcVif1, &D_00212110);
    sceDmaSync(g_pdcVif1, 0, 0);
    g_pdcVif1->chcr.TTE = 0;
}

/**
 * @brief Starts each game system.
 *
 * @todo 98.23% matched
 * https://decomp.me/scratch/IOVxc
 *
 * @note Stack frame 48 bytes smaller than expected.
 */
INCLUDE_ASM(const s32, "P2/main", Startup__Fv);
#ifdef SKIP_ASM
void Startup()
{
    // Set up progress bar
    int nRemain = 26;
    int rgbaComplete = 0x007f0000; // blue
    int rgbaRemain = 0x003f3f3f; // gray
    int rgbaWarning = 0x00003f3f; // yellow
    int rgbaTrouble = 0x0000003f; // red
    CProg prog = CProg((RGBA *)&rgbaComplete, (RGBA *)&rgbaRemain, (RGBA *)&rgbaWarning, (RGBA *)&rgbaTrouble);

    // Begin startup phase, iterating over and calling each function in the startup sampler
    SetPhase(PHASE_Startup);
    prog.Begin();
    for (int i = 0; i < sizeof(g_startupSampler) / sizeof(g_startupSampler[0]); i++) // TODO Check if this is actually called startup sampler
    {
        if (i > 2)
        {
            prog.SetRemain(nRemain);
        }

        nRemain--;
        ((void (*)(void))g_startupSampler[i])(); // Cast to function pointer before calling
    }

    // Cleanup
    prog.SetRemain(0);
    prog.End();
    ClearPhase();
}
#endif
