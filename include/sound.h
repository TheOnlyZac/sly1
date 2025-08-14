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

/**
 * @brief SFX ID. 
 */
enum SFXID
{
    SFXID_Click1 = 2,
    SFXID_Swoosh = 3,
    SFXID_JtFootfall1 = 4,
    SFXID_JtFootfall2 = 5,
    SFXID_JtFootfall3 = 6,
    SFXID_JtFootfall4 = 7,
    SFXID_EnvCaneReach1 = 8,
    SFXID_EnvCaneReach2 = 9,
    SFXID_EnvCaneReach3 = 10,
    SFXID_Cane_Attack1 = 11,
    SFXID_EnvDartsHit = 12,
    SFXID_CaneHandleLock = 13,
    SFXID_Fire = 19,
    SFXID_Thud1 = 20,
    SFXID_EnvAlarmSounding = 21,
    SFXID_EnvCricketChirp = 22,
    SFXID_Splash = 22, // note: same value as EnvCricketChirp....No idea why theres a dupe.
    SFXID_AmbElectric = 27,
    SFXID_Ripoff_Something = 35,
    SFXID_Env_Holographic_Marker = 40,
    SFXID_Bottle_Break = 44,
    SFXID_Darts_Fire = 51,
    SFXID_EnvDartsHi = 52,
    SFXID_Roc_Hit = 55,
    SFXID_Blaster_Fire = 58,
    SFXID_Npc_Whistle = 63,
    SFXID_Jt_Land = 73,
    SFXID_Collect_Life = 105,
    SFXID_Last_Clue = 106,
    SFXID_Yipee = 109,
    SFXID_Binoc_Hum = 112,
    SFXID_Binoc_Zoom = 113,
    SFXID_Click2 = 115,
    SFXID_Collect_Charm = 116,
    SFXID_Sneaky_Footstep = 119,
    SFXID_Collect_Coin = 120,
    SFXID_Click3 = 121,
    SFXID_Click4 = 122,
    SFXID_Thud7 = 123,
    SFXID_Take_out_Binoc = 142,
    SFXID_Put_Away_Binoc = 143,
    SFXID_Jt_Hurt = 163,
    SFXID_Ripoff_Hit = 335,
    SFXID_Honk = 337,
    SFXID_Ricochet = 338
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
