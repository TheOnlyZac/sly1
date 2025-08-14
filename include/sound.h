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
    SFXID_click1 = 2,
    SFXID_swoosh = 3,
    SFXID_JtFootfall1 = 4,
    SFXID_JtFootfall2 = 5,
    SFXID_JtFootfall3 = 6,
    SFXID_JtFootfall4 = 7,
    SFXID_EnvCaneReach1 = 8,
    SFXID_EnvCaneReach2 = 9,
    SFXID_EnvCaneReach3 = 10,
    SFXID_cane_attack1 = 11,
    SFXID_EnvDartsHit = 12,
    SFXID_CaneHandleLock = 13,
    SFXID_fire = 19,
    SFXID_thud1 = 20,
    SFXID_EnvAlarmSounding = 21,
    SFXID_EnvCricketChirp = 22,
    SFXID_splash = 22, // note: same value as EnvCricketChirp....No idea why theres a dupe.
    SFXID_AmbElectric = 27,
    SFXID_ripoff_something = 35,
    SFXID_env_holographic_marker = 40,
    SFXID_bottle_break = 44,
    SFXID_darts_fire = 51,
    SFXID_EnvDartsHi = 52,
    SFXID_roc_hit = 55,
    SFXID_blaster_fire = 58,
    SFXID_npc_whistle = 63,
    SFXID_jt_land = 73,
    SFXID_collect_life = 105,
    SFXID_last_clue = 106,
    SFXID_yipee = 109,
    SFXID_binoc_hum = 112,
    SFXID_binoc_zoom = 113,
    SFXID_click2 = 115,
    SFXID_collect_charm = 116,
    SFXID_sneaky_footstep = 119,
    SFXID_collect_coin = 120,
    SFXID_click3 = 121,
    SFXID_click4 = 122,
    SFXID_thud7 = 123,
    SFXID_take_out_binoc = 142,
    SFXID_put_away_binoc = 143,
    SFXID_jt_hurt = 163,
    SFXID_ripoff_hit = 335,
    SFXID_honk = 337,
    SFXID_ricochet = 338
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
