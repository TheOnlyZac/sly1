/**
 * @file prompt.h
 */
#ifndef PROMPT_H
#define PROMPT_H

#include "common.h"
#include <screen.h>
#include <joy.h>

/**
 * @brief Prompt kind.
 * @todo Verify the values. These are taken straight from the prototype.
 */
enum PRK
{
    PRK_Nil = -1,
    PRK_PauseMenu = 0,
    PRK_ExitLevel = 1,
    PRK_GameOver = 2,
    PRK_QuitConfirm = 3,
    PRK_MemcardMissing = 4,
    PRK_MemcardFormatConfirm = 5,
    PRK_MemcardFormatting = 6,
    PRK_MemcardFormatError = 7,
    PRK_MemcardCreateConfirm = 8,
    PRK_MemcardCreating = 9,
    PRK_MemcardCreateError = 10,
    PRK_MemcardCardFull = 11,
    PRK_MemcardChooseSaveSlot = 12,
    PRK_MemcardSlotSaving = 13,
    PRK_MemcardSlotSaved = 14,
    PRK_MemcardChooseLoadSlot = 15,
    PRK_MemcardChooseEraseSlot = 16,
    PRK_MemcardEraseConfirm = 17,
    PRK_MemcardAutoNotify = 18,
    PRK_CdRemoved = 19,
    PRK_OptionsMenu = 20,
    PRK_AttractMenu = 21,
    PRK_Max = 22,
};

/**
 * @brief Prompt (?).
 * @todo Verify the values. These are taken straight from the prototype.
 */
enum PRP
{
    PRP_Nil = -1,
    PRP_Basic = 0,
    PRP_Memcard = 1,
    PRP_Cd = 2,
    PRP_Max = 3,
};

/**
 * @brief Response kind.
 * @todo Verify the values. These are taken straight from the prototype.
 */
enum RESPK
{
    RESPK_Nil = -1,
    RESPK_Yes = 0,
    RESPK_No = 1,
    RESPK_Continue = 2,
    RESPK_Map = 3,
    RESPK_Options = 4,
    RESPK_Save = 5,
    RESPK_Exit = 6,
    RESPK_Quit = 7,
    RESPK_Slot1 = 8,
    RESPK_Slot2 = 9,
    RESPK_Slot3 = 10,
    RESPK_GameOptions = 11,
    RESPK_SoundOptions = 12,
    RESPK_Max = 13,
};

/**
 * @brief Prompt.
 * @todo Verify the fields. These are taken straight from the prototype.
 */
struct PROMPT : public BLOT
{
    PRK prk;
    int irespk;
    PRK mpprpprk[3];
    int fReshow;
    PRK prkReshow;
};

char *AchzFromRespk(RESPK respk);

// ...

void SetPromptPrk(PROMPT *pprompt, PRK prk);

void PostPromptLoad(PROMPT *pprompt);

// ...

void OnPromptActive(PROMPT *pprompt, int fActive);

// ...

void UpdatePromptActive(PROMPT *pprompt, JOY *pjoy);

void SetPrompt(PROMPT *pprompt, PRP prp, PRK prk);

void SetPromptBlots(PROMPT *pprompt, BLOTS blots);

// ...

void DrawPrompt(PROMPT *pprompt);

// ...

void ExecutePrompt(PROMPT *pprompt);

void CancelPrompt(PROMPT *pprompt);

#endif // PROMPT_H
