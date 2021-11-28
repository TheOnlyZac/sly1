#include <util.h>
#include <game.h>
#include <joy.h>
#include <savegame.h>
#include <difficulty.h>
#include <coin.h>
#include <aseg.h>
#include <wipe.h>
#include <xform.h>

#include <stdio.h>
#include <iostream>
#include <conio.h>

int main(int argc, char* argv[])
{
	std::cout << "Sly Cooper and the Thievius Raccoonus (SCUS-971.98)" << std::endl;

	// Set chetkido values
	g_pgsCur->gameworld = GAMEWORLD::Snow;
	g_pgsCur->worldlevel = WORLDLEVEL::Approach;
	g_pgsCur->c_coins = 99;
	g_pgsCur->c_lives = 0;

	std::cout << "Press ENTER to quit..." << std::endl;

	char chKey = ' ';
	char chLastKey = ' ';

	while (true)
	{
		// Get player input
		chLastKey = chKey;
		chKey = getch();

		// Check and handle player input
		switch (chKey)
		{
		case '\r': // Quit game
			std::cout << std::endl << "Thanks for playing!" << std::endl;
			return 1;
			break;
		case ' ': // Show jump button pressed
			std::cout << "jump ";
			break;
		case 'o': // Show circle button pressed
			std::cout << "circle ";

			// Check for easter egg (jump and press the circle button)
			if (chLastKey == ' ')
			{
				CheatActivateChetkido();
				std::cout << std::endl << chetkido_buffer << std::endl;
			}

			break;
		default: // Print key pressed
			std::cout << chKey << " ";
			break;
		}
	}

    return 0;
}
