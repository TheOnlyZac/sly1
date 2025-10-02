/**
 * @file bbmark.h
 */
#ifndef BBMARK_H
#define BBMARK_H

#include "common.h"

typedef int GRFPVA;

// Forward.
struct SW;
struct SO;

// TODO: Implement structs.
struct XP;
struct OXA;
struct OXF;

/**
 * @brief Unknown.
 */
struct OX
{
    XP *pxp;
    OX *poxNext;
    OX *poxOther;
    SO *psoOther;
};

/**
 * @brief Unknown.
 */
struct OXA
{
    OX *pox;
    SO *pso;
    OXA *poxaNext;
    OXA *poxaPrev;
};

void UpdateSwPox(SW *psw, OXA *poxa0, OXA *poxa1, OXF oxfAdd, OXF oxfRemove);

OX *PoxAddSw(SW *psw, OXA *poxa, OXA *poxaOther);

OX *PoxRemoveSw(SW *psw, OXA *poxa, OXA *poxaOther);

OX *PoxFromSoSo(SO *pso, SO *psoOther);

XP *PxpFirstFromSoSo(SO *pso, SO *psoOther);

void AddSwAaobrObject(SW *psw, SO *pso);

void RemoveSwAaobrObject(SW *psw, SO *pso);

void InvalidateSwAaox(SW *psw);

void UpdateSwAaox(SW *psw);

void InvalidateSwXpForObject(SW *psw, SO *pso, GRFPVA grfpvaInvalid);

void RecalcSwXpAll(SW *psw, int fCenterXp);

void RecalcSwOxfFilterForObject(SW *psw, SO *pso);

#endif // BBMARK_H
