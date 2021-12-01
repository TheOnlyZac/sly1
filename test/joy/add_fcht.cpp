#include <joy.h>

#include <cassert>

int main()
{
	// Test setting setting cheat flag
	g_grfcht = 0x0;

	AddFcht((int)FCHT::InfiniteCharms);
	assert(g_grfcht == 0x2);

	AddFcht((int)FCHT::LowGravity);
	assert(g_grfcht == 0x6);

	AddFcht((int)FCHT::Invulnerability);
	assert(g_grfcht == 0x7);

	AddFcht((int)FCHT::LowFriction);
	assert(g_grfcht == 0xF);

	return 0;
}