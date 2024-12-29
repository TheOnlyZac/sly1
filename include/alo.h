/**
 * @file alo.h
 */
#ifndef ALO_H
#define ALO_H

#include "common.h"
#include <lo.h>
#include <dl.h>

// Forward
struct CBinaryInputStream;

struct FICG
{
    uchar grficSweep;
    uchar grficRush;
    uchar grficSmash;
    uchar grficBomb;
    uchar grficShock;
};

/**
 * @brief Unknown
*/
struct SNIP
{
    int grfsnip;
    OID oid;
    int ib;
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
 * @brief unknown
 *
 */
void SnipAloObjects(ALO *palo, int csnip, SNIP *asnip);

/**
 * @brief Updates an ALO
 *
 * @param palo ALO to initialize
 */
void UpdateAlo(ALO *palo, float dt);

/**
 * @brief Clones an ALO
 * 
 */
void CloneAlo(ALO *palo, ALO *paloBase);

/**
 * Fades in an ALO
 */
void FadeAloIn(ALO *palo, float dtFade);

/**
 * Fades out an ALO
 */
void FadeAloOut(ALO *palo, float dtFade);

/**
 * @brief unknown
 */
void LoadAloFromBrx(ALO *palo, CBinaryInputStream *pbis);

/**
 * @brief unknown
 */
void SetAloTargetHitTest(ALO *palo, int fHitTest);

#endif // ALO_H
