#include <game.h>
#include <joy.h>
#include <gs.h>

/* Sets the number of coins on the save file */
void SetCcoin(int nParam)
{
	g_pgsCur->ccoin = nParam;
}

/* Returns the max number of charms the player can have */
int CcharmMost()
{
	/* This was more complicated in the may proto because there was
	a powerup which enables you to have more than two charms */
	return 2;
}

/* Returns true if Sly has a charm or infinite charms cheat is enabled */
bool FCharmAvailable()
{
	if ((g_pgsCur->ccharm > 0) || ((g_grfcht & (int)(FCHT::InfiniteCharms)) != (int)FCHT::None))
	{
		return true;
	}
	return false;
}

/* Sets the number of charms on the save file */
void SetCcharm(int nParam)
{
	g_pgsCur->ccharm = nParam;
}
