/**
 * @file wm.h
*/
#pragma once
#include <iostream>

/**
 * @brief Unknown, possibly WorldMap
*/
struct WM
{
    // todo
};

/**
 * @brief Unknown, possibly WorldMap State
*/
enum WMS
{
    WMS_ZERO = 0, // temp

    // todo
    // ...

    WMS_MAX
};

/**
 * @brief Sets the WM state.
 *
 * @param pwm Pointer to the WM
 * @param pwms Pointer to the WM state
*/
void SetWmWms(WM* pwm, WMS wms);
