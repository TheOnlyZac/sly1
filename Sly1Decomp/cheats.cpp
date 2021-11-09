#include "cheats.h"
#include "savegame.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

char chetkido_ciphertext[] = "@KFWHJGL";
char s_the_password_is[] = "The password is: ";

void activate_code_chetkido()
{
    bool i_am_a_hacker = true;

    char cipher_slice[16];
    char* next_xor_char;

    int completion = check_game_completion();

   if ((
       ((g_pgsCur->gameworld << 8 | g_pgsCur->worldlevel) == 0x400) && // curr level is A Perilous Ascent
       ((completion & 6) == 6) && // Save file has 100% completion
       (g_pgsCur->c_coins == 99) && // Coin count is 99
       (g_pgsCur->c_lives == 0) // Lives count is 0
       ) || i_am_a_hacker) // Hacker override
   {
       // Copy encrypted string into sipher 
       strcpy_s(cipher_slice, chetkido_ciphertext);
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