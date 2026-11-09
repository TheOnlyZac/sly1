/**
 * @file sound.h
 *
 * @brief Sound playback.
 */
#ifndef SOUND_H
#define SOUND_H

#include "common.h"
#include <util.h>

// Forward.
struct ALO;

/**
 * @brief SFX ID.
 *
 * @todo Figure out what DAT_00262050 is as well as what value is being used in the following functions:
 *   WakeSoWater (Gets sound 0, 16, 32, or 48 from DAT_00262050)
 *   FireExplsExplso (Seems like an enemy or actor that moves and emits particles)
 *   StartSwIntermittentSounds()
 *   SetJtJtcs()
 *   FUN_001eb748
 */
enum SFXID
{
    SFXID_UnkNeg2 = -2, // Found in FUN_001be8f8()
    SFXID_Nil = -1,     // Used to call a sound in FUN_001a54f8() for some reason?
    SFXID_UiTick = 0,   // Probably wrong value, but needed for UpdateCodes in joy.c. Also Found in FUN_001ed318
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
    SFXID_UiBinocAmbient = 112,
    SFXID_UiBinocZoom = 113,
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
    // MVGK_Dialog = 0x2,
    // MVGK_User1 = 0x3,
    // MVGK_User2 = 0x4,
    // MVGK_UIser3 = 0x5,
    // MVGK_User4 = 0x6,
    // MVGK_External = 0x7,
    // MVGK_Global = 0x8,
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
    undefined4 unk_pre; // Padding found from asm offsets (guess).
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
    undefined4 unk_5;
};

/**
 * @brief Sound Effect.
 */
struct SFX
{
    /* 0x00 */ SFXID sfxid;
    /* 0x04 */ float sStart;
    /* 0x08 */ float sFull;
    /* 0x0c */ float uVol;
    float uPitch;
    LM lmRepeat;
    /* 0x1c */ AMB *pamb;
    /* 0x20 */ float uDoppler;
};

/**
 * @brief Excitement.
 * @todo Implement the struct.
 */
struct EXC
{
    int iexc;
    DLE dle;
};

typedef int IEXC;

extern IEXC g_iexcHyst;

/**
 * @brief Stops and unloads the music bank (if loaded) and resets the music state.
 */
void UnloadMusic();

/**
 * @brief Check if a VAG is playing.
 * @return Nonzero if a VAG stream handle is currently held.
 */
int FVagPlaying();

/**
 * @brief Returns the VAG unpaused state.
 * @note Despite the name this is a getter for D_00274744 (name is original, meaning is a guess).
 */
int SetVagUnpaused();

/**
 * @brief Clears the VAG unpaused flag and stops the VAG. (Name unknown, guess.)
 */
void FUN_001be708();

/**
 * @brief Clears D_00274730. (Meaning unknown.)
 */
void FUN_001BE5D8();

/**
 * @brief Pauses the current VAG if one is playing.
 */
void PauseVag();

/**
 * @brief Continues the current VAG if one is playing.
 */
void ContinueVag();

/**
 * @brief Pauses the music sound handle. (Name is a guess.)
 */
void SfxhMusicUnknown1();

/**
 * @brief Continues the music sound handle. (Name is a guess.)
 */
void SfxhMusicUnknown2();

/**
 * @brief Sets the rvol of the music MVGK on channel 3 to 0 (mute) or 1.
 * @param mute Nonzero to mute. (Purpose is a guess.)
 */
void MvgkUnknown3(int mute);

/**
 * @brief Sets the sound playback mode to 0 or 1.
 * @param mode Treated as a boolean. (Purpose is a guess.)
 */
void MvgkUnknown4(int mode);

/**
 * @brief Detaches an ambient sound from its owner pointer.
 * @param ppamb Pointer to the owner's AMB pointer; cleared afterwards.
 */
void DropPamb(AMB **ppamb);

/**
 * @brief Returns the ambients-paused flag.
 */
int FAmbientsPaused();

/**
 * @brief Stops the current VAG.
 */
void StopVag();

/**
 * @brief Allocates a zeroed excitement (EXC) from the world's EXC heap and links it into the EXC list.
 * @return The new EXC, or 0 if the heap is full.
 */
