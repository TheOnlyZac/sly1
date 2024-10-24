/**
 * @file shd.h
 *
 * @brief Shaders.
 */
#ifndef SHD_H
#define SHD_H

#include "common.h"
#include <geom.h>
#include <surf.h>
#include <sce/gs.h>

typedef struct SHD; // Forward declaration
typedef struct SHDP; // Forward declaration

// MARK: BMP

struct BMPF
{
    short dx;
    short dy;
    uint grfzon;
    uchar psm;
    uchar cgsRow;
    short cgsPixels;
    uint cbPixels;
    uchar *pbPixels;
};

struct BMP : public BMPF
{
    int cqwPixels;
    sceGsTex0 tex0;
};

// MARK: CLUT

struct CLUTF
{
    uint grfzon;
    short crgba;
    short cgsColors;
    RGBA *prgba;
};

struct CLUT : public CLUTF
{
    int cqwColors;
    sceGsTex2 tex2;
};

// MARK: Texture?

struct TCX
{
    float du;
    float dv;
};

struct TEXF
{
    ushort OID;
    short grdtex;
    uchar cibmp;
    uchar ciclut;
};

struct TEX : public TEXF
{
    ushort unk_0;
    SHD *pshd;
    BMP **apbmp;
    CLUT **apclut;
};

// MARK: QW
//tood move to separate file

#include <vec.h>

union QW
{
    VECTOR vec;
    VECTOR4 vec4;
    uint16 ull;
    ulong aul[2];
    uint aun[4];
    short aus[8];
    uchar ab[16];
    int16 ll;
    long al[2];
    int an[4];
    ushort as[8];
    float ag[4];
};

// MARK: SAIR

struct SAIR
{
    SHDP *pshdp;
    SUR *psur;
    SAIR *psairNext;
};

// MARK: SAI

struct SAI
{
    int grfsai;
    SHD *pshd;
    int iframe;
    TCX txt;
    SAIR *psairFirst;
    SAI *psaiNext;
};


// MARK: SAA

enum SAAK
{
    SAAK_Nil = -1,
    SAAK_None = 0,
    SAAK_Loop = 1,
    SAAK_PingPong = 2,
    SAAK_Shuffle = 3,
    SAAK_Hologram = 4,
    SAAK_Eyes = 5,
    SAAK_Scroller = 6,
    SAAK_Circler = 7,
    SAAK_Looker = 8,
    SAAK_Max = 9
};

struct SAA
{
    undefined4 unk_0;
    float tUpdates;
    SAAK saak;
    OID oid;
    SAI sai;
};

// MARK: SHD

enum SHDK
{
    SHDK_Nil = -1,
    SHDK_ThreeWay = 0,
    SHDK_Prelit = 1,
    SHDK_Shadow = 2,
    SHDK_SpotLight = 3,
    SHDK_ProjectedVolume = 4,
    SHDK_CreateTexture = 5,
    SHDK_Background = 6,
    SHDK_Foreground = 7,
    SHDK_WorldMap = 8,
    SHDK_MurkClear = 9,
    SHDK_MurkFill = 10,
    SHDK_Max = 11
};

struct SHDP
{
    int cqwRegs;
    QW *aaqwRegs;
};

struct SHDF
{
    uchar shdk;
    uchar grfshd;
    ushort OID; // ?
    RGBA rgba;
    RGBA rgbaVolume;
    uint grfzon;
    ushort OidAltSat;
    uchar rp;
    uchar ctex;
};

struct SHD
{
    TEX *atex;
    int cshdp;
    SHDP *ashdp;
    int cframe;
    SAA *psaa;
};

#endif // SHD_H
