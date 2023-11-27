#pragma once

/* UI state
 May not be accurate as it seems to differ from the May proto */
enum UIS
{
	UIS_Splash = 0,
	UIS_Attract = 1,
	UIS_Playing = 2,
	UIS_Pausing = 3,
	UIS_Paused = 4,
	UIS_Unpausing = 5,
	UIS_WorldMap = 6,
	// ??? = 7,
	UIS_Wiping = 8,
	UIS_Max = 9
};

struct UI
{
	// todo
};

static UI g_ui;

void SetUiUis(UI* pui, UIS uis);
void UpdateUi(UI* pui);
void DrawUi();
void RenderUi();
