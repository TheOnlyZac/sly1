#include <util.h>
#include "../assert.h"

int main()
{
	// Clamp value using global 0-1 limit
	assert(GLimitLm(&g_lmZeroOne, -2.3) == 0.f);
	assert(GLimitLm(&g_lmZeroOne, 0) == 0.f);
	assert(GLimitLm(&g_lmZeroOne, 0.234) == 0.234f);
	assert(GLimitLm(&g_lmZeroOne, 0.7) == 0.7f);
	assert(GLimitLm(&g_lmZeroOne, 1) == 1.f);
	assert(GLimitLm(&g_lmZeroOne, 4) == 1.f);

	// Clamp value using local limit
	LM lmFiveTen(5, 10);
	assert(GLimitLm(&lmFiveTen, 1) == 5.f);
	assert(GLimitLm(&lmFiveTen, 5) == 5.f);
	assert(GLimitLm(&lmFiveTen, 7) == 7.f);
	assert(GLimitLm(&lmFiveTen, 10) == 10.f);
	assert(GLimitLm(&lmFiveTen, 99) == 10.f);

	return 0;
}
