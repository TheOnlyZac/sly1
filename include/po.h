/**
 * @file po.h
 *
 * @brief Player object.
 */
#ifndef PO_H
#define PO_H

#include "common.h"
#include <dialog.h>
#include <so.h>

struct ALO;
struct AMB;

/**
 * @brief (?) kind.
 * @todo This should maybe be moved to pzo.h?
 */
enum PCK
{
    PCK_Nil = -1,
    PCK_Key = 0,
    PCK_Gold = 1,
    PCK_Max = 2
};

/**
 * @todo Unknown.
 * @note Based on proto, may be inaccurate.
 */
struct PZI
{
    int fCollectEnabled;
    ALO *paloBag;
    ALO *mpccharmpaloCharm[5];
    float sAutoCollect;
    ALO *paloCollect;
};

/**
 * @class PO
 * @brief Used for playable objects (e.g. JT).
 *
 * @note Based on proto, may be inaccurate.
 */
struct PO : public SO
{
    int fPlayable;
    int fLockBase;
    VECTOR posBasePrev;
    float tWakeRipple;
    AMB *pambWake;
    PZI pzi;
    ALO *paloUseCharm;
};

/**
 * @brief Switch to the given PO, if it isn't the currently active one.
 */
void MakePoActive(PO *ppo);

/**
 * @brief Collect a prize.
 */
void CollectPoPrize(PO *ppo, PCK pck, ALO *paloOther);

/**
 * @brief Gets a pointer to the current PO.
 */
PO *PpoCur();

/**
 * @brief Finds the index of the given PO (?)
 */
int _IppoFindPo(PO *ppo);

/**
 * @brief Add the given PO to the list.
 */
void AddPoToList(PO *ppo);

/**
 * @brief Remove the given PO from the list.
 */
void RemovePoFromList(PO *ppo);

/**
 * @brief Adds the given PO to the list and then calls an unknown function.
 */
void OnPoAdd(PO *ppo);

/**
 * @brief Removes the given PO from the list and then calls an unknown function.
 */
void OnPoRemove(PO *ppo);

/**
 * @brief Unknown.
 */
void SwitchToIppo(int index);

/**
 * @brief Unknown.
 */
void SetPoPlayable(PO *ppo, int playable);

/**
 * @brief Switch to the given PO.
 */
void SwitchToPo(PO *ppo);

/**
 * @brief Use a charm.
 */
void UsePoCharm(PO *ppo);

#endif // PO_H
