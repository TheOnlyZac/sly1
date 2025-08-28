/**
 * @file glob.h
 */
#ifndef GLOB_H
#define GLOB_H

#include <bis.h>
#include <alo.h>
#include <vec.h>

/**
 * @todo Implement struct.
 */
struct GLOBSET
{
	// ...
};

/**
 * @todo Implement struct.
 */
struct GLOB
{
    // ...
};

/*
void BuildGlobsetSaaArray(GLOBSET *pglobset);

void LoadGlobsetFromBrx(GLOBSET *pglobset, CBinaryInputStream *pbis, ALO *palo);

void EnsureBuffer(int iBuffer, VIFS *pvifs);

void EnsureBufferCel(int iBuffer, VIFS *pvifs);

void BuildSubcel(GLOBSET *pglobset, int iBuffer, SUBCEL *psubcel, int cposf, VECTORF *aposf, int ctwef, TWEF *atwef, SUBPOSEF *asubposef, VECTORF *aposfPoses, float *agWeights, VIFS *pvifs);

void BuildSubglobSinglePass(GLOBSET *pglobset, GLOB *pglob, int iBuffer, SUBGLOB *psubglob, SHD *pshd, VECTORF *aposf, VECTORF *anormalf, RGBAF *argbaf, UVF *auvf, int cvtxf, VTXF *avtxf, SUBPOSEF *asubposef, VECTORF *aposfPoses, VECTORF *anormalfPoses, float *agWeights, VIFS *avifs, SGVR *psgvr);

void BuildSubglobThreeWay(GLOBSET *pglobset, GLOB *pglob, int iBuffer, SUBGLOB *psubglob, SHD *pshd, VECTORF *aposf, VECTORF *anormalf, RGBAF *argbaf, UVF *auvf, int cvtxf, VTXF *avtxf, SUBPOSEF *asubposef, VECTORF *aposfPoses, VECTORF *anormalfPoses, float *agWeights, VIFS *avifs, SGVR *psgvr);

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
*/

#endif // GLOB_H
