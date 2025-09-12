/**
 * @file dialog.h
 *
 * @brief Declarations for the dialog system.
 */
#ifndef DIALOG_H
#define DIALOG_H

#include "common.h"
#include <game.h>
#include <util.h>
#include <alo.h>

/**
 * @brief Dialog Kind.
 */
enum DIALOGK
{
    DIALOGK_Binoc = 0,
    DIALOGK_Instruct = 1,
    DIALOGK_Confront = 2,
    DIALOGK_Max = 3,
};

/**
 * @brief Dialog State.
 */
enum DIALOGS
{
    DIALOGS_Enabled = 0,
    DIALOGS_Triggered = 1,
    DIALOGS_Disabled = 2,
    DIALOGS_Playing = 3,
    DIALOGS_Calling = 4,
    DIALOGS_UnableToCall = 5,
    DIALOGS_Max = 6,
};

/**
 * @class DIALOG.
 * @brief Dialog line in a cutscene.
 */
struct DIALOG : public ALO
{
    STRUCT_PADDING(padding0, 184);
    DIALOGK dialogk;
    DIALOGS dialogs;
    float tDialogs;
    int cde;
    undefined4 field_0x2f0;
    int ideCur;
    // struct DP dp;
    OID oidPntAnchor;
    int *pfPlayed;
    int fPlayed;
    int cpfEquivalence;
    int *apfEquivalence[4];
    int fDefault;
    int fCrucial;
};

/**
 * @brief Dialog Event Kind.
 */
enum DEK
{
    DEK_Nil = -1,
    DEK_PreloadVag = 0,
    DEK_SpeakerLeft = 1,
    DEK_SpeakerRight = 2,
    DEK_Talk = 3,
    DEK_CallSplice = 4,
    DEK_ShowLetterbox = 5,
    DEK_HideLetterbox = 6,
    DEK_ShowMovie = 7,
    DEK_Max = 8
};

/**
 * @brief Dialog Event.
 */
struct DE
{
    DEK dek;
};

void InitDialog(DIALOG *pdialog);

void LoadDialogFromBrx(DIALOG *pdialog, CBinaryInputStream *pbis);

void LoadDialogEventsFromBrx(DIALOG *pdialog, CBinaryInputStream *pbis, int *pcde, DE **pade);

void SetDialogInstruct(DIALOG *pdialog);

void SetDialogConfront(DIALOG *pdialog);

void GetDialogPlayed(DIALOG *pdialog, int *pfPlayed);

void SetDialogPlayed(DIALOG *pdialog, int fPlayed);

void SetDialogDialogs(DIALOG *pdialog, DIALOGS dialogs);

void UpdateDialog(DIALOG *pdialog, float dt);

void HandleDialogEvent(DIALOG *pdialog, DE *pde);

void HandleDialogMessage(DIALOG *pdialog, MSGID msgid, void *pv);

int FPauseDialog(DIALOG *pdialog);

void HandleDialogEvents(DIALOG *pdialog);

void TriggerDialog(DIALOG *pdialog);

void UntriggerDialog(DIALOG *pdialog);

extern DIALOG *g_pdialogCalling; // Dialog currently being called

#endif // DIALOG_H
