#pragma once

typedef struct UI;
typedef enum UIS;

enum class WIPEK : int
{
	Fade = 0x0,
	Keyhole	= 0x1,
	WorldMap = 0x2,
	Frozen = 0x3,
	Max = 0x4
};

enum class WIPES
{
	Idle = 0,
	WipingOut = 1,
	Black = 2,
	WipingIn = 3,
	Max = 4
};

struct WIPE
{
	// todo
};

void SetWipeWipes(WIPE* pwipe, WIPES wipes);
