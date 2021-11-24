#include "..\include\coin.h"

#include <savegame.h>

void OnCoinSmack(Coin * pcoin)
{
	const GameSave* gsCur = g_pgsCur;
	const int newCoinCount = gsCur->c_coins + 1;
	
	// Increment coin count
	g_pgsCur->c_coins = newCoinCount;

	if (newCoinCount > 99)
	{ // Case: Player has max coins
		
		int max_charms = 2; // todo: implment CcharmMost()
		if (gsCur->c_charms < max_charms)
		{ // Case: Player has max charms
			// Set coins to 0 and give Sly a lucky charm

			g_pgsCur->c_coins = 0;
			/* todo: gui widget stuff, the function that actually gives the lucky charm
			is a callback on the gui widget */
		}
		else
		{ // Case: Player does not have max charms charms
			
			if (gsCur->c_lives < 99)
			{ // Case: Player does not have max lives
				// Set coins to 0 and give Sly an extra life

				g_pgsCur->c_coins = 0;
				/* todo: gui stuff including the callback that actually gives the extra life */
			}
			else
			{ // Case: Max coins, charms, and lives
				// make sure coins is capped at the max value and do nothing

				g_pgsCur->c_coins = 99;
			}

		}
	}
}
