/**
 * @file pzo.h
 *
 * @brief Vaults, clue bottles, keys and locks.
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
 * @brief Something (?) clue state?
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
 * @class _SPRIZE
 * @brief Base class for SPRIZEs.
 */
struct SPRIZE : public SO
{
    // ...
};

/**
 * @class _SCPRIZE
 * @brief Base class for SCPRIZEs.
 */
struct SCPRIZE : public SPRIZE
{
    // ...
};

/**
 * @class CLUE
 * @brief Clue bottle.
 */
struct CLUE : public SPRIZE
{
    // ...
};

/**
 * @class LOCK
 * @brief Treasure key lock.
 */
struct LOCK : public ALO
{
    // ...
};

/**
 * @class LOCK_GROUP
 * @brief Group of treasure key lock objects.
 */
struct LOCKG : public ALO
{
    // ...
    /* 0x2DC */ uint coidLock;
    /* 0x2E0 */ OID aoidLock[8];
};

/**
 * @class VAULT
 * @brief Vault used for unlocking thief moves in levels.
 */
struct VAULT : public PO
{
    // ...
};

/**
 * @brief Vault tumbler.
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

/**
 * @brief Loads a LOCK object from a binary input stream.
 *
 * @param plock Pointer to the LOCK to initialize.
 * @param pbis Pointer to the binary input stream to read from.
 */
void LoadLockFromBrx(LOCK *plock, CBinaryInputStream *pbis);

/**
 * @brief Sets up a LOCK object after loading.
 *
 * @param plock Pointer to the LOCK object.
 */
void PostLockLoad(LOCK *plock);

/**
 * @brief Loads a LOCKG object from a binary input stream.
 *
 * @param plockg Pointer to the LOCKG to initialize.
 * @param pbis Pointer to the binary input stream to read from.
 */
void LoadLockgFromBrx(LOCKG *plockg, CBinaryInputStream *pbis);

/**
 * @brief Sets up a LOCKG object after loading.
 *
 * @param plockg Pointer to the LOCKG object.
 */
void PostLockgLoad(LOCKG *plockg);

/**
 * @brief Sets the index of the LOCKG object(?)
 *
 * @param plockg Pointer to the LOCKG object.
 * @param ifws Index to set.
 */
void SetLockgIndex(LOCKG *plockg, int ifws);

/**
 * @brief Adds a lock to the given lock group.
 *
 * @param plockg Pointer to the LOCKG object.
 * @param oidLock OID of the LOCK to add.
 */
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
