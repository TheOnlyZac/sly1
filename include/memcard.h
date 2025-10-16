/**
 * @file memcard.h
 */
#ifndef MEMCARD_H
#define MEMCARD_H

#include "common.h"

/**
 * @todo Incomplete.
 */
struct MEMCARD
{
    /* 0x00 */ int semaphoreId;
    /* 0x04 */ int threadId;
    /* 0x08 */ int field_0x08;
    /* 0x0c */ int field_0x0c;
    /* 0x10 */ int field_0x10;
};

/**
 * @note Judging from the memset in InitSave,
 * this struct could be over 20k bytes long.
 */
struct SAVE
{
    int field_0x00;
    // ...
};

/**
 * @brief Startup the memory card system.
 */
void StartupMemcard();

void UpdateSave(SAVE *psave);

extern SAVE g_save;

#endif // MEMCARD_H
