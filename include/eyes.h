/**
 * @file eyes.h
 */
#ifndef EYES_H
#define EYES_H

#include "common.h"
#include <shd.h>

/**
 * @brief Eyes state.
 */
enum EYESS
{
    EYESS_Nil = -1,
    EYESS_Open = 0,
    EYESS_Closing = 1,
    EYESS_Closed = 2,
    EYESS_Opening = 3,
    EYESS_Max = 4
};

/**
 * @brief Eyes.
 */
struct EYES : public SAA
{
    /* 0x2c */ float dtBlink;
    /* 0x30 */ float dtOpenMin;
    /* 0x34 */ float dtOpenMax;
    /* 0x38 */ float uDoubleBlink;
    /* 0x3c */ OID oidOther;
    /* 0x40 */ SAI saiOther;
    /* 0x5c */ int cframe;
    /* 0x60 */ EYESS eyess;
    /* 0x64 */ float tEyess;
    /* 0x68 */ float dtOpen;
    /* 0x6c */ float sviframe;
    /* 0x70 */ float gframe;
    /* 0x74 */ float uClosed;
};

void InitEyes(EYES *peyes, SAAF *psaaf);

void PostEyesLoad(EYES *peyes);

void SetEyesEyess(EYES *peyes, EYESS eyess);

void UpdateEyes(EYES *peyes, float dt);

void SetEyesClosed(EYES *peyes, float uClosed);

SAI *PsaiFromEyesShd(EYES *peyes, SHD *pshd);

#endif // EYES_H
