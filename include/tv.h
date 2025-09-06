/**
 * @file tv.h
 */
#ifndef TV_H
#define TV_H

#include "common.h"
#include <speaker.h>
#include <screen.h>
#include <gifs.h>
#include <alo.h>

// Forward.
struct RPL;

/**
 * @brief TV State.
 */
enum TVS
{
    TVS_Nil = -1,
    TVS_Listen = 0,
    TVS_Talk = 1,
    TVS_Max = 2
};

/**
 * @brief TV (?) State.
 */
enum TVGS
{
    TVGS_Nil = -1,
    TVGS_Opening = 0,
    TVGS_Open = 1,
    TVGS_Closing = 2,
    TVGS_Closed = 3,
    TVGS_Max = 4
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct TV : public BLOT
{
    // ...
};

void InitTv(TV *ptv, BLOTK blotk);

void PostTvLoad(TV *ptv);

void GetTvItvbMinMax(TV *ptv, int *pitvbDrawMin, int *pitvbDrawMax);

void DrawTvArea(TV *ptv, GIFS *gifs, int z);

void DrawTvBands(TV *ptv, GIFS *gifs);

void DrawTvOutline(TV *ptv, GIFS *gifs);

void DrawTv(TV *ptv);

void SetTvTvs(TV *ptv, TVS tvs);

void AcceptTvSpeaker(TV *ptv);

void SetTvTvgs(TV *ptv, TVGS tvgs);

void SetTvBlots(TV *ptv, BLOTS blots);

void UpdateTv(TV *ptv);

void RenderTv(TV *ptv);

void PreTvContext(RPL *prpl);

void PostTvContext(RPL *prpl);

void SetTvSpeaker(TV *ptv, SPEAKER *pspeaker);

void SetTvReplace(TV *ptv, ALO *paloReplace);

void OnTvReset(TV *ptv);

#endif // TV_H
