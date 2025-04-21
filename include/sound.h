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
    SFXID_UiTick = 0, // inaccurate
    // ...

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

/**
 * @brief Starts sound playback.
 *
 * @param sfxid The sound effect ID
 * @param ppamb Pointer to the ambient sound object
 * @param palo Pointer to the ALO object
 * @param ppos Position of the sound source
 * @param sStart The start time(?)
 * @param sFull The full time(?)
 * @param uVolAtSource Volume at the source
 * @param frq Frequency
 * @param uDoppler Doppler effect
 * @param plmRepeat Pointer to the repeat limit
 * @param plmRepDis Pointer to the repeat distance limit
 */
void StartSound(SFXID sfxid, AMB **ppamb, ALO *palo, VECTOR *ppos, float sStart, float sFull, float uVolAtSource, float frq, float uDoppler, LM *plmRepeat, LM *plmRepDis);

#endif // SOUND_H
