#include <gs.h>

#include <cassert>

int main()
{
	PopulatePchzLevelTable();

	// Test save file percent calculation
	int percent = CalculatePercentCompletion(g_pgsCur);
	assert(percent == 0);

	return 0;
}
