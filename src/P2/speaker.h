#include <game.h>
#include <joy.h>
#include <mat.h>
#include <vec.h>
#include <font.h>
#include <util.h>

typedef int GRFPVA;

// todo: rewrite struct
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
