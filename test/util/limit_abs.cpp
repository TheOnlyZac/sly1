#include <util.h>
#include "../assert.h"

int main()
{
	// Clamp value between -1 and 1
	assert(GLimitAbs(-5, 1) == -1.f);
	assert(GLimitAbs(-1, 1) == -1.f);
	assert(GLimitAbs(-0.4, 1) == -0.4f);
	assert(GLimitAbs(0.76, 1) == 0.76f);
	assert(GLimitAbs(1, 1) == 1.f);
	assert(GLimitAbs(17, 1) == 1.f);

	// Clamp value between -3.14 and 3.14
	assert(GLimitAbs(-5, 3.14) == -3.14f);
	assert(GLimitAbs(-1, 3.14) == -1.f);
	assert(GLimitAbs(-0.4, 3.14) == -0.4f);
	assert(GLimitAbs(0.76, 3.14) == 0.76f);
	assert(GLimitAbs(3.14, 3.14) == 3.14f);
	assert(GLimitAbs(17, 3.14) == 3.14f);

	// Clamp value between -100 and 100
	assert(GLimitAbs(-1000, 100) == -100.f);
	assert(GLimitAbs(-100, 100) == -100.f);
	assert(GLimitAbs(-17.3, 100) == -17.3f);
	assert(GLimitAbs(0, 100) == 0.f);
	assert(GLimitAbs(91, 100) == 91.f);
	assert(GLimitAbs(100.2, 100) == 100.f);
	assert(GLimitAbs(420.69, 100) == 100.f);

	return 0;
}
