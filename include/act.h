/**
 * @file act.h
 */
#ifndef ACT_H
#define ACT_H

#include "common.h"
#include <vec.h>
#include <mat.h>
#include <dl.h>

// Forward.
struct SW;
struct ALO;

typedef int GRFRA;

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct ACT
{
    /* 0x00 */ STRUCT_PADDING(1); // TODO: Add vtables
    /* 0x04 */ ALO *palo;
    /* 0x08 */ DLE dleAlo;
    /* 0x10 */ STRUCT_PADDING(1);
    /* 0x14 */ int nPriority;
    /* 0x18 */ float tMatch;
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct ACTVAL : public ACT
{
    /* 0x1c */ STRUCT_PADDING(25);
    /* 0x80 */ float radTwistGoal;
    /* 0x84 */ float dradTwistGoal;
    /* 0x88 */ STRUCT_PADDING(15);
    /* 0xc4 */ float *agPoses;
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct ACTREF : public ACT
{
    /* 0x1c */ STRUCT_PADDING(4);
    /* 0x2c */ float *pradTwistGoal;
    /* 0x30 */ float *pdradTwistGoal;
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct ACTADJ : public ACT
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct ACTBANK : public ACT
{
    /* 0x1c */ float uBank;
    /* 0x20 */ float dtPredict;
};

ACT *PactNew(SW *psw, ALO *palo, VTACT *pvtact);

ACT *PactNewClone(ACT *pactBase, SW *psw, ALO *palo);

void CloneAct(ACT *pact, ACT *pactBase);

void InitAct(ACT *pact, ALO *palo);

void RetractAct(ACT *pact, GRFRA grfra);

void GetActPositionGoal(ACT *pact, float dtOffset, VECTOR *ppos, VECTOR *pv);

void GetActRotationGoal(ACT *pact, float dtOffset, MATRIX3 *pmat, VECTOR *pw);

void GetActTwistGoal(ACT *pact, float *pradTwist, float *pdradTwist);

void GetActScale(ACT *pact, MATRIX3 *pmat);

float GGetActPoseGoal(ACT *pact, int ipose);

void CalculateActDefaultAck(ACT *pact);

void SnapAct(ACT *pact, int fForce);

void CalculateAloPositionSpring(ALO *palo, float dt, VECTOR *pposGoal, VECTOR *pvGoal, VECTOR *pdv);

void ProjectActPosition(ACT *pact);

void CalculateAloRotationSpring(ALO *palo, float dt, MATRIX3 *pmatGoal, VECTOR *pwGoal, VECTOR *pdw);

void ProjectActRotation(ACT *pact);

void ProjectActPose(ACT *pact, int ipose);

void PredictAloPosition(ALO *palo, float dtOffset, VECTOR *ppos, VECTOR *pv);

void PredictAloRotation(ALO *palo, float dtOffset, MATRIX3 *pmat, VECTOR *pw);

void AdaptAct(ACT *pact);

void InitActval(ACTVAL *pactval, ALO *palo);

void GetActvalPositionGoal(ACTVAL *pactval, float dtOffset, VECTOR *ppos, VECTOR *pv);

void GetActvalRotationGoal(ACTVAL *pactval, float dtOffset, MATRIX3 *pmat, VECTOR *pw);

void GetActvalTwistGoal(ACTVAL *pactval, float *pradTwist, float *pdradTwist);

void GetActvalScale(ACTVAL *pactval, MATRIX3 *pmat);

float GGetActvalPoseGoal(ACTVAL *pactval, int ipose);

void InitActref(ACTREF *pactref, ALO *palo);

void GetActrefPositionGoal(ACTREF *pactref, float dtOffset, VECTOR *ppos, VECTOR *pv);

void GetActrefRotationGoal(ACTREF *pactref, float dtOffset, MATRIX3 *pmat, VECTOR *pw);

void GetActrefTwistGoal(ACTREF *pactref, float *pradTwist, float *pdradTwist);

void GetActrefScale(ACTREF *pactref, MATRIX3 *pmat);

float GGetActrefPoseGoal(ACTREF *pactref, int ipose);

void InitActadj(ACTADJ *pactadj, ALO *palo);

void GetActadjPositionGoal(ACTADJ *pactadj, float dtOffset, VECTOR *ppos, VECTOR *pv);

void GetActadjRotationGoal(ACTADJ *pactadj, float dtOffset, MATRIX3 *pmat, VECTOR *pw);

void GetActadjTwistGoal(ACTADJ *pactadj, float *pradTwist, float *pdradTwist);

void GetActadjScale(ACTADJ *pactadj, MATRIX3 *pmat);

float GGetActadjPoseGoal(ACTADJ *pactadj, int ipose);

void InitActbank(ACTBANK *pactbank, ALO *palo);

void GetActbankRotationGoal(ACTBANK *pactbank, float dtOffset, MATRIX3 *pmat, VECTOR *pw);

#endif // ACT_H
