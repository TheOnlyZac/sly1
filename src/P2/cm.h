#pragma once

/**
 * @brief Game Camera
*/
struct CM
{
	// todo
	// ...
};

// Global variables
static CM g_cm; // Main game camera
extern CM* g_pcm; // Pointer to the main game camera

/**
 * @brief Sets up the game camera.
 *
 * @param pcm Pointer to the camera.
*/
void SetupCm(CM* pcm);
