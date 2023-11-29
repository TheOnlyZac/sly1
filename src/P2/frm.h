#pragma once

/**
 * Frame
*/
struct FRM
{
	// todo
	// ...
};

// Global variables
static int g_ifrmMax;
static FRM* g_pfrmOpen;

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
