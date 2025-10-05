/**
 * @file rog.h
 *
 * @note At the time of writing, all the enum values were taken
 * straight from the prototype, so they may be incorrect/incomplete.
 */
#ifndef ROG_H
#define ROG_H

#include "common.h"
#include <ensure.h>
#include <oid.h>
#include <joy.h>
#include <po.h>
#include <mq.h>

// Forward.
struct XP;
struct DZ;
struct FX;
struct WKR;

typedef int GRFSG;

/**
 * @brief (?) state.
 */
enum ROVS
{
    ROVS_Nil = -1,
    ROVS_Brake = 0,
    ROVS_Drive = 1,
    ROVS_Descend = 2,
    ROVS_Ascend = 3,
    ROVS_Max = 4
};

/**
 * @brief (?) state.
 */
enum ROBS
{
    ROBS_Nil = -1,
    ROBS_Descend = 0,
    ROBS_Instruct = 1,
    ROBS_Normal = 2,
    ROBS_Lose = 3,
    ROBS_Win = 4,
    ROBS_Ascend = 5,
    ROBS_Max = 6
};

/**
 * @brief (?) state.
 */
enum ROVTS
{
    ROVTS_Nil = -1,
    ROVTS_Calm = 0,
    ROVTS_Firing = 1,
    ROVTS_Max = 2
};

/**
 * @brief (?) state.
 */
enum ROHS
{
    ROHS_Nil = -1,
    ROHS_Inactive = 0,
    ROHS_Spawn = 1,
    ROHS_Wander = 2,
    ROHS_Collect = 3,
    ROHS_Grab = 4,
    ROHS_Return = 5,
    ROHS_Exit = 6,
    ROHS_Happy = 7,
    ROHS_Sad = 8,
    ROHS_Die = 9,
    ROHS_Dead = 10,
    ROHS_Max = 11
};

/**
 * @brief (?) state.
 */
enum ROCS
{
    ROCS_Nil = -1,
    ROCS_Rest = 0,
    ROCS_Hit1 = 1,
    ROCS_Hit2 = 2,
    ROCS_Hit3 = 3,
    ROCS_Hit4 = 4,
    ROCS_Hit5 = 5,
    ROCS_Hit6 = 6,
    ROCS_Hit7 = 7,
    ROCS_Hit8 = 8,
    ROCS_Destroyed = 9,
    ROCS_Max = 10
};

/**
 * @brief (?) state.
 */
enum ROPS
{
    ROPS_Nil = -1,
    ROPS_StayPut = 0,
    ROPS_Reveal = 1,
    ROPS_Collect = 2,
    ROPS_Collected = 3,
    ROPS_Max = 4
};

/**
 * @brief (?) state.
 */
enum ROSTS
{
    ROSTS_Nil = -1,
    ROSTS_Close = 0,
    ROSTS_Open = 1,
    ROSTS_Max = 2
};

/**
 * @brief (?) kind.
 */
