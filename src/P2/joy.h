#pragma once
#include <util.h>
#include <iostream>

typedef unsigned char byte;

typedef long ulong_128;
typedef short GRFBTN;

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

/* Joypad state */
enum JOYS
{
	JOYS_Initing = 0,
	JOYS_Searching = 1,
	JOYS_Waiting = 2,
	JOYS_Ready = 3,
	JOYS_Max = 4
};

/* Joypad kind */
enum JOYK
{
	JOYK_Unknown = 0,
	JOYK_Digital = 1,
	JOYK_Analog = 2,
	JOYK_Shock = 3,
	JOYK_Shock2 = 4,
	JOYK_Max = 5
};

/* Rumble state */
enum RUMS
{
	RUMS_Dead = 0,
	RUMS_Idle = 1,
	RUMS_Rumble = 2,
	RUMS_Stop = 3,
	RUMS_Kill = 4,
	RUMS_Max = 5
};

struct RUMINS
{
	int fHighSpeedMotor;
	BYTE bLowSpeedMotor;
	BYTE unk1, unk2;
	float dt;
};

struct RUMPAT
{
	int crumins;
	RUMINS arumins[32];
};


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

/* Handles joypad input */
struct JOY
{
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

/* Cheat Code Flags */
enum FCHT
{
	FCHT_None = 0x0,
	FCHT_Invulnerability = 0x1,
	FCHT_InfiniteCharms = 0x2,
	FCHT_LowGravity = 0x4,
	FCHT_LowFriction = 0x8,
	FCHT_ResetWorld = 0x4000
};

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



static JOY g_joy;
static float g_tCodeCheck;
extern int g_grfcht;
extern char chetkido_buffer[]; // temp

void SetJoyJoys(JOY* pjoy, JOYS joys, JOYK joyk);
void UpdateJoy(JOY* pjoy);

void SetRumbleRums(RUMBLE* prumble, RUMS rums);
void InitRumble(RUMBLE* prumble, int nPort, int nSlot);

void UpdateCodes();
void AddFcht(int nParam);
void AddGrfusr(int mask);
void CheatActivateChetkido();
