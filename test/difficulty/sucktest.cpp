#include <difficulty.h>
#include <gs.h>

#include <cassert>

int main()
{
	// Initialize difficulty
	OnDifficultyGameLoad(&g_difficulty);

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
	assert(g_plsCur->uSuck == 0.0);
}
