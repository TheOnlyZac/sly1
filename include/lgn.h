/**
 * @file lgn.h
 */
#ifndef LGN_H
#define LGN_H

#include "common.h"
#include <screen.h>
#include <shape.h>
#include <break.h>
#include <joy.h>
#include <zap.h>
#include <cm.h>
#include <po.h>
#include <jt.h>

// Forward.
struct RO;
struct CPDEFI;

/**
 * @brief (?) state.
 */
enum LGNS
{
    LGNS_Nil = -1,
    LGNS_Passive = 0,
    LGNS_Active = 1,
    LGNS_Zap = 2,
    LGNS_Dead = 3,
    LGNS_Max = 4
};

/**
 * @brief Unknown.
 */
struct SWP : public BRK
{
    // ...
};

/**
 * @brief Unknown.
 * @note Inherits from PO in the prototype but not in retail.
 */
struct LGN
{
    // ...
};

/**
 * @brief Unknown.
 */
struct LGNR : public BLOT
{
    // ...
};

void InitLgn(LGN *plgn);

void PostLgnLoad(LGN *plgn);

void UpdateLgnActive(LGN *plgn, JOY *pjoy, float dt);

void UpdateLgn(LGN *plgn, float dt);

void OnLgnActive(LGN *plgn, int fActive, PO *ppoOther);

void RenderLgnAll(LGN *plgn, CM *pcm, RO *pro);

void GetLgnCpdefi(LGN *plgn, float dt, CPDEFI *pcpdefi);

int FInvulnerableLgn(LGN *plgn, ZPK zpk);

JTHS JthsCurrentLgn(LGN *plgn);

void UseLgnCharm(LGN *plgn);

void ApplyLgnThrow(LGN *plgn, PO *ppo);

int FTakeLgnDamage(LGN *plgn, ZPR *pzpr);

void HandleLgnMessage(LGN *plgn, MSGID msgid, void *pv);

void SetLgnLgns(LGN *plgn, LGNS lgns);

void UpdateLgnrAim(LGNR *plgnr, JOY *pjoy);

void DrawLgnr(LGNR *plgnr);

void InitSwp(SWP *pswp);

void PostSwpLoad(SWP *pswp);

void UpdateSwp(SWP *pswp, float dt);

void ProjectSwpTransform(SWP *pswp, float dt, int fParentDirty);

void SetSwpShape(SWP *pswp, SHAPE *pshape, float tMax);

#endif // LGN_H
