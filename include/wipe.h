#pragma once
#include <dialog.h>
#include <game.h>
#include <joy.h>
#include <keyhole.h>
#include <sw.h>
#include <transition.h>
#include <wm.h>

typedef unsigned char byte;

enum class WIPEK : int
{
    Fade = 0x0,
    Keyhole = 0x1,
    WorldMap = 0x2,
    Frozen = 0x3,
    Max = 0x4
};

struct TRANS
{
    uint32_t fSet;
    struct LevelTableStruct* pchzWorld; // Current file thats loading struct
    OID oidWarp; // Checkpoint Warps
    OID trans_mod_flags;
    GRFTRANS grftrans; // Lost all lives flags 
};

enum WIPES
{
    WIPES_Idle = 0,
    WIPES_WipingOut = 1,
    WIPES_Black = 2,
    WIPES_WipingIn = 3,
    WIPES_Max = 4,
};

struct WIPE
{
    struct VTWIPE_199* u4pvtwipe;
    WIPES wipes;
    float tWipes;
    float uBlack;
    struct TRANS trans;
    WIPEK wipek;
    struct TRANS transButton;
    WIPEK wipekButton;
};

static TRANS trans;
static WIPE g_pwipe;
static DIALOG g_pdialogCalling;
static CTransition g_transition;
static sw g_psw;
static wm g_wmc;
static keyhole g_pkeyhole;

void WipeToWorldWarp(LevelTableStruct* pchzWorld, OID oidWarp, WIPEK wipek);
void ActivateWipe(WIPE* pwipe, TRANS* ptrans, WIPEK wipek);
void SetWipeWipes(WIPE* pwipe, WIPES wipes);
void DrawWipe(WIPE* pwipe);
void UpdateWipe(WIPE* pwipe, JOY* param_2);
void InitWipe(WIPE* pwipe);
void SetWipeButtonTrans(WIPE* param_1, TRANS* param_2, WIPEK param_3);
int FCatchWipeButtonTrans(WIPE* pwipe, JOY* pjoy, WIPES wipesNew);