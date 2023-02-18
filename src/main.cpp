#include <gs.h>
#include <joy.h>

#include <stdio.h>

int main(int argc, char* argv[])
{
	printf("Sly Cooper and the Thievius Raccoonus (SCUS-971.98)\n");

	// Set chetkido values
	g_pgsCur->gameworldCur = GAMEWORLD::Snow;
	g_pgsCur->worldlevelCur = WORLDLEVEL::Approach;
	g_pgsCur->ccoin = 99;
	g_pgsCur->clife = 0;

	printf("Press ENTER to quit...\n");

	char chKey = ' ';
	char chLastKey = ' ';

	while (true)
	{
		// Get player input
		chLastKey = chKey;
		chKey = getc(stdin);

		// Check and handle player input
		switch (chKey)
		{
		case '\r': // Quit game
			printf("Thanks for playing!\n");
			return 1;
		case 'x': // Show jump button pressed
		case 'X':
			printf("jump ");
			break;
		case 'o': // Show circle button pressed
		case 'O':
			printf("circle ");

			// Check for easter egg (jump and press the circle button)
			if (chLastKey == 'x' || chLastKey == 'X')
			{
				CheatActivateChetkido();
				printf("\n");
				printf(chetkido_buffer);
				printf("\n");
			}

			break;
		default: // Print key pressed
			putchar(chKey);
			printf(" ");
			break;
		}
	}

    return 0;
}
