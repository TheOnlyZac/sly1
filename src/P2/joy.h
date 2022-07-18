#pragma once

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

extern char chetkido_buffer[]; // temp
extern int g_grfcht;

void AddFcht(int nParam);
void CheatActivateChetkido();
