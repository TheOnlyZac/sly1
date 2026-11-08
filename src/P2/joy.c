#include <joy.h>
#include <game.h>
#include <cm.h>
#include <text.h>
#include <clock.h>
#include <sound.h>
#include <memory.h>
#include <screen.h>
#include <transition.h>
#include <sce/memset.h>
#include <sdk/ee/libpad.h>

// static char g_chzThePasswordIs[] = "The password is: %s";
// static char g_chzCiphertext[] = "@KFWHJGL"; // decrypts to "chetkido"
extern char g_chzThePasswordIs[];
extern char g_chzCiphertext[];

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

INCLUDE_ASM("asm/nonmatchings/P2/joy", UpdateJoy__FP3JOY);
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
    if (joys == pjoy->joys && joyk == pjoy->joyk)
        return;

    if (joyk == JOYK_Unknown)
    {
        pjoy->term = 0;
        joys = JOYS_Searching;
    }

    JOYK joykPrev = pjoy->joyk;
    if (joykPrev < JOYK_Shock && joyk > JOYK_Analog)
    {
        InitRumble(pjoy->prumble, pjoy->nPort, pjoy->nSlot);
    }

    if (joys == JOYS_Ready)
    {
        uint i = 0;
        pjoy->tRead = 0.0f;
        pjoy->fStickMoved2 = 0;
        pjoy->fStickMoved = 0;
        pjoy->grfbtn = 0;

        float *almDeflectMax = &pjoy->almDeflect[0].gMax;
        float *almDeflect2Max = &pjoy->almDeflect2[0].gMax;
        LM *almDeflect = pjoy->almDeflect;
        LM *almDeflect2 = pjoy->almDeflect2;

        for (; i < 4; i++)
        {
            almDeflect2->gMin = -0.75f;
            almDeflect2++;

            almDeflect->gMin = -0.75f;
            almDeflect++;

            *almDeflect2Max = 0.75f;
            almDeflect2Max += 2;

            *almDeflectMax = 0.75f;
            almDeflectMax += 2;
        }
    }

    pjoy->joys = joys;
    pjoy->joyk = joyk;
    pjoy->tJoys = g_clock.tReal;
}

INCLUDE_ASM("asm/nonmatchings/P2/joy", GetJoyXYDeflection__FP3JOYUcUcPfN23PUcT6PiP2LM);
#ifdef SKIP_ASM
/**
 * @todo ~60% matched, the logic is right but the float register allocation differs.
 */
void GetJoyXYDeflection(JOY *pjoy, uchar bX, uchar bY, float *pdx, float *pdy, float *pu, uchar *pbXPrev, uchar *pbYPrev, int *pfMoved, LM *alm)
{
    int fMoved = *pfMoved;
    float x, y;

    if (fMoved == 0)
    {
        if (pjoy->tRead != 0.0f)
        {
            if (bX != *pbXPrev || bY != *pbYPrev || bX < 0x60 || bX > 0xA0 || bY < 0x60 || bY > 0xA0)
                fMoved = 1;
        }
        *pfMoved = fMoved;
    }

    if (fMoved)
    {
        x = (float)bX * 2.0f * (1.0f / 255.0f) + -1.0f;
        y = 1.0f - (float)bY * 2.0f * (1.0f / 255.0f);
    }
    else
    {
        x = 0.0f;
        y = 0.0f;
    }

    float xx = x * x;
    float yy = y * y;
    float uMax = 0.0f;
    for (uint i = 0; i < 4; i++)
    {
        float d = x * g_aja[i][0] + y * g_aja[i][1];
        float lim;
        if (d >= 0.0f)
        {
            if (alm[i].gMax < d)
                alm[i].gMax = d;
            lim = alm[i].gMax;
        }
        else
        {
            if (d < alm[i].gMin)
                alm[i].gMin = d;
            lim = alm[i].gMin;
        }
        lim = d / lim;
        if (uMax < lim)
            uMax = lim;
    }

    float uLo = 0.0f;
    float uHi = 1.0f;
    float uRaw = (uMax - 0.35f) * 2.0f;
    float u;
    if (uRaw < uLo)
        u = uLo;
    else if (uRaw > uHi)
        u = uHi;
    else
        u = uRaw;
    *pu = u;

    float len = __builtin_sqrtf(xx + yy);
    if (len > 0.0001f)
    {
        *pdx = u * x / len;
        *pdy = u * y / len;
    }
    else
    {
        *pdx = *pdy = 0.0f;
    }

    *pbXPrev = bX;
    *pbYPrev = bY;
}
#endif // SKIP_ASM

