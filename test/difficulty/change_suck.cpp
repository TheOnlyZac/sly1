#include <difficulty.h>
#include <gs.h>

#include <test/test.h>

int main()
{
	// Initialize difficulty
	OnDifficultyGameLoad(&g_difficulty);
	OnDifficultyWorldPreLoad(&g_difficulty);
	OnDifficultyWorldPostLoad(&g_difficulty);

	// Test changing level suck
	g_plsCur->uSuck = 0.0f;
	JtAssert(g_plsCur->uSuck == 0.0f);

	ChangeSuck(0.1, &g_difficulty);
	JtAssert(g_plsCur->uSuck == 0.1f);

	ChangeSuck(1.0, &g_difficulty);
	JtAssert(g_plsCur->uSuck == 1.0f);

	ChangeSuck(-1.0, &g_difficulty);
	JtAssert(g_plsCur->uSuck == -1.0f);

	// Test collect key scenario
	OnDifficultyCollectKey(&g_difficulty);
	JtAssert(g_plsCur->uSuck == 0.0f);
}
