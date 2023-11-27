#include <joy.h>
#include <gs.h>

#include <test/test.h>

#include <cstring>

int main()
{
	// Test chetkido string output
	g_pgsCur->gameworldCur = GAMEWORLD_Snow;
	g_pgsCur->worldlevelCur = WORLDLEVEL_Approach;
	g_pgsCur->ccoin = 99;
	g_pgsCur->clife = 0;

	CheatActivateChetkido();
	JtAssert(strstr(chetkido_buffer, "The password is: chetkido") != NULL);

	g_pgsCur->ccoin = 98;

	CheatActivateChetkido();
	JtAssert(strstr(chetkido_buffer, "The password is: chetkido") == NULL);

	return 0;
}
