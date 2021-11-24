#include <game.h>
#include <cheats.h>
#include <savegame.h>

/* Sets the number of coins on the save file */
void SetCcoin(int nParam)
{
	g_pgsCur->c_coins = nParam;
}

/* Returns the max number of charms the player can have */
int CcharmMost()
{
	/* This was more complicated in the may proto because there was 
	a powerup which enables you to have more than two charms */
	return 2;
}

/* Returns true if Sly has or can use a charm */
bool FCharmAvailable()
{
	if ((g_pgsCur->c_charms > 0) || ((g_grfcht & (int)(FCHT::InfiniteCharms)) != (int)FCHT::None))
	{
		return true;
	}
	return false;
}

/* Sets the number of charms on the save file */
void SetCcharm(int nParam)
{
	g_pgsCur->c_charms = nParam;
}
