/**
 * @file screen.h
 *
 * @brief Declarations for the screen blot system.
*/
#pragma once

/**
 * @brief Blot State
*/
enum BLOTS
{
	BLOTS_Hidden = 0,
	BLOTS_Appearing = 1,
	BLOTS_Visible = 2,
	BLOTS_Disappearing = 3,
	BLOTS_Max = 4
};

/**
 * @brief Blot
 *
 * Used to draw screen objects.
*/
struct BLOT
{
	// todo
	int padding[0x280];
};

/**
 * @brief Sets the BLOT state.
 *
 * @param pblot Pointer to the blot to set.
 * @param blots The state to set.
 *
 * @todo Implement this function.
*/
void SetBlotBlots(BLOT* pblot, BLOTS blots);

/**
 * @brief Renders the BLOT object.
 *
 * @todo Implement this function.
*/
void RenderBlots();

/**
 * @brief Draws the BLOT object.
 *
 * @todo Implement this function.
*/
void DrawBlots();