int FReadJoy(JOY *pjoy)
{
    u_char abPad[0x40];
    u_char *pabPad = abPad;
    int fRet = 1;

    memset(pabPad, 0, sizeof(abPad));

    if (scePadRead(pjoy->nPort, pjoy->nSlot, pabPad) > 0)
    {
        GRFBTN grfbtnPrev = pjoy->grfbtn;
        pjoy->grfbtn = ~((abPad[2] << 8) | abPad[3]);

        if (pjoy->term != 0)
        {
            if (pjoy->term != abPad[1])
                fRet = 0;
        }
        pjoy->term = abPad[1];

        if (pjoy->joyk == JOYK_Shock2)
            CopyAb(pjoy->mpbtnpb, &abPad[8], 12);

        pjoy->grfbtnPressed = pjoy->grfbtn & ~grfbtnPrev;
        pjoy->grfbtnReleased = grfbtnPrev & ~pjoy->grfbtn;

        if (pjoy->joyk >= JOYK_Analog)
        {
            GetJoyXYDeflection(pjoy, abPad[6], abPad[7], &pjoy->x, &pjoy->y, &pjoy->uDeflect, &pjoy->bX, &pjoy->bY, &pjoy->fStickMoved, pjoy->almDeflect);
            GetJoyXYDeflection(pjoy, abPad[4], abPad[5], &pjoy->x2, &pjoy->y2, &pjoy->uDeflect2, &pjoy->bX2, &pjoy->bY2, &pjoy->fStickMoved2, pjoy->almDeflect2);
        }
        else
        {
            pjoy->y2 = pjoy->uDeflect2 = pjoy->x = pjoy->y = pjoy->uDeflect = pjoy->x2 = 0.0f;
            // the repeated store is needed to match
            pjoy->x2 = 0.0f;
        }

        // let the d-pad stand in for the left stick unless the camera is in a state that handles input itself
        if (g_pcm == NULL || STRUCT_OFFSET(g_pcm, 0x3D0, int) == 0 || STRUCT_OFFSET(g_pcm, 0x3D8, void *) != (void *)((uint8_t *)g_pcm + 0x454))
        {
            if (pjoy->grfbtn & 0xF000)
            {
                pjoy->x = pjoy->y = pjoy->uDeflect = 0.0f;

                if (pjoy->grfbtn & PAD_LEFT_ARROW)
                    pjoy->x = -1.0f;
                else if (pjoy->grfbtn & PAD_RIGHT_ARROW)
                    pjoy->x = 1.0f;

                if (pjoy->grfbtn & PAD_UP_ARROW)
                    pjoy->y = 1.0f;
                else if (pjoy->grfbtn & PAD_DOWN_ARROW)
                    pjoy->y = -1.0f;

                if (pjoy->x * pjoy->y != 0.0f)
                {
                    pjoy->x *= 0.8f;
                    pjoy->y *= 0.8f;
                }
                pjoy->uDeflect = 1.0f;
            }
        }

        _MatchCodes(pjoy, grfbtnPrev);
        pjoy->tRead = g_clock.tReal;

        if (pjoy->grfbtn != 0 || pjoy->uDeflect != 0.0f || pjoy->uDeflect2 != 0.0f)
            pjoy->tActive = g_clock.tReal;
    }
    else
    {
        if (g_clock.tReal - pjoy->tRead >= 2.0f)
            fRet = 0;
    }

    return fRet;
}

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

JUNK_NOP();
JUNK_ADDIU(10);

void StartJoySelection(JOY *pjoy)
{
    pjoy->dxLatch = 0;
    pjoy->dyLatch = 0;
}

int DxSelectionJoy(JOY *pjoy)
{
    if (pjoy->dxLatch == 0)
    {
        if (pjoy->grfbtnPressed & PAD_LEFT_ARROW)
        {
            SetJoyBtnHandled(pjoy, PAD_LEFT_ARROW);
            pjoy->dxLatch = -1;
        }
        else if (pjoy->grfbtnPressed & PAD_RIGHT_ARROW)
        {
            SetJoyBtnHandled(pjoy, PAD_RIGHT_ARROW);
            pjoy->dxLatch = 1;
        }
        else if (pjoy->uDeflect >= 0.8f && __builtin_fabsf(pjoy->x) > __builtin_fabsf(pjoy->y))
        {
            if (pjoy->x < 0.0f)
                pjoy->dxLatch = -1;
            else
                pjoy->dxLatch = 1;
        }

        if (pjoy->dxLatch != 0)
        {
            pjoy->dtLatchX = 0.3333f;
            pjoy->tLatchX = g_clock.tReal + pjoy->dtLatchX;
        }
    }
    else
    {
        int fHeld = 0;
        if (pjoy->dxLatch < 0)
        {
            if ((pjoy->grfbtn & PAD_LEFT_ARROW) || (pjoy->uDeflect >= 0.25f && __builtin_fabsf(pjoy->x) > __builtin_fabsf(pjoy->y) && pjoy->x < 0.0f))
                fHeld = 1;
        }
        else
        {
            if ((pjoy->grfbtn & PAD_RIGHT_ARROW) || (pjoy->uDeflect >= 0.25f && __builtin_fabsf(pjoy->x) > __builtin_fabsf(pjoy->y) && 0.0f < pjoy->x))
                fHeld = 1;
        }

        if (!fHeld)
        {
            pjoy->dxLatch = 0;
        }
        else if (pjoy->tLatchX <= g_clock.tReal)
        {
            float dtMin = 0.1f;
            float dtMax = 0.3333f;
            float dt = pjoy->dtLatchX * 2.0f * 0.33333334f;
            float dtNew;
            if (dt < dtMin)
                dtNew = dtMin;
            else if (dt > dtMax)
                dtNew = dtMax;
            else
                dtNew = dt;
            pjoy->dtLatchX = dtNew;
            pjoy->tLatchX = g_clock.tReal + dtNew;
        }
        else
        {
            return 0;
        }
    }
    return pjoy->dxLatch;
}

