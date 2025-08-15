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
 *
 * @todo Figure out what DAT_00262050 is as well as what value is being used in the following functions:
 *   FUN_00156288 (Gets sound 0, 16, 32, or 48 from DAT_00262050)
 *   FUN_001590a0 (Seems like an enemy or actor that moves and emits particles)
 *   StartSwIntermittentSounds()
 *   SetJtJtcs()
 *   FUN_001eb748
 */
enum SFXID
{
    SFXID_UnkNeg2 = -2, // Found in FUN_001be8f8()
    SFXID_None = -1,    // Used to call a sound in FUN_001a54f8() for some reason?
    SFXID_UiTick = 0,   // This value for UiTick is probably wrong, but it's needed for UpdateCodes in joy.c. Also Found in FUN_001ed318
    SFXID_Unk1 = 1,     // Found in RebuildTimerAchzDraw()
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
    SFXID_Unk14 = 14,   // Found in SetJtJts()
    SFXID_Unk15 = 15,   // Found in UndeinedFunction_001b17b0()
    SFXID_Fire = 19,
    SFXID_Thud1 = 20,
    SFXID_EnvAlarmSounding = 21,
    SFXID_EnvCricketChirp = 22,
    SFXID_Splash = 22, // note: same value as EnvCricketChirp....No idea why theres a dupe.
    SFXID_Unk26 = 26,   // Found in FUN_001b01b0()
    SFXID_AmbElectric = 27,
    SFXID_Unk33 = 33,   // Found in FUN_001999d0()
    SFXID_Unk34 = 34,   // Found in FUN_001eef90()
    SFXID_Ripoff_Something = 35,
    SFXID_Env_Holographic_Marker = 40,
    SFXID_Unk42 = 42,   // Found in BreakBrk()
    SFXID_Bottle_Break = 44,
    SFXID_Darts_Fire = 51,
    SFXID_EnvDartsHi = 52,
    SFXID_Unk53 = 53,   // Found in FUN_0013bf68()
    SFXID_Roc_Hit = 55,
    SFXID_Blaster_Fire = 58,
    SFXID_Unk59 = 59,   // Found in FUN_0019b378
    SFXID_Npc_Whistle = 63,
    SFXID_Unk65 = 65,   // Found in FUN_0015ad80(), FUN_0015ae38(), FUN_0015b128()
    SFXID_Unk71 = 71,   // Found in UpdateStepFootfall(). Most likely Land sound.
    SFXID_Unk72 = 72,   // Found in UpdateStepFootfall(). Most likely Land sound.
    SFXID_Jt_Land = 73,
    SFXID_Unk74 = 74,   // Found in UpdateStepFootfall(). Most likely Land sound.
    SFXID_Unk77 = 77,   // Found in SetJtJts()
    SFXID_Unk78 = 78,   // Found in SetJtJts()
    SFXID_Unk79 = 79,   // Found in SetJtJts()
    SFXID_Unk80 = 80,   // Found in SetJtJts()
    SFXID_Unk81 = 81,   // Found in ExitedRobRoh(), FUN_001eb748()
    SFXID_Unk89 = 89,   // Found in SetJtJts()
    SFXID_unk90 = 90,   // Found in UpdateSuvActive()
    SFXID_Unk103 = 103, // Found in FUN_001d32d8()
    SFXID_Collect_Life = 105,
    SFXID_Last_Clue = 106,
    SFXID_Yipee = 109,
    SFXID_Binoc_Hum = 112,
    SFXID_Binoc_Zoom = 113,
    SFXID_Unk114 = 114,   // Found in RebuildTimerAchzDraw()
    SFXID_Click2 = 115,
    SFXID_Collect_Charm = 116,
    SFXID_Sneaky_Footstep = 119,
    SFXID_Collect_Coin = 120,
    SFXID_Click3 = 121,
    SFXID_Click4 = 122,
    SFXID_Thud7 = 123,
    SFXID_Unk126 = 126,   // Found in SetJtJts(), UpdateJtActive(), RebuildTimerAchzDraw(), runs_on_cane_hook_grab()
    SFXID_Unk127 = 127,   // Found in RebuildTimerAchzDraw()
    SFXId_unk138 = 138,   // Found in SetWmWms()
    SFXId_unk139 = 139,   // Found in SetWmWms()
    SFXID_Unk140 = 140,   // Found in SetTvTvgs()
    SFXID_Unk141 = 141,   // Found in SetTvTvgs()
    SFXID_Take_out_Binoc = 142,
    SFXID_Put_Away_Binoc = 143,
    SFXID_Unk148 = 148,   // Found in SetJtJts()
    SFXID_Jt_Hurt = 163,
    SFXID_Unk166 = 166,   // Found in FUN_001d5398()
    SFXID_Unk333 = 333,   // Found in FUN_001a4070()
    SFXID_Unk334 = 334,   // Found in FUN_001a54f8()
    SFXID_Ripoff_Hit = 335,
    SFXID_Unk336 = 336,   // Found in SetRovRovts()
    SFXID_Honk = 337,
    SFXID_Ricochet = 338,
    SFXID_Unk429 = 429,   // Found in init_burning_rubber()
    SFXID_Unk431 = 431,   // Found in init_burning_rubber()
    SFXID_Unk443 = 443,   // Found in init_burning_rubber()
    SFXID_Unk460 = 460,   // Found in FUN_0018ae38()
    SFXID_Unk466 = 466,   // Found in init_burning_rubber()
    SFXID_Unk637 = 637,   // Found in init_burning_rubber()
    SFXID_Unk639 = 639,   // Found in init_burning_rubber()
    SFXID_Unk640 = 640,   // Found in init_burning_rubber()
    SFXID_Unk678 = 678,   // Found in init_burning_rubber()
    SFXID_Unk731 = 731,   // Found in init_burning_rubber()
    SFXID_Unk732 = 732,   // Found in init_burning_rubber()
    SFXID_Unk733 = 733,   // Found in init_burning_rubber()
    SFXID_Unk734 = 734,   // Found in init_burning_rubber()
};

enum MVGK
{
    MVGK_Effects = 0x0,
    MVGK_Music = 0x1,
    MVGK_Dialog = 0x2,
    MVGK_User1 = 0x3,
    MVGK_User2 = 0x4,
    MVGK_UIser3 = 0x5,
    MVGK_User4 = 0x6,
    MVGK_External = 0x7,
    MVGK_Global = 0x8,
    MVGK_Max = 0x9
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

/**
 * @brief
 */
void SetMvgkRvol(MVGK mvgk, float rvol);

/**
 * @brief
 */
void SetMvgkUvol(float uvol);

#endif // SOUND_H
