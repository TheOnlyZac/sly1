/**
 * @file po.h
 *
 * @brief Player object.
 */
#ifndef PO_H
#define PO_H

#include "common.h"
#include <so.h>

/**
 * @brief Player object.
 *
 * @todo Implement struct fields.
 */
struct PO : public SO
{
    // ...
};

/**
 * @brief Switch to the given PO, if it isn't the currently active one.
 */
void MakePoActive(PO *ppo);

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
 * @brief Unknown.
 */
void SwitchToIppo(int index);

/**
 * @brief Unknown.
 */
void SetPoPlayable(PO *ppo, int param);

/**
 * @brief Switch to the given PO.
 */
void SwitchToPo(PO *ppo);

#endif // PO_H
