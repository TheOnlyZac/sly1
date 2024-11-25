#include <sce/memset.h>
#include <difficulty.h>
#include <game.h>

INCLUDE_ASM(const s32, "P2/difficulty", PdifficultyEnsureSw);
INCLUDE_ASM(const s32, "P2/difficulty", func_00151A58);

void OnDifficultyGameLoad(DIFFICULTY* pdifficulty) {
    memset(pdifficulty, 0, sizeof(DIFFICULTY)); // DIFFICULTY should be 0x24 bytes
}

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

void ChangeSuck(float nParam, DIFFICULTY *pdifficulty)
{
    g_plsCur->uSuck = GLimitLm(&pdifficulty->p_difficulty_level->suck_lm, nParam);
}
