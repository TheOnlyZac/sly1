/**
 * @file shd.h
 *
 * @brief Shaders.
 */
#ifndef SHD_H
#define SHD_H

#include "common.h"
#include <sdk/ee/eestruct.h>
#include <bis.h>
#include <oid.h>
#include <geom.h>
#include <dmas.h>
#include <gifs.h>

typedef struct SHD; // Forward declaration
typedef struct SHDP; // Forward declaration

typedef int GRFZON;

/**
 * @brief (?) kind.
 */
enum CTK
{
    CTK_Nil = -1,
    CTK_Original = 0,
    CTK_Pass0 = 0,
    CTK_Ambient = 0,
    CTK_Pass1 = 1,
    CTK_Diffuse = 1,
    CTK_Saturation = 2,
    CTK_Pass2 = 2,
    CTK_Max = 3,
};

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
    ushort crgba;
    ushort cgsColors;
    RGBA *prgba;
};

struct CLUT : public CLUTF
{
    int cqwColors;
    sceGsTex2 tex2;
};

/**
 * @brief Texture Coordinates.
 */

struct TCX
{
    float du;
    float dv;
};

/**
 * @brief Texture File.
 */

struct TEXF
{
    ushort OID;
    short grdtex;
    uchar cibmp;
    uchar ciclut;
};

/**
 * @brief Texture.
 */

struct TEX : public TEXF
{
    ushort unk_0;
    SHD *pshd;
    BMP **apbmp;
    CLUT **apclut;
};

// MARK: SAIR

/**
 * @brief Shader Animation Instance Register.
 */

struct SAIR
{
    SHDP *pshdp;
    SUR *psur;
    SAIR *psairNext;
};

/**
 * @brief Shader Animation Instance.
 */

struct SAI
{
    int grfsai; // 0x10
    SHD *pshd; // 0x14
    int iframe; // 0x18
    TCX txt; // 0x1c
    SAIR *psairFirst; // 0x2c
    SAI *psaiNext; // 0x30
};


// MARK: SAA

/**
 * @brief Shader Animation Animator Kind.
 */

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

/**
 * @brief Shader Animation Animator.
 */

struct SAA
{
    VTSAA* pvtsaa; //0x00
    float tUpdates; //0x04
    SAAK saak; //0x08
    OID oid; //0x0c
    SAI sai; //0x10
};

/**
 * @brief Shader Animation Animator File. 
 */
struct SAAF
{
    short oid;          // 0x00
    ushort grfsaaf;     // 0x02
    float dtLoopMin;    // 0x04
    float dtLoopMax;    // 0x08
    float dtPauseMin;   // 0x0C
    float dtPauseMax;   // 0x10

    union {
        ushort dframe;   // 0x14 (Used by LOOP / PINGPONG)
        float dtLookMin; // 0x14 (Used by LOOKER)
    };
    
    float dtLookMax;     // 0x18 (Used by LOOKER)
};

/**
 * @brief Shader kind.
 */

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

/**
 * @brief Shader Data Packet.
 */

struct SHDP
{
    int cqwRegs;
    QW *aaqwRegs;
};

/**
 * @brief Shader Data.
 */

struct SHDF
{
    /* 0x00 */ uchar shdk;
    /* 0x01 */ uchar grfshd;
    /* 0x02 */ short oid;
    RGBA rgba;
    RGBA rgbaVolume;
    uint grfzon;
    ushort OidAltSat;
    uchar rp;
    uchar ctex;
};

/**
 * @brief Shader.
 */

struct SHD : public SHDF
{
    TEX *atex; 
    int cshdp; 
    SHDP *ashdp; 
    int cframe; 
    SAA *psaa; 
};

/**
 * @brief Unknown.
 * @todo Does this belong here?
 */
struct SLI
{

};

sceGsTex0 Tex0FromTexIframeCtk(TEX *ptex, int iframe, CTK ctk);

void PackTexGifs(TEX *ptex, int iframe, CTK ctk, SHDK shdk, GIFS *pgifs);

void LoadClutFromBrx(CBinaryInputStream *pbis, CLUT *pclut);

void LoadColorTablesFromBrx(CBinaryInputStream *pbis);

void LoadBmpFromBrx(CBinaryInputStream *pbis, BMP *pbmp);

void LoadBitmapsFromBrx(CBinaryInputStream *pbis);

void LoadFontsFromBrx(CBinaryInputStream *pbis);

void LoadTexFromBrx(CBinaryInputStream *pbis, TEX *ptex);

void LoadShadersFromBrx(CBinaryInputStream *pbis);

void UploadPermShaders();

void PropagateShaders(GRFZON grfzonCamera);

void FillShaders(GRFZON grfzon);

void UnloadShaders();

void ConvertRgbToHsv(VECTOR *pvecRGB, VECTOR *pvecHSV);

void ConvertHsvToRgb(VECTOR *pvecHSV, VECTOR *pvecRGB);

void ConvertUserHsvToUserRgb(VECTOR *pvecHSV, VECTOR *pvecRGB);

void ConvertUserRgbToUserHsv(VECTOR *pvecRGB, VECTOR *pvecHSV);

SHD *PshdFindShader(OID oid);

void SetSaiIframe(SAI *psai, int iframe);

void SetSaiDuDv(SAI *psai, float du, float dv);

void PropagateSais();

void UpdateShaders(float dt);

#endif // SHD_H
