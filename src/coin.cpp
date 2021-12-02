#include <coin.h>
#include <game.h>
#include <gs.h>

/* Handle when the player touches a coin */
void OnCoinSmack(COIN* pcoin)
{
	const GS* gsCur = g_pgsCur;
	const int newCoinCount = g_pgsCur->ccoin + 1;
	
	// Increment coin count
	g_pgsCur->ccoin = newCoinCount;

	if (newCoinCount > 99)
	{ // Case: Player has max coins
		
		int max_charms = CcharmMost();
		if (gsCur->ccharm < max_charms)
		{ // Case: Player does not have max charms
			// Set coins to 0 and give Sly a lucky charm

			g_pgsCur->ccoin = 0;
			/* todo: gui widget stuff, the function that actually gives the lucky charm
			is a callback on the gui widget */
			g_pgsCur->ccharm += 1; // temp
		}
		else
		{ // Case: Player has max charms
			
			if (gsCur->clife < 99)
			{ // Case: Player does not have max lives
				// Set coins to 0 and give Sly an extra life

				g_pgsCur->ccoin = 0;
				/* todo: gui stuff including the callback that actually gives the extra life */
				g_pgsCur->clife += 1; // temp
			}
			else
			{ // Case: Player has max lives
				// Make sure coins is capped at the max value and do nothing

				g_pgsCur->ccoin = 99;
			}

		}
	}
}
