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

// Forward.
struct SPEAKER;
struct DE;

/**
 * @brief Dialog Pause Flags.
 */
enum FDP
{
    FDP_PreloadSound = 1,
    FDP_SpeakerLeft = 2,
    FDP_SpeakerRight = 4,
    FDP_Sound = 8,
    FDP_Lipsync = 16,
    FDP_Text = 32,
    FDP_Zoom = 64,
    FDP_Time = 128,
    FDP_User = 256,
    GRFDP_None = 0,
    GRFDP_All = 511
};

/**
 * @brief Dialog pause flag bitmask.
 */
typedef uint GRFDP;

/**
 * @brief Dialog Kind.
 */
enum DIALOGK
{
    DIALOGK_Nil = -1,
    DIALOGK_Binoc = 0,
    DIALOGK_Instruct = 1,
    DIALOGK_Confront = 2,
    DIALOGK_Max = 3
};

/**
 * @brief Dialog State.
 */
enum DIALOGS
{
    DIALOGS_Nil = -1,
    DIALOGS_Enabled = 0,
    DIALOGS_Triggered = 1,
    DIALOGS_Disabled = 2,
    DIALOGS_Playing = 3,
    DIALOGS_Calling = 4,
    DIALOGS_UnableToCall = 5,
    DIALOGS_Pending = 6,
    DIALOGS_Max = 7
};

/**
 * @brief Dialog Pause Kind.
 */
enum DPK
{
    DPK_Nil = -1,
    DPK_None = 0,
    DPK_X = 1,
    DPK_Square = 2,
    DPK_Circle = 3,
    DPK_Triangle = 4,
    DPK_L1 = 5,
    DPK_L2 = 6,
    DPK_R1 = 7,
    DPK_R2 = 8,
    DPK_JoyLeft = 9,
    DPK_JoyRight = 10,
    DPK_JoyLeftX = 11,
    DPK_JoyLeftY = 12,
    DPK_DoubleJump = 13,
    DPK_VaultOpen = 14,
    DPK_Max = 15
};

/**
 * @brief Dialog Pause state.
 */
struct DP
{
    /* 0x00 */ GRFDP grfdp;            // Active pause condition flags
    /* 0x04 */ DPK dpk;                // Pause button/action kind
    /* 0x08 */ SPEAKER *pspeakerLeft;  // Left speaker
    /* 0x0c */ SPEAKER *pspeakerRight; // Right speaker
    /* 0x10 */ ASEGA *pasegaLipsync;   // Lip sync animation segment application
    /* 0x14 */ float tPauseMin;        // Minimum pause duration
};

/**
 * @class DIALOG
 * @brief Dialog line in a cutscene.
 */
