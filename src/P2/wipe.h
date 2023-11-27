#pragma once
#include <dialog.h>
#include <game.h>
#include <joy.h>
#include <keyhole.h>
#include <sw.h>
#include <transition.h>
#include <wm.h>

typedef unsigned char byte;

// Wipe kind
enum WIPEK
{
	WIPEK_Fade = 0,
	WIPEK_Keyhole = 1,
	WIPEK_WorldMap = 2,
	WIPEK_Frozen = 3,
	WIPEK_Max = 4
};

// Wipe state
enum WIPES
{
	WIPES_Idle = 0,
	WIPES_WipingOut = 1,
	WIPES_Black = 2,
	WIPES_WipingIn = 3,
	WIPES_Max = 4
};

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

static KEYHOLE* g_pkeyhole;
static DIALOG* g_pdialogCalling;
static WM g_wmc;
static TRANS trans; // ?

static WIPE g_wipe;
extern WIPE* g_pwipe;

void WipeToWorldWarp(LevelTableStruct* pchzWorld, OID oidWarp, WIPEK wipek);
void ActivateWipe(WIPE* pwipe, TRANS* ptrans, WIPEK wipek);
void SetWipeWipes(WIPE* pwipe, WIPES wipes);
void DrawWipe(WIPE* pwipe);
void UpdateWipe(WIPE* pwipe, JOY* pjoy);
void InitWipe(WIPE* pwipe);
void SetWipeButtonTrans(WIPE* param_1, TRANS* param_2, WIPEK param_3);
int  FCatchWipeButtonTrans(WIPE* pwipe, JOY* pjoy, WIPES wipesNew);
