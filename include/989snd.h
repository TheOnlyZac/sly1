/**
 * @file 989snd.h
 *
 * @brief 989snd sound driver.
 */
#ifndef SND989_H
#define SND989_H

#include "sdk/libcdvd.h"

typedef unsigned int u_int;
typedef unsigned long u_long;

extern "C" {

typedef void (*SndCompleteProc)(int, u_long);
typedef void* SoundBankPtr;

void snd_StartSoundSystem(void);
int snd_FlushSoundCommands(void);
SoundBankPtr snd_BankLoadByLoc(int loc, int offset);
void snd_BankLoadByLoc_CB(int loc, int offset, SndCompleteProc cb, u_long user_data);
void snd_ResolveBankXREFS(void);
void snd_UnloadBank(SoundBankPtr bank);
void snd_SetMasterVolume(int which, int vol);
int snd_GetMasterVolume(int which);
void snd_SetPlaybackMode(int mode);
void snd_SetMixerMode(int channel_mode, int reverb_mode);
void snd_SetGroupVoiceRange(int group, int min, int max);
u_int snd_PlaySoundVolPanPMPB(SoundBankPtr bank, int sound, int vol, int pan, int pitch_mod, int bend);
void snd_StopSound(u_int handle);
void snd_PauseSound(u_int handle);
void snd_ContinueSound(u_int handle);
void snd_PauseAllSoundsInGroup(u_int groups);
void snd_ContinueAllSoundsInGroup(u_int groups);
u_int snd_SoundIsStillPlaying(u_int handle);
void snd_SoundIsStillPlaying_CB(u_int handle, SndCompleteProc cb, u_long user_data);
int snd_IsSoundALooper(SoundBankPtr bank, u_int sound);
void snd_SetSoundVolPan(u_int handle, int vol, int pan);
int snd_GetSoundOriginalPitch(SoundBankPtr bank, int index);
void snd_SetSoundPitch(u_int handle, int pitch);
void snd_AutoVol(u_int handle, int vol, int delta_time, int delta_from);
void snd_SetMIDIRegister(u_int handle, int reg, int value);
int snd_GetMIDIRegister(u_int handle, int reg);
void snd_SetGlobalExcite(int value);
int snd_InitVAGStreamingEx(int num_channels, int buffer_size, unsigned int read_mode, int enable_streamsafe_from_ee);
void snd_StopAllStreams(void);
u_int snd_PlayVAGStreamByLoc(int loc1, int loc2, int offset1, int offset2, int vol, int pan, int vol_group, u_int queue, u_int flags);
void snd_ContinueVAGStream(u_int stream);
void snd_IsVAGStreamBuffered_CB(u_int stream, SndCompleteProc cb, u_long user_data);
int snd_StreamSafeCheckCDIdle(int block_ee_iop);
int snd_StreamSafeCdRead(u_int lbn, u_int sectors, void* buf, sceCdRMode* mode);
int snd_StreamSafeCdSync(int mode);
int snd_StreamSafeCdBreak(void);
int snd_StreamSafeCdGetError(void);
void snd_SetReverbType(int core, int type);
void snd_SetReverbDepth(int core, int left, int right);
void snd_PreAllocReverbWorkArea(int core, int type);
int snd_InitMovieSound(int sizeOfIOPBuffer, int volumeLevel, int panCenter, int volumeGroup, int unk);
void snd_ResetMovieSound(void);
void snd_CloseMovieSound(void);
void snd_StartMovieSound(int iopBuffer, int iopBufferSize, int iopPausePosition, u_int sr, int ch);
int snd_GetTransStatus(void);
int snd_GetDopplerPitchMod(int approaching_mph);
}

#endif // SND989_H
