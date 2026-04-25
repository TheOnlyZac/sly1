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
    /* 0x30 */ int unk[0x4];   
    /* 0x3c */ OID oid;        
    /* 0x40 */ int unk2;       
    /* 0x44 */ SHD *pshd;      
    /* 0x48 */ int unk1[0x6];  
    /* 0x60 */ EYESS eyess;    
    /* 0x70 */ float iframe;   
    /* 0x74 */ float uClosed; 
};

void InitEyes(EYES *peyes, SAAF *psaaf);

void PostEyesLoad(EYES *peyes);

void SetEyesEyess(EYES *peyes, EYESS eyess);

void UpdateEyes(EYES *peyes, float dt);

void SetEyesClosed(EYES *peyes, float uClosed);

SAI *PsaiFromEyesShd(EYES *peyes, SHD *pshd);

#endif // EYES_H
