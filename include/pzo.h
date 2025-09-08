/**
 * @file pzo.h
 *
 * @brief Vaults, clue bottles and keys.
 */
#ifndef PZO_H
#define PZO_H

#include "common.h"
#include <joy.h>
#include <alo.h>
#include <so.h>
#include <po.h>
#include <sm.h>
#include <cm.h>

// Forward.
struct RO;
struct WKR;

/**
 * @brief (?) clue state?
 */
enum PCS
{
    PCS_Nil = -1,
    PCS_Collected = 0,
    PCS_Collectible = 1,
    PCS_NotCollectible = 2,
    PCS_Max = 3
};

/**
 * @brief Goal advice dialog kind (?)
 */
enum GOADK
{
    GOADK_Nil = -1,
    GOADK_LessThanHalf = 0,
    GOADK_MoreThanHalf = 1,
    GOADK_Most = 2,
    GOADK_AllButOne = 3,
    GOADK_All = 4,
    GOADK_Max = 5
};

/**
 * @brief Unknown.
 */
struct SPRIZE : public SO
{
    // ...
};

/**
 * @brief Unknown.
 */
struct SCPRIZE : public SPRIZE
{
    // ...
};

/**
 * @brief Clue bottle.
 */
struct CLUE : public SPRIZE
{
    // ...
};

/**
 * @brief Lock.
 */
struct LOCK : public ALO
{
    // ...
};

/**
 * @brief Lock (?)
 */
struct LOCKG : public ALO
{
    // ...
};

/**
 * @brief Vault.
 */
struct VAULT : public PO
{
    // ...
};

/**
 * @brief Vault tumble.
 */
struct TMBL
{
    ALO *palo;
    SM *psmDial;
    SMA *psmaDial;
};

void InitSprize(SPRIZE *psprize);

void LoadSprizeFromBrx(SPRIZE *psprize, CBinaryInputStream *pbis);

void BindSprize(SPRIZE *psprize);

void PostSprizeLoad(SPRIZE *psprize);

void UpdateSprize(SPRIZE *psprize, float dt);

void CollectSprize(SPRIZE *psprize);

void EmitSprizeExplosion(SPRIZE *psprize);

PCS PcsFromSprize(SPRIZE *psprize);

void AddSprizeAseg(SPRIZE *psprize, OID oidAseg);

void HandleSprizeMessage(SPRIZE *psprize, MSGID msgid, void *pv);

int FIgnoreSprizeIntersection(SPRIZE *psprize, SO *psoOther);

void InitScprize(SCPRIZE *pscprize);

void CloneScprize(SCPRIZE *pscprize, SCPRIZE *pscprizeBase);

PCS PcsFromScprize(SCPRIZE *pscprize);

void CollectScprize(SCPRIZE *pscprize);

void LoadLockFromBrx(LOCK *plock, CBinaryInputStream *pbis);

void PostLockLoad(LOCK *plock);

void LoadLockgFromBrx(LOCKG *plockg, CBinaryInputStream *pbis);

void PostLockgLoad(LOCKG *plockg);

void SetLockgIndex(LOCKG *plockg, int ifws);

void AddLockgLock(LOCKG *plockg, OID oidLock);

void TriggerLockg(LOCKG *plockg);

void InitClue(CLUE *pclue);

void LoadClueFromBrx(CLUE *pclue, CBinaryInputStream *pbis);

void CloneClue(CLUE *pclue, CLUE *pclueBase);

void PostClueLoad(CLUE *pclue);

void OnClueSmack(CLUE *pclue);

void CollectClue(CLUE *pclue);

void BreakClue(CLUE *pclue);

void CollectClueSilent(CLUE *pclue);

void ImpactClue(CLUE *pclue, int fParentDirty);

int FAbsorbClueWkr(CLUE *pclue, WKR *pwkr);

void RenderClueAll(CLUE *pclue, CM *pcm, RO *pro);

void CollectAllClues(int nParam);

void SetGrfvault(int grfvault);

void InitVault(VAULT *pvault);

void PostTmblLoad(TMBL *ptmbl, OID oidInitialState);

void PostVaultLoad(VAULT *pvault);

void OnVaultActive(VAULT *pvault, int fActive, PO *ppoOther);

void UpdateVaultActive(VAULT *pvault, JOY *pjoy, float dt);

void HandleVaultMessage(VAULT *pvault, MSGID msgid, void *pv);

void AddVaultGoadDialog(VAULT *pvault, GOADK goadk, OID oidDialog);

#endif // PZO_H
