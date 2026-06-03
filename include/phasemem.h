/**
 * @file phasemem.h
 */
#ifndef PHASEMEM_H
#define PHASEMEM_H

#include "common.h"
#include <dmas.h>
#include <render.h>
#include <shd.h>

/**
 * @brief Engine phase.
 */
enum PHASE
{
    PHASE_Nil = -1,
    PHASE_None = 0,
    PHASE_Startup = 1,
    PHASE_Load = 2,
    PHASE_Main = 3,
    PHASE_Mpeg = 4,
    PHASE_Max = 5
};

/**
 * @todo Verify size.
 */
struct PHASEMEM_STARTUP
{
    uchar abSpool[3427328];
};

/**
 * @todo Verify size.
 */
struct PHASEMEM_LOAD
{
    uchar abSpool[3427328];
};

/**
 * @todo Verify size.
 */
struct PHASEMEM_MAIN
{
    QW aaqwGifs[2][32768];
    QW aaqwVifs[2][65536];
    SLI aasli[2][4192];
    RPL arpl[1024];
};

/**
 * @todo Verify size.
 */
struct PHASEMEM_MPEG
{
    uchar abSpool[32832];
    uchar abMpegEeAudio[49152];
    uchar abMpegWork[1388392];
    // ...
};

union PHASEMEM
{
    PHASEMEM_STARTUP startup;
    PHASEMEM_LOAD load;
    PHASEMEM_MAIN main;
    PHASEMEM_MPEG mpeg;
};

/**
 * @brief Current engine phase.
 */
extern PHASE g_phase;

/**
 * @brief Set the current engine phase.
 */
void SetPhase(PHASE phase);

/**
 * @brief Clear the current engine phase.
 */
void ClearPhase(PHASE phase);

#endif // PHASEMEM_H
