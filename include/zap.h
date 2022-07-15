#include <iostream>
#include <game.h>
#include <gs.h>

struct ZAP
{
	// todo
	// ...
};

enum class ZOK : int
{
	ZOK_Inherit = 0,
	ZOK_Ignore = 3,
	ZOK_NoZap = 2,
	ZOK_Max = 5,
	ZOK_Zap = 1,
	ZOK_ZapAndIgnore = 4
};
