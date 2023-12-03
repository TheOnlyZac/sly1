/**
 * @file ui.h
 *
 * @brief Declarations for the user interface.
*/
#ifndef UI_H
#define UI_H

/**
 * @brief UI state
 *
 * Might not be accurate as it seems to differ from the May proto
*/
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

/**
 * @brief User Interface
*/
struct UI
{
	// todo
};

// Global variables
static UI g_ui; // Main UI

/**
 * @brief Sets the UI state.
 *
 * @param pui Pointer to UI struct
 * @param uis UI state
 *
 * @todo Implement function.
*/
void SetUiUis(UI* pui, UIS uis);

/**
 * @brief Updates the UI.
 *
 * @param pui Pointer to UI struct
 *
 * @todo Implement function.
*/
void UpdateUi(UI* pui);

/**
 * @brief Calls DrawBlots to draw the UI.
*/
void DrawUi();

/**
 * @brief Calls RenderBlots to render the UI.
*/
void RenderUi();

#endif // UI_H
