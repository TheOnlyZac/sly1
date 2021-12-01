#include <joy.h>
#include <gs.h>

#include <cassert>
#include <cstring>

int main()
{
	// Test chetkido string output
	g_pgsCur->gameworldCur = GAMEWORLD::Snow;
	g_pgsCur->worldlevelCur = WORLDLEVEL::Approach;
	g_pgsCur->ccoin = 99;
	g_pgsCur->clife = 0;

	CheatActivateChetkido();
	assert(strstr(chetkido_buffer, "The password is: chetkido") != NULL);

	g_pgsCur->ccoin = 98;

	CheatActivateChetkido();
	assert(strstr(chetkido_buffer, "The password is: chetkido") == NULL);

	return 0;
}
