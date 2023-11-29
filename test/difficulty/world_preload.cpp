#include <difficulty.h>
#include <gs.h>

#include <test/test.h>

void SetGameLevel(GAMEWORLD gameworld, WORLDLEVEL worldlevel);

int main()
{
	// Initialize difficulty
	OnDifficultyGameLoad(&g_difficulty);


	// jb_intro = easy
	SetGameLevel(GAMEWORLD_Intro, WORLDLEVEL_Approach);
	OnDifficultyWorldPreLoad(&g_difficulty);
	JtAssert(g_difficulty.pdifficultyLevel == &g_difficultyEasy);


	// cw_security = easy
	SetGameLevel(GAMEWORLD_Clockwerk, WORLDLEVEL_Level2);
	OnDifficultyWorldPreLoad(&g_difficulty);
	JtAssert(g_difficulty.pdifficultyLevel == &g_difficultyEasy);


	// uw_bonus_security
	SetGameLevel(GAMEWORLD_Underwater, WORLDLEVEL_Level3);

	// no key = medium
	g_plsCur->fls = static_cast<FLS>((int)g_plsCur->fls & ~(int)FLS_KeyCollected); // unset KeyCollected flag
	OnDifficultyWorldPreLoad(&g_difficulty);
	JtAssert(g_difficulty.pdifficultyLevel == &g_difficultyMedium);

	// with key = hard
	g_plsCur->fls = static_cast<FLS>((int)g_plsCur->fls | (int)FLS_KeyCollected); // setKeyCollected flag
	OnDifficultyWorldPreLoad(&g_difficulty);
	JtAssert(g_difficulty.pdifficultyLevel == &g_difficultyHard);

	return 0;
}

void SetGameLevel(GAMEWORLD gameworld, WORLDLEVEL worldlevel)
{
	g_pwsCur = &g_pgsCur->aws[(int)gameworld];
	g_plsCur = &g_pwsCur->als[(int)worldlevel];
	g_pgsCur->gameworldCur = gameworld;
	g_pgsCur->worldlevelCur = worldlevel;
}
