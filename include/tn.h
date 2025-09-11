/**
 * @brief tn.h
 */
#ifndef TN_H
#define TN_H

#include "common.h"
#include <alo.h>
#include <bsp.h>
#include <vec.h>
#include <cm.h>
#include <mq.h>

// Forward.
struct RO;

/**
 * @brief Tunnel state?
 */
enum TNS
{
    TNS_Nil = -1,
    TNS_Out = 0,
    TNS_In = 1,
    TNS_Max = 2
};

/**
 * @class NEW_TUNNEL
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct TN : public ALO
{
    // ...
};

/**
 * @brief Tunnel something (?)
 * @todo Implement the struct.
 */
struct TNFN
{
    // ...
};

TNFN *PtnfnFromTn(TN *ptn);

void GetTnfnNose(TNFN *ptnfn, CPDEFI *pcpdefi, VECTOR *pposNose, TN *ptnAdjust);

void InitTn(TN *ptn);

void OnTnRemove(TN *ptn);

void LoadTnFromBrx(TN *ptn, CBinaryInputStream *pbis);

void PostTnLoad(TN *ptn);

void SetTnTns(TN *ptn, TNS tns);

void UpdateTnCallback(TN *ptn, MSGID msgid, void *pv);

void UpdateTn(TN *ptn, float dt);

void RenderTnSelf(TN *ptn, CM *pcm, RO *pro);

void FreezeTn(TN *ptn, int fFreeze);

void SetTnFocusRatio(TN *ptn, float u);

void CalculateTnCrv(TN *ptn, VECTOR *ppos, VECTOR *pdposCrv, VECTOR *pvecClosest);

void CalculateTnPos(TN *ptn, VECTOR *pdposCrv, float sBase, float dsOffset, CLQ *aclq, LM *alm, FTND ftnd, VECTOR *pposOther);

void ActivateCptn(CPTN *pcptn, void *pv);

void DeactivateCptn(CPTN *pcptn, void *pv);

void SetCptn(CPTN *pcptn, void *pv);

void RevokeCptn(CPTN *pcptn, void *pv);

void UpdateCptn(CPTN *pcptn, CPDEFI *pcpdefi, JOY *pjoy, float dt);

void LoadTbspFromBrx(CBinaryInputStream *pbis, int *pctsurf, TSURF **patsurf, int *pctbsp, TBSP **patbsp);

int FCheckTbspPoint(TBSP *atbsp, VECTOR *pposLocal);

#endif TN_H
