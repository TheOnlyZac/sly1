/**
 * @file wr.h
 * @note At the time of writing all structs were
 * based on the may prototype so they can be inaccurate.
 */
#ifndef WR_H
#define WR_H

#include "common.h"
#include <difficulty.h>
#include <glob.h>
#include <oid.h>
#include <mat.h>
#include <alo.h>
#include <lo.h>
#include <mq.h>

// Forward.
struct WR;

/**
 * @brief (?) Kind.
 */
enum WEK
{
    WEK_Nil = -1,
    WEK_XYZ = 0,
    WEK_XY = 1,
    WEK_XZ = 2,
    WEK_YZ = 3,
    WEK_X = 4,
    WEK_Y = 5,
    WEK_Z = 6,
    WEK_Max = 7
};

/**
 * @brief (?) Kind.
 */
enum WREK
{
    WREK_Nil = -1,
    WREK_Circle = 0,
    WREK_Bend = 1,
    WREK_Max = 2
};

/**
 * @brief Unknown.
 */
struct ONZE
{
    float uAmpl;
    float gFreq;
    float gPhase;
    float uRandom;
};

/**
 * @brief Unknown.
 */
struct ONZ
{
    LM lm;
    float uBias;
    int conze;
    ONZE aonze[4];
};

/**
 * @brief Unknown.
 */
struct WEKI
{
    WEK wek;
    float sInner;
    float uInner;
    float sOuter;
    float uOuter;
    undefined1 unknown[12];
    MATRIX4 dmat;
};

/**
 * @brief Unknown.
 */
struct WRE
{
    WREK wrek;
    int imat;
};

/**
 * @brief Unknown.
 */
struct WRBG
{
    ALO *palo;
    GLOB *pglob;
    OID oid;
    WR *pwr;
    int cmat;
    int fDpos;
    int fDuv;
    undefined1 unknown[4];
    WEKI weki;
    WRBG *pwrbgNextGlobset;
    WRBG *pwrbgNextWr;
};

/**
 * @brief Unknown.
 */
struct WR : public LO
{
    float tLastUpdate;
    int cwre;
    int cmat;
    int imatHalf;
    WRE awre[8];
    int iwreCur;
    undefined1 unknown[12];
	MATRIX4 amatDpos[4];
    MATRIX4 amotDuv[4];
    WRBG *pwrbgFirst;
    int fValuesChanged;
};

void InitWr(WR *pwr);

void HandleWrMessage(WR *pwr, MSGID msgid, void *pv);

void ApplyWrGlob(WR *pwr, ALO *palo, GLOB *pglob);

void UpdateWrStateVectors(WR *pwr);

void WarpWrTransform(WR *pwr, float sWavelengthMin, VECTOR *pposSrc, MATRIX3 *pmatSrc, VECTOR *pposDst, MATRIX3 *pmatDst, VECTOR *pvDst);

void GetWrBounds(WR *pwr, VECTOR * pdpos);

float UNoise(int n);

float UNoise(float gFreq, float gPhase, float uRandom);

float UBias(float u, float uBias);

float GFromOnz(ONZ *ponz);

void UpdateWrMatrixes(WR *pwr);

void AddWrCircleWarp(WR *pwr);

void AddWrBendWarp(WR *pwr);

WRE *PwreGetWrCur(WR *pwr, ENSK ensk, WREK wrek);

WRE *PwreGetWrCircle(WR *pwr, ENSK ensk);

WRE *PwreGetWrBend(WR *pwr, ENSK ensk);

void SetWrWavelength(WR *pwr, float sWavelength);

void GetWrWavelength(WR *pwr, float *psWavelength);

void AddOnzOnze(ONZ *ponz, float uAmpl, float gFreq, float gPhase, float uRandom);

void AddWrBendNoise(WR *pwr, float uAmpl, float gFreq, float gPhase, float uRandom);

void AddWrSwivelNoise(WR *pwr, float uAmpl, float gFreq, float gPhase, float uRandom);

#endif // WR_H