struct DIALOG : public ALO
{
    /* 0x2d0 */ DIALOGK dialogk;         // Kind of dialog (binoc, instruct, confront)
    /* 0x2d4 */ DIALOGS dialogs;         // Current dialog playback state
    /* 0x2d8 */ float tDialogs;          // Timestamp when the current state was entered
    /* 0x2dc */ int cde;                 // Count of dialog events in the ade array
    /* 0x2e0 */ DE *ade;                 // Array of dialog events
    /* 0x2e4 */ int ideCur;              // Index of the current dialog event
    /* 0x2e8 */ DP dp;                   // Dialog pause state
    /* 0x300 */ OID oidPntAnchor;        // Anchor point object ID
    /* 0x304 */ int *pfPlayed;           // Pointer to played flag in level state
    /* 0x308 */ int fPlayed;             // Local fallback played flag
    /* 0x30c */ OID oidDialog;           // Dialog object ID used for level state lookup
    /* 0x310 */ int cpfEquivalence;      // Count of equivalent dialog played flags
    /* 0x314 */ int *apfEquivalence[4];  // Pointers to equivalent dialog played flags
    /* 0x324 */ int fDefault;            // Whether this is a default dialog
    /* 0x328 */ int fCrucial;            // Whether this dialog is crucial
    /* 0x32c */ undefined4 unk_0x32c;
    /* 0x330 */ int fDuckAudio;          // Whether game audio should be ducked during playback
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
struct DESPEAKER
{
    /* 0x00 */ OID oid;
    /* 0x04 */ OID oidReplace;
};

struct DETALK
{
    /* 0x00 */ float uZoom;
    /* 0x04 */ float dtPause;
    /* 0x08 */ int fUser;
    /* 0x0c */ DPK dpk;
    /* 0x10 */ char *pchzText;
    /* 0x14 */ OID oidSpeaker;
    /* 0x18 */ OID oidLipsAseg;
    /* 0x1c */ OID oidFocus;
    /* 0x20 */ OID oidPntAnchor;
};

/**
 * @brief Dialog Event.
 */
struct DE
{
    /* 0x00 */ DEK dek;
    /* 0x04 */ union
    {
        /* 0x04 */ char *pchz;
        /* 0x04 */ OID oid;
        /* 0x04 */ DESPEAKER speaker;
        /* 0x04 */ DETALK talk;
        /* 0x04 */ OID oidLabel;
    };
};

/**
 * @brief Dialog API flags indicating whether a dialog can be called or played.
 */
struct DIAPI
{
    /* 0x00 */ int fCallable;
    /* 0x04 */ int fPlayable;
};

/**
 * @brief Initializes a DIALOG instance.
 *
 * @param pdialog Pointer to the DIALOG to initialize.
 */
void InitDialog(DIALOG *pdialog);

/**
 * @brief Loads a DIALOG from a binary input stream.
 *
 * @param pdialog Pointer to the DIALOG to load into.
 * @param pbis Pointer to the binary input stream.
 */
void LoadDialogFromBrx(DIALOG *pdialog, CBinaryInputStream *pbis);

/**
 * @brief Loads an array of dialog events (DE) from a binary input stream.
 *
 * @param pdialog Pointer to the owning DIALOG.
 * @param pbis Pointer to the binary input stream.
 * @param pcde Output pointer for the number of dialog events loaded.
 * @param pade Output pointer for the allocated array of dialog events.
 */
void LoadDialogEventsFromBrx(DIALOG *pdialog, CBinaryInputStream *pbis, int *pcde, DE **pade);

/**
 * @brief Looks up the persistent played flag for a dialog OID in the level state.
 *
 * @param pls Pointer to the level state.
 * @param oidDialog OID of the dialog.
 * @return Pointer to the played flag, or NULL if not persisted in level state.
 */
int *PfLookupDialog(LS *pls, OID oidDialog);

/**
 * @brief Finalizes a DIALOG after loading from BRX.
 *
 * @param pdialog Pointer to the DIALOG.
 */
void PostDialogLoad(DIALOG *pdialog);

/**
 * @brief Sets the dialog kind to DIALOGK_Instruct.
 *
 * @param pdialog Pointer to the DIALOG.
 */
void SetDialogInstruct(DIALOG *pdialog);

/**
 * @brief Sets the dialog kind to DIALOGK_Confront.
 *
 * @param pdialog Pointer to the DIALOG.
 */
void SetDialogConfront(DIALOG *pdialog);

/**
 * @brief Gets whether the dialog has been played.
 *
 * @param pdialog Pointer to the DIALOG.
 * @param pfPlayed Output pointer receiving the played flag.
 */
void GetDialogPlayed(DIALOG *pdialog, int *pfPlayed);

/**
 * @brief Sets whether the dialog has been played.
 *
 * @param pdialog Pointer to the DIALOG.
 * @param fPlayed Non-zero if played, zero otherwise.
 */
void SetDialogPlayed(DIALOG *pdialog, int fPlayed);

/**
 * @brief Transitions a DIALOG to a new state.
 *
 * @param pdialog Pointer to the DIALOG.
 * @param dialogs New dialog state.
 */
void SetDialogDialogs(DIALOG *pdialog, DIALOGS dialogs);

/**
 * @brief Updates a DIALOG each frame.
 *
 * @param pdialog Pointer to the DIALOG.
 * @param dt Delta time for the frame.
 */
void UpdateDialog(DIALOG *pdialog, float dt);

/**
 * @brief Executes a single dialog event (DE).
 *
 * @param pdialog Pointer to the DIALOG.
 * @param pde Pointer to the dialog event to execute.
 */
void HandleDialogEvent(DIALOG *pdialog, DE *pde);

/**
 * @brief Handles messages sent to a DIALOG object.
 *
 * @param pdialog Pointer to the DIALOG.
 * @param msgid Message ID.
 * @param pv Message payload pointer.
 */
void HandleDialogMessage(DIALOG *pdialog, MSGID msgid, void *pv);

/**
 * @brief Checks and updates pause conditions for an active DIALOG.
 *
 * @param pdialog Pointer to the DIALOG.
 * @return Non-zero if the dialog is still paused on the current event, 0 if ready to advance.
 */
int FPauseDialog(DIALOG *pdialog);

/**
 * @brief Skips remaining dialog events (executing state-affecting events) and ends confront UI.
 *
 * @param pdialog Pointer to the DIALOG.
 */
void FUN_001516c0(DIALOG *pdialog);

/**
 * @brief Advances and dispatches dialog events while the dialog is not paused.
 *
 * @param pdialog Pointer to the DIALOG.
 */
void HandleDialogEvents(DIALOG *pdialog);

/**
 * @brief Starts playing a dialog via the given player/blot or the binoc-u-com.
 *
 * @param pdialog Pointer to the DIALOG to play.
 * @param pblot Pointer to the active player object cast as BLOT, or NULL to use g_binoc.
 */
void FUN_00151860(DIALOG *pdialog, BLOT *pblot);

/**
 * @brief Triggers a DIALOG to begin calling or playing if eligible.
 *
 * @param pdialog Pointer to the DIALOG.
 */
void TriggerDialog(DIALOG *pdialog);

/**
 * @brief Untriggers a DIALOG, returning it to the enabled state if not currently triggered or playing.
 *
 * @param pdialog Pointer to the DIALOG.
 */
void UntriggerDialog(DIALOG *pdialog);

/**
 * @brief Pointer to the dialog currently being called.
 */
extern DIALOG *g_pdialogCalling;

/**
 * @brief Pointer to the dialog currently being played.
 */
extern DIALOG *g_pdialogPlaying;

#endif // DIALOG_H
