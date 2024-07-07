/**
 * @file sound.h
 *
 * @brief Sound playback.
 */
#ifndef SOUND_H
#define SOUND_H

#include "common.h"
#include <util.h>
#include <alo.h>

enum SFXID
{
    // todo
};

/**
 * @brief Ambient sound.
 */
struct AMB
{
    SFXID sfxid;
    int iSerial;
    void *bnk;
    AMB **ppamb;
    float tStarted;
    float uVolAtSource;
    uint sfxh;
    undefined4 unk_1;
    VECTOR pos;
    ALO *palo;
    float sStart;
    float sFull;
    int fContinuous;
    int fOutOfRange;
    int fAttached;
    int fStopped;
    float volAttenuated;
    float pan;
    float frq;
    float rDoppler;
    int dnDoppler;
    int fPitchOrig;
    int ptchOrig;
    float tNext;
    LM lmRepeat;
    LM lmRepDist;
    undefined4 unk_2;
    undefined4 unk_3;
    undefined4 unk_4;
};

#endif // SOUND_H
