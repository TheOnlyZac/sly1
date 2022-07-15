#pragma once

/* UI state
 May not be accurate as it seems to differ from the May proto */
enum class UIS
{
	Splash = 0,
	Attract = 1,
	Playing = 2,
	Pausing = 3,
	Paused = 4,
	Unpausing = 5,
	WorldMap = 6,
	// ??? = 7,
	Wiping = 8,
	Max = 9
};

struct UI
{
	// todo
};

void SetUiUis(UI* pui, UIS uis);
void DrawUi();
void RenderUi();
