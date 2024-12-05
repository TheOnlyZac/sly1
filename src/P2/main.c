#include "common.h"
#include <sdk/ee/eekernel.h>
#include <sce/libdma.h>
#include <dmas.h>

// extern g_chpzArgs;
// extern g_aphzArgs;
extern void *D_00211E10;
extern void *D_00212110;

/**
 * @brief Main function.
 *
 * Invoked by the startup routine, starts the main game loop.
 */
INCLUDE_ASM(const s32, "P2/main", main);

/**
 * @note This function isn't called but it is present immediately following main.
 */
INCLUDE_ASM(const s32, "P2/main", main_epilogue);

/**
 * @brief Starts up the VU0.
 */
// INCLUDE_ASM(const s32, "P2/main", StartupVU0__Fv);
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
 */
INCLUDE_ASM(const s32, "P2/main", Startup__Fv);
