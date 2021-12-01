#include <joy.h>
#include <gs.h>

#include <cstdio>
#include <cstring>

const char sChetkidoCiphertext[] = "@KFWHJGL";
const char sThePasswordIs[] = "The password is: %s";

char chetkido_buffer[64]; // temp
int g_grfcht = (int)FCHT::None;

/* Sets the given cheat flag and reloads the level if necessary */
void AddFcht(int nParam)
{
	g_grfcht |= nParam & ~(int)FCHT::ResetWorld;
	if ((nParam & 0x4000) != 0)
	{ // Case: Cheat reload flag set
		//ResetWorld(FTRANS::None); // todo
	}
}

/* Decrypt the chetkido string and output the hidden message */
void CheatActivateChetkido()
{
    char cipherSlice[16];
    char* nextXorChar;
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
       nextXorChar = cipherSlice;
       
	   /* Decrypt the string "@KFWHJGL" resulting in "chetkido"
	    (XOR cipher with key 0x23) */
       if (cipherSlice[0] != 0)
       {
           while (true)
           {
               *nextXorChar = cipherSlice[0] ^ 0x23;
               nextXorChar++;
               if (*nextXorChar == 0) break;
               cipherSlice[0] = *nextXorChar;
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
