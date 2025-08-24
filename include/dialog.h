/**
 * @file dialog.h
 *
 * @brief Declarations for the dialog system.
 */
#ifndef DIALOG_H
#define DIALOG_H

#include <game.h>
#include <util.h>

/**
 * @brief Dialog Kind
 */
enum DIALOGK
{
    DIALOGK_Binoc = 0,
    DIALOGK_Instruct = 1,
    DIALOGK_Confront = 2,
    DIALOGK_Max = 3,
};

/**
 * @brief Dialog State
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
 * @brief Dialog
 */
struct DIALOG
{
    int padding[0xB8];
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

DIALOG *g_pdialogCalling; // Dialog currently being called

// ...

#endif // DIALOG_H
