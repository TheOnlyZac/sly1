/**
 * @file lo.h
 *
 * @brief Level objects.
 */
#ifndef LO_H
#define LO_H

#include "common.h"
#include <oid.h>
#include <basic.h>
#include <dl.h>
#include <splice/frame.h>
#include <mq.h>

struct ALO; // Forward declaration.
struct SW;
struct PXR;
struct LM;
struct CLQ;
struct VECTOR;

/**
 * @brief "LO"
 */
struct LO : public BASIC
{
    OID oid;
    DLE dleOid;
    SW *psw;
    ALO *paloParent;
    DLE dleChild;
    LO *ploCidNext;
    MQ *pmqFirst;
    // char *pchzName; // Not in release
    CFrame *pframe;
    PXR *ppxr;
    // ulong dtickPerf; // Not in release
};

/**
 * @brief "Proxy Root"?
 */
struct PXR
{
    LO *plo;
    OID oidProxyRoot;
    DLE dleProxyRoot;
    char *pchzProxyRoot;
};

/**
 * @brief Initialize LO with defaults set
 */
void InitLo(LO *plo);

/**
 * @brief Calls HandleLoSpliceEvent with unknown event
 *        Called by LO subclasses?
 */
void PostLoLoad(LO *plo);

/**
 * @brief Adds LO to 'dlChild' of either parent ALO, if present, or SW
 *        If LO is in world, also calls AddLoHierarchy
 */
void AddLo(LO *plo);

/**
 * @brief Calls OnLoAdd, and SendLoMessage with MSGID_added
 */
void AddLoHierarchy(LO *plo);

/**
 * @brief Does nothing
 */
void OnLoAdd();

/**
 * @brief Removes LO from 'dlChild' of either parent ALO, if present, or SW
 *        If LO is in world, also calls RemoveLoHierarchy
 */
void RemoveLo(LO *plo);

/**
 * @todo
 */
void DeferLoRemove(LO *plo);

/**
 * @brief If global 'uSuck' is within given range, calls DeferLoRemove with this LO
 */
void SetLoSuckHideLimits(LO *plo, LM *plmUSuck);

/**
 * @brief Calls OnLoRemove, and SendLoMessage with MSGID_removed
 */
void RemoveLoHierarchy(LO *plo);

/**
 * @brief Does nothing
 */
void OnLoRemove(LO *plo);

/**
 * @brief If LO is in world, remove it
 */
void SnipLo(LO *plo);

/**
 * @brief Check ALO is parent/grandparent/etc of LO
 */
int FFindLoParent(LO *plo, ALO *paloParent);

/**
 * @brief Removes LO, sets ALO as parent, then re-adds LO
 */
void SetLoParent(LO *plo, ALO *paloParent);

/**
 * @brief Checks if the LO is currently in the world.
 */
int FIsLoInWorld(LO *PLO);

/**
 * @brief Check if LO is in world and updates provided flag with result
 */
void GetLoInWorld(LO *plo, int *pfInWorld);

/**
 * @brief Creates new LO, clones provided LO, returns new LO
 */
LO* PloCloneLo(LO *plo, SW *psw, ALO *paloParent);

/**
 * @brief Clones from 'base' LO into provided LO
 */
void CloneLoHierarchy(LO *plo, LO *ploBase);

/**
 * @brief Clones from 'base' LO into provided LO
 */
void CloneLo(LO *plo, LO *ploBase);

/**
 * @todo
 */
void SubscribeSwPpmqStruct(SW *psw, MQ **ppmqFirst, PFNMQ pfnmq, void *pvContext);

void UnsubscribeSwPpmqStruct(SW *psw, MQ **ppmqFirst, PFNMQ pfnmq, void *pvContext);

void SubscribeLoStruct(LO *plo, PFNMQ pfnmq, void *pvContext);

void UnsubscribeLoStruct(LO *plo, PFNMQ pfnmq, void *pvContext);

void SubscribeLoObject(LO *plo, LO *ploTarget);

void UnsubscribeLoObject(LO *plo, LO *ploTarget);

/**
 * @brief Calls HandleLoMessage, then each MQ function with provided MSGID and data pointer
 */
void SendLoMessage(LO *plo, MSGID msgid, void *pv);

/**
 * @brief Loads options from Brx
 */
void LoadLoFromBrx(LO *plo, CBinaryInputStream *pbis);

/**
 * @brief Checks if LO OID, or LO's PXR OID, match provided OID
 */
int FMatchesLoName(LO *plo, OID oid);

/**
 * @brief Return OID of LO's PXR, or Nil
 */
OID GetProxyLo(LO *plo);

/**
 * @brief Return OID of LO's PXR, or LO's own OID
 */
OID OidProxyLoPreferred(LO *plo);

/**
 * @brief Updates provided OID pointer with LO's PXR OID
 */
void GetLoOidProxy(LO *plo, OID *poid);

/**
 * @todo Args for following functions based on proto
 */
void PostSpliceEventCallback(LO *plo, uint symidEvent, void *pvarg);

int FFilterSpliceEvent(LO *plo, /* SYMEVID */ int symevid, int cargs, void **ppvargs);

void HandleLoSpliceEvent(LO *plo, uint symidEvent, int cargs, void **ppvargs);

void EnsureLoSidebagBool(LO *plo, uint optid, int f);

void EnsureLoSidebagInt(LO *plo, uint optid, int n);

void EnsureLoSidebagFoat(LO *plo, uint optid, float g);

void EnsureLoSidebagClq(LO *plo, uint optid, CLQ *pclq);

void EnsureLoSidebagLm(LO *plo, uint optid, LM *plm);

void EnsureLoSidebagOid(LO *plo, uint optid, OID oid);

void EnsureLoSidebagVector(LO *plo, uint optid, VECTOR *pvec);

#endif // LO_H