EXC *PexcAlloc();

/**
 * @brief Allocates a zeroed ambient sound (AMB) from the world's AMB heap and links it into the AMB list.
 * @return The new AMB, or 0 if the heap is full.
 */
AMB *PambAlloc();

/**
 * @brief Unlinks an EXC from the world's EXC list and frees it.
 */
void RemoveExc(EXC *pexc);

/**
 * @brief Clears the owner pointer of an AMB, invalidates its serial, then unlinks and frees it.
 */
void RemoveAmb(AMB *pamb);

/**
 * @brief Stops the music if it is currently playing. (State values are guesses.)
 */
void KillMusic();

/**
 * @brief Removes an EXC and, if it was the hysteresis level, makes it the current high. (Meaning is a guess.)
 * @param pexc The EXC to remove, may be null.
 */
void UnsetExcitementHyst(EXC *pexc);

/**
 * @brief Unknown.
 */
void SetIexcCurHigh(EXC *pexc);

/**
 * @brief Removes an excitement (EXC). If it was the current high, recomputes the high and resets the global excite level and
 * the music volume (channel 7). (Behavior inferred from the asm, meanings are guesses.)
 * @param pexc The EXC to remove, may be null.
 */
void UnsetExcitement(EXC *pexc);

/**
 * @brief Unknown.
 */
void KillExcitement();

/**
 * @brief Starts up the sound system.
 */
void StartupSound();

/**
 * @brief Ensures the soundbank is available.
 */
void SbpEnsureBank(int bank);

/**
 * @brief Ensures the soundbank for an SFX ID is loaded.
 * @param sfxid SFX ID, used to index a bank table (table layout is a guess).
 */
void SbpEnsureBank(SFXID sfxid);

/**
 * @brief Create a new sound effect.
 */
void NewSfx(SFX **ppsfx);

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
 * @brief Ramps down (or stops immediately) an ambient sound and removes it.
 * @param pamb Ambient sound, may be null.
 * @param msRampdown Rampdown time in ms (scaled by a guessed constant); 0 stops immediately.
 */
void StopSound(AMB *pamb, int msRampdown);

/**
 * @brief TODO
 */
void SetPambVol(AMB *pamb, float uVolAtSource);

/**
 * @brief TODO
 */
void SetPambFrq(AMB *pamb, float frq);

/**
 * @brief Set the uvol of an mvgk.
 *
 * @note May version takes an mvgk as an argument, but this seems not to.
 */
void SetMvgkUvol(float uvol);

/**
 * @brief Unknown.
 */
void MvgkUnknown1(MVGK mvgk);

/**
 * @brief Sets the rvol of an mvgk.
 */
void SetMvgkRvol(int channel, MVGK mvgk, float rvol);

/**
 * @brief Unknown.
 */
void MvgkUnknown2();

/**
 * @brief Stops everything related to the sound system.
 */
void KillSoundSystem();

/**
 * @brief Unknown.
 */
void KillSounds(int param_1);

/**
 * @brief Unknown.
 */
void FUN_001c0cb0();

/**
 * @brief Returns the cached value of AM register `reg`.
 */
int GetAMRegister(int reg);

/**
 * @brief Refreshes the cached AM register `reg` from the live sequencer value.
 * (`value` is unused by the body but kept for the caller's ABI.)
 */
void UpdateAMRegister(int reg, int value);

/**
 * @brief Returns the listener (ear) position. (Name/meaning inferred from usage in SDistEar.)
 */
VECTOR *PposEar();

typedef float (*PFNEARDIST)(VECTOR *, VECTOR *);

/**
 * @brief Distance function used for the listener, variant A (unmatched, name unknown).
 */
extern "C" float FUN_001BF2E0(VECTOR *, VECTOR *);

/**
 * @brief Plain 3D distance between two positions (VU0 code, not yet matched; name unknown).
 */
extern "C" float FUN_001BF398(VECTOR *, VECTOR *);

/**
 * @brief Returns the distance function to use for the listener: FUN_001BF2E0 for camera look kinds 1 and 2
 * while the look policy is active, otherwise FUN_001BF398. (Interpretation is a guess.)
 */
PFNEARDIST PfneardistGet();

