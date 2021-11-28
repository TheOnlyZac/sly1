#include <cassert>

#include <difficulty.h>
#include <savegame.h>

int main()
{
	// todo
	OnDifficultyGameLoad(&g_difficulty);

	// todo
	OnDifficultyWorldPreLoad(&g_difficulty);
	OnDifficultyWorldPostLoad(&g_difficulty);

	// Test changing level suck
	g_plsCur->uSuck = 0.0;
	assert(g_plsCur->uSuck == 0.0);

	ChangeSuck(0.1, &g_difficulty);
	assert(g_plsCur->uSuck == 0.1);

	ChangeSuck(1.0, &g_difficulty);
	assert(g_plsCur->uSuck == 1.0);

	ChangeSuck(-1.0, &g_difficulty);
	assert(g_plsCur->uSuck == -1.0);

	// Test collect key scenario
	OnDifficultyCollectKey(&g_difficulty);
}
