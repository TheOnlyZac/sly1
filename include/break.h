/**
 * @file break.h
 */
#ifndef BREAK_H
#define BREAK_H

#include "common.h"
#include <so.h>
#include <bis.h>
#include <oid.h>
#include <sound.h>
#include <difficulty.h>

typedef int GRFBRK;

/**
 * @brief Breakable piece state.
 */
enum BRKPS
{
    BRKPS_Nil = -1,
    BRKPS_Idle = 0,
    BRKPS_Pending = 1,
    BRKPS_Fading = 2,
    BRKPS_Max = 3
};

/**
 * @brief Unknown.
 */
enum BRPT
{
    BRPT_Nil = -1,
    BRPT_Disappear = 0,
    BRPT_Remain = 1,
    BRPT_Fixed = 2,
    BRPT_RemainFixed = 3,
    BRPT_Appear = 4,
    BRPT_Max = 5
};

/**
 * @brief Unknown.
 */
struct BRP
{
    /* 0x00 */ BRPT brpt;
    /* 0x04 */ OID oid;
    /* 0x08 */ LO *plo;
};

/**
 * @class (_BRK)
 * @brief Breakable base.
 */
struct BRK : public SO
{
    // ...
    /* 0x550 */ int cbrp;
    /* 0x554 */ BRP abrp[16];
    // ...
    /* 0x63c */ GRFBRK grfbrk;
    // ...
};

/**
 * @brief BREAKABLE_PIECE
 * @brief Shards of breakables that appear when it's broken.
 */
struct BRKP
{
    // ...
};

/**
 * @class BREAKABLE
 * @brief Breakable object.
 */
struct BREAK : BRK
{
    // ...
};

/**
 * @class ZAPBREAK
 * @brief Unknown.
 *
 * @todo Move to zap.h?
 */
struct ZAPBREAK
{
    // ...
};

/**
 * @class FRAGILE.
 * @brief Unknown.
 */
struct FRAGILE
{
    // ...
};

/**
 * @brief Unknown.
 *
 * @todo Should this be somewhere else?
 */
struct XP
{
    // ...
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
