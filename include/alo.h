/**
 * @file alo.h
 */
#ifndef ALO_H
#define ALO_H

#include "common.h"
#include <lo.h>
#include <dl.h>

struct FICG
{
    uchar grficSweep;
    uchar grficRush;
    uchar grficSmash;
    uchar grficBomb;
    uchar grficShock;
};

/**
 * @brief "Lightweight"
 *
 * @todo Finish implementing struct.
 */
struct ALO : public LO
{
    DL dlChild;
    DLE dleBusy;
    DLE dleMRD;
    ALO *paloRoot;
    ALO *paloFreezeRoot;
    DLE dleFreeze;
    DL dlFreeze;
    int cpmrg;
    //MRG *apmrg[4];
    float sMRD;
    float sCelBorderMRD;
    int grfzon;
    float dsMRDSnap;
    undefined4 unk_1;
    //FRZ frz;
    //XF xf;
    //VECTOR pso

    undefined4 padding[0x88];
    FICG ficg;

    undefined1 padding2[0x16];
    // ...
};

/**
 * @brief Initializes an ALO
 *
 * @param palo ALO to initialize
 */
void InitAlo(ALO *palo);

/**
 * @brief Updates an ALO
 *
 * @param palo ALO to initialize
 */
void UpdateAlo(ALO *palo, float dt);

#endif // ALO_H
