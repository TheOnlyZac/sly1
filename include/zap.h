/**
 * @file zap.h
 *
 * @brief Zap (damage) system.
 */
#ifndef ZAP_H
#define ZAP_H

#include "common.h"
#include <ensure.h>
#include <oid.h>
#include <so.h>

// Forward.
struct XP;
struct PO;
struct ZPD;

typedef void (*PFNZAP)(ZPD *pzpd, PO *ppo);

/**
 * @brief Zap kind.
 */
enum ZPK
{
    ZPK_Nil = -1,
    ZPK_Blunt = 0,
    ZPK_Electric = 1,
    ZPK_Fire = 2,
    ZPK_Water = 3,
    ZPK_Crush = 4,
    ZPK_Pit = 5,
    ZPK_Max = 6
};

/**
 * @brief Zap _?_ Kind
 *
 * @todo Figure out what the O stands for.
*/
enum ZOK
{
    ZOK_Nil = -1,
    ZOK_Inherit = 0,
    ZOK_Zap = 1,
    ZOK_NoZap = 2,
    ZOK_Ignore = 3,
    ZOK_ZapAndIgnore = 4,
    ZOK_Max = 5
};

/**
 * @brief Unknown.
 */
struct ZPD
{
    /* 0x00 */ SO *pso;
    /* 0x04 */ ZPK zpk;
    float dzThrow;
    int fThrowCut;
    int coidThrow;
    OID aoidThrow[32];
    /* 0x94 */ int cploThrow;
    /* 0x98 */ LO *aploThrow[32];
};

/**
 * @brief Zap.
 */
struct ZAP
{
    // ...
};

/**
 * @brief TOUCH_ZAPPER
 * @brief Zapper trigger on touching the player.
 *
 * @todo Does it inherit from ZAP?
*/
struct TZP : public SO
{
    // ...
    /* 0x550 */ ZPD zpd;
    // ...
};

/**
 * @brief Unknown.
 */
struct ZPR
{
    /* 0x00 */ ZPK zpk;
    LO *ploSource;
    /* 0x08 */ void *pv;
    /* 0x0c */ PFNZAP pfnzap;
};

/**
 * @brief Zap volume?
 * @todo Implement the struct.
 */
struct VOLZP : public TZP
{
    // ...
};

void InitTzp(TZP *ptzp);

void PostTzpLoad(TZP *ptzp);

void UpdateTzp(TZP *ptzp, float dt);

void CloneTzp(TZP *ptzp, TZP *ptzpBase);

void RenderTzpAll(TZP *ptzp, CM *pcm, RO *pro);

int FInflictTzpZap(TZP *ptzp, XP *pxp, ZPR *pzpr);

ZPD *PzpdEnsureTzp(TZP *ptzp, ENSK ensk);

/**
 * @todo Rename.
 */
void FUN_001F5210(TZP *ptzp);

void InitVolzp(VOLZP *pvolzp);

void UpdateVolzp(VOLZP *pvolzp, float dt);

void InitZpd(ZPD *pzpd, SO *pso);

void PostZpdLoad(ZPD *pzpd);

void ApplyZpdThrow(ZPD *pzpd, PO *ppo);

void InflictZpdZap(ZPD *pzpd, XP *pxp, ZPR *pzpr);

void AddZpdZapObject(ZPD *pzpd, OID oid);

void AddZpdZapLo(ZPD *pzpd, LO *plo);

void RemoveZpdZapLo(ZPD *pzpd, LO *plo);

#endif // ZAP_H
