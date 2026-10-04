/**
 * @file vb.h
 *
 * @brief Voodoo boss (Mz. Ruby) and the helper that feeds her events.
 *
 * Field offsets below are from the start of the object. VBG is left empty
 * because STEPGUARD already occupies 0x720–0xb74; do not add members until
 * the base size is known. Access those fields with STRUCT_OFFSET.
 */
#ifndef VB_H
#define VB_H

#include "common.h"
#include <stepguard.h>
#include <po.h>
#include <lo.h>
#include <so.h>
#include <alo.h>
#include <oid.h>
#include <cid.h>

struct ASEGA;
struct SMA;
struct SM;
struct XFM;
struct SW;
struct CBinaryInputStream;

/**
 * @brief One 16-byte slot in the VBC event buffer.
 * Buffer is 0xC0 slots (0xC00 bytes), allocated in func_001ED168.
 */
struct VBEVENT
{
    /* 0x00 */ int nType;
    /* 0x04 */ void *pvTarget;
    /* 0x08 */ float dt;
    /* 0x0C */ void *pvContext;
};

/**
 * @brief LO that owns the event list. func_001ED168 / func_001ED198.
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
};

extern char D_00625760;
extern char g_unkblot7;
extern SNIP D_00275C90;
extern SNIP D_00275CA0;
extern OID D_00275CF8;

void func_001EB518(SO *pso, CBinaryInputStream *pbis);
void func_001EB550(void *pv);
void func_001EB598(ALO *palo);
void func_001EB608(PO *ppo, int fActive, PO *ppoOther);
int  func_001EBC88(void *pv);
void func_001EBCD8(void *pvb, void *pv);
int  func_001EBD08(void);
void func_001EBF40(void *pv, CBinaryInputStream *pbis);
void func_001EC098(PO *ppo);
void func_001EC0B8(PO *ppo);
int  func_001EC188(void);
void func_001EC380(ALO *palo, CM *pcm, RO *pro);
void func_001EC478(void *pv, int nSgs);
void func_001ECDF8(void *pv);
void func_001ECE98(void *pv, int n);
void func_001ED018(void *pvb, int n);
void func_001ED020(void *pvb);
void func_001ED050(void *pvb, int n);
void func_001ED070(void *pvb, int n);
void func_001ED090(void *pvb, void *pasega, void *pv);
void func_001ED168(LO *plo);
void func_001ED198(LO *plo);
void func_001ED1D8(void *pv);
void func_001ED210(void *pv);
void func_001ED318(void *pv, int *pn);
void *func_001ED4C8(void *pvb, int n, void *pv, float g);
void func_001ED558(void *pvb, void *pv, void *pvExtra, float g);
void func_001ED588(void *pvb, void *pv, void *pvExtra, float g);
void func_001ED5B8(void *pvb, void *pv, float g);
void func_001ED5D8(void *pvb, void *pv, float g);
void func_001ED5F8(void *pvb, void *pv, float g);
void func_001ED618(void *pvb, void *pv, float g);
void *FUN_001e9970(void);
void *PvAllocSwImpl(int cb);
void SubscribeAsegaObject(ASEGA *pasega, LO *plo);
void GetXfmPos(XFM *pxfm, VECTOR *ppos);
void SetSmaGoal(SMA *psma, OID oid);
void GetSmaCur(SMA *psma, OID *poid);
void LoadStepguardFromBrx(STEPGUARD *pstepguard, CBinaryInputStream *pbis);
void SetStepguardGoal(STEPGUARD *pstepguard, VECTOR *ppos);
void UpdateStepguardGoal(STEPGUARD *pstepguard, int n);
void OnPoActive(PO *ppo, int n, PO *ppoOther);
void OnStepguardExitingSgs(STEPGUARD *pstepguard, SGS sgs);
LO *PloFindSwObjectByClass(SW *psw, int n, CID cid, LO *plo);

#endif // VB_H
