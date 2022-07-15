#pragma once
#include <util.h>

typedef long ulong_128;
typedef short GRFBTN;
typedef char BYTE;

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
	float tJOys;
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
	int fStickMoves;
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
	RUMBLE* prumble;
	short unk_short_3;
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

static JOY g_joy;
extern int g_grfcht;
extern char chetkido_buffer[]; // temp

void UpdateJoy(JOY* pjoy);
void AddFcht(int nParam);
void CheatActivateChetkido();
