#include <xform.h>
#include "../assert.h"

int main()
{
	EXIT exit;

	SetExitExits(&exit, EXITS::Blocked);
	assert(exit.fKeyed == EXITS::Blocked);

	SetExitExits(&exit, EXITS::Disabled);
	assert(exit.fKeyed == EXITS::Disabled);

	SetExitExits(&exit, EXITS::Enabled);
	assert(exit.fKeyed == EXITS::Enabled);

	SetExitExits(&exit, EXITS::Exiting);
	assert(exit.fKeyed == EXITS::Exiting);

	return 0;
}
