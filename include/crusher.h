/**
 * @file crusher.h
 */
#ifndef CRUSHER_H
#define CRUSHER_H

#include "common.h"
#include <stepguard.h>
#include <vec.h>

// Forward.
struct WKR;

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct CRFOD : public STEPGUARD
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct CRFODB : public STEPGUARD
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct CRFODK : public CRFOD
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct CRBRAIN : public ALO
{
    // ...
};

void OnCrfodAdd(CRFOD *pcrfod);

void OnCrfodRemove(CRFOD *pcrfod);

void CloneCrfod(CRFOD *pcrfod, CRFOD *pcrfodBase);

void InitCrfodb(CRFODB *pcrfodb);

void CalcHeadingVector(float rad, VECTOR *pvector);

void UpdateCrfodbGoal(CRFODB *pcrfodb, int fEnter);

int FDetectCrfodb(CRFODB *pcrfodb);

int FAbsorbCrfodbWkr(CRFODB *pcrfodb, WKR *pwkr);

SGS SgsNextCrfodkAI(CRFODK *pcrfodk);

int FDetectCrfodk(CRFODK *pcrfodk);

int FAbsorbCrfodkWkr(CRFODK *pcrfodk, WKR *pwkr);

void InitCrbrain(CRBRAIN *pcrbrain);

// TODO: Add unknown functions here.

#endif // CRUSHER_H
