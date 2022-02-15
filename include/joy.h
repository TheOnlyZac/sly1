#pragma once
#include <iostream>
typedef unsigned char    byte;
/* Cheats Enabled Flags */
enum class FCHT : int
{
	None = 0x0,
	Invulnerability = 0x1,
	InfiniteCharms = 0x2,
	LowGravity = 0x4,
	LowFriction = 0x8,
	ResetWorld = 0x4000
};

enum RUMS
{
    RUMS_Idle = 1,
    RUMS_Dead = 0,
    RUMS_Stop = 3,
    RUMS_Kill = 4,
    RUMS_Max = 5,
    RUMS_Rumble = 2
};

struct RUMBLE
{
    struct VTRUMBLE_92* u4pvtrumble;
    int nPort;
    int nSlot;
    RUMS rums;
    byte field_0xd;
    byte field_0xe;
    byte field_0xf;
    struct RUMPAT_92* prumpat;
    int irumins;
    float dtRumble;
    float dtRumins;
};

enum class JOYS : int
{
    JOYS_Max = 4,
    JOYS_Ready = 3,
    JOYS_Waiting = 2,
    JOYS_Initing = 0,
    JOYS_Searching = 1
};

enum class JOYK : int
{
    JOYK_Shock2 = 4,
    JOYK_Digital = 1,
    JOYK_Max = 5,
    JOYK_Analog = 2,
    JOYK_Shock = 3,
    JOYK_Unknown = 0
};

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

enum DPK
{
    DPK_JoyRight = 10,
    DPK_DoubleJump = 13,
    DPK_Square = 2,
    DPK_None = 0,
    DPK_JoyLeft = 9,
    DPK_JoyLeftX = 11,
    DPK_JoyLeftY = 12,
    DPK_R1 = 7,
    DPK_Circle = 3,
    DPK_L1 = 5,
    DPK_L2 = 6,
    DPK_VaultOpen = 14,
    DPK_R2 = 8,
    DPK_Triangle = 4,
    DPK_X = 1,
    DPK_Max = 15
};

struct LM_92 
{
    float gMin;
    float gMax;
    float u4ag[1];
};

struct JOY 
{
    struct VTJOY_92* u4pvtjoy;
    int nPort;
    int nSlot;
    uint64_t aullDma;
    int term;
    JOYS joys;
    byte field_0x15;
    byte field_0x16;
    byte field_0x17;
    JOYK joyk;
    byte field_0x19;
    byte field_0x1a;
    byte field_0x1b;
    float tJoys;
    float tRead;
    float tActive;
    int dxLatch;
    int dyLatch;
    float tLatchX;
    float dtLatchX;
    float tLatchY;
    float dtLatchY;
    float x;
    float y;
    float uDeflect;
    byte bX;
    byte bY;
    byte field_0x4e;
    byte field_0x4f;
    int fStickMoved;
    struct LM_92 almDeflect[4];
    float x2;
    float y2;
    float uDeflect2;
    byte bX2;
    byte bY2;
    byte field_0x82;
    byte field_0x83;
    int fStickMoved2;
    struct LM_92 almDeflect2[4];
    uint16_t grfbtn;
    enum PadButtons grfbtnPressed;
    uint16_t grfbtnReleased;
    char mpbtnpb[12];
    RUMBLE* prumble;
    byte field_0xbe;
    byte field_0xbf;
    int fRumbleEnabled;
};

extern char chetkido_buffer[]; // temp
extern int g_grfcht;

void AddFcht(int nParam);
void CheatActivateChetkido();
