/**
 * @file memcard.h
 * @brief Memory Card access and save files.
 */
#ifndef MEMCARD_H
#define MEMCARD_H

#include "common.h"
#include "game.h"

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
    int port;         // 0x04 (guess)
    int slot;         // 0x08 (guess)
    int field_0x0c;
    int field_0x10;
    int mode;         // 0x14 (guess)
    int state;        // 0x18 (guess)
    float tState;     // 0x1c (guess)
    STRUCT_PADDING(1);
    int mcType;       // 0x24 (guess)
    int mcFree;       // 0x28 (guess)
    int mcFormat;     // 0x2c (guess)
    uint8_t unk_0x30[0x22];
    uint8_t unk_0x52;
    uint8_t unk_0x53;
    uint16_t unk_0x54;
    uint8_t unk_0x56;
    uint8_t unk_0x57;
    uint8_t unk_0x58;
    // ...
};

/**
 * @brief Startup the memory card system.
 */
void StartupMemcard();

void InitMemcard(MEMCARD *pmemcard);

// MemcardThreadEntry?
void FUN_0018b600();

void SetMemcardThreadHighPrio(MEMCARD *pmemcard);

int FMemcardThreadValid(MEMCARD *pmemcard);

void InitSave(SAVE *psave, int unk1, int unk2);

void UpdateSave(SAVE *psave);

/**
 * @brief Unknown function.
 * @param psave Pointer to save file.
 * @todo Figure out what this actually does, give better name. 
 */
void FUN_0018c7f8(SAVE *psave);

int FUN_0018b910(int n);
int FUN_0018b930(int n);
int FUN_0018b988(int a, int b);
int FUN_0018bc90(int a, int b, int *pout);
int FUN_0018bd00(int a, int b, int *pc);
void FUN_0018c178(SAVE *psave, int state);
int FUN_0018c1a8(SAVE *psave);
int FUN_0018c1e8(SAVE *psave);
int FUN_0018c888(SAVE *psave, char *pchz, int c, char *pbHdr, int *pe);
int FUN_0018c9c0(SAVE *psave, char *pchz, char *pbHdr);
int FUN_0018cfc0(SAVE *psave, char *pchz, GS *pgs);
int FUN_0018d028(SAVE *psave, char *pchz, GS *pgs, char *pbHdr);
int FUN_0018d168(SAVE *psave, int *pcb);
int FUN_0018d368(SAVE *psave, char *pchz, void *pv, int cb);
int CompareSaves(SAVE *psave1, SAVE *psave2);
int FUN_0018d1f8(SAVE *psave);
int FUN_0018d228(SAVE *psave, int b);
int FUN_0018d268(SAVE *psave, char *pchz, int mode, int *pfd);
int FUN_0018d2b0(SAVE *psave, int fd);
int FUN_0018d2e8(SAVE *psave, int fd, void *pv, int cb, int *pc);
int FUN_0018d328(SAVE *psave, int fd, void *pv, int cb, int *pc);

extern SAVE g_save;

#endif // MEMCARD_H
