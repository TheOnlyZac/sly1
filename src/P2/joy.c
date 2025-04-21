#include <sce/memset.h>
#include <sdk/ee/libpad.h>
#include <joy.h>
#include <clock.h>
#include <transition.h>
#include <game.h>
#include <text.h>
#include <screen.h>
#include <sound.h>

// static char g_chzThePasswordIs[] = "The password is: %s";
// static char g_chzCiphertext[] = "@KFWHJGL"; // decrypts to "chetkido"
extern char g_chzThePasswordIs[];
extern char g_chzCiphertext[];

extern void *PvAllocGlobalImpl(int); // todo: remove when function is known

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
    if (g_grfusr & 0x84)
    {
        // Unknown state
        g_grfjoyt = 0;
    }
    else if (g_grfusr & FUSR_Menu)
    {
        // Pause menu/dialog box is open
        g_grfjoyt = 5;
    }
    else if (g_grfusr & FUSR_HandsOff)
    {
        // In-game cutscene/transition/animation is playing
        g_grfjoyt = 4;
    }
    else
    {
        // Game is running normally
        g_grfjoyt = 7;
    }
}

// todo: investigate if aullDma assignment can be cleaned up when type is known
void InitJoy(JOY *pjoy, int nPort, int nSlot)
{
    memset(pjoy, 0, sizeof(JOY));
    SetJoyJoys(pjoy, JOYS_Searching, JOYK_Unknown);
    pjoy->nPort = nPort;
    pjoy->nSlot = nSlot;
    pjoy->aullDma = (uint *)(((int)PvAllocGlobalImpl(0x140) + 0x3F) & ~0x3F);
    scePadPortOpen(pjoy->nPort, pjoy->nSlot, pjoy->aullDma);
    pjoy->prumble = (RUMBLE *)PvAllocGlobalImpl(0x20);
    pjoy->fRumbleEnabled = true;
}

