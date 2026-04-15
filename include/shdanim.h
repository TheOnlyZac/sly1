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

// Forward.

struct RPL;

/**
 * @brief Position and orientation/direction ?
 * @todo Implement the struct.
 */

struct POSAD
{
    float x, y, z; // position
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
    float dtLoopMin;         // 0x2C
    float dtLoopMax;         // 0x30
    float dtPauseMin;        // 0x34
    float dtPauseMax;        // 0x38
    float dframe;            // 0x3C
    float iframe;            // 0x40
    float dtPause;           // 0x44
    float dtPauseRemaining;  // 0x48
};

/**
 * @brief Ping-pong shader animation.
 */

struct PINGPONG : public SAA
{
    float dtLoopMin;         // 0x2C
    float dtLoopMax;         // 0x30
    float dtPauseMin;        // 0x34
    float dtPauseMax;        // 0x38
    float dframe;            // 0x3C
    float iframe;            // 0x40
    float dtPause;           // 0x44
    float dtPauseRemaining;  // 0x48
};

/**
 * @brief Suffle shader animation.
 */

struct SHUFFLE : public SAA
{
    float dtPauseMin; // 0x2C
    float dtPauseMax; // 0x30
    float dtPause;   // 0x34
};

/**
 * @brief Hologram shader animation.
 */

struct HOLOGRAM : public SAA
{
    float startAngle;        // 0x2C
    float angleStep;         // 0x30
    float angleStepPerFrame; // 0x34
};

/**
 * @brief UV Scrolling shader animation.
 */

struct SCROLLER : public SAA
{
    float duSpeed; // 0x2C
    float dvSpeed; // 0x30
    float du;      // 0x34
    float dv;      // 0x38
    float su;      // 0x3C (Scale U)
    float sv;      // 0x40 (Scale V)
};

/**
 * @brief Circular shader animation.
 */

struct CIRCLER : public SAA
{
    float radsSpeed; // 0x2C
    float radius;    // 0x30
    float duCenter;  // 0x34
    float dvCenter;  // 0x38
};

/**
 * @brief Looker shader animation.
 */
 
struct LOOKER : public SAA
{
    float uCenter;     // 0x2C (from psaaf->dtLoopMin)
    float vCenter;     // 0x30 (from psaaf->dtLoopMax)
    float duMin;       // 0x34 (dtPauseMin - dtLoopMin)
    float duMax;       // 0x38 (dframe - dtLoopMin)
    float dvMin;       // 0x3C (dtPauseMax - dtLoopMax)
    float dvMax;       // 0x40 (dframe_0x18 - dtLoopMax)
    // 0x44 - 0x4C (Likely runtime state like current look target)
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
