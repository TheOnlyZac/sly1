#ifndef MAIN_H
#define MAIN_H

static int g_chpzArgs;
static char** g_aphzArgs;

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

#endif // MAIN_H
