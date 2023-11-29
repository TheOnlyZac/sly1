#include <joy.h>

#include <test/test.h>

int main()
{
	// Test setting setting cheat flag
	g_grfcht = 0x0;

	AddFcht((int)FCHT_InfiniteCharms);
	JtAssert(g_grfcht == 0x2);

	AddFcht((int)FCHT_LowGravity);
	JtAssert(g_grfcht == 0x6);

	AddFcht((int)FCHT_Invulnerability);
	JtAssert(g_grfcht == 0x7);

	AddFcht((int)FCHT_LowFriction);
	JtAssert(g_grfcht == 0xF);

	return 0;
}
