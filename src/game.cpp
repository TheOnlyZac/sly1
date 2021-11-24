#include <game.h>
#include <savegame.h>

/* Returns the max number of charms the player can have 
* It is more complicated in the may proto because there is 
* a powerup which enables you to have more than two charms.
*/
int CcharmMost()
{
	return 2;
}

void SetCcharm(int nParam)
{
	g_pgsCur->c_charms = nParam;
}