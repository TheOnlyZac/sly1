#include "common.h"

INCLUDE_ASM(const s32, "P2/989snd", snd_StartSoundSystem);

INCLUDE_ASM(const s32, "P2/989snd", snd_FlushSoundCommands__Fv);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d060);

INCLUDE_ASM(const s32, "P2/989snd", snd_GotReturns__Fv);

INCLUDE_ASM(const s32, "P2/989snd", snd_PrepareReturnBuffer__FPUii);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d138);

INCLUDE_ASM(const s32, "P2/989snd", snd_BankLoadByLoc);

INCLUDE_ASM(const s32, "P2/989snd", snd_BankLoadByLoc_CB);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d3e8);

INCLUDE_ASM(const s32, "P2/989snd", snd_ResolveBankXREFS);

INCLUDE_ASM(const s32, "P2/989snd", snd_UnloadBank);

INCLUDE_ASM(const s32, "P2/989snd", snd_SetMasterVolume);

INCLUDE_ASM(const s32, "P2/989snd", snd_GetMasterVolume);

INCLUDE_ASM(const s32, "P2/989snd", snd_SetPlaybackMode);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d510);

INCLUDE_ASM(const s32, "P2/989snd", snd_SetMixerMode);

INCLUDE_ASM(const s32, "P2/989snd", snd_SetGroupVoiceRange);

INCLUDE_ASM(const s32, "P2/989snd", snd_PlaySoundVolPanPMPB);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d5d8);

INCLUDE_ASM(const s32, "P2/989snd", snd_StopSound);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d630);

INCLUDE_ASM(const s32, "P2/989snd", snd_PauseSound);

INCLUDE_ASM(const s32, "P2/989snd", snd_ContinueSound);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d6a0);

INCLUDE_ASM(const s32, "P2/989snd", snd_PauseAllSoundsInGroup);

INCLUDE_ASM(const s32, "P2/989snd", snd_ContinueAllSoundsInGroup);

INCLUDE_ASM(const s32, "P2/989snd", snd_SoundIsStillPlaying);

INCLUDE_ASM(const s32, "P2/989snd", snd_SoundIsStillPlaying_CB);

INCLUDE_ASM(const s32, "P2/989snd", snd_IsSoundALooper);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d790);

INCLUDE_ASM(const s32, "P2/989snd", snd_SetSoundVolPan);

INCLUDE_ASM(const s32, "P2/989snd", snd_GetSoundOriginalPitch);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d808);

INCLUDE_ASM(const s32, "P2/989snd", snd_SetSoundPitch);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d848);

INCLUDE_ASM(const s32, "P2/989snd", snd_AutoVol);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d8a0);

INCLUDE_ASM(const s32, "P2/989snd", snd_SetMIDIRegister);

INCLUDE_ASM(const s32, "P2/989snd", snd_GetMIDIRegister);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d920);

INCLUDE_ASM(const s32, "P2/989snd", snd_SetGlobalExcite);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011d958);

INCLUDE_ASM(const s32, "P2/989snd", snd_SendIOPCommandAndWait__FiiPc);

INCLUDE_ASM(const s32, "P2/989snd", snd_SendIOPCommandNoWait__FiiPcPFiUl_vUl);

INCLUDE_ASM(const s32, "P2/989snd", func_0011DDD0);

INCLUDE_ASM(const s32, "P2/989snd", snd_PostMessage__Fv);

INCLUDE_ASM(const s32, "P2/989snd", snd_SendCurrentBatch__Fv);

INCLUDE_ASM(const s32, "P2/989snd", snd_InitVAGStreamingEx);

INCLUDE_ASM(const s32, "P2/989snd", snd_StopAllStreams);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011e040);

INCLUDE_ASM(const s32, "P2/989snd", snd_PlayVAGStreamByLoc);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011e0a8);

INCLUDE_ASM(const s32, "P2/989snd", snd_ContinueVAGStream);

INCLUDE_ASM(const s32, "P2/989snd", snd_IsVAGStreamBuffered_CB);

INCLUDE_ASM(const s32, "P2/989snd", snd_StreamSafeCheckCDIdle);

INCLUDE_ASM(const s32, "P2/989snd", snd_StreamSafeCdRead);

INCLUDE_ASM(const s32, "P2/989snd", snd_StreamSafeCdSync);

INCLUDE_ASM(const s32, "P2/989snd", snd_StreamSafeCdBreak);

INCLUDE_ASM(const s32, "P2/989snd", snd_StreamSafeCdGetError);

INCLUDE_ASM(const s32, "P2/989snd", snd_SetReverbType);

INCLUDE_ASM(const s32, "P2/989snd", snd_SetReverbDepth);

INCLUDE_ASM(const s32, "P2/989snd", snd_PreAllocReverbWorkArea);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011e3d8);

INCLUDE_ASM(const s32, "P2/989snd", snd_InitMovieSound);

INCLUDE_ASM(const s32, "P2/989snd", snd_ResetMovieSound);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011e488);

INCLUDE_ASM(const s32, "P2/989snd", snd_CloseMovieSound);

INCLUDE_ASM(const s32, "P2/989snd", snd_StartMovieSound);

INCLUDE_ASM(const s32, "P2/989snd", snd_GetTransStatus);

INCLUDE_ASM(const s32, "P2/989snd", junk_0x0011e520);

INCLUDE_ASM(const s32, "P2/989snd", snd_GetDopplerPitchMod);
