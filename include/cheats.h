#pragma once

enum class FCHT : int
{
	None = 0x0,
	Invulnerability = 0x1,
	InfiniteCharms = 0x2,
	LowGravity = 0x4,
	LowFriction = 0x8,
	ResetWorld = 0x4000
};

static const char chetkido_ciphertext[] = "@KFWHJGL";
static const char s_the_password_is[] = "The password is: %s";

static int g_grfcht = (int)FCHT::None;

void showChetkido();
