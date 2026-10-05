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
    float u, v, q;
};

/**
 * @brief UV coordinates (Homogeneous/Q-depth).
 */
typedef struct UVQ UVQD;

/**
 * @brief Loop shader animation.
 */
struct LOOP : public SAA
{
    /* 0x2c */ float dtLoopMin;
    /* 0x30 */ float dtLoopMax;
    /* 0x34 */ float dtPauseMin;
    /* 0x38 */ float dtPauseMax;
    /* 0x3c */ float sviframe;
    /* 0x40 */ float gframe;
    /* 0x44 */ float dtPauseRequested;
    /* 0x48 */ float dtPause;
};

/**
 * @brief Ping-pong shader animation.
 */
struct PINGPONG : public SAA
{
    /* 0x2c */ float dtPingpongMin;
    /* 0x30 */ float dtPingpongMax;
    /* 0x34 */ float dtPauseMin;
    /* 0x38 */ float dtPauseMax;
    /* 0x3c */ float sviframe;
    /* 0x40 */ float gframe;
    /* 0x44 */ float dtPauseRequested;
    /* 0x48 */ float dtPause;
};

/**
 * @brief Shuffle shader animation.
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
    /* 0x2c */ float dradAdjust;
    /* 0x30 */ float dradSymmetry;
    /* 0x34 */ float dradFrame;
};

/**
 * @brief UV Scrolling shader animation.
 */
struct SCROLLER : public SAA
{
    /* 0x2c */ float svu;
    /* 0x30 */ float svv;
    /* 0x34 */ float duMod;
    /* 0x38 */ float dvMod;
    /* 0x3c */ float svuMaster;
    /* 0x40 */ float svvMaster;
};

/**
 * @brief Circular shader animation.
 */
struct CIRCLER : public SAA
{
    /* 0x2c */ float sw;
    /* 0x30 */ float sRadius;
    /* 0x34 */ float du;
    /* 0x38 */ float dv;
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
    /* 0x3c */ float dvMin;
    /* 0x40 */ float dvMax;
    /* 0x44 */ int cvtx;
    /* 0x48 */ UVQD *puvqd;
    /* 0x4c */ POSAD *pposad;
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
void SetUvPuvqd(UVF *puv, UVQD *puvqd);
void NotifyLookerRender(LOOKER *plooker, ALO *palo, RPL *prpl);

#endif // SHDANIM_H
