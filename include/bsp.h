/**
 * @file bsp.h
 *
 * @brief Binary Space Partitioning.
 *
 * @note At the time of writing all structs are based on
 * the May 19 prototype, so they could be inaccurate.
 */
#ifndef BSP_H
#define BSP_H

#include "common.h"
#include <geom.h>
#include <vec.h>

/**
 * @brief Unknown.
 */
enum PRUNE
{
    PRUNE_Neg = 0,
    PRUNE_Pos = 1,
    PRUNE_Mixed = 2
};

/**
 * @brief BSP tree node.
 */
struct BSP
{
    SURF *psurf;
    BSP *pbspNeg;
    BSP *pbspPos;
};

/**
 * @brief BSP Collection (?).
 */
struct BSPC
{
    int cbsp;
    int cbspFull;
    BSP *absp;
};

/**
 * @brief (?) BSP.
 */
struct VBSP
{
    VECTOR normal;
    float gDot;
    VBSP *pvbspNeg;
    VBSP *pvbspPos;
    // Might contain other fields?
};

/**
 * @brief Unknown.
 */
struct LSG
{
    // ...
};

/**
 * @brief Unknown.
 */
int ClsgClipEdgeToBsp(BSP *pbspRoot, VECTOR *ppos1, VECTOR *ppos2, int *mpibspn, int clsgMax, LSG *alsg);

/**
 * @brief Unknown.
 */
PRUNE PruneBsp(BSP *pbsp, VECTOR *ppos, float sRadius, BSP **ppbspNext);

/**
 * @brief Unknown.
 */
BSP *PbspPointInBspQuick(VECTOR *ppos, BSP *pbsp);

/**
 * @brief Unknown.
 */
void CloneBspc(GEOM *pgeomSrc, BSPC *pbspcSrc, GEOM *pbspcDst, BSPC *pbspcDst);

#endif // BSP_H