/**
 * @brief Distance from the listener to a position.
 * @param ppos Position to measure to.
 * @return Distance as computed by the near-distance function (return type is a guess).
 */
float SDistEar(VECTOR *ppos);

/**
 * @brief Recomputes volume and pan of an ambient sound.
 */
void RefreshPambVolPan(AMB *pamb);

/**
 * @brief Sets a cached AM register and forwards it to the music handle if it changed.
 */
void SetAMRegister(int reg, uchar value);

/**
 * @brief Continues a paused VAG stream when appropriate. (Meaning is a guess.)
 * @return 1 if paused for VAG, otherwise 0 (guess).
 */
int FPauseForVag();

/**
 * @brief Records the preload completion handle and resolves bank XREFs.
 * @param handle Completion handle (guess).
 * @param userData Unused.
 */
void PreloadMusidSongComplete(uint handle, unsigned long userData);

enum REVERBK
{
    REVERBK_None = 0,
    REVERBK_StudioA = 1,
    REVERBK_StudioB = 2,
    REVERBK_StudioC = 3,
    REVERBK_Pipe = 4,
    REVERBK_Room = 5,
    REVERBK_Max = 6,
    REVERBK_Nil = -1
};

struct SW;

/**
 * @brief Sets the default reverb type and depth for a world.
 * @param psw World.
 * @param reverbk Reverb kind, indexes a table of hardware reverb types.
 * @param depth Reverb depth (used for both left and right).
 */
void SetSwDefaultReverb(SW *psw, REVERBK reverbk, const int depth);

/**
 * @brief Sets the volume of the effects, dialog and others (and optionally music) on MVGK channel 6 for wipes.
 * @param fMusic Nonzero to also set the music volume.
 * @param vol Volume. (Name and channel semantics are guesses.)
 */
void HandleWipeVolumes(int fMusic, float vol);

/**
 * @brief Whether the SFX's soundbank is loaded (loads it first if needed) and a per-sfx continuous flag.
 * @return Per-SFX table value (meaning is a guess).
 */
int FContinuousSound(SFXID sfxid);

/**
 * @brief Plays the next sneaky footstep sound if enabled. (Meaning is a guess.)
 */
void NextSneakyFootstep();

/**
 * @brief Gets the next foot fall index. (Guess.)
 */
int HsNextFootFall();

/**
 * @brief Pushes a reverb setting on the world's reverb stack and applies it (stack holds up to 4 entries, bounds are from the asm).
 * @param psw World.
 * @param reverb Reverb kind.
 * @param k Reverb depth (named k in the existing header, used for both channels).
 */
/**
 * @brief Adds an intermittent sound to the world's list (max 16), with default repeat and distance limits.
 * @param psw World.
 * @param sfxid Sound to add.
 * @note Name is a guess (originally FUN_001C0A50).
 */
void AddSwIntermittentSound(SW *psw, SFXID sfxid);

/**
 * @brief Sets the distance limits of the most recently added intermittent sound.
 * @param plm Limits; stored as 8000 - 50 * (swapped min/max). Name and units are guesses (originally FUN_001C0AB8).
 */
void SetSwIntermittentDist(SW *psw, LM *plm);

/**
 * @brief Sets the repeat limits of the most recently added intermittent sound.
 * @note Name is a guess (originally FUN_001C0B08).
 */
void SetSwIntermittentRepeat(SW *psw, LM *plm);

/**
 * @brief Starts every intermittent sound registered on the world.
 */
void StartSwIntermittentSounds(SW *psw);

/**
 * @brief Sound completion callback for an ambient sound: marks the AMB stopped if it is still the same one.
 * @param result Completion result; the callback only acts when 0.
 * @param userData Packed value: low 32 bits are the AMB pointer, high 32 bits the AMB serial.
 * @note Name and exact semantics are guesses (originally FUN_001BFFC8).
 */
void AmbCompleteProc(int result, unsigned long userData);

void PushSwReverb(SW *psw, REVERBK reverb, int k);

/**
 * @brief Pops the top reverb setting from the world's reverb stack and re-applies the previous one.
 * @param psw World.
 */
void PopSwReverb(SW *psw);

#endif // SOUND_H
