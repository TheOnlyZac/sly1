#include "common.h"
#include <game.h>
#include "prog.h"

// extern g_chpzArgs;
// extern g_aphzArgs;

INCLUDE_ASM(const s32, "P2/main", main);
INCLUDE_ASM(const s32, "P2/main", main_epilogue);

INCLUDE_ASM(const s32, "P2/main", StartupVU0__Fv);

INCLUDE_ASM(const s32, "P2/main", StartupVU1__Fv);

INCLUDE_ASM(const s32, "P2/main", Startup__Fv);
