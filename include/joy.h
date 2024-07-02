/**
 * @file joy.h
 *
 * @brief Joypad state.
 */
#ifndef JOY_H
#define JOY_H

#include "common.h"
#include <util.h>

//MARK:Rumble

/**
 * @brief Rumble state
 */
enum RUMS
{
    RUMS_Dead = 0,
    RUMS_Idle = 1,
    RUMS_Rumble = 2,
    RUMS_Stop = 3,
    RUMS_Kill = 4,
    RUMS_Max = 5
};

/**
 * @brief Rumble intensity
 */
struct RUMINS
{
    int fHighSpeedMotor;
    byte bLowSpeedMotor;
    byte unk1;
    byte unk2;
    float dt;
};

/**
 * @brief Rumble pattern
 */
struct RUMPAT
{
    int crumins;
    RUMINS arumins[32];
};

/**
 * @brief Rumble
 *
 * Combines the rumble state, rumble pattern, and rumble intensity along with the
 * port and slot of the controller.
 */
struct RUMBLE
{
    int nPort;
    int nSlot;
    RUMS rums;
    RUMPAT *prumpat;
    int irumins;
    float dtRumble;
    float dtRumins;
};

//MARK:Joy

/**
 * @brief Joypad button integer type.
 */
typedef int GRFBTN;

/**
 * @brief Joypad state.
 */
enum JOYS
{
    JOYS_Initing = 0,
    JOYS_Searching = 1,
    JOYS_Waiting = 2,
    JOYS_Ready = 3,
    JOYS_Max = 4
};

/**
 * @brief Joypad kind
 */
enum JOYK
{
    JOYK_Unknown = 0,
    JOYK_Digital = 1,
    JOYK_Analog = 2,
    JOYK_Shock = 3,
    JOYK_Shock2 = 4,
    JOYK_Max = 5
};

/**
 * @brief Joypad
 */
struct JOY
{
    // joypad info
    int nPort;
    int nSlot;
    int *aullDma[8]; // todo: fix type
    int term;
    JOYS joys;
    JOYK joyk;
    float tJoys;
    float tRead;
    float tActive;
    int dxLatch;
    int dyLatch;
    float tLatchX;
    float tLatchY;
    float dtLatchY;

    // left analog stick
    float x, y;
    float uDeflect;
    float bX, bY;
    short unk_short;
    int fStickMoved;
    LM almDeflect[4];

    // right analog stick
    float x2, y2;
    float uDeflect2;
    float bX2, bY2;
    short unk_short2;
    float fStickMoved2;
    LM almDeflect2[4];

    // face buttons
    GRFBTN grfbtn;
    GRFBTN grfbtnPressed;
    GRFBTN grfbtnReleased;
    unsigned char mpbtnpb[12];

    // rumble
    short unk_short_3;
    RUMBLE *prumble;
    int fRumbleEnabled;
};

//MARK:User

/**
 * @brief User flags integer type.
 */
typedef int GRFUSR;

/**
 * @brief User Flags.
 */
enum FUSR
{
    FUSR_Menu = 0x1,
    FUSR_HandsOff = 0x2,
    FUSR_NoPause = 0x4
};

//MARK:Cheats

/**
 * @brief Cheat flags integer type.
 */
typedef int GRFCHT;

struct CHT
{
    short *pCodeSeq;      // Pointer to code sequence
    int cnInputSeqLen;    // Cheat code length
    void *pfn;            // Callback function pointer
    int nParam;           // Param for callback function
    int nInputCounter;    // Counter for correct inputs
    int index;            // Index of cheat code in linked list
    struct CHT *pchtNext; // Pointer to next cheat code
};

/**
 * @brief Cheat Flags
 */
enum FCHT
{
    FCHT_None = 0x0,
    FCHT_Invulnerability = 0x1,
    FCHT_InfiniteCharms = 0x2,
    FCHT_LowGravity = 0x4,
    FCHT_LowFriction = 0x8,
    FCHT_ResetWorld = 0x4000
};

#endif // JOY_H
