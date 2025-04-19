#include <sce/memset.h>
#include <difficulty.h>
#include <game.h>
#include <transition.h>
#include <coin.h>

INCLUDE_ASM(const s32, "P2/difficulty", PdifficultyEnsureSw);
INCLUDE_ASM(const s32, "P2/difficulty", func_00151A58);

void OnDifficultyGameLoad(DIFFICULTY* pdifficulty) {
    memset(pdifficulty, 0, sizeof(DIFFICULTY)); // note: DIFFICULTY should be 0x24 bytes
}

INCLUDE_ASM(const s32, "P2/difficulty", OnDifficultyWorldPreLoad);
#ifdef SKIP_ASM
/**
 * @todo 16.92% matched.
 */
void OnDifficultyWorldPreLoad(DIFFICULTY* pdifficulty)
{
	const GS* gsCur = g_pgsCur;
	const LS* lsCur = g_plsCur;
	const int gameworld = (int)(gsCur->gameworldCur);
	const int worldlevel = (int)(gsCur->worldlevelCur);

	DIFFICULTYLEVEL* difficultyProps;

	pdifficulty->ccoinRichMin = 4;
	pdifficulty->ccoinRichMax = 6;
	pdifficulty->ccoinPoorMax = 3;
	pdifficulty->ccoinPoorMin = 1;

	if (((gameworld == (int)GAMEWORLD_Intro) || (gameworld == (int)GAMEWORLD_Clockwerk)) || (worldlevel == (int)WORLDLEVEL_Hub))
	{ // Case: Current world is 0 or 5, or current level is a hub
		difficultyProps = &g_difficultyEasy; // Set easy difficulty
	}
	else if (((int)lsCur->fls & (int)FLS_KeyCollected) == 0)
	{ // Case: Key NOT collected on current level
		difficultyProps = &g_difficultyMedium; // set medium difficulty
	}
	else
	{ // Case: Key collected on current level
		difficultyProps = &g_difficultyHard; // set hard difficulty
	}

	pdifficulty->pDifficultyLevel = difficultyProps;

	ChangeSuck(lsCur->uSuck, pdifficulty);
	difficultyProps = pdifficulty->pDifficultyLevel; // redundant?

	// todo: finish function
}
#endif

INCLUDE_ASM(const s32, "P2/difficulty", OnDifficultyWorldPostLoad);
#ifdef SKIP_ASM
/**
 * @todo 30.85% matched.
 */
void OnDifficultyWorldPostLoad(DIFFICULTY* pdifficulty)
{
	DIFFICULTYLEVEL* difficultyProps;
	int csuckCharms;

	// Case: The transition is a quit-game reload
	if ((g_transition.grftrans & 8) == 0)
	{
		const float newSuck = GLimitLm((LM*)&pdifficulty->pDifficultyLevel->unk_lm_0x8, g_plsCur->uSuck);
		ChangeSuck(newSuck, pdifficulty);
	}
	// Case: The ransition is not a quit-game reload
	else {
		difficultyProps = pdifficulty->pDifficultyLevel;

		// Case: Suck value is BELOW charmLow or ABOVE charmHigh
		if ((g_plsCur->uSuck < difficultyProps->uSuckCharmLow) ||
			(difficultyProps->uSuckCharmHigh <= g_plsCur->uSuck))
		{
			// Suck value is lower than both thresholds
			if (g_plsCur->uSuck < difficultyProps->uSuckCharmHigh)
			{
				RemoveSwExtraneousCharms(g_psw);				return;
			}

			// Suck value is not below the charmLow, so it must be above charmHigh
			csuckCharms = difficultyProps->ccharmHigh;
		}
		// Case: Suck value is ABOVE charmLow but BELOW charmHigh
		else
		{
			csuckCharms = difficultyProps->ccharmLow;
		}

		if (g_pgsCur->ccharm < csuckCharms)
		{
			SetCcharm(csuckCharms);
			pdifficulty->dps = DPS_GivenCharms;
		}
	}
}
#endif

void OnDifficultyInitialTeleport(DIFFICULTY* pdifficulty) {
    return;
}

INCLUDE_ASM(const s32, "P2/difficulty", OnDifficultyPlayerDeath);
#ifdef SKIP_ASM
void OnDifficultyPlayerDeath(float scalar, DIFFICULTY* pdifficulty)
{
	DIFFICULTYLEVEL* pdifflevel = pdifficulty->pDifficultyLevel;

	// Get suck values for current level
	float uSuckCur = g_plsCur->uSuck;
	float duSuckDeath = pdifflevel->duSuckDeath;

	// Increase suck value
	ChangeSuck(uSuckCur + scalar * duSuckDeath, pdifficulty);

	// Update suckunknown_0x10
	float result;
	if (g_pgsCur->clife < 0)
	{
		// itgame over
		result = pdifficulty->pDifficultyLevel->field18_0x40;
	}
	else
	{
		// not game over
		result = pdifflevel->field17_0x3c;
		if (g_pgsCur->clife <= pdifflevel->field21_0x4c)
		{
			result = result + pdifflevel->field22_0x50;
		}
	}
	result = GLimitLm(&g_lmZeroOne, g_plsCur->unk_suck_0x10 + scalar * result);
	g_plsCur->unk_suck_0x10 = result;
}
#endif

INCLUDE_ASM(const s32, "P2/difficulty", OnDifficultyTriggerCheckpoint);

INCLUDE_ASM(const s32, "P2/difficulty", OnDifficultyCollectKey);

INCLUDE_ASM(const s32, "P2/difficulty", OnDifficultyBreak);

void ChangeSuck(float nParam, DIFFICULTY *pdifficulty)
{
    g_plsCur->uSuck = GLimitLm(&pdifficulty->pDifficultyLevel->suck_lm, nParam);
}
