#include <iostream>
#include <game.h>

typedef unsigned char byte;

enum DIALOGK
{
    DIALOGK_Binoc = 0,
    DIALOGK_Instruct = 1,
    DIALOGK_Confront = 2,
    DIALOGK_Max = 3,
};

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

struct DIALOG
{
    int padding[0xB8];
    DIALOGK dialogk;
    byte field_0x2e1;
    byte field_0x2e2;
    byte field_0x2e3;
    DIALOGS dialogs;
    byte field_0x2e5;
    byte field_0x2e6;
    byte field_0x2e7;
    float tDialogs;
    int cde;
    byte field_0x2f0;
    byte field_0x2f1;
    byte field_0x2f2;
    byte field_0x2f3;
    int ideCur;
    //struct DP dp;
    OID oidPntAnchor;
    byte field_0x311;
    byte field_0x312;
    byte field_0x313;
    int* pfPlayed;
    int fPlayed;
    int cpfEquivalence;
    int* apfEquivalence[4];
    int fDefault;
    int fCrucial;
};
