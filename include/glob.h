/**
 * @file glob.h
 */
#ifndef GLOB_H
#define GLOB_H

#include <bis.h>
#include <vec.h>

// Forward declarations.
struct ALO;
struct RO;
struct BND;
struct WRBG;
struct VIFS;
struct POSAD;
struct UVQ;
typedef struct UVQ UVQD;

typedef int GRFGLOB;
typedef int GRFGLOBSET;

/**
 * @todo Implement struct.
 */
struct GLOB
{
    // ...
};

/**
 * @todo Implement struct.
 */
struct GLOBI
{
    // ...
};

/**
 * @todo Implement struct.
 */
struct SUBGLOB
{
    // ...
};

/**
 * @todo Implement struct.
 */
struct SUBGLOBI
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Verify fields.
 */
struct LTFN
{
    /* 0x00 */ float ruShadow;
    /* 0x04 */ float ruMidtone;
    /* 0x08 */ float ruHighlight;
    /* 0x0c */ float ruUnused;
    /* 0x10 */ float duShadow;
    /* 0x14 */ float duMidtone;
    /* 0x18 */ float duHighlight;
    /* 0x1c */ float duUnused;
};

/**
 * @brief Unknown.
 * @todo Verify fields.
 */
struct GLOBSET
{
    /* 0x00 */ int cbnd;
    /* 0x04 */ BND *abnd;
    /* 0x08 */ OID *mpibndoid;
    /* 0x0c */ int cglob;
    /* 0x10 */ GLOB *aglob;
    /* 0x14 */ GLOBI *aglobi;
    /* 0x18 */ LTFN ltfn;
    /* 0x38 */ GRFGLOBSET grfglobset;
    /* 0x3c */ RGBA rgbaCel;
    /* 0x40 */ int cpose;
    /* 0x44 */ float *agPoses;
    /* 0x48 */ float *agPosesOrig;
    /* 0x4c */ WRBG *pwrbgFirst;
    /* 0x50 */ int cpsaa;
    /* 0x54 */ SAA **apsaa;
};

/**
 * @todo Implement the struct and figure out does it belong here.
 */
struct SGVR
{
    /* 0x00 */ int *pcvtx;
    /* 0x04 */ POSAD **ppposad;
    /* 0x08 */ UVQD **ppuvqd;
};

void BuildGlobsetSaaArray(GLOBSET *pglobset);

void LoadGlobsetFromBrx(GLOBSET *pglobset, CBinaryInputStream *pbis, ALO *palo);

void EnsureBuffer(int iBuffer, VIFS *pvifs);

void EnsureBufferCel(int iBuffer, VIFS *pvifs);

/*
void BuildSubcel(GLOBSET *pglobset, int iBuffer, SUBCEL *psubcel, int cposf, VECTORF *aposf, int ctwef, TWEF *atwef, SUBPOSEF *asubposef, VECTORF *aposfPoses, float *agWeights, VIFS *pvifs);

void BuildSubglobSinglePass(GLOBSET *pglobset, GLOB *pglob, int iBuffer, SUBGLOB *psubglob, SHD *pshd, VECTORF *aposf, VECTORF *anormalf, RGBAF *argbaf, UVF *auvf, int cvtxf, VTXF *avtxf, SUBPOSEF *asubposef, VECTORF *aposfPoses, VECTORF *anormalfPoses, float *agWeights, VIFS *avifs, SGVR *psgvr);

void BuildSubglobThreeWay(GLOBSET *pglobset, GLOB *pglob, int iBuffer, SUBGLOB *psubglob, SHD *pshd, VECTORF *aposf, VECTORF *anormalf, RGBAF *argbaf, UVF *auvf, int cvtxf, VTXF *avtxf, SUBPOSEF *asubposef, VECTORF *aposfPoses, VECTORF *anormalfPoses, float *agWeights, VIFS *avifs, SGVR *psgvr);
*/

void BuildSubglobLighting(GLOB *pglob, SUBGLOB *psubglob, SUBGLOBI *psubglobi);

void PostGlobsetLoad(GLOBSET *pglobset, ALO *palo);

void BindGlobset(GLOBSET *pglobset, ALO *palo);

void CloneGlobset(GLOBSET *pglobset, ALO *palo, GLOBSET *pglobsetBase);

void CloneGlob(GLOBSET *pglobset, GLOB *pglob, GLOBI *pglobi);

void UpdateGlobset(GLOBSET * pglobset, ALO *palo, float dt);

void UpdateAloConstraints(ALO *palo);

void UpdateAloInfluences(ALO *palo, RO *pro);

void PredrawGlob(GLOBSET *pglobset, GLOB *pglob, GLOBI *pglobi, ALO *palo);

void RotateVu1Buffer();

void DrawGlob(RPL *prpl);

#endif // GLOB_H
