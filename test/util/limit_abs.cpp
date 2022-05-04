#include <util.h>

#include <test/test.h>

// disable warning for truncating double to float
#pragma warning(disable: 4305)

int main()
{
	// Clamp value between -1 and 1
	JtAssert(GLimitAbs(-5, 1) == -1.f);
	JtAssert(GLimitAbs(-1, 1) == -1.f);
	JtAssert(GLimitAbs(-0.4, 1) == -0.4f);
	JtAssert(GLimitAbs(0.76, 1) == 0.76f);
	JtAssert(GLimitAbs(1, 1) == 1.f);
	JtAssert(GLimitAbs(17, 1) == 1.f);

	// Clamp value between -3.14 and 3.14
	JtAssert(GLimitAbs(-5, 3.14) == -3.14f);
	JtAssert(GLimitAbs(-1, 3.14) == -1.f);
	JtAssert(GLimitAbs(-0.4, 3.14) == -0.4f);
	JtAssert(GLimitAbs(0.76, 3.14) == 0.76f);
	JtAssert(GLimitAbs(3.14, 3.14) == 3.14f);
	JtAssert(GLimitAbs(17, 3.14) == 3.14f);

	// Clamp value between -100 and 100
	JtAssert(GLimitAbs(-1000, 100) == -100.f);
	JtAssert(GLimitAbs(-100, 100) == -100.f);
	JtAssert(GLimitAbs(-17.3, 100) == -17.3f);
	JtAssert(GLimitAbs(0, 100) == 0.f);
	JtAssert(GLimitAbs(91, 100) == 91.f);
	JtAssert(GLimitAbs(100.2, 100) == 100.f);
	JtAssert(GLimitAbs(420.69, 100) == 100.f);

	return 0;
}
