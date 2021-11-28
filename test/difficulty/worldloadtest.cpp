#include <difficulty.h>
#include <gs.h>

#include <cassert>

int main()
{
	// Initialize difficulty
	OnDifficultyGameLoad(&g_difficulty);

	// Test world pre load and post loat
	OnDifficultyWorldPreLoad(&g_difficulty);
	OnDifficultyWorldPostLoad(&g_difficulty);
	assert(0); // todo

	return 0;
}