INCLUDE_ASM(const s32, "P2/joy", UpdateJoy__FP3JOY);
#ifdef SKIP_ASM
/**
 * @todo 31.94% matched.
 */
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
    if (padState == 6 || padState == 2) // todo: enum for padState
    {
        cond = true; // todo: what is this condition?
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
                // todo
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
#endif // SKIP_ASM

void SetJoyJoys(JOY *pjoy, JOYS joys, JOYK joyk)
{
    JOYK joykPrev;
    LM *almDeflect2;
    LM *almDeflect;
    float *almDeflect2Max;
    float *almDeflectMax;
    uint i;

    if (joys != pjoy->joys || joyk != pjoy->joyk)
    {
        if (joyk == JOYK_Unknown)
        {
            pjoy->term = 0;
            joys = JOYS_Searching;
            joykPrev = pjoy->joyk;
        }
        else
        {
            joykPrev = pjoy->joyk;
        }

        if (joykPrev < 3 && 2 < joyk)
        {
            InitRumble(pjoy->prumble, pjoy->nPort, pjoy->nSlot);
        }

        if (joys == JOYS_Ready)
        {
            i = 0;
            pjoy->tRead = 0.0;
            pjoy->fStickMoved2 = 0;
            almDeflectMax = &pjoy->almDeflect[0].gMax;
            pjoy->fStickMoved = 0;
            almDeflect2Max = &pjoy->almDeflect2[0].gMax;
            pjoy->grfbtn = 0;
            almDeflect = pjoy->almDeflect;
            almDeflect2 = pjoy->almDeflect2;

            for (; i < 4; i++)
            {
                almDeflect2->gMin = -0.75;
                almDeflect->gMin = -0.75;
                almDeflect2++;
                *almDeflect2Max = 0.75;
                almDeflect++;
                *almDeflectMax = 0.75;
                almDeflect2Max += 2;
                almDeflectMax += 2;
            }
        }

        pjoy->joys = joys;
        pjoy->joyk = joyk;
        pjoy->tJoys = g_clock.tReal;
    }
}

INCLUDE_ASM(const s32, "P2/joy", GetJoyXYDeflection__FP3JOYUcUcPfN23PUcT6PiP2LM);

INCLUDE_ASM(const s32, "P2/joy", FReadJoy__FP3JOY);

void SetJoyBtnHandled(JOY *pjoy, GRFBTN btn)
{
    pjoy->grfbtnPressed &= ~btn;
}

void TriggerJoyRumbleRumk(JOY *pjoy, RUMK rumk, float dt)
{
    if (pjoy->fRumbleEnabled && pjoy->joyk > JOYK_Analog && pjoy->joys == JOYS_Ready)
    {
        TriggerRumbleRumk(pjoy->prumble, rumk, dt);
    }
}

INCLUDE_ASM(const s32, "P2/joy", func_0016EC80);

void StartJoySelection(JOY *pjoy)
{
    pjoy->dxLatch = 0;
    pjoy->dyLatch = 0;
}

INCLUDE_ASM(const s32, "P2/joy", DxSelectionJoy__FP3JOY);

INCLUDE_ASM(const s32, "P2/joy", DySelectionJoy__FP3JOY);

INCLUDE_ASM(const s32, "P2/joy", UBtnpJoy__FP3JOY4BTNP);

void AddCode(CODE *pcode)
{
    CODE *p_inputs_counter = g_pcode;

    while (p_inputs_counter != nullptr)
    {
        if (pcode == p_inputs_counter)
        {
            return;
        }
        p_inputs_counter = p_inputs_counter->pchtNext;
    }

    pcode->pchtNext = g_pcode;
    g_pcode = pcode;
    if (g_joy.grfbtn == *pcode->ajbc)
    {
        pcode->nInputCounter = 1;
    }
    else
    {
        pcode->nInputCounter = 0;
    }
}

INCLUDE_ASM(const s32, "P2/joy", func_0016F1F0);

void _ResetCodes()
{
    CODE *pcode = g_pcode;
    if (g_pcode != nullptr)
    {
        g_pcode->nInputCounter = 0;
        while (pcode = pcode->pchtNext, pcode != nullptr)
        {
            pcode->nInputCounter = 0;
        }
    }
}

void _MatchCodes(JOY *pjoy, GRFBTN btn)
{
    if (g_pcode != nullptr && pjoy == &g_joy && btn != g_joy.grfbtn && g_joy.grfbtn != 0)
    {
        CODE *pcode = g_pcode;

        while (pcode != nullptr)
        {
            if (pcode->nInputCounter < pcode->cjbc)
            {
                if (g_joy.grfbtn == pcode->ajbc[pcode->nInputCounter])
                {
                    pcode->nInputCounter++;
                }
                else
                {
                    pcode->nInputCounter = 0;
                }
            }
            pcode = pcode->pchtNext;
        }
        g_tCodeCheck = g_clock.tReal + 1.0f;
    }
}

INCLUDE_ASM(const s32, "P2/joy", UpdateCodes__Fv);
#ifdef SKIP_ASM
/**
 * @todo 45.89% matched.
 */
void UpdateCodes()
{
    int i;
    CODE **ppcht;
    CODE *pchtToExecute;
    CODE *pcht;

    if (g_tCodeCheck != 0x0f && g_tCodeCheck <= g_clock.tReal)
    {
        pchtToExecute = NULL;
        pcht = g_pcode;

        if (g_pcode != NULL)
        {
            i = g_pcode->index;
            pcht = g_pcode;
            while (true)
            {
                if (i == 0)
                {
                    if (pcht->nInputCounter < pcht->cjbc)
                    {
                        ppcht = &pcht->pchtNext;
                    }
                    else if ((/* pchtToExecute == NULL || */ // todo fix
                              ppcht = &pcht->pchtNext,
                              pchtToExecute->cjbc < pcht->cjbc))
                    {
                        ppcht = &pcht->pchtNext;
                        pchtToExecute = pcht;
                    }
                }
                else
                {
                    *ppcht = pcht->pchtNext;
                    pcht->pchtNext = NULL;
                    pcht->nInputCounter = 0;
                    pcht->index = 0;
                }
                pcht = *ppcht;
                if (pcht == NULL)
                    break;

                i = pcht->index;
            }
        }

        // Check if we found a match
        if (pchtToExecute != NULL)
        {
            // Execute the cheat
            StartSound(SFXID_UiTick, NULL, NULL, NULL, 3000, 300, 1, 0, 0, NULL, NULL);
            //(pchtToExecute->pfn)(pchtToExecute->nParam); //todo fix function pointer
        }

        _ResetCodes();
        g_tCodeCheck = 0.0f;
    }
}
#endif

void ClearFchts()
{
    g_grfcht = FCHT_None;
    ResetWorld(FTRANS_None);
}

void AddFcht(int nParam)
{
    g_grfcht |= nParam & ~FCHT_ResetWorld;
    if (nParam & FCHT_ResetWorld)
    {
        ResetWorld(FTRANS_None);
    }
}

INCLUDE_ASM(const s32, "P2/joy", func_0016F470);

void Chetkido()
{
    // Check preconditions
    int widCur;
    FGS cmpFlags;
    GS *gsCur;

    widCur = (g_pgsCur->gameworldCur << 8) | (g_pgsCur->worldlevelCur);
    if (widCur != 0x400) // level is "A Perilous Ascent"
        return;

    cmpFlags = get_game_completion();
    if ((cmpFlags & (FGS_HalfClues | FGS_AllClues)) != (FGS_HalfClues | FGS_AllClues)) // clues collected
        return;

    gsCur = g_pgsCur;
    if (gsCur->ccoin != 99 || gsCur->clife != 0) // 99 coins and 0 lives
        return;

    // Decrypt chetkido using XOR cipher, key 0x23
    char buf[64];
    char achzPlaintext[16];
    char *pchCur = &achzPlaintext[0];

    strcpy(achzPlaintext, g_chzCiphertext);
    while (*pchCur != '\0')
    {
        *pchCur++ ^= 0x23;
    }

    // Show note blot with message
    sprintf(buf, g_chzThePasswordIs, achzPlaintext);
    ((NOTE *)&g_note.unk278)->pvtnote->pfnSetNoteAchzDraw((NOTE *)&g_note.unk278, buf);
    SetBlotDtVisible((NOTE *)&g_note.unk278, 10.0f);
    ((NOTE *)&g_note.unk278)->pvtnote->pfnShowBlot((NOTE *)&g_note.unk278);
}

INCLUDE_ASM(const s32, "P2/joy", StartupCodes__Fv);
#ifdef SKIP_ASM
/**
 * @todo 4.38% matched.
 */
void StartupCodes()
{
    ////AddCode(&cheat_reload_level.pCodeSeq);
    ////AddCode(&cheat_reload_no_cheats.pCodeSeq);
    ////AddCode(&cheat_reload_slippery_movement.pCodeSeq);
    ////AddCode(&cheat_slippery_objects.pCodeSeq);
    ////AddCode(&cheat_infinite_charms.pCodeSeq);
    ////AddCode(&cheat_collect_bottles.pCodeSeq);
    ////AddCode(&cheat_unlock_pages.pCodeSeq);
    ////AddCode(&cheat_unlock_all_worlds.pCodeSeq);
    ////AddCode(&cheat_chetkido_password.pCodeSeq);
}
#endif // SKIP_ASM
