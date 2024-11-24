#include "common.h"
#include <game.h>
#include <prog.h>

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
 */
INCLUDE_ASM(const s32, "P2/main", StartupVU0__Fv);

/**
 * @brief Starts up the VU1.
 */
INCLUDE_ASM(const s32, "P2/main", StartupVU1__Fv);

/**
 * @brief Starts each game system.
 */
INCLUDE_ASM(const s32, "P2/main", Startup__Fv);
