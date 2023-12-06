#ifndef MAIN_H
#define MAIN_H

static int g_chpzArgs;
static char** g_aphzArgs;

static int g_cframe;

/**
 * @brief Main function
 *
 * @param cphzArgs Number of arguments
 * @param aphzArgs Array of arguments
*/
int main(int cphzArgs, char* aphzArgs[]);

/**
 * @brief Starts up the main game systems.
*/
void Startup();

/**
 * @brief Temp, used for debugging.
 *
 * Prints the current tick to stdout.
 *
 * @note This function is not in the game and is only used for testing.
*/
void MainDebug();

#endif // MAIN_H
