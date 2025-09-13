/**
 * @file jlo.h
 */
#ifndef JLO_H
#define JLO_H

#include "common.h"
#include <button.h>
#include <xform.h>
#include <alo.h>
#include <so.h>

/**
 * @brief (?) state.
 */
enum JLOS
{
    JLOS_Nil = -1,
    JLOS_Jump = 0,
    JLOS_Land = 1,
    JLOS_Idle = 2,
    JLOS_Fire = 3,
    JLOS_Taunt = 4,
    JLOS_Max = 5
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct JLO : public SO
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct JLOVOL : public VOLBTN
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct JLOC : public ALO
{
    // ...
};

void InitJlo(JLO *pjlo);

void LoadJloFromBrx(JLO *pjlo, CBinaryInputStream *pbis);

void PostJloLoad(JLO *pjlo);

void PresetJloAccel(JLO *pjlo, float dt);

void UpdateJlo(JLO *pjlo, float dt);

JLOS JlosNextJlo(JLO *pjlo);

void SetJloJlovol(JLO *pjlo, JLOVOL *pjlovol);

void FireJlo(JLO *pjlo);

void LandJlo(JLO *pjlo);

void JumpJlo(JLO *pjlo);

void HandleJloMessage(JLO *pjlo, MSGID msgid, void *pv);

void SetJloJlos(JLO *pjlo, JLOS jlos);

void ActivateJlo(JLO *pjlo);

void DeactivateJlo(JLO *pjlo);

void InitJloc(JLOC *pjloc);

void LoadJlocFromBrx(JLOC *pjloc, CBinaryInputStream *pbis);

void PostJlocLoad(JLOC *pjloc);

XFM *PxfmChooseJloc(JLOC *pjloc);

void InitJlovol(JLOVOL *pjlovol);

void BindJlovol(JLOVOL *pjlovol);

void HandleJlovolMessage(JLOVOL *pjlovol, MSGID msgid, void *pv);

#endif // JLO_H
