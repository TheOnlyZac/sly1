#pragma once
#include <iostream>
#include <game.h>
#include <util.h>

typedef unsigned char byte;

enum class DIALOGK
{
    Binoc = 0,
    Instruct = 1,
    Confront = 2,
    Max = 3,
};

enum class DIALOGS
{
    Enabled = 0,
    Triggered = 1,
    Disabled = 2,
    Playing = 3,
    Calling = 4,
    UnableToCall = 5,
    Max = 6,
};

struct DIALOG
{
    int padding[0xB8];
    DIALOGK dialogk;
    DIALOGS dialogs;
    float tDialogs;
    int cde;
    undefined4 field_0x2f0;
    int ideCur;
    //struct DP dp;
    OID oidPntAnchor;
    int* pfPlayed;
    int fPlayed;
    int cpfEquivalence;
    int* apfEquivalence[4];
    int fDefault;
    int fCrucial;
};
