/**
 * @file memcard.h
 * @brief Memory Card access and save files.
 */
#ifndef MEMCARD_H
#define MEMCARD_H

#include "common.h"

/**
 * @brief Memory Card.
 * @todo Incomplete.
 */
struct MEMCARD
{
    /* 0x00 */ int semaId;
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

void InitMemcard(MEMCARD *pmemcard);

// MemcardThreadEntry?
void FUN_0018b600(void *data);

void SetMemcardThreadHighPrio(MEMCARD *pmemcard);

int FMemcardThreadValid(MEMCARD *pmemcard);

void InitSave(SAVE *psave, int unk1, int unk2);

void UpdateSave(SAVE *psave);

extern SAVE g_save;

#endif // MEMCARD_H
