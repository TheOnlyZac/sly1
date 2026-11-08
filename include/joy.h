/**
 * @file joy.h
 *
 * @brief Joypad manager.
 */
#ifndef JOY_H
#define JOY_H

#include "common.h"
#include <rumble.h>
#include <util.h>

#define JOY_BUTTON_PRESSED(pjoy, pad_button) (pjoy->grfbtnPressed & (pad_button) != _NOT_PRESSED)

// MARK:Pad

enum PAD
{
    _NOT_PRESSED = 0x0,
    PAD_L2 = 0x1,
    PAD_R2 = 0x2,
    PAD_L1 = 0x4,
    PAD_R1 = 0x8,
    PAD_TRIANGLE = 0x10,
    PAD_CIRCLE = 0x20,
    PAD_CROSS = 0x40,
    PAD_SQUARE = 0x80,
    PAD_SELECT = 0x100,
    PAD_L3 = 0x200,
    PAD_R3 = 0x400,
    PAD_START = 0x800,
    PAD_UP_ARROW = 0x1000,
    PAD_RIGHT_ARROW = 0x2000,
    PAD_DOWN_ARROW = 0x4000,
    PAD_LEFT_ARROW = 0x8000
};

enum BTNP
{
    BTNP_Nil = -1,
    BTNP_PadRight = 0,
    BTNP_PadLeft = 1,
    BTNP_PadUp = 2,
    BTNP_PadDown = 3,
    BTNP_Triangle = 4,
    BTNP_Circle = 5,
    BTNP_X = 6,
    BTNP_Square = 7,
    BTNP_L1 = 8,
    BTNP_R1 = 9,
    BTNP_L2 = 10,
    BTNP_R2 = 11,
    BTNP_Max = 12
};

// MARK:Joy

/**
 * @brief Joypad button integer type.
 */
typedef ushort GRFBTN;

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
 * @brief Joypad kind.
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
 * @brief Joypad id.
 */
enum JOYID
{
    JOYID_Nil = -1,
    JOYID_Left = 0,
    JOYID_Right = 1,
    JOYID_Max = 2
};

/**
 * @brief Joypad.
 */
struct JOY
{
    undefined4 *pvtjoy;

    // joypad info
    int nPort;
    int nSlot;
    uint *aullDma; // todo: fix type
    int term;
    JOYS joys;
    JOYK joyk;
    float tJoys;
    float tRead;
    float tActive;
    int dxLatch;
    int dyLatch;
    float tLatchX;
    float dtLatchX;
    float tLatchY;
    float dtLatchY;

    // left analog stick
    float x, y;
    /* 0x48 */ float uDeflect;
    byte bX, bY;
    ushort unk_short;
    int fStickMoved;
    LM almDeflect[4];

    // right analog stick
    float x2, y2;
    /* 0x7c */ float uDeflect2;
    byte bX2, bY2;
    ushort unk_short2;
    int fStickMoved2;
    LM almDeflect2[4];

    // face buttons
    GRFBTN grfbtn;
    GRFBTN grfbtnPressed;
    GRFBTN grfbtnReleased;
    byte mpbtnpb[12];

    // rumble
    short unk_short_3;
    RUMBLE *prumble;
    int fRumbleEnabled;
};

extern JOY g_joy;

extern float g_aja[4][2];

extern ushort g_mpbtnpfbtn[BTNP_Max];

// MARK:User

/**
 * @brief User flags integer type.
 */
typedef int GRFUSR;

extern GRFUSR g_grfusr;

extern int g_grfjoyt;

/**
 * @brief User Flags.
 */
enum FUSR
{
    FUSR_Menu = 0x1,
    FUSR_HandsOff = 0x2,
    FUSR_NoPause = 0x4
};

// MARK:Cheats

struct CODE
{
    ushort *ajbc;      // Pointer to code sequence
    int cjbc;          // Code sequence length
    void (*pfn)(int);  // Callback function pointer
    int nParam;        // Param for callback function
    int nInputCounter; // Counter for correct inputs
    int index;         // Index of cheat code in linked list
    CODE *pchtNext;    // Pointer to next cheat code
};

extern CODE *g_pcode;
extern float g_tCodeCheck;

