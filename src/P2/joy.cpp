/**
 * @file joy.cpp
 *
 * @brief Implements the joypad manager.
*/
#include <joy.h>
#include <gs.h>
#include <clock.h>
#include <cstdio>
#include <cstring>
#include <util.h>
#include <transition.h>
#include <libpad.h>

int g_grfusr;
int g_grfjoyt;

const char sChetkidoCiphertext[] = "@KFWHJGL";
const char sThePasswordIs[] = "The password is: %s";

char chetkido_buffer[64]; // temp
int g_grfcht = (int)FCHT_None;

void StartupJoy()
{
    UpdateGrfjoytFromGrfusr();
    scePadInit(0);
    InitJoy(&g_joy, 0, 0);
}

void AddGrfusr(int mask)
{
    g_grfusr |= mask;
    UpdateGrfjoytFromGrfusr();
}

void RemoveGrfusr(int mask)
{
    g_grfusr &= ~mask;
    UpdateGrfjoytFromGrfusr();
}

void UpdateGrfjoytFromGrfusr()
{
    if ((g_grfusr & 0x84) != 0)
    {
        g_grfjoyt = 0;
    }
    else if ((g_grfusr & FUSR_Menu) != 0)
    {
        g_grfjoyt = 5;
    }
    else if ((g_grfusr & FUSR_HandsOff) != 0)
    {
        g_grfjoyt = 4;
    }
    else
    {
        g_grfjoyt = 7;
    }
}

void InitJoy(JOY *pjoy, int nPort, int nSlot)
{
    memset(pjoy, 0, sizeof(JOY));
    SetJoyJoys(pjoy, JOYS_Searching, JOYK_Unknown);
    pjoy->nPort = nPort;
    pjoy->nSlot = nSlot;

    //unk* thing = unk_fun18d4b0(0x140) //todo reverse function
    //u128 paullDma = thing->field_0x3fU & 0xffffffc0;
    ulong_128 *paullDma = (ulong_128 *)0x0; //! temp, will segfault

    pjoy->aullDma = paullDma;
    scePadPortOpen(pjoy->nPort, pjoy->nSlot, paullDma);

    RUMBLE *prumble = /* unk_fun18d4b0(0x20) */ (RUMBLE*)0x0; //! temp, will segfault
    pjoy->prumble = prumble;
    pjoy->fRumbleEnabled = 1;
}

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

void UpdateJoy(JOY *pjoy)
{
    bool cond = false;
    JOYS joysNew;
    JOYK joykNew, joyk;
    uint padState;

    // if the joy manager is initializing, early return
    if (pjoy->joys == JOYS_Initing)
        return;

    padState = scePadGetState(pjoy->nPort, pjoy->nSlot);
    if (padState == 6 || padState == 2) //todo: enum for padState
    {
        cond = true; //todo: what is this condition?
    }
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

    // Return if condition not met
    if (!cond)
        return;

    joysNew = pjoy->joys;
    joykNew = pjoy->joyk;
    if (joysNew == JOYS_Waiting)
    {
        padState = scePadGetState(pjoy->nPort, pjoy->nSlot);
        if (padState != '\x01')
        {
            if (padState > '\x01')
            {
                if (padState != '\x02')
                {
                    joykNew = JOYK_Unknown;
                }
                SetJoyJoys(pjoy, joysNew, joykNew);
                return;
            }
            joykNew = JOYK_Unknown;
            if (padState != '\0')
            {
                SetJoyJoys(pjoy, joysNew, joykNew);
                return;
            }

            joyk = pjoy->joyk;
            if (joyk == JOYK_Analog)
            {
                joykNew = JOYK_Shock;
            }
            else
            {
                if (static_cast<int>(joyk) > 2)
                {
                    joykNew = JOYK_Unknown;

                    if (joyk != JOYK_Shock)
                    {
                        SetJoyJoys(pjoy, joysNew, joykNew);
                        return;
                    }
                    joykNew = JOYK_Shock2;
                    joysNew = JOYS_Ready;
                    SetJoyJoys(pjoy, joysNew, joykNew);
                    return;
                }
                //todo
                //...
            }
        }
    }
    else
    {
        // todo
        // ...
    }

    SetJoyJoys(pjoy, joysNew, joykNew);
}

void SetRumbleRums(RUMBLE *prumble, RUMS rums)
{
    // ...
}

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

void UpdateCodes()
{
    if (g_tCodeCheck != 0x0f && g_tCodeCheck <= g_clock.tReal)
    {
        // ...
    }

    // ...

    g_tCodeCheck = 0.0f;
}

void RemoveAllFchts()
{
    g_grfcht = FCHT_None;
    g_transition.ResetWorld(FTRANS_None); // todo double check, should ResetWorld be static?
}

void AddFcht(int nParam)
{
    g_grfcht |= nParam & ~(int)FCHT_ResetWorld;
    if ((nParam & 0x4000) != 0)
    {   // Case: Cheat reload flag set
        //ResetWorld(FTRANS::None); // todo
    }
}

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
        strncpy(cipherSlice, sChetkidoCiphertext, 16);
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
