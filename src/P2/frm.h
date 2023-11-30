#pragma once

/**
 * @brief Frame
*/
struct FRM
{
	// todo
	// ...
};

// Global variables
static int g_ifrmMax; // Maximum number of frames
static FRM* g_pfrmOpen; // Pointer to the open frame

/**
 * @brief Opens a new frame.
 *
 * Additionally increments the frame count.
*/
void OpenFrame();

/**
 * @brief Closes the current frame.
*/
void CloseFrame();

/**
 * @brief Clears the pending frame.
 *
 * @param pfrm Pointer to the frame.
*/
void ClearPendingFrame(FRM* pfrm);
