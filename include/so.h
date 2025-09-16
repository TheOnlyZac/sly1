/**
 * @file so.h
 *
 * @brief Scene objects.
*/
#ifndef SO_H
#define SO_H

#include "common.h"
#include <geom.h>
#include <util.h>
#include <mark.h>
#include <alo.h>
#include <mat.h>
#include <vec.h>
#include <sw.h>
#include <sm.h>
#include <cm.h>

// Forward.
class CBinaryInputStream;
struct XA;
struct XP;
struct RO;
struct WKR;
struct ZPR;
struct WATER;
struct CNSTR;
struct CONSTR;

typedef int GRFFSO;

/**
 * @brief Unknown.
 * @todo Does this belong here?
 */
enum EGK
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Does this belong here?
 */
enum CT
{
    CT_Free = 0,
    CT_Tangent = 1,
    CT_Project = 2,
    CT_Locked = 3
};

enum FSO
{
    FSO_FindChild = 0x1,
    FSO_FindImmediateChild = 0x2,
    FSO_FindParent = 0x3,
    FSO_FindNearest = 0x4,
    FSO_FindAll = 0x5,
    GRFFSO_FindMask = 0xFF,
    FSO_IncludeRemovedObjects = 0x100,
    FSO_ReturnActualCount = 0x200
};

/**
 * @class OBJECT
 * @brief Unknown, related to level objects.
 *
 * @todo Implement struct.
 */
struct SO : public ALO
{
    // ...
};

/**
 * @brief Initialize the given SO.
 *
 * @param pso Pointer to the SO.
 *
 * @todo Verify this is actually that function.
 */
void InitSo(SO *pso);

/**
 * @brief Event handler for SO added to world(?)
 *
 * @param pso Pointer to the SO.
 */
void OnSoAdd(SO *pso);

/**
 * @brief Event handler for SO removed from world(?)
 *
 * @param pso Pointer to the SO.
 */
void OnSoRemove(SO *pso);

void EnableSoPhys(SO *pso, int fPhys);

void DisplaceSo(SO *pso, int fParentDirty);

void ImpactSo(SO *pso, int fParentDirty);

void PivotSo(SO *pso, int fParentDirty);

void ExtendSoBounds(SO *pso, VECTOR *ppos, float sRadius);

void UpdateSoBounds(SO *pso);

void UpdateGeomWorld(GEOM *pgeomLocal, GEOM *pgeomWorld, VU_VECTOR pos, MATRIX3 *pmat);

void UpdateSoXfWorldHierarchy(SO *pso);

void UpdateSoXfWorld(SO *pso);

int FIgnoreSoIntersection(SO *pso, SO *psoOther);

void UpdateSoImpacts(SO *pso);

float UProjectVector(VECTOR *ppos0, VECTOR *ppos1, VECTOR *ppos);

void AdjustSoXpLocal(SO *pso, XP *pxp, int ixpd);

void CalculateSoAngularEffectWorld(SO *pso, VECTOR *ptau, VECTOR *pdw);

void AccelSoTowardPosSpring(SO *pso, VECTOR *pposTarget, CLQ *pclqPos, VECTOR *pvTarget, CLQ *pclqV, float dt);

void AccelSoTowardMatSpring(SO *pso, MATRIX3 *pmatTarget, CLQ *pclqRot, VECTOR *pwTarget, CLQ *pclqW, float dt);

/**
 * @brief TODO.
 */
void PresetSoAccel(SO *pso, float dt);

void DrawGeom(GEOM *pgeom, CM *pcm, RGBA *rgba);

void RenderSoSelf(SO *pso, CM *pcm, RO *pro);

void UpdateSo(SO *pso, float dt);

void SetSoMass(SO *pso, float m);

void AdjustSoMomint(SO *pso, float r);

void DiscardSoXps(SO *pso);

void UpdateSoPosWorldPrev(SO *pso);

void TranslateSoToPos(SO *pso, VECTOR *ppos);

void RotateSoToMat(SO *pso, MATRIX3 *pmat);

void TranslateSoToPosSafe(SO *pso, VECTOR *ppos, VECTOR *pdpos);

void SetSoVelocityVec(SO *pso, VECTOR *pv);

void SetSoAngularVelocityVec(SO *pso, VECTOR *pw);

