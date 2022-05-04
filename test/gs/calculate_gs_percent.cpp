#include <gs.h>

#include <test/test.h>

int main()
{
	PopulatePchzLevelTable();

	// Test save file percent calculation
	int percent = CalculatePercentCompletion(g_pgsCur);
	JtAssert(percent == 0);

	return 0;
}
