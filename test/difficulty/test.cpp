#include <cassert>

#include <difficulty.h>

int main()
{
	OnDifficultyGameLoad(&g_difficulty);
	OnDifficultyWorldPreLoad(&g_difficulty);
	OnDifficultyWorldPostLoad(&g_difficulty);
	ChangeSuck(0.1, &g_difficulty);
	OnDifficultyInitialTeleport(&g_difficulty);
	OnDifficultyCollectKey(&g_difficulty);
}