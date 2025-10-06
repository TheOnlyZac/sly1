#include "common.h"
#include <lib/libkernl/filestub.h>
#include <sdk/ee/eekernel.h>
#include <sdk/ee/sifrpc.h>
#include <sdk/libcdvd.h>
#include <sce/libdma.h>
#include <phasemem.h>
#include <sce/iop.h>
#include <render.h>
#include <clock.h>
#include <save.h>
#include <mpeg.h>
#include <wipe.h>
#include <prog.h>
#include <dmas.h>
#include <frm.h>
#include <joy.h>
#include <ui.h>
#include <sw.h>
#include <cm.h>
#include <cd.h>

extern void *D_00211E10;
extern void *D_00212110;

typedef void (*SFN)(void);
extern SFN s_asfn[29];

extern int g_chpzArgs;
extern char **g_apchzArgs;

extern char D_0024B248[]; // "ioprp243.img" TODO: Remove once data is migrated.
extern char *s_apchzSifModules[];

void Startup(); // Forward declaration

/**
 * @brief Main function.
 *
 * Invoked by the startup routine, starts the main game loop.
 *
 * @todo 80.99% matched
 * https://decomp.me/scratch/4XwiN
 */
INCLUDE_ASM("asm/nonmatchings/P2/main", main);
#ifdef SKIP_ASM
int main(char **argv, int argc) {
    g_apchzArgs = argv;
    g_chpzArgs = argc;

    // These appear to be loaded into registers in the target assembly
    Startup();
    CMpeg* mpeg = &g_mpeg;

    while (true)
    {
        if (g_mpeg.oid_1 && g_pwipe->wipes != WIPES_WipingOut)
        {
            FlushFrames(1);
            mpeg->ExecuteOids();
        }

        if (g_transition.m_fPending)
        {
            FlushFrames(1);
            g_transition.Execute();
        }

        if (g_mpeg.oid_1 && g_pwipe->wipes != WIPES_WipingOut)
        {
            FlushFrames(1);
            mpeg->ExecuteOids();
        }

        UpdateJoy(&g_joy);
        UpdateCodes();
        UpdateSave(&g_save);
        UpdateUi(&g_ui);
        UpdateGameState(g_clock.dt);

        if (g_psw)
        {
            SetupCm(g_pcm);
            OpenFrame();

            MarkClockTick(&g_clock);

            if (g_psw->pcbUpdate)
            {
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
 * @brief Starts up the PS2 subsystem interface.
 */
void StartupSif()
{
    // Create a path to the "ioprp243.img" image.
    char achzPath[256];
    CdPath(achzPath, D_0024B248, 1);
    
    // Initialize SIF RPC system and CD/DVD subsystem.
    sceSifInitRpc(0);
    sceCdInit(0);

    // Hang if the CD media mode is invalid at startup.
    if (!FValidCdMmode())
    {
        while (true) {}
    }

    // Set the CD media mode and reset the filesystem.
    SetCdMmode();
    sceFsReset();

    // Reboot the IOP using the "ioprp243.img" image and wait until it completes.
    while (!sceSifRebootIop(achzPath)) {}
    while (!sceSifSyncIop()) {}

    // Reinitialize SIF and CD/DVD systems after reboot.
    sceSifInitRpc(0);
    sceSifLoadFileReset();
    sceCdInit(0);

    // Hang if the CD media mode is invalid after reboot.
    if (!FValidCdMmode())
    {
        while (true) {}
    }

    // Restore CD media mode and reset FS again after reboot.
    SetCdMmode();
    sceFsReset();
    sceCdDiskReady(0);
    FCdCompleted(1);

    // Load IOP modules listed in s_apchzSifModules.
    for (uint i = 0; i < 6; i++)
    {
        CdPath(achzPath, s_apchzSifModules[i], 1);
        while (sceSifLoadModule(achzPath, 0, 0) < 0) {}
    }
}

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
void StartupVU1()
{
    // Enable tag transfer
    g_pdcVif1->chcr.TTE = 1;
    FlushCache(0); /* XXX: bring in eekernel defs and use WRITEBACK_DCACHE */

    // Send initialization DMAtag and wait. Then, disable tag transfer again.
    sceDmaSend(g_pdcVif1, &D_00212110);
    sceDmaSync(g_pdcVif1, 0, 0);
    g_pdcVif1->chcr.TTE = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/main", Startup__Fv);
#ifdef SKIP_ASM
/**
 * @brief Starts each game system.
 *
 * @todo 99.71% matched.
 * Stack frame is 48 bytes smaller than expected.
 * https://decomp.me/scratch/IOVxc
 * https://decomp.me/scratch/NNtNR
 */
void Startup()
{
    // Set up the progress bar.
    int nRemain = 26;
    int rgbaComplete = 0x007f0000; // blue
    int rgbaRemain = 0x003f3f3f; // gray
    int rgbaWarning = 0x00003f3f; // yellow
    int rgbaTrouble = 0x0000003f; // red
    CProg prog = CProg((RGBA *)&rgbaComplete, (RGBA *)&rgbaRemain, (RGBA *)&rgbaWarning, (RGBA *)&rgbaTrouble);

    // Begin startup phase.
    SetPhase(PHASE_Startup);
    prog.Begin();

    // Call each function in the startup function array.
    SFN *psfn = s_asfn;
    for (int i = 0; i < sizeof(s_asfn) / sizeof(s_asfn[0]); i++)
    {
        if (i > 2)
        {
            prog.SetRemain(nRemain);
        }

        (*psfn++)();
        nRemain--;
    }

    // Cleanup.
    prog.SetRemain(0);
    prog.End();
    ClearPhase(PHASE_Startup);
}
#endif
