#pragma once
#include <dialog.h>
#include <game.h>
#include <joy.h>
#include <keyhole.h>
#include <sw.h>
#include <transition.h>
#include <wm.h>

typedef unsigned char byte;

/**
 * Wipe Kind
 */
enum WIPEK
{
	WIPEK_Fade = 0,
	WIPEK_Keyhole = 1,
	WIPEK_WorldMap = 2,
	WIPEK_Frozen = 3,
	WIPEK_Max = 4
};

/**
 * Wipe State
*/
enum WIPES
{
	WIPES_Idle = 0,
	WIPES_WipingOut = 1,
	WIPES_Black = 2,
	WIPES_WipingIn = 3,
	WIPES_Max = 4
};

/**
 * Wipe
*/
struct WIPE
{
    WIPES wipes;
    float tWipes;
    float uBlack;
    struct TRANS trans;
    WIPEK wipek;
    struct TRANS transButton;
    WIPEK wipekButton;
};

// Global variables
static KEYHOLE* g_pkeyhole;
static DIALOG* g_pdialogCalling;
static WM g_wmc;
static TRANS trans; // ?

static WIPE g_wipe;
extern WIPE* g_pwipe;

/**
 * @brief Sets the values on the global transition and calles ActivateWipe to warp given world.
 *
 * @param pchzWorld World to transition to
 * @param oidWarp Unknown
 * @param wipek Wipe kind
 *
 * @todo Figure out what oidWarp is used for.
 */
void WipeToWorldWarp(LevelTableStruct* pchzWorld, OID oidWarp, WIPEK wipek);

/**
 * @brief Activates a wipe.
 *
 * @param pwipe Pointer to the wipe
 * @param ptrans Pointer to the transition
 * @param wipek Wipe kind
 */
void ActivateWipe(WIPE* pwipe, TRANS* ptrans, WIPEK wipek);

/**
 * @brief Sets the wipe state.
 *
 * @param pwipe Pointer to the wipe
 * @param wipes Wipe state
 */
void SetWipeWipes(WIPE* pwipe, WIPES wipes);

/**
 * @brief Draws a wipe.
 *
 * @param pwipe Pointer to the wipe
 */
void DrawWipe(WIPE* pwipe);

/**
 * @brief Updates a wipe.
 *
 * Joypad is passed so it can catch the button press to skip the wipe.
 *
 * @brief pwipe Pointer to the wipe
 * @brief pjoy Pointer to the joypad
 */
void UpdateWipe(WIPE* pwipe, JOY* pjoy);

/**
 * @brief Initializes a wipe.
 *
 * Sets the wipe state to Idle.
 *
 * @param pwipe Pointer to the wipe
 */
void InitWipe(WIPE* pwipe);

/**
 * @brief Sets the button flags on the transition.
 *
 * @param pwipe Pointer to the wipe
 * @param ptrans Pointer to the transition
 * @param wipek Wipe kind
 */
void SetWipeButtonTrans(WIPE* pwipe, TRANS* ptrans, WIPEK wipek);

/**
 * @brief Catches a button during a wipe transition.
 *
 * @param pwipe Pointer to the wipe
 * @param pjoy Pointer to the joypad
 * @param wipesNew New wipe state
 */
int  FCatchWipeButtonTrans(WIPE* pwipe, JOY* pjoy, WIPES wipesNew);
