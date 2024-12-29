/**
 * @file phasemem.h
 */
#ifndef PHASEMEM_H
#define PHASEMEM_H

#include "common.h"
#include <sdk/ee/eekernel.h>

enum PHASE {
    PHASE_Nil = -1,
    PHASE_None = 0x0,
    PHASE_Startup = 0x1,
    PHASE_Load = 0x2,
    PHASE_Main = 0x3,
    PHASE_Mpeg = 0x4,
    PHASE_Max = 0x5
};

static PHASE g_phase;

#endif // PHASEMEM_H
