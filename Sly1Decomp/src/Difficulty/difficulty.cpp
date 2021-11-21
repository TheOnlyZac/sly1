#include "difficulty.h"

#include <Savegame/savegame.h>
#include <Util/util.h>

#include <iostream>

Difficulty* g_difficulty = new Difficulty();
DifficultyProps g_difficultyEasy, g_difficultyMedium, g_difficultyHard;

/* Update the suck value on the current level save data */
void ChangeSuck(float nParam, Difficulty* pdifficulty)
{
	const float newSuck = GLimitLm(&pdifficulty->props->suckLm, (g_plsCur->uSuck + nParam * 0.1)); // clamp new suck
	g_plsCur->uSuck = newSuck; // set current level suck to clamped value
}

/* Called when game starts, clears the difficulty struct */
void OnDifficultyGameLoad(Difficulty* pdifficulty)
{
	std::memset(pdifficulty, 0, sizeof(Difficulty));
}

/* Set the game difficulty props based on current save state */
void OnDifficultyWorldPreLoad(Difficulty* pdifficulty)
{
	const GameSave* gsCur = g_pgsCur;
	const LevelSave* lsCur = g_plsCur;
	const int worldId = gsCur->gameworld;

	DifficultyProps* difficultyProps;

	pdifficulty->ccoinRichMin = 4;
	pdifficulty->ccoinRichMax = 6;
	pdifficulty->ccoinPoorMax = 3;
	pdifficulty->ccoinPoorMin = 1;

	if (((worldId == GAMEWORLD_Intro) || (worldId == GAMEWORLD_Clockwerk)) || (gsCur->worldlevel == WORLDLEVEL_Hub))
	{ // Case: World is 0 or 5, or current level is a hub (map ID 1)
		difficultyProps = &g_difficultyEasy; // Set easy difficulty
	}
	else if ((lsCur->fls & FLS_KeyCollected) == 0)
	{ // Case: Key NOT collected on current level
		difficultyProps = &g_difficultyMedium; // set medium difficulty
	}
	else
	{ // Case: Key collected on current level
		difficultyProps = &g_difficultyHard; // set hard difficulty
	}

	pdifficulty->props = difficultyProps;

	ChangeSuck(lsCur->uSuck, pdifficulty);
	difficultyProps = pdifficulty->props; // redundant?

	// todo: finish function
}

/* Update the player suck and determine the number of suck charms they get */
void OnDifficultyWorldPostLoad(Difficulty* pdifficulty)
{
	DifficultyProps* difficultyProps;
	int csuckCharms;

	// Case: The transition is a quit-game reload
	if (/*(g_transition.load_flags & 8) = 0 */ true) // todo implement g_transition
	{
		const float newSuck = GLimitLm((LM*)&pdifficulty->props->unk_lm_0x8, g_plsCur->uSuck);
		ChangeSuck(newSuck, pdifficulty);
	}
	// Case: The ransition is not a quit-game reload
	else {
		difficultyProps = pdifficulty->props;

		// Case: Suck value is BELOW charmLow or ABOVE charmHigh
		if ((g_plsCur->uSuck < difficultyProps->uSuckCharmLow) ||
			(difficultyProps->uSuckCharmHigh <= g_plsCur->uSuck))
		{
			// Suck value is lower than both thresholds
			if (g_plsCur->uSuck < difficultyProps->uSuckCharmHigh)
			{
				//RemoveSwExtraneousCharms(g_psw); // todo implement function
				return;
			}

			// Suck value is not below the charmLow, so it must be above charmHigh
			csuckCharms = difficultyProps->ccharmHigh;
		}
		// Case: Suck value is ABOVE charmLow but BELOW charmHigh
		else
		{
			csuckCharms = difficultyProps->ccharmLow;
		}

		if (g_pgsCur->c_charms < csuckCharms)
		{
			//SetCcharm(numCharms); // todo implement function
			pdifficulty->dps = DPS_GivenCharms;
		}
	}
}

// Stubbed, purpose unknown
void OnDifficultyInitialTeleport(Difficulty* pdifficulty)
{
	return;
}

// Resets some difficulty values upon collecting a key
void OnDifficultyCollectKey(Difficulty* pdifficulty)
{
	LevelSave* lsCur = g_plsCur;

	ChangeSuck(0.0, pdifficulty);

	lsCur->unk_suck_0x10 = 0.0;
	lsCur->unk_field_0x70 = 0;

	std::memset(&lsCur->unk_field_0x74, 0, 1);
}