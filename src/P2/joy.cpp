#include <joy.h>
#include <gs.h>
#include <clock.h>

#include <cstdio>
#include <cstring>

const char sChetkidoCiphertext[] = "@KFWHJGL";
const char sThePasswordIs[] = "The password is: %s";

char chetkido_buffer[64]; // temp
int g_grfcht = (int)FCHT_None;

// Sets the given joypad state
void SetJoyJoys(JOY *pjoy, JOYS joys, JOYK joyk)
{
    if (joys == pjoy->joys && joyk == pjoy->joyk)
        return;

    // Check if controller is missing
    if (joyk == JOYK_Unknown)
    {
        pjoy->term = 0;
        joys = JOYS_Searching;
    }
    JOYK joykPrev = pjoy->joyk;

    // Check for rumble conditions
    if ((int)joykPrev < 3 && (int)joyk > 2)
    {
        InitRumble(pjoy->prumble, pjoy->nPort, pjoy->nSlot);
    }

    if (joys == JOYS_Ready)
    {
        pjoy->tRead = 0.0f;

        pjoy->fStickMoved = 0;
        pjoy->fStickMoved2 = 0;
        LM *almDeflect = pjoy->almDeflect;
        LM *almDeflect2 = pjoy->almDeflect2;

        for (int i = 0; i < 4; i++)
        {
            almDeflect->gMin = -0.75f;
            almDeflect->gMax = 0.75f;
            almDeflect += 1;

            almDeflect2->gMin = -0.75f;
            almDeflect2->gMax = 0.75;
            almDeflect2 += 1;
        }
    }

    pjoy->joys = joys;
    pjoy->joyk = joyk;
    pjoy->tJoys = g_clock.tReal;
}

// Updates the joypad manager
void UpdateJoy(JOY *pjoy)
{
    bool condition = false;
    JOYS joysNew{};

    // if the joy manager is initializing, abort
    if (pjoy->joys == JOYS_Initing)
        return;

    //unsigned long padState = padGetState(pjoy->nPort, pjoy->nSlot); // ps2sdk call
    unsigned long padState = 0.0l; // temp

    if (padState == 6 || padState == 2)
        condition = true;
    joysNew = pjoy->joys;

    if (joysNew != JOYS_Ready)
    {
        if (pjoy->joyk != JOYK_Unknown)
        {
            if (g_clock.tReal - pjoy->tJoys >= 2.0f)
            {
                padState = 0;
            }
        }
    }

    if (pjoy->joyk != JOYK_Unknown && padState == 0)
    {
        SetJoyJoys(pjoy, JOYS_Searching, JOYK_Unknown);
    }

    if (!condition)
        return;

    joysNew = pjoy->joys;
    JOYK joyk = pjoy->joyk;
    if (joysNew == JOYS_Waiting)
    {
        // todo
        // ...
    }
    else
    {
        // todo
        // ...
    }

    SetJoyJoys(pjoy, joysNew, joyk);
}

// todo
void SetRumbleRums(RUMBLE *prumble, RUMS rums)
{
    // ...
}

// Set the rumble rums on the controller in the given port/slot
void InitRumble(RUMBLE *prumble, int nPort, int nSlot)
{
    if (prumble->rums == RUMS_Dead)
    {
        SetRumbleRums(prumble, RUMS_Idle);
        prumble->nSlot = nSlot;
    }
    else
    {
        SetRumbleRums(prumble, RUMS_Stop);
        prumble->nSlot = nSlot;
    }
    prumble->nPort = nPort;
}

// todo
void UpdateCodes()
{
    if (g_tCodeCheck != 0x0f && g_tCodeCheck <= g_clock.tReal)
    {
        // ...
    }

    // ...

    g_tCodeCheck = 0.0f;
}

/* Sets the given cheat flag and reloads the level if necessary */
void AddFcht(int nParam)
{
    g_grfcht |= nParam & ~(int)FCHT_ResetWorld;
    if ((nParam & 0x4000) != 0)
    {   // Case: Cheat reload flag set
        //ResetWorld(FTRANS::None); // todo
    }
}

void AddGrfusr(int mask)
{
    //todo
}

/* Decrypt the chetkido string and output the hidden message */
void CheatActivateChetkido()
{
    char cipherSlice[16];
    char *nextXorChar;
    char out_buffer[64];

    const int gameworld = (int)(g_pgsCur->gameworldCur);
    const int worldlevel = (int)(g_pgsCur->worldlevelCur);
    const int completion = FGameCompletion();

    if (((gameworld << 8 | worldlevel) == 0x400) // curr level is snow approach
        && ((completion & 6) == 6)               // save file has 100% completion
        && (g_pgsCur->ccoin == 99)               // coin count is 99
        && (g_pgsCur->clife == 0))               // lives count is 0
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
                if (*nextXorChar == 0)
                    break;
                cipherSlice[0] = *nextXorChar;
            }
        }

        /* Write output string to char buffer and show on-screen
	     temporarily using chetkido buffer to store output until blot class is implemented */

        sprintf(out_buffer, "%s", sThePasswordIs);
        sprintf(chetkido_buffer, "%s", out_buffer);
        //cornerPopupBlot::prepareGuiText(out_buffer); // todo: blot class
        //SetBlotDtVisible(cornerPopupBlog, 10.0); // todo: implement classmethod
        //cornerPopupBlot::openIfNotAlready(); // todo: implement classmethod
    }
}
