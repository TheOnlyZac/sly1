#include "cheats.h"

#include <Savegame/savegame.h>

#include <cstdio>
#include <cstring>
#include <iostream>

char chetkido_ciphertext[] = "@KFWHJGL";
char s_the_password_is[] = "The password is: ";

void activate_code_chetkido()
{
    bool overrideConditions = true;

    char cipher_slice[16];
    char* next_xor_char;

    const int gameworld = (int)(g_pgsCur->gameworld);
    const int worldlevel = (int)(g_pgsCur->worldlevel);
    const int completion = check_game_completion();

   if ((
       ((gameworld << 8 | worldlevel) == 0x400) && // curr level is A Perilous Ascent
       ((completion & 6) == 6) && // Save file has 100% completion
       (g_pgsCur->c_coins == 99) && // Coin count is 99
       (g_pgsCur->c_lives == 0) // Lives count is 0
       ) || overrideConditions) // Override conditions
   {
       // Copy encrypted string into sipher 
       std::strncpy(cipher_slice, chetkido_ciphertext, 16);
       next_xor_char = cipher_slice;
       
       if (cipher_slice[0] != 0)
       {
           while (true)
           {
               *next_xor_char = cipher_slice[0] ^ 0x23;
               next_xor_char++;
               if (*next_xor_char == 0) break;
               cipher_slice[0] = *next_xor_char;
           }
       }
       std::cout << s_the_password_is << cipher_slice << "\n";
   }
   else
   {
       std::cout << "Conditions not met" << "\n";
   }
   return;
}
