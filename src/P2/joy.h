#pragma once
#include <util.h>
#include <iostream>

typedef unsigned char byte;

typedef long ulong_128;
typedef short GRFBTN;

enum PadButtons
{
    PAD_RIGHT_ARROW = 8192,
    PAD_L1 = 4,
    PAD_L2 = 1,
    PAD_L3 = 512,
    PAD_LEFT_ARROW = 32768,
    _NOT_PRESSED = 0,
    PAD_SELECT = 256,
    PAD_CIRCLE = 32,
    PAD_R1 = 8,
    PAD_R2 = 2,
    PAD_R3 = 1024,
    PAD_UP_ARROW = 4096,
    PAD_START = 2048,
    PAD_SQUARE = 128,
    PAD_TRIANGLE = 16,
    PAD_CROSS = 64,
    PAD_DOWN_ARROW = 16384
};

/* Joypad state */
enum class JOYS : int
{
	Initing = 0,
	Searching = 1,
	Waiting = 2,
	Ready = 3,
	Max = 4
};

/* Joypad K? */
enum class JOYK : int
{
	Unknown = 0,
	Digital = 1,
	Analog = 2,
	Shock = 3,
	Shock2 = 4,
	Max = 5
};

/* Rumble state */
enum class RUMS : int
{
	Dead = 0,
	Idle = 1,
	Rumble = 2,
	Stop = 3,
	Kill = 4,
	Max = 5
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
enum class FCHT : int
{
	None = 0x0,
	Invulnerability = 0x1,
	InfiniteCharms = 0x2,
	LowGravity = 0x4,
	LowFriction = 0x8,
	ResetWorld = 0x4000
};

enum DPK
{
    JoyRight = 10,
    DoubleJump = 13,
    Square = 2,
    None = 0,
    JoyLeft = 9,
    JoyLeftX = 11,
    JoyLeftY = 12,
    R1 = 7,
    Circle = 3,
    L1 = 5,
    L2 = 6,
    VaultOpen = 14,
    R2 = 8,
    Triangle = 4,
    X = 1,
    Max = 15
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
void CheatActivateChetkido();
