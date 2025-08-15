#include <sound.h>
#include <989snd.h>

INCLUDE_ASM(const s32, "P2/sound", UnloadMusic__Fv);

INCLUDE_ASM(const s32, "P2/sound", SbpEnsureBank__Fi);

INCLUDE_ASM(const s32, "P2/sound", SbpEnsureBank__F5SFXID);

INCLUDE_ASM(const s32, "P2/sound", NewSfx__FPP3SFX);

INCLUDE_ASM(const s32, "P2/sound", FContinuousSound__F5SFXID);

INCLUDE_ASM(const s32, "P2/sound", func_001BE5D8);

INCLUDE_ASM(const s32, "P2/sound", SetVagUnpaused__FUiUl);

INCLUDE_ASM(const s32, "P2/sound", PreloadVag__FPc2FK);

INCLUDE_ASM(const s32, "P2/sound", FUN_001be708);

INCLUDE_ASM(const s32, "P2/sound", PreloadVag1);

INCLUDE_ASM(const s32, "P2/sound", FPauseForVag__Fv);

INCLUDE_ASM(const s32, "P2/sound", RefreshPambVolPan__FP3AMB);

INCLUDE_ASM(const s32, "P2/sound", FUN_001be8f8);

INCLUDE_ASM(const s32, "P2/sound", FVagPlaying__Fv);

INCLUDE_ASM(const s32, "P2/sound", func_001BE990);

INCLUDE_ASM(const s32, "P2/sound", StopVag__Fv);

INCLUDE_ASM(const s32, "P2/sound", PauseVag__Fv);

INCLUDE_ASM(const s32, "P2/sound", ContinueVag__Fv);

INCLUDE_ASM(const s32, "P2/sound", KillMusic__Fv);

INCLUDE_ASM(const s32, "P2/sound", PreloadMusidSongComplete__FUiUl);

INCLUDE_ASM(const s32, "P2/sound", PreloadMusidSong__F5MUSID);

INCLUDE_ASM(const s32, "P2/sound", StartMusidSong__F5MUSID);

INCLUDE_ASM(const s32, "P2/sound", PauseMusic__Fv);

INCLUDE_ASM(const s32, "P2/sound", ContinueMusic__Fv);

INCLUDE_ASM(const s32, "P2/sound", SfxhMusicUnknown1);

INCLUDE_ASM(const s32, "P2/sound", SfxhMusicUnknown2);

INCLUDE_ASM(const s32, "P2/sound", PexcAlloc__Fv);

INCLUDE_ASM(const s32, "P2/sound", RemoveExc__FP3EXC);

INCLUDE_ASM(const s32, "P2/sound", KillExcitement__Fv);

INCLUDE_ASM(const s32, "P2/sound", PexcSetExcitement__Fi);

INCLUDE_ASM(const s32, "P2/sound", SetIexcCurHigh__FP3EXC);

INCLUDE_ASM(const s32, "P2/sound", UnsetExcitement__FP3EXC);

INCLUDE_ASM(const s32, "P2/sound", UnsetExcitementHyst__FP3EXC);

INCLUDE_ASM(const s32, "P2/sound", StartupSound__Fv);

INCLUDE_ASM(const s32, "P2/sound", func_001BF1E8);

INCLUDE_ASM(const s32, "P2/sound", FAmbientsPaused__Fv);

INCLUDE_ASM(const s32, "P2/sound", CalculateVolPan__FfP6VECTORPfT2fff);

INCLUDE_ASM(const s32, "P2/sound", func_001BF2E0);

INCLUDE_ASM(const s32, "P2/sound", func_001BF398);

INCLUDE_ASM(const s32, "P2/sound", PposEar__Fv);

INCLUDE_ASM(const s32, "P2/sound", SetDoppler__FP3AMB);

INCLUDE_ASM(const s32, "P2/sound", PfneardistGet__Fv);

INCLUDE_ASM(const s32, "P2/sound", SDistEar__FP6VECTOR);

INCLUDE_ASM(const s32, "P2/sound", CalculateDistVolPan__FP6VECTORPfT1fff);

INCLUDE_ASM(const s32, "P2/sound", PambAlloc__Fv);

INCLUDE_ASM(const s32, "P2/sound", DropPamb__FPP3AMB);

INCLUDE_ASM(const s32, "P2/sound", RemoveAmb__FP3AMB);

INCLUDE_ASM(const s32, "P2/sound", StopSound__FP3AMBi);

INCLUDE_ASM(const s32, "P2/sound", SetPambFrq__FP3AMBf);

INCLUDE_ASM(const s32, "P2/sound", SetPambVol__FP3AMBf);

INCLUDE_ASM(const s32, "P2/sound", FillPamb__FP3AMBPP3AMBiP3ALOP6VECTORfffffP2LMT10_);

INCLUDE_ASM(const s32, "P2/sound", ActivatePamb__FP3AMB5SFXID);

INCLUDE_ASM(const s32, "P2/sound", ScheduleNextIntermittentSound__FP3AMB);

INCLUDE_ASM(const s32, "P2/sound", StartSound__F5SFXIDPP3AMBP3ALOP6VECTORfffffP2LMT9);

INCLUDE_ASM(const s32, "P2/sound", func_001BFFC8);

INCLUDE_ASM(const s32, "P2/sound", HandleWipeHandleWipeVolumes__FifVolumes);

INCLUDE_ASM(const s32, "P2/sound", UpdateSounds__Fv);

void SetMvgkUvol(float uvol)
{
    snd_SetMasterVolume(8, (int)(uvol * 1024.0f));
}

INCLUDE_ASM(const s32, "P2/sound", MvgkUnknown1);

INCLUDE_ASM(const s32, "P2/sound", SetMvgkRvol__F4MVGKf);

INCLUDE_ASM(const s32, "P2/sound", MvgkUnknown2);

INCLUDE_ASM(const s32, "P2/sound", MvgkUnknown3);

INCLUDE_ASM(const s32, "P2/sound", MvgkUnknown4);

INCLUDE_ASM(const s32, "P2/sound", KillSoundSystem__Fv);

INCLUDE_ASM(const s32, "P2/sound", KillSounds__Fi);

INCLUDE_ASM(const s32, "P2/sound", PushSwReverb__FP2SW7REVERBKi);

INCLUDE_ASM(const s32, "P2/sound", PopSwReverb__FP2SW);

INCLUDE_ASM(const s32, "P2/sound", SetSwDefaultReverb__FP2SW7REVERBKi);

INCLUDE_ASM(const s32, "P2/sound", func_001C0A50);

INCLUDE_ASM(const s32, "P2/sound", func_001C0AB8);

INCLUDE_ASM(const s32, "P2/sound", func_001C0B08);

INCLUDE_ASM(const s32, "P2/sound", StartSwIntermittentSounds__FP2SW);

INCLUDE_ASM(const s32, "P2/sound", FUN_001c0c08);

INCLUDE_ASM(const s32, "P2/sound", FUN_001c0c50);

INCLUDE_ASM(const s32, "P2/sound", FUN_001c0c68);

INCLUDE_ASM(const s32, "P2/sound", FUN_001c0cb0);

INCLUDE_ASM(const s32, "P2/sound", HsNextFootFall__Fv);

INCLUDE_ASM(const s32, "P2/sound", NextSneakyFootstep__Fv);
