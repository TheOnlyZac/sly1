#include <difficulty.h>
#include <gs.h>
#include "../test.h"

void SetGameLevel(GAMEWORLD gameworld, WORLDLEVEL worldlevel);

int main()
{
	// Initialize difficulty
	OnDifficultyGameLoad(&g_difficulty);


	// jb_intro = easy
	SetGameLevel(GAMEWORLD::Intro, WORLDLEVEL::Approach);
	OnDifficultyWorldPreLoad(&g_difficulty);
	JtAssert(g_difficulty.props == &g_difficultyEasy);


	// cw_security = easy
	SetGameLevel(GAMEWORLD::Clockwerk, WORLDLEVEL::Level2);
	OnDifficultyWorldPreLoad(&g_difficulty);
	JtAssert(g_difficulty.props == &g_difficultyEasy);


	// uw_bonus_security
	SetGameLevel(GAMEWORLD::Underwater, WORLDLEVEL::Level3);
	
	// no key = medium
	g_plsCur->fls = static_cast<FLS>((int)g_plsCur->fls & ~(int)FLS::KeyCollected); // unset KeyCollected flag
	OnDifficultyWorldPreLoad(&g_difficulty);
	JtAssert(g_difficulty.props == &g_difficultyMedium);

	// with key = hard
	g_plsCur->fls = static_cast<FLS>((int)g_plsCur->fls | (int)FLS::KeyCollected); // setKeyCollected flag
	OnDifficultyWorldPreLoad(&g_difficulty);
	JtAssert(g_difficulty.props == &g_difficultyHard);

	return 0;
}

void SetGameLevel(GAMEWORLD gameworld, WORLDLEVEL worldlevel)
{
	g_pwsCur = &g_pgsCur->aws[(int)gameworld];
	g_plsCur = &g_pwsCur->als[(int)worldlevel];
	g_pgsCur->gameworldCur = gameworld;
	g_pgsCur->worldlevelCur = worldlevel;
}