#include <difficulty.h>
#include <gs.h>

#include <cassert>

int main()
{
	// Initialize difficulty
	OnDifficultyGameLoad(&g_difficulty);
	OnDifficultyWorldPreLoad(&g_difficulty);
	OnDifficultyWorldPostLoad(&g_difficulty);

	assert(0); // todo: test initializing difficulty under different conditions

	return 0;
}