int DySelectionJoy(JOY *pjoy)
{
    if (pjoy->dyLatch == 0)
    {
        if (pjoy->grfbtnPressed & PAD_UP_ARROW)
        {
            SetJoyBtnHandled(pjoy, PAD_UP_ARROW);
            pjoy->dyLatch = -1;
        }
        else if (pjoy->grfbtnPressed & PAD_DOWN_ARROW)
        {
            SetJoyBtnHandled(pjoy, PAD_DOWN_ARROW);
            pjoy->dyLatch = 1;
        }
        else if (pjoy->uDeflect >= 0.8f && __builtin_fabsf(pjoy->y) > __builtin_fabsf(pjoy->x))
        {
            if (0.0f < pjoy->y)
                pjoy->dyLatch = -1;
            else
                pjoy->dyLatch = 1;
        }

        if (pjoy->dyLatch != 0)
        {
            pjoy->dtLatchY = 0.3333f;
            pjoy->tLatchY = g_clock.tReal + pjoy->dtLatchY;
        }
    }
    else
    {
        int fHeld = 0;
        if (pjoy->dyLatch < 0)
        {
            if ((pjoy->grfbtn & PAD_UP_ARROW) || (pjoy->uDeflect >= 0.25f && __builtin_fabsf(pjoy->y) > __builtin_fabsf(pjoy->x) && 0.0f < pjoy->y))
                fHeld = 1;
        }
        else
        {
            if ((pjoy->grfbtn & PAD_DOWN_ARROW) || (pjoy->uDeflect >= 0.25f && __builtin_fabsf(pjoy->y) > __builtin_fabsf(pjoy->x) && pjoy->y < 0.0f))
                fHeld = 1;
        }

        if (!fHeld)
        {
            pjoy->dyLatch = 0;
        }
        else if (pjoy->tLatchY <= g_clock.tReal)
        {
            float dtMin = 0.1f;
            float dtMax = 0.3333f;
            float dt = pjoy->dtLatchY * 2.0f * 0.33333334f;
            float dtNew;
            if (dt < dtMin)
                dtNew = dtMin;
            else if (dt > dtMax)
                dtNew = dtMax;
            else
                dtNew = dt;
            pjoy->dtLatchY = dtNew;
            pjoy->tLatchY = g_clock.tReal + dtNew;
        }
        else
        {
            return 0;
        }
    }
    return pjoy->dyLatch;
}

float UBtnpJoy(JOY *pjoy, BTNP btnp)
{
    if (pjoy->grfbtn & g_mpbtnpfbtn[btnp])
    {
        if (pjoy->joyk >= JOYK_Shock2)
        {
            int r = 1;
            int b = pjoy->mpbtnpb[btnp];
            if (r < b)
                r = b;
            return r * (1.0f / 255.0f);
        }
        return 1.0f;
    }
    return 0.0f;
}

void AddCode(CODE *pcode)
{
    CODE *p_inputs_counter = g_pcode;

    while (p_inputs_counter)
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

JUNK_NOP();
JUNK_WORD(0xAC820014);

void _ResetCodes()
{
    CODE *pcode = g_pcode;
    if (!pcode)
        return;

    pcode->nInputCounter = 0;
    while (pcode = pcode->pchtNext)
    {
        pcode->nInputCounter = 0;
    }
}

void _MatchCodes(JOY *pjoy, GRFBTN btn)
{
    if (!g_pcode || pjoy != &g_joy || btn == g_joy.grfbtn || g_joy.grfbtn == 0)
        return;

    CODE *pcode = g_pcode;
    while (pcode)
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

INCLUDE_ASM("asm/nonmatchings/P2/joy", UpdateCodes__Fv);
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

JUNK_NOP();
JUNK_ADDIU(10);

void Chetkido()
{
    // Check preconditions.
    int widCur = (g_pgsCur->gameworldCur << 8) | (g_pgsCur->worldlevelCur);
    if (widCur != 0x400) // level is "A Perilous Ascent"
        return;

    FGS cmpFlags = get_game_completion();
    if ((cmpFlags & (FGS_HalfClues | FGS_AllClues)) != (FGS_HalfClues | FGS_AllClues)) // clues collected
        return;

    GS *gsCur = g_pgsCur;
    if (gsCur->ccoin != 99 || gsCur->clife != 0) // 99 coins and 0 lives
        return;

    // Decrypt chetkido using XOR cipher, key 0x23
    char buf[64];
    char achzPlaintext[16];
    strcpy(achzPlaintext, g_chzCiphertext);

    char *pchCur = achzPlaintext;
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

INCLUDE_ASM("asm/nonmatchings/P2/joy", StartupCodes__Fv);
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
