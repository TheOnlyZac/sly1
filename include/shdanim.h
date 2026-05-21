/**
 * @file shdanim.h
 *
 * @brief Shader animations.
 */
#ifndef SHDANIM_H
#define SHDANIM_H

#include "common.h"
#include <glob.h>
#include <shd.h>

// Forward declaration.
struct RPL;

/**
 * @brief Position and orientation/direction ?
 * @todo Implement the struct.
 */
struct POSAD
{
    float x, y, z;
};

/**
 * @brief UV coordinates (Float).
 */
struct UVF
{
    float u, v;
};

/**
 * @brief UV coordinates (Homogeneous/Q-depth).
 */
struct UVQ
{
    float u, v, q, d;
};

/**
 * @brief Loop shader animation.
 */
struct LOOP : public SAA
{
    /* 0x2c */ float dtLoopMin;
    /* 0x30 */ float dtLoopMax;
    /* 0x34 */ float dtPauseMin;
    /* 0x38 */ float dtPauseMax;
    /* 0x3c */ float dframe;
    /* 0x40 */ float iframe;
    /* 0x44 */ float dtPause;
    /* 0x48 */ float dtPauseRemaining;
};

/**
 * @brief Ping-pong shader animation.
 */
struct PINGPONG : public SAA
{
    /* 0x2c */ float dtLoopMin;
    /* 0x30 */ float dtLoopMax;
    /* 0x34 */ float dtPauseMin;
    /* 0x38 */ float dtPauseMax;
    /* 0x3c */ float dframe;
    /* 0x40 */ float iframe;
    /* 0x44 */ float dtPause;
    /* 0x48 */ float dtPauseRemaining;
};

/**
 * @brief Suffle shader animation.
 */
struct SHUFFLE : public SAA
{
    /* 0x2c */ float dtPauseMin;
    /* 0x30 */ float dtPauseMax;
    /* 0x34 */ float dtPause;
};

/**
 * @brief Hologram shader animation.
 */
struct HOLOGRAM : public SAA
{
    /* 0x2c */ float startAngle;
    /* 0x30 */ float angleStep;
    /* 0x34 */ float angleStepPerFrame;
};

/**
 * @brief UV Scrolling shader animation.
 */
struct SCROLLER : public SAA
{
    /* 0x2c */ float duSpeed;
    /* 0x30 */ float dvSpeed;
    /* 0x34 */ float du;
    /* 0x38 */ float dv;
    /* 0x3c */ float su;
    /* 0x40 */ float sv;
};

/**
 * @brief Circular shader animation.
 */
struct CIRCLER : public SAA
{
    /* 0x2c */ float radsSpeed;
    /* 0x30 */ float radius;
    /* 0x34 */ float duCenter;
    /* 0x38 */ float dvCenter;
};

/**
 * @brief Looker shader animation.
 */
struct LOOKER : public SAA
{
    /* 0x2c */ float uCenter;
    /* 0x30 */ float vCenter;
    /* 0x34 */ float duMin;
    /* 0x38 */ float duMax;
    /* 0x3C */ float dvMin;
    /* 0x40 */ float dvMax;
    // 0x44 - 0x4c (Likely runtime state like current look target)
};

int CbFromSaak(SAAK saak);
VTSAA *PvtsaaFromSaak(SAAK saak);
SAA *PsaaLoadFromBrx(CBinaryInputStream *pbis);
void InitSaa(SAA *psaa, SAAF *psaaf);
void PostSaaLoad(SAA *psaa);
int FUpdatableSaa(SAA *psaa);
float UCompleteSaa(SAA *psaa);
SAI *PsaiFromSaaShd(SAA *psaa, SHD *pshd);
void InitLoop(LOOP *ploop, SAAF *psaaf);
void PostLoopLoad(LOOP *ploop);
void UpdateLoop(LOOP *ploop, float dt);
float UCompleteLoop(LOOP *ploop);
void InitPingpong(PINGPONG *ppingpong, SAAF *psaaf);
void PostPingpongLoad(PINGPONG *ppingpong);
void UpdatePingpong(PINGPONG *ppingpong, float dt);
float UCompletePingpong(PINGPONG *ppingpong);
void InitShuffle(SHUFFLE *pshuffle, SAAF *psaaf);
void UpdateShuffle(SHUFFLE *pshuffle, float dt);
void InitHologram(HOLOGRAM *phologram, SAAF *psaaf);
void PostHologramLoad(HOLOGRAM *phologram);
void NotifyHologramRender(HOLOGRAM *phologram, ALO *palo, RPL *prpl);
void InitScroller(SCROLLER *pscroller, SAAF *psaaf);
void UpdateScroller(SCROLLER *pscroller, float dt);
float UCompleteScroller(SCROLLER *pscroller);
void SetScrollerMasterSpeeds(SCROLLER *pscroller, float svu, float svv);
void InitCircler(CIRCLER *pcircler, SAAF *psaaf);
void UpdateCircler(CIRCLER *pcircler, float dt);
float UCompleteCircler(CIRCLER *pcircler);
void InitLooker(LOOKER *plooker, SAAF *psaaf);
void SetLookerSgvr(LOOKER *plooker, SGVR *psgvr, GLOBSET *pglobset, GLOB *pglob, SUBGLOB *psubglob);
void SetVecPosad(VECTOR *pvec, POSAD *pposad);
void SetUvPuvqd(UVF *puv, UVQ *puvqd);
void NotifyLookerRender(LOOKER *plooker, ALO *palo, RPL *prpl);

#endif // SHDANIM_H
