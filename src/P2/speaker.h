#pragma once
#include <game.h>
#include <joy.h>
#include <mat.h>
#include <vec.h>
#include <font.h>
#include <util.h>

typedef int GRFPVA;

/**
 * Speaker
 *
 * Either represents a speaker that emits sound in the game world, or a
 * physical speaker in the real world. More research is needed.
 *
 * todo: identify undefined fields
 */
struct SPEAKER
{
    char padding[0x2e0];
    struct RGBA rgbaText;
    float radFOV;
    float sDistCm;
    float uxTv;
    float uyTv;
    undefined4 field_0x2f4;
    undefined4 field_0x2f8;
    undefined4 field_0x2fc;
    struct VECTOR dposLight;
    struct VECTOR dposLightConfront;
    float uxTvConfront;
    float uyTvConfront;
    OID oidSmIdle;
    struct SM_conflict* psmIdle;
    struct SMA* psmaIdle;
};

/**
 * Dialog Player
 */
struct DP
{
    GRFDP grfdp;
    DPK dpk;
    SPEAKER* pspeakerLeft;
    byte field_0x9;
    byte field_0xa;
    byte field_0xb;
    SPEAKER* pspeakerRight;
    struct ASEGA* pasegaLipsync;
    float tPauseMin;
};
