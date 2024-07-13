/**
 * @file alo.h
 */
#ifndef ALO_H
#define ALO_H

#include "common.h"
#include <lo.h>
#include <dl.h>

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

    // ...
};

#endif // ALO_H