void AddSoAcceleration(SO *pso, VECTOR *pdv);

void AddSoAngularAcceleration(SO *pso, VECTOR *pdw);

void SetSoConstraints(SO *pso, CT ctForce, VECTOR *pnormalForce, CT ctTorque, VECTOR *pnormalTorque);

void SetSoParent(SO *pso, ALO *paloParent);

void ApplySoProxy(SO *pso, PROXY *pproxyApply);

/**
 * @brief TODO.
 */
void AccelSoTowardMatSmooth(SO *pso, float dt, MATRIX3 *pmat, SMP *psmp);

void GetSoCpdefi(SO *pso, float dt, CPDEFI *pcpdefi);

int FIsSoTouching(SO *pso, SO *psoTarget);

SO *PsoFirstSoTouching(SO *pso);

/**
 * @brief Clones an SO.
 */
void CloneSo(SO *pso, SO *psoBase);

void ApplySoConstraintWorld(SO *pso, CONSTR *pconstr, VECTOR *pvecWorld, VECTOR *pvecConstr, VECTOR *pvecRemain);

void ApplyConstr(CONSTR *pconstr, VECTOR *pvec, VECTOR *pvecConstr, VECTOR *pvecRemain);

void ApplySoConstraintLocal(SO *pso, CONSTR *pconstr, VECTOR *pvecLocal, VECTOR *pvecConstr, VECTOR *pvecRemain);

void AddSoXa(SO *pso, XA *pxaAdd);

void RemoveSoXa(SO *pso, XA *pxaRemove);

void AddSoWaterAcceleration(SO *pso, WATER *pwater, float dt);

void AddSoExternalAccelerations(SO *pso, XA *pxa, float dt);

/**
 * @brief Load SO from BRX.
 *
 * @param pso Pointer to the SO.
 * @param pbis Pointer to the binary input stream.
 */
void LoadSoFromBrx(SO *pso, CBinaryInputStream *pbis);

void SetSoSphere(SO *pso, float sRadius);

void SetSoNoInteract(SO *pso, int fNoInteract);

void ConstrFromCnstr(CNSTR cnstr, CT *pct, VECTOR *pnormal);

void SetSoCnstrForce(SO *pso, CNSTR cnstr);

void SetSoCnstrTorque(SO *pso, CNSTR cnstr);

void SetSoCameraStyle(SO *pso, CMK cmk);

void SetSoIgnoreLocked(SO *pso, int fIgnoreLocked);

void SetSoIceable(SO *pso, int fIceable);

void SetSoMtlk(SO *pso, MTLK mtlk);

void SetSoEdgeGrab(SO *pso, EGK egk);

void SendSoMessage(SO *pso, MSGID msgid, void *pv);

XP *PxpFindSoGround(SO *psoRoot, SO *psoLeaf, int *pixpd);

void SetSoNoGravity(SO *pso, int fNoGravity);

void SetSoNoXpsAll(SO *pso, int fNoXps);

void SetSoNoXpsSelf(SO *pso, int fNoXps);

void SetSoNoXpsCenter(SO *pso, int fNoXps);

void RebuildSoPhysHook(SO *pso);

SO *PsoFindSoPhysHook(SO *psoLeaf, int ib);

void RecalcSoLocked(SO *pso);

int FGetSoContactList(SO *pso, void *pvstate);

void GetSoContacts(SO *pso, int *pcpso, SO ***papso);

int FSoInStsoList(STSO *pstsoFirst, SO *pso);

void GenerateSoSpliceTouchingEvents(SO *pso);

int FInflictSoZap(SO *pso, XP *pxp, ZPR *pzpr);

void EnsureSoLvo(SO *pso);

void ProjectSoLvo(SO *pso, float dt);

void ProjectSoTransform(SO *pso, float dt, int fForce);

void ApplySoImpulse(SO *pso, VECTOR *ppos, VECTOR *pv, float sftMax);

void CalculateSoTrajectoryApex(SO *pso, VECTOR *pposTarget, float dzMax, VECTOR *pv);

int FAbsorbSoWkr(SO *pso, WKR *pwkr);

void CloneSoPhys(SO *pso, SO *psoPhys, int cposExtra);

#endif // SO_H