enum ROBK
{
    ROBK_Nil = -1,
    ROBK_Primary = 0,
    ROBK_Secondary = 1,
    ROBK_Tertiary = 2,
    ROBK_Max = 3
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct ROV : public PO
{
    /* 0x610 */ ROVS rovs;
    /* 0x614 */ ROVTS rovts;
    /* 0x618 */ float radJoyLeft;
    /* 0x61c */ float uJoyDeflectLeft;
    /* 0x620 */ float radJoyRight;
    /* 0x624 */ float uJoyDeflectRight;
    /* 0x628 */ float svMax;
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct ROB : public ALO
{
    // ...
    /* 0x2e0 */ int coidRost;
    /* 0x2e4 */ OID aoidRost[16]; // TODO: Verify size.
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct ROH : public SO
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct ROC : public SO
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct ROST : public SO
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct ROP : public SO
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct RODD
{
    // ...
};

void InitRov(ROV *prov);

void LoadRovFromBrx(ROV *prov, CBinaryInputStream *pbis);

void PostRovLoad(ROV *prov);

void UpdateRovActive(ROV *prov, JOY *pjoy, float dt);

void UpdateRov(ROV *prov, float dt);

void ReadRovJoystick(ROV *prov, JOY *pjoy);

ROVS RovsNextRov(ROV *prov);

void SetRovRovs(ROV *prov, ROVS rovs);

ROVTS RovtsNextRov(ROV *prov);

void SetRovRovts(ROV *prov, ROVTS rovts);

void HandleRovMessage(ROV *prov, MSGID msgid, void *pv);

void PresetRovAccel(ROV *prov, float dt);

void AdjustRovXpVelocity(ROV *prov, XP *pxp, int ixpd);

void AdjustRovNewXp(ROV *prov, XP *pxp, int ixpd);

void PropagateRovForce(ROV *prov, GRFSG grfsg, XP *pxp, int ixpd, DZ *pdz, FX *afx);

int FIsRovSoundBase(ROV *prov);

void InitRob(ROB *prob);

void SetRobCollectible(ROB *prob, OID oidCollectible);

void SetRobHarvester(ROB *prob, OID oidHarvester);

void SetRobVehicle(ROB *prob, OID oidVehicle);

void SetRobPrize(ROB *prob, OID oidPrize);

void AddRobSpawnTunnel(ROB *prob, OID oidSpawnTunnel);

ROBK RobkCur();

void BindRob(ROB *prob);

void PostRobLoad(ROB *prob);

void UpdateRob(ROB *prob, float dt);

ROBS RobsNextRob(ROB *prob);

void SetRobRobs(ROB *prob, ROBS robs);

void AddRobRoc(ROB *prob);

void AddRobRoh(ROB *prob);

void AdjustRobDifficulty(ROB *prob, float rRoc);

void DestroyedRobRoc(ROB *prob, ROC *proc);

void SpawnedRobRoh(ROB *prob, ROH *proh);

void GrabbedRobRoh(ROB *prob, ROH *proh);

void DroppedRobRoh(ROB *prob, ROH *proh);

void ReturnedRobRoh(ROB *prob, ROH *proh);

void ExitedRobRoh(ROB *prob, ROH *proh);

void KilledRobRoh(ROB *prob, ROH *proh);

int FChooseRobRoc(ROB *prob, ROH *proh);

void TakeRobRoc(ROB *prob, ROH *proh, ROC *proc);

int FChooseRobRoh(ROB *prob, ROC *proc);

int FChooseRobReturnPoint(ROB *prob, ROH *proh);

void ChooseRobWanderLocation(ROB *prob, ROH *proh);

RODD *ProddCurRob(ROB *prob, ENSK ensk);

void InitRoh(ROH *proh);

void LoadRohFromBrx(ROH *proh, CBinaryInputStream *pbis);

void CloneRoh(ROH *proh, ROH *prohBase);

void PostRohLoad(ROH *proh);

void UpdateRoh(ROH *proh, float dt);

void MoveRohToTarget(ROH *proh, VECTOR *ppos, int fBackwards);

ROHS RohsNextRoh(ROH *proh);

void SetRohRohs(ROH *proh, ROHS rohs);

int FAbsorbRohWkr(ROH *proh, WKR *pwkr);

ROC *ProcContactRoh(ROH *proh);

void InitRoc(ROC *proc);

void LoadRocFromBrx(ROC *proc, CBinaryInputStream *pbis);

void CloneRoc(ROC *proc, ROC *procBase);

void PostRocLoad(ROC *proc);

void UpdateRoc(ROC *proc, float dt);

void PresetRocAccel(ROC *proc, float dt);

void AdjustRocNewXp(ROC *proc, XP *pxp, int ixpd);

int FAbsorbRocWkr(ROC *proc, WKR *pwkr);

ROCS RocsNextRoc(ROC *proc);

void SetRocRocs(ROC *proc, ROCS rocs);

void InitRost(ROST *prost);

void LoadRostFromBrx(ROST *prost, CBinaryInputStream *pbis);

void CloneRost(ROST *prost, ROST *prostBase);

void PostRostLoad(ROST *prost);

void UpdateRost(ROST *prost, float dt);

ROSTS RostsNextRost(ROST *prost);

void SetRostRosts(ROST *prost, ROSTS rosts);

void InitRop(ROP *prop);

void LoadRopFromBrx(ROP *prop, CBinaryInputStream *pbis);

void PostRopLoad(ROP *prop);

void UpdateRop(ROP *prop, float dt);

void SetRopRops(ROP *prop, ROPS rops);

ROPS RopsNextRop(ROP *prop);

#endif // ROG_H
