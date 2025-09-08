/**
 * @file mark.h
 */
#ifndef MARK_H
#define MARK_H

#include "common.h"
#include <geom.h>
#include <bsp.h>
#include <vec.h>
#include <so.h>
#include <sw.h>

// TODO: Figure out where this should be defined at.
struct XP;

/**
 * @brief (?) kind.
 */
enum XPK
{
    XPK_Nil = -1
};

/**
 * @brief Material kind?
 */
enum MTLK
{
    MTLK_Nil = -1,
    MTLK_Default = 0,
    MTLK_Sand = 1,
    MTLK_Metal = 2,
    MTLK_Wood = 3,
    MTLK_Rock = 4,
    MTLK_Rubber = 5,
    MTLK_Ice = 6,
    MTLK_Tire = 7,
    MTLK_Velcro = 8,
    MTLK_NoBounce = 9,
    MTLK_NoFriction = 10,
    MTLK_NoFrictionElastic = 11,
    MTLK_Max = 12
};

/**
 * @brief Unknown.
 */
struct SBI
{
    VECTOR pos;
    VECTOR normal;
    float gDist;
    XPK xpk;
    // ...
};

float MuFromAmtlk(MTLK *amtlk);

float ElasFromAmtlk(MTLK *amtlk);

XP *PxpAdd(SO *pso0, SO *pso1, VECTOR *ppos, VECTOR *pnormal, float gDist, XPK xpk, void *pv0, void *pv1, XP **ppxpFirst);

void RecalcSwXpPos(SW *psw, int cpxp, XP **apxp);

void RecalcSwXpMovement(SW *psw, int cpxp, XP **apxp);

void FreeSwXpList(SW *psw, XP *pxpFirst);

void FindClosestPointOnLine(VECTOR *ppos, VECTOR *pposSeg0, VECTOR *pposSeg1, float *pu, float *ps);

void FindClosestPointOnLineSegment(VECTOR *ppos, VECTOR *pposSeg0, VECTOR *pposSeg1, float *pu, float *ps);

int ClsgClipSoAllEdges(SO *pso0, SO *pso1, BSP *pbsp, int clsgMax, LSG *alsg);

int ClsgClipSoBspEdges(SO *pso0, SO *pso1, int cbspPruned, BSP *abspPruned, int clsgMax, LSG *alsg);

void CategorizeAlsg(int clsg, LSG *alsg, int *pciposEmbed, int *aiposEmbed, LSG **aplsgEmbed, LSG **pplsgEdge);

int CplsgFindEdgePath(SURF *asurf, int isurf, int isurfTarget, LSG *plsgEdge, LSG **aplsg);

void MarkSoContactsBspBsp(SO *pso0, SO *pso1, int cbspPruned, BSP *abspPruned, BSP *pbspPruned, XP **ppxpFirst);

int CsbiIntersectSphereBsp(VECTOR *pposCenter, float sRadius, int cbsp, BSP *absp, BSP *pbspPrune, GEOM *pgeom, int csbiMax, SBI *asbi);

void MarkSoContactsSphereBsp(SO *pso0, VECTOR *pposCenter, float sRadius, SO *pso1, int cbsp, BSP *absp, BSP *pbspPrune, XP **ppxpFirst);

void MarkSoContactsSphereSphere(SO *pso0, SO *pso1, XP **ppxpFirst);

void CalculateCenterContact(SO *pso, VECTOR *pnormal, float gDot, VECTOR *ppos, float *ps);

int FMarkSoContactsCenterBsp(SO *pso0, SO *pso1, int cbspPruned, BSP *abspPruned, BSP *pbspPruned, XP **ppxpFirst);

int FClipEdgeToSphere(VECTOR *pposSphere, float sRadius, VECTOR *ppos0, VECTOR *ppos1, float *pu, VECTOR *ppos, VECTOR *pnormal, float *pgDot);

int FMarkSoContactsCenterSphere(SO *pso0, SO *pso1, XP **ppxpFirst);

void AddSoXps(SO *psoRoot, SO *psoOther, int fCenterXp, int cbspPruned, BSP *abspPruned, BSP *pbspPruned, XP **ppxpFirst);

XP *PxpMarkSwContactsRoot(SW *psw, SO **apso, int fCenterXp);

#endif // MARK_H
