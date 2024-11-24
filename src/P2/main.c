#include "common.h"
// #include <game.h>
// #include <prog.h>

// extern g_chpzArgs;
// extern g_aphzArgs;

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
 *
 * @note Matching, but blocked by data definitions.
 */
INCLUDE_ASM(const s32, "P2/main", StartupVU0__Fv);
// void StartupVU0(void)
// {
//     D_00261F14->chcr.TTE = 1;
//     FlushCache(0); /* XXX: bring in eekernel defs and use WRITEBACK_DCACHE */

//     // Send VU0 init DMAtag
//     sceDmaSend(D_00261F14, (void *)&D_00211E10);
//     func_00202C38(D_00261F14, 0, 0);

//     D_00261F14->chcr.TTE = 0;
// }

/**
 * @brief Starts up the VU1.
 *
 * @note Matching, but blocked by data definitions.
 */
INCLUDE_ASM(const s32, "P2/main", StartupVU1__Fv);
// void StartupVU1(void)
// {
//     // Enable tag transfer
//     g_pdcVif1->chcr.TTE = 1;
//     FlushCache(0); /* XXX: bring in eekernel defs and use WRITEBACK_DCACHE */
//     // Send initialization DMAtag and wait.
//     // Afterwards, disable tag transfer again.
//     sceDmaSend(g_pdcVif1,(void*)&D_00212110);
//     sceDmaSync(g_pdcVif1,0,0);
//     g_pdcVif1->chcr.TTE = 0;
//     return;
// }

/**
 * @brief Starts each game system.
 */
INCLUDE_ASM(const s32, "P2/main", Startup__Fv);
