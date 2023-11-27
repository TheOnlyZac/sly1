#include <xform.h>
#include <cassert>

#include <test/test.h>

int main()
{
	EXIT exit;

	// todo: why does the custom assert macro cause errors here

	SetExitExits(&exit, EXITS_Blocked);
	assert(exit.fKeyed == EXITS_Blocked);

	SetExitExits(&exit, EXITS_Disabled);
	assert(exit.fKeyed == EXITS_Disabled);

	SetExitExits(&exit, EXITS_Enabled);
	assert(exit.fKeyed == EXITS_Enabled);

	SetExitExits(&exit, EXITS_Exiting);
	assert(exit.fKeyed == EXITS_Exiting);

	return 0;
}
