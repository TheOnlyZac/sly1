#include <cheats.h>
#include <savegame.h>

#include <cstdio>
#include <cstring>
#include <iostream>

char chetkido_buffer[64]; // temp
int g_grfcht = (int)FCHT::None;

const char sChetkidoCiphertext[] = "@KFWHJGL";
const char sThePasswordIs[] = "The password is: %s";

/* Decrypt the chetkido string and output the hidden message */
void CheatActivateChetkido()
{
    char cipherSlice[16];
    char* next_xor_char;
	char out_buffer[64];

    const int gameworld = (int)(g_pgsCur->gameworld);
    const int worldlevel = (int)(g_pgsCur->worldlevel);
    const int completion = FGameCompletion();

   if (
       ((gameworld << 8 | worldlevel) == 0x400) && // curr level is snow approach
       ((completion & 6) == 6) && // check save file has 100% completion
       (g_pgsCur->c_coins == 99) && // check oin count is 99
       (g_pgsCur->c_lives == 0)) // check lives count is 0
   {
       // Copy encrypted string into cipher 
       std::strncpy(cipherSlice, sChetkidoCiphertext, 16);
       next_xor_char = cipherSlice;
       
	   // Decrypt the string "@KFWHJGL" resulting in "chetkido"
	   // (XOR cipher with key 0x23)
       if (cipherSlice[0] != 0)
       {
           while (true)
           {
               *next_xor_char = cipherSlice[0] ^ 0x23;
               next_xor_char++;
               if (*next_xor_char == 0) break;
               cipherSlice[0] = *next_xor_char;
           }
       }

	   /* Write output string to char buffer and show on-screen
	     temporarily using chetkido buffer to store output until blot class is implemented */
	   sprintf(out_buffer, sThePasswordIs, cipherSlice);
	   sprintf(chetkido_buffer, out_buffer); // temp
       //cornerPopupBlot::prepareGuiText(out_buffer); // todo: blot class
	   //SetBlotDtVisible(cornerPopupBlog, 10.0); // todo: implement classmethod
	   //cornerPopupBlot::openIfNotAlready(); // todo: implement classmethod
   }
}
