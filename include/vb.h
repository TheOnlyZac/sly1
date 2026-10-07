/**
 * @file vb.h
 *
 * @brief Voodoo boss (Mz. Ruby) and the helper that feeds her events.
 *
 * @todo Field offsets below are from the start of the object. VBG is left
 * empty because STEPGUARD already occupies 0x720–0xb74; do not add members
 * until the base size is known. Access those fields with STRUCT_OFFSET.
 */
#ifndef VB_H
#define VB_H

#include "common.h"
#include <stepguard.h>

/**
 * @brief One 16-byte slot in the VBC event buffer.
 * Buffer is 0xC0 slots (0xC00 bytes), allocated in FUN_001ED168.
 */
struct VBEVENT
{
    /* 0x00 */ int nType;
    /* 0x04 */ void *pvTarget;
    /* 0x08 */ float dt;
    /* 0x0C */ void *pvContext;
};

/**
 * @brief LO that owns the event list. FUN_001ED168 / FUN_001ED198.
 * LO ends at 0x30, so these really are the next fields.
 */
struct VBC : public LO
{
    /* 0x34 */ int cEvents;
    /* 0x38 */ VBEVENT *aevents;
    /* 0x3c */ int iEvent;
    /* 0x40 */ void *pv40;
    /* 0x44 */ int n44;
};

/**
 * @brief Voodoo-boss guard. Incomplete on purpose.
 * 0xC10+ fields live past STEPGUARD; do not declare them here yet.
 */
struct VBG : public STEPGUARD
{
    // ...
};

void FUN_001EB518(SO *pso, CBinaryInputStream *pbis);
void FUN_001EB550(void *pv);
void FUN_001EB598(ALO *palo);
void FUN_001EB608(PO *ppo, int fActive, PO *ppoOther);
int FUN_001EBC88(void *pv);
void FUN_001EBCD8(void *pvb, void *pv);
int FUN_001EBD08(void);
void FUN_001EBF40(void *pv, CBinaryInputStream *pbis);
void FUN_001EC098(PO *ppo);
void FUN_001EC0B8(PO *ppo);
int FUN_001EC188();
void FUN_001EC380(ALO *palo, CM *pcm, RO *pro);
void FUN_001EC478(void *pv, int nSgs);
void FUN_001ECDF8(void *pv);
void FUN_001ECE98(void *pv, int n);
void FUN_001ED018(void *pvb, int n);
void FUN_001ED020(void *pvb);
void FUN_001ED050(void *pvb, int n);
void FUN_001ED070(void *pvb, int n);
void FUN_001ED090(void *pvb, void *pasega, void *pv);
void FUN_001ED168(LO *plo);
void FUN_001ED198(LO *plo);
void FUN_001ED1D8(void *pv);
void FUN_001ED210(void *pv);
void FUN_001ED318(void *pv, int *pn);
void *FUN_001ED4C8(void *pvb, int n, void *pv, float g);
void FUN_001ED558(void *pvb, void *pv, void *pvExtra, float g);
void FUN_001ED588(void *pvb, void *pv, void *pvExtra, float g);
void FUN_001ED5B8(void *pvb, void *pv, float g);
void FUN_001ED5D8(void *pvb, void *pv, float g);
void FUN_001ED5F8(void *pvb, void *pv, float g);
void FUN_001ED618(void *pvb, void *pv, float g);

#endif // VB_H
