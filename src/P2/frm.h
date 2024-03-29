/**
 * @file frm.h
 *
 * @brief Declarations for the frame system.
*/
#ifndef FRM_H
#define FRM_H

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
static int g_cframe; // Current frame count

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

#endif // FRM_H
