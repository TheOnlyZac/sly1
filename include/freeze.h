/**
 * @file freeze.h
 */
#ifndef FREEZE_H
#define FREEZE_H

#include "common.h"
#include <alo.h>
#include <so.h>
#include <sw.h>
#include <dl.h>

/**
 * @brief Merge (?)
 * @todo Should this be defined elsewhere?
 */
struct MRG
{
    DLE dle;
    int cpalo;
    ALO **apalo;
};

void RemergeSwObject(SW *psw, ALO *palo);

void MergeSwFreezeGroups(SW *psw, ALO *paloFreezeGroup1, ALO *paloFreezeGroup2);

void SplinterSwFreezeGroup(SW *psw, ALO *paloFreezeRoot);

void MergeSwGroup(SW *psw, MRG *pmrg);

void AddSwMergeGroup(SW *psw, MRG *pmrg);

void RemoveFromArray(int *pcpv, void **apv, void *pv);

void RemoveSwMergeGroup(SW *psw, MRG *pmrg);

void RemergeSwObjects(SW *psw);

void FreezeAloHierarchy(ALO *palo, int fFreeze);

void GetAloFrozen(ALO *palo, int *pfFrozen);

void FreezeAlo(ALO *palo, int fFreeze);

void FreezeSo(SO *pso, int fFreeze);

void RefreezeSwObjects(SW *psw);

void UpdateSwBusyList(SW *psw);

#endif // FREEZE_H
