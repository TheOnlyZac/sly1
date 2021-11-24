#include <game.h>
#include <savegame.h>

/* Sets the number of coins on the save file */
void SetCcoin(int nParam)
{
	g_pgsCur->c_coins = nParam;
}

/* Returns the max number of charms the player can have 
* It is more complicated in the may proto because there is 
* a powerup which enables you to have more than two charms.
*/
int CcharmMost()
{
	return 2;
}

/* Sets the number of charms on the save file */
void SetCcharm(int nParam)
{
	g_pgsCur->c_charms = nParam;
}