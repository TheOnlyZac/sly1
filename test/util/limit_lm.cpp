#include <util.h>

#include <test/test.h>

// disable warning for truncating double to float
#pragma warning(disable: 4305)

int main()
{
	// Clamp value using global 0-1 limit
	JtAssert(GLimitLm(&g_lmZeroOne, -2.3) == 0.f);
	JtAssert(GLimitLm(&g_lmZeroOne, 0) == 0.f);
	JtAssert(GLimitLm(&g_lmZeroOne, 0.234) == 0.234f);
	JtAssert(GLimitLm(&g_lmZeroOne, 0.7) == 0.7f);
	JtAssert(GLimitLm(&g_lmZeroOne, 1) == 1.f);
	JtAssert(GLimitLm(&g_lmZeroOne, 4) == 1.f);

	// Clamp value using local limit
	LM lmFiveTen(5, 10);
	JtAssert(GLimitLm(&lmFiveTen, 1) == 5.f);
	JtAssert(GLimitLm(&lmFiveTen, 5) == 5.f);
	JtAssert(GLimitLm(&lmFiveTen, 7) == 7.f);
	JtAssert(GLimitLm(&lmFiveTen, 10) == 10.f);
	JtAssert(GLimitLm(&lmFiveTen, 99) == 10.f);

	return 0;
}
