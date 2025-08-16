#include "sound.h"
#include <989snd.h>
#include <sce/memset.h>

extern uchar D_00604790[]; // temp

/**
 * @brief Media volume float.
 */
struct MVG
{
    float vol; // Current volume
    MVGK mvgk; // Media volume float kind
    undefined4 unk2;
    undefined4 unk3;
};

extern MVG D_00274838[10]; // temp

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
#ifdef SKIP_ASM
void ContinueMusic()
{
    SetMvgkRvol(MVGK_Music, 1.0f);
}
#endif

INCLUDE_ASM(const s32, "P2/sound", SfxhMusicUnknown1);

INCLUDE_ASM(const s32, "P2/sound", SfxhMusicUnknown2);

INCLUDE_ASM(const s32, "P2/sound", PexcAlloc__Fv);

INCLUDE_ASM(const s32, "P2/sound", RemoveExc__FP3EXC);

INCLUDE_ASM(const s32, "P2/sound", KillExcitement__Fv);

INCLUDE_ASM(const s32, "P2/sound", PexcSetExcitement__Fi);

INCLUDE_ASM(const s32, "P2/sound", SetIexcCurHigh__FP3EXC);

INCLUDE_ASM(const s32, "P2/sound", UnsetExcitement__FP3EXC);

INCLUDE_ASM(const s32, "P2/sound", UnsetExcitementHyst__FP3EXC);

void StartupSound()
{
    memset(D_00604790, 0, 0x1c);
    snd_StartSoundSystem();
    SbpEnsureBank(0);
    snd_InitVAGStreamingEx(1, 0x2000, 1, 1);
    snd_SetGlobalExcite(0x14);
    MvgkUnknown2();
    snd_SetMixerMode(0, 1);
    snd_SetGroupVoiceRange(0, 0, 0x2f);
    snd_SetGroupVoiceRange(1, 0x18, 0x2f);
    snd_SetGroupVoiceRange(3, 0x18, 0x2f);
    snd_SetGroupVoiceRange(2, 0x18, 0x2f);
    snd_PreAllocReverbWorkArea(2, 4);
}
INCLUDE_ASM(const s32, "P2/sound", func_001BF1E8); // nop

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

INCLUDE_ASM(const s32, "P2/sound", MvgkUnknown1__F4MVGK);
#ifdef SKIP_ASM
/**
 * @todo This is a mess... but it matches 53.35% so I'll take it for now. -Zac
 */
void MvgkUnknown1(MVGK mvgk)
{
    float v = D_00274838[0].vol;
    for (int i = 1; i < 10; ++i)
    {
        float x = D_00274838[i].vol;
        if (x > v) v = x;
    }

    if (v > 1.0f) v = 1.0f;
    if (v < 0.0f) v = 0.0f;

    int ivol = (int)(v * 1024.0f);
    snd_SetMasterVolume(mvgk, ivol);
}
#endif

INCLUDE_ASM(const s32, "P2/sound", SetMvgkRvol__F4MVGKf);
#ifdef SKIP_ASM
/**
 * @todo 61.79% matching.
 */
void SetMvgkRvol(MVGK mvgk, float rvol)
{
    D_00274838[mvgk].vol = rvol;
    MvgkUnknown1(mvgk);
}
#endif

INCLUDE_ASM(const s32, "P2/sound", MvgkUnknown2__Fv);

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