/**
 * @brief Cheat flags.
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

/**
 * @brief Cheat flags integer type.
 */
typedef int GRFCHT;

extern GRFCHT g_grfcht;

/**
 * @brief Cheat type.
 *
 * @note Usage unknown.
 */
enum CHT
{
    CHT_Nil = 0x0,
    CHT_Charms = 0x1,
    CHT_Max = 0x2
};

void StartupJoy();

void AddGrfusr(GRFUSR grfusr);

void RemoveGrfusr(GRFUSR grfusr);

void UpdateGrfjoytFromGrfusr();

void InitJoy(JOY *pjoy, int nPort, int nSlot);

void UpdateJoy(JOY *pjoy);

void SetJoyJoys(JOY *pjoy, JOYS joys, JOYK joyk);

/**
 * @brief Converts one analog stick's raw bytes into a deflection.
 *
 * Maps the bytes to -1..1 (y is flipped so up is positive), tracks the largest
 * deflection seen along each of four axes in alm to auto calibrate the range,
 * and writes the direction scaled by how far the stick is pushed.
 *
 * @param pjoy Joypad being read.
 * @param bX Raw stick x byte.
 * @param bY Raw stick y byte.
 * @param pdx Output: scaled x.
 * @param pdy Output: scaled y.
 * @param pu Output: deflection from 0 to 1.
 * @param pbXPrev In/out: previous raw x byte.
 * @param pbYPrev In/out: previous raw y byte.
 * @param pfMoved In/out: set once the stick has moved off center.
 * @param alm The four per axis limits being calibrated.
 */
void GetJoyXYDeflection(JOY *pjoy, uchar bX, uchar bY, float *px, float *py, float *puDeflect, uchar *pbX, uchar *pbY, int *pfStickMoved, LM *almDeflect);

void GetJoyXYDeflection(JOY *pjoy, uchar bX, uchar bY, float *pdx, float *pdy, float *pu, uchar *pbXPrev, uchar *pbYPrev, int *pfMoved, LM *alm);

/**
 * @brief Polls the pad and updates the joypad state.
 *
 * Reads the buttons, computes pressed and released masks, converts both analog
 * sticks, lets the d-pad stand in for the left stick, and checks cheat codes.
 *
 * @param pjoy Joypad to update.
 * @return 0 if the pad looks disconnected (terminal id changed or no data for
 * 2 seconds), otherwise 1.
 */
int FReadJoy(JOY *pjoy);

void SetJoyBtnHandled(JOY *joy, ushort btn);

void TriggerJoyRumbleRumk(RUMBLE *prumble, JOY *pjoy, float dt);

void StartJoySelection(JOY *pjoy);

/**
 * @brief Gets the horizontal menu navigation step from the d-pad or left stick.
 *
 * Fires once when a direction is first pressed, then repeats while it is held,
 * with the delay between repeats shrinking down to a minimum.
 *
 * @param pjoy Joypad to read.
 * @return -1 for left, 1 for right, 0 for no step this frame.
 */
int DxSelectionJoy(JOY *pjoy);

/**
 * @brief Gets the vertical menu navigation step from the d-pad or left stick.
 *
 * Same latching and key repeat behavior as DxSelectionJoy. The stick y axis is
 * positive when pushed up (see GetJoyXYDeflection), so up maps to -1.
 *
 * @param pjoy Joypad to read.
 * @return -1 for up, 1 for down, 0 for no step this frame.
 */
int DySelectionJoy(JOY *pjoy);

/**
 * @brief Gets how hard a button is pressed.
 *
 * @param pjoy Joypad to read.
 * @param btnp Button to check.
 * @return 0 if not held, 1 on pads without pressure sensitivity, otherwise
 * the pressure scaled to 1/255 through 1.
 */
float UBtnpJoy(JOY *pjoy, BTNP btnp);

void AddCode(CODE *pcode);

void _ResetCodes();

void _MatchCodes(JOY *pjoy, GRFBTN grfbtnPrev);

void UpdateCodes();

void ClearFchts();

void AddFcht(uint nParam);

void Chetkido();

void StartupCodes();

#endif // JOY_H
