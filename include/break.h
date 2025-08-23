/**
 * @file break.h
 */
#ifndef BREAK_H
#define BREAK_H

#include "common.h"
#include <bis.h>
#include <oid.h>
#include <sound.h>
#include <difficulty.h>

typedef int GRFIC;
typedef int GRFTAK;

struct BRK
{
    // ...
};

struct BRKP
{
    // ...
};

/**
 * @brief BRKP State (?).
 */
enum BRKPS
{
    BRKPS_Nil = -1,
    BRKPS_Idle = 0,
    BRKPS_Pending = 1,
    BRKPS_Fading = 2,
    BRKPS_Max = 3,
};

struct BREAK
{
    // ...
};

/**
 * @todo Move to zap.h?
 */
struct ZAPBREAK
{
    // ...
};

struct FRAGILE
{
    // ...
};

struct XP
{
    // ...
};

struct WKR
{
    LO *ploSource;
    LO *ploTarget;
    float sftMax;
    GRFIC grfic;
    GRFTAK grftak;
    float gSort;
};

void InitBrk(BRK *pbrk);

void LoadBrkFromBrx(BRK *pbrk, CBinaryInputStream *pbis);

void CloneBrk(BRK *pbrk, BRK *pbrkBase);

void PostBrkLoad(BRK *pbrk);

void PostBrkLoadCallbackHookup(BRK *pbrk, MSGID msgid, void *pv);

void UpdateBrk(BRK *pbrk, float dt);

int FAbsorbBrkWkr(BRK *pbrk, WKR *pwkr);

void BreakBrk(BRK *pbrk);

void SetBrkBroken(BRK *pbrk, int fBroken);

void SetBrkExclude(BRK *pbrk, OID oid);

void SetBrkRemain(BRK *pbrk, OID oid);

void SetBrkFixed(BRK *pbrk, OID oid);

void SetBrkRemainFixed(BRK *pbrk, OID oid);

void SetBrkOnPlayer(BRK *pbrk, int fBreakOnPlayer);

void GetBrkOnPlayer(BRK *pbrk, int *pfBreakOnPlayer);

void SetBrkOnBomb(BRK *pbrk, int fBreakOnBomb);

void GetBrkOnBomb(BRK *pbrk, int *pfBreakOnBomb);

void AddBrkTouchObject(BRK *pbrk, OID oid);

void AddBrkTouchClass(BRK *pbrk, CID cid);

/**
 * @todo Rename function.
 */
void FUN_0013DAB8();

SFX *PsfxEnsureBrk(BRK *pbrk, ENSK ensk);

int FCheckBrkTouchObject(BRK *pbrk, SO *psoRoot);

void UpdateBrkp(BRKP *pbrkp, float dt);

void HandleBrkpMessage(BRKP *pbrkp, MSGID msgid, void *pv);

int FIgnoreBrkpIntersection(BRKP *pbrkp, SO *psoOther);

void SetBrkpBrkps(BRKP *pbrkp, BRKPS brkps);

void InitBreak(BREAK *pbreak);

void InitFragile(FRAGILE *pfragile);

void AdjustFragileNewXp(FRAGILE *pfragile, XP *pxp, int ixpd);

void AdjustZapbreakNewXp(ZAPBREAK *pzapbreak, XP *pxp, int ixpd);

void UpdateZapbreak(ZAPBREAK *pzapbreak, float dt);

#endif // BREAK_H
