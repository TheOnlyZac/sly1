#include <difficulty.h>

INCLUDE_ASM(const s32, "P2/difficulty", FUN_001519e0);
INCLUDE_ASM(const s32, "P2/difficulty", func_00151A58);

INCLUDE_ASM(const s32, "P2/difficulty", OnDifficultyGameLoad);

INCLUDE_ASM(const s32, "P2/difficulty", OnDifficultyWorldPreLoad);

INCLUDE_ASM(const s32, "P2/difficulty", OnDifficultyWorldPostLoad);

void OnDifficultyInitialTeleport(DIFFICULTY* pdifficulty) {
    // Stubbed, does nothing.
    return;
}

INCLUDE_ASM(const s32, "P2/difficulty", OnDifficultyPlayerDeath);

INCLUDE_ASM(const s32, "P2/difficulty", OnDifficultyTriggerCheckpoint);

INCLUDE_ASM(const s32, "P2/difficulty", OnDifficultyCollectKey);

INCLUDE_ASM(const s32, "P2/difficulty", OnDifficultyBreak);

INCLUDE_ASM(const s32, "P2/difficulty", ChangeSuck);
