/**
 * @file joy.h
 *
 * @brief Declarations for joypad interactions.
*/
#ifndef JOY_H
#define JOY_H

#include <util.h>

typedef short GRFBTN;

/**
 * @brief Joypad buttons
*/
enum PadButtons
{
    NOT_PRESSED = 0,
    PAD_L2 = 1,
    PAD_R2 = 2,
    PAD_L1 = 4,
    PAD_R1 = 8,
    PAD_TRIANGLE = 16,
    PAD_CIRCLE = 32,
    PAD_CROSS = 64,
    PAD_SQUARE = 128,
    PAD_SELECT = 256,
    PAD_L3 = 512,
    PAD_R3 = 1024,
    PAD_START = 2048,
    PAD_UP_ARROW = 4096,
    PAD_RIGHT_ARROW = 8192,
    PAD_DOWN_ARROW = 16384,
    PAD_LEFT_ARROW = 32768
};

/**
 * @brief Joypad state
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
    BYTE bLowSpeedMotor;
    BYTE unk1, unk2;
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
    RUMPAT* prumpat;
    int irumins;
    float dtRumble;
    float dtRumins;
};

/**
 * @brief Joypad
*/
struct JOY
{
    // joypad info
    int nPort;
    int nSlot;
    ulong_128* aullDma;
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
    RUMBLE* prumble;
    int fRumbleEnabled;
};

/**
 * @brief User Flags
*/
enum FUSR
{
    FUSR_Menu = 0x1,
    FUSR_HandsOff = 0x2,
    FUSR_NoPause = 0x4
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

/**
 * @brief Int representation of cheat flags
*/
typedef int GRFCHT;

/**
 * @brief ??? Kind
*/
enum DPK
{
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

// Global variables
static JOY g_joy; // Handles joypad input

extern int g_grfusr; // User flags
extern int g_grfjoyt; // Joypad type

static float g_tCodeCheck; // Time since last code check
extern int g_grfcht; // Cheat flags
extern char chetkido_buffer[]; // temp, used for Chetkido cheat code

/**
 * @brief Starts up the joy system.
*/
void StartupJoy();

/**
 * @brief Sets the given flag on the global grfusr variable.
 *
 * @param mask Flag to set
*/
void AddGrfusr(int mask);

/**
 * @brief Clears the given flag on the global grfusr variable.
 *
 * @param mask Flag to clear
*/
void RemoveGrfusr(int mask);

/**
 * @brief Updates the grfjoy based on the global grfusr value.
*/
void UpdateGrfjoytFromGrfusr();

/**
 * @brief Initializes the given joypad.
 *
 * @param pjoy Pointer to the joypad
 * @param nPort Port of the controller
 * @param nSlot Slot of the controller
*/
void InitJoy(JOY* pjoy, int nPort, int nSlot);

/**
 * @brief Sets the joypad state and kind.
 *
 * @param pjoy Pointer to the joypad
 * @param joys Joypad state
 * @param joyk Joypad kind
*/
void SetJoyJoys(JOY* pjoy, JOYS joys, JOYK joyk);

/**
 * @brief Updates the given joypad.
 *
 * @param pjoy Pointer to the joypad
*/
void UpdateJoy(JOY* pjoy);

/**
 * @brief Sets the rumble state.
 *
 * @param prumble Pointer to the rumble
 * @param rums Rumble state
*/
void SetRumbleRums(RUMBLE* prumble, RUMS rums);

/**
 * @brief Initializes the rumble.
 *
 * @param prumble Pointer to the rumble
 * @param nPort Port of the controller
 * @param nSlot Slot of the controller
*/
void InitRumble(RUMBLE* prumble, int nPort, int nSlot);

/**
 * @brief Updates the check for cheat code entry.
*/
void UpdateCodes();

/**
 * @brief Removes all cheat codes.
 *
 * @note Name is not official.
*/
void RemoveAllFchts();

/**
 * @brief Activates a cheat code.
 *
 * Sets the given flag on the global fcht variable. Also reloads the level if
 * is is a reload code.
 *
 * @param nparam Cheat code to check
*/
void AddFcht(int nParam);

/**
 * @brief Activates the Chetkido cheat code.
 *
 * Decrypts the string "The password is: Chetkido" and displays it on the screen
 * if the following conditions are met:
 *   - The level is snow_approach
 *   - The game has 100% completion
 *   - Coin count is 99
 *   - Life count is 0
 *
 * @note Unofficial name because the real name is unknown.
 * @todo Implement rendering the string on the screen.
*/
void CheatActivateChetkido();

#endif // JOY_H
