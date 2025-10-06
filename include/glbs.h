/**
 * @file glbs.h
 */
#ifndef GLBS_H
#define GLBS_H

#include "common.h"
#include <cm.h>
#include <mat.h>
#include <vec.h>
#include <shd.h>
#include <light.h>

// Forward.
struct UV;

/**
 * @brief (?) kind.
 */
enum TRLK
{
    TRLK_Nil = -1,
    TRLK_Download = 0,
    TRLK_DownloadRelight = 1,
    TRLK_Relight = 2,
    TRLK_RelightCache = 3,
    TRLK_Quick = 4,
    TRLK_Max = 5
};

/**
 * @brief Unknown.
 */
typedef struct RGL
{
    /* 0x00 */ MATRIX4 matObjectToWorld;
    /* 0x40 */ MATRIX4 matWorldToObject;
    FGFN fgfn;
    float uAlpha;
    /* 0x94 */ TRLK trlk;
    int fCull;
    /* 0x9c */ TWPS twps;
    QW qwPosCenter;
} RGLD;

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct VTXG
{
    STRUCT_PADDING(10);
};

/**
 * @brief Unknown.
 */
struct GLBS
{
    /* 0x00  */ RGLD m_rgld;
    /* 0xb0  */ int m_cplightStatic;
    /* 0xb4  */ int m_cplightAll;
    LIGHT *m_aplight[16];
    /* 0xf8  */ SHD *m_pshd;
    VTXG m_vtxg;
    /* 0x124 */ int m_cvtxg;
    /* 0x128 */ VTXG m_avtxg[148];

    /**
     * @brief Constructor.
     */
    GLBS();

    /**
     * @brief Destructor.
     */
    ~GLBS();

    void SetTransform(VECTOR *ppos, MATRIX3 *pmat);

    void FindLights(VECTOR *ppos, float sRadius);

    void ResetStrip();

    void BeginStrip(SHD *pshd);

    void DrawPrelit();

    void DrawThreeWay();

    void EndStrip();

    void SetNormal(VECTOR *ppos); // Might be SetPos?

    void SetRgba(RGBA &rgba); // Might not be correct.

    void SetUv(UV *puv);

    void SetVtx(int fAdc);
};

#endif // GLBS_H
