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
struct UV;
struct UVQD;
struct POSAD;
struct RPL;

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct LOOP : public SAA
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct PINGPONG : public SAA
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct SHUFFLE : public SAA
{
    float dtPauseMin;
    float dtPauseMax;
    float dtPause;
};

/**
 * @brief Level transition hologram?
 * @todo Implement the struct.
 */
struct HOLOGRAM : public SAA
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct SCROLLER : public SAA
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct CIRCLER : public SAA
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct LOOKER : public SAA
{
    // ...
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
void SetUvPuvqd(UV *puv, UVQD *puvqd);
void NotifyLookerRender(LOOKER *plooker, ALO *palo, RPL *prpl);

#endif // SHDANIM_H
