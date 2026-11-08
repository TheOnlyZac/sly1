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
 * @brief Action.
 * @todo Implement the struct.
 */
struct ACT
{
    /* 0x00 */ VTACT *pvtact;
    /* 0x04 */ ALO *palo;
    /* 0x08 */ DLE dleAlo;
    /* 0x10 */ char ack0; // Four per-aspect values, initialized to -1. Purpose unknown.
    /* 0x11 */ char ack1;
    /* 0x12 */ char ack2;
    /* 0x13 */ char ack3;
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
    /* 0x88 */ STRUCT_PADDING(2);
    /* 0x90 */ MATRIX3 matScale;
    /* 0xc0 */ STRUCT_PADDING(1);
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
    /* 0x34 */ MATRIX3 *pmatScale;
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

/**
 * @brief Gets the scale of an action. The base action has no scale, so this is the identity matrix.
 *
 * @param pact The action.
 * @param pmat Receives the scale matrix.
 */
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

/**
 * @brief Adapts an action. Resets the first two ack values from 7 to 3.
 *
 * @param pact The action to adapt.
 * @note The meaning of the ack values is unknown.
 */
void AdaptAct(ACT *pact);

void InitActval(ACTVAL *pactval, ALO *palo);

void GetActvalPositionGoal(ACTVAL *pactval, float dtOffset, VECTOR *ppos, VECTOR *pv);

void GetActvalRotationGoal(ACTVAL *pactval, float dtOffset, MATRIX3 *pmat, VECTOR *pw);

void GetActvalTwistGoal(ACTVAL *pactval, float *pradTwist, float *pdradTwist);

/**
 * @brief Gets the scale of a value action.
 *
 * @param pactval The action.
 * @param pmat Receives the scale matrix.
 */
void GetActvalScale(ACTVAL *pactval, MATRIX3 *pmat);

float GGetActvalPoseGoal(ACTVAL *pactval, int ipose);

void InitActref(ACTREF *pactref, ALO *palo);

void GetActrefPositionGoal(ACTREF *pactref, float dtOffset, VECTOR *ppos, VECTOR *pv);

void GetActrefRotationGoal(ACTREF *pactref, float dtOffset, MATRIX3 *pmat, VECTOR *pw);

void GetActrefTwistGoal(ACTREF *pactref, float *pradTwist, float *pdradTwist);

/**
 * @brief Gets the scale of a reference action.
 *
 * @param pactref The action.
 * @param pmat Receives the scale matrix, copied from the referenced matrix.
 */
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
