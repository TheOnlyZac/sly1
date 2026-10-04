/**
 * @file splice/spliceutils.h
 *
 * @brief Utility functions for the splice scripting engine.
 */
#ifndef SPLICE_SPLICEUTILS_H
#define SPLICE_SPLICEUTILS_H

#include "common.h"
#include <splice/splotheap.h>

extern CSplotheap g_splotheapPair;
extern CSplotheap g_splotheapFrame;
extern CSplotheap g_splotheapVarb;
extern CSplotheap g_splotheapProc;
extern CSplotheap g_splotheapMethod;

/**
 * @brief Splice startup function.
*/
void StartupSplice();

/**
 * @brief Shutdown the splice scripting engine.
 */
void ShutdownSplice();

#endif // SPLICE_SPLICEUTILS_H
