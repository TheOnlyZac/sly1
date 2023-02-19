#include <game.h>
#include <joy.h>
#include <mat.h>
#include <vec.h>
typedef unsigned char byte;
typedef int GRFPVA;

// todo: rewrite struct
struct SPEAKER
{
    char padding[0x2e0];
    //struct RGBA_199 rgbaText;
    float radFOV;
    float sDistCm;
    float uxTv;
    float uyTv;
    byte field_0x2f4;
    byte field_0x2f5;
    byte field_0x2f6;
    byte field_0x2f7;
    byte field_0x2f8;
    byte field_0x2f9;
    byte field_0x2fa;
    byte field_0x2fb;
    byte field_0x2fc;
    byte field_0x2fd;
    byte field_0x2fe;
    byte field_0x2ff;
    struct VECTOR dposLight;
    struct VECTOR dposLightConfront;
    float uxTvConfront;
    float uyTvConfront;
    OID oidSmIdle;
    byte field_0x329;
    byte field_0x32a;
    byte field_0x32b;
    struct SM_conflict* psmIdle;
    struct SMA* psmaIdle;
};

struct DP
{
    GRFDP grfdp;
    byte field_0x1;
    byte field_0x2;
    byte field_0x3;
    DPK dpk;
    SPEAKER* pspeakerLeft;
    byte field_0x9;
    byte field_0xa;
    byte field_0xb;
    SPEAKER* pspeakerRight;
    struct ASEGA* pasegaLipsync;
    float tPauseMin;
};