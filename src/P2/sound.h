/**
 * @file sound.h
 *
 * @brief Declarations for the sound system.
*/
#ifndef SOUND_H
#define SOUND_H

#include <util.h>
#include <dl.h>
#include <alo.h>
#include <vec.h>

/**
 * @brief EASND
*/
struct EASND {
    uint16_t csfxid;
    uint16_t asfxid[6];
    uint16_t isfxidLast;
    uint16_t oid;
    int sFull;
    int sStop;
    float gPitch;
    float gDoppler;
    float gVolume;
};

struct sound {
    EASND* peasnd;
};

/**
 * @brief Sound Effect ID
*/
enum SFXID {
    SFXID_Nil = -1,
    SFXID_CaneHandleUnlock = 0,
    SFXID_AmbElectric = 1,
    SFXID_CaneHandleLock = 2,
    SFXID_EnvBreakable = 3,
    SFXID_CaneSmash = 4,
    SFXID_CaneWhack = 5,
    SFXID_EnvAlarmSounding = 6,
    SFXID_NpcFootstep = 7,
    SFXID_CaneHitGeneric = 8,
    SFXID_EnvDartsHit = 9,
    SFXID_EnvCaneReach = 10,
    SFXID_EnvCannonFire = 11,
    SFXID_EnvCricketChirp = 12,
    SFXID_EnvBreakSafe = 13,
    SFXID_NpcBigDirtLanding = 14,
    SFXID_EnvFuseBurn = 15,
    SFXID_EnvLaser = 16,
    SFXID_EnvGlassBreak = 17,
    SFXID_EnvLootExplode = 18,
    SFXID_EnvMissileExplode = 19,
    SFXID_EnvLaserHum = 20,
    SFXID_JtDeathPerm = 21,
    SFXID_JtFootfall1 = 22,
    SFXID_JtFootfall2 = 23,
    SFXID_JtFootfall3 = 24,
    SFXID_JtFootfall4 = 25,
    SFXID_JtDeathtmp = 26,
    SFXID_JtShimmy = 27,
    SFXID_JtHopInBarrel = 28,
    SFXID_JdHopOutBarrel = 29,
    SFXID_JtJump = 30,
    SFXID_JtMistake = 31,
    SFXID_JtWade2 = 32,
    SFXID_JtWade1 = 33,
    SFXID_JtWade3 = 34,
    SFXID_NpcBuzzingFlies = 35,
    SFXID_JtWade4 = 36,
    SFXID_NpcJump = 37,
    SFXID_NpcDiscover = 38,
    SFXID_NpcDoorOpen = 39,
    SFXID_NpcFlySplat = 40,
    SFXID_NpcRatSqueak1 = 41,
    SFXID_NpcRatSqueak2 = 42,
    SFXID_PrizeGold = 43,
    SFXID_NpcCroak = 44,
    SFXID_PrizeCheckpoint = 45,
    SFXID_PrizeLoot = 46,
    SFXID_PrizeOneup = 47,
    SFXID_PrizeTail = 48,
    SFXID_PrizeKey = 49,
    SFXID_EnvEzap = 50,
    SFXID_EnvSplash = 51,
    SFXID_EnvExplode = 52,
    SFXID_CaneReach = 53,
    SFXID_NpcDeathExplode = 54,
    SFXID_MiscHaha = 55,
    SFXID_UiBinocAmbient = 56,
    SFXID_CaneDive = 57,
    SFXID_UiBinocZoom = 58,
    SFXID_UiTick = 59,
    SFXID_UiTock = 60,
    SFXID_JtDoublejump = 61,
    SFXID_UiCoin = 62,
    SFXID_JtSwim1 = 63,
    SFXID_JtSwim2 = 64,
    SFXID_JtSwim3 = 65,
    SFXID_EnvDrum = 66,
    SFXID_PrizeCheckpointSmile = 67,
    SFXID_PrizeCheckpointGiggle = 68,
    SFXID_UiHorseshoeCollect = 69,
    SFXID_UiHorseshoeBounce = 70,
    SFXID_UiHorseshoeSpin = 71,
    SFXID_RegularSwitch = 72,
    SFXID_MenuSelect = 73,
    SFXID_MenuMove = 74,
    SFXID_MenuUnavail = 75,
    SFXID_TimerExpires = 76,
    SFXID_BombExplode = 77,
    SFXID_JtOnEdge = 78,
    SFXID_PercXylophone = 79,
    SFXID_CameraButton = 80,
    SFXID_RipVehicleMove = 81,
    SFXID_RipTurretFire = 82,
    SFXID_RipShoot = 83,
    SFXID_RipDoorOpen = 84,
    SFXID_RipBulletHit = 85,
    SFXID_RipCrabEscape = 86,
    SFXID_EnvHololoop = 87,
    SFXID_UiTeleportOut = 88,
    SFXID_UiTeleportIn = 89,
    SFXID_CaneRubberGrab = 90,
    SFXID_CaneRubberRelease = 91,
    SFXID_JtScorch = 92,
    SFXID_EnvVaultOpen = 93,
    SFXID_EnvHololoopElectronic = 94,
    SFXID_EnvKeyThrowLock = 95,
    SFXID_JtZapFire = 96,
    SFXID_JtZapElectric = 97,
    SFXID_JtExertionJump1 = 98,
    SFXID_JtZapWater = 99,
    SFXID_JtZapWater2 = 100,
    SFXID_JtZapWater3 = 101,
    SFXID_JtEdgeCatch1 = 102,
    SFXID_JtEdgeCatch2 = 103,
    SFXID_JtEdgeCatch3 = 104,
    SFXID_JtZapPit = 105,
    SFXID_JtZapCrush = 106,
    SFXID_EnvVaultWheel = 107,
    SFXID_EnvVaultClank = 108,
    SFXID_EnvVaultCreak = 109,
    SFXID_EnvDiamondShrink = 110,
    SFXID_EnvVaultDial = 111,
    SFXID_EnvBreakableBush = 112,
    SFXID_CaneRopeGrab = 113,
    SFXID_CaneRopeRelease = 114,
    SFXID_EnvBreakableRock = 115,
    SFXID_EnvBreakableMetal = 116,
    SFXID_EnvBreakableBook = 117,
    SFXID_EnvFlashbulb = 118,
    SFXID_UiGuitLow = 119,
    SFXID_EnvDartgunFire1 = 120,
    SFXID_EnvDartgunDestroy = 121,
    SFXID_EnvTeleport = 122,
    SFXID_EnvSteamHissLow = 123,
    SFXID_EnvDrip3 = 124,
    SFXID_EnvFireLoop = 125,
    SFXID_NpcCarmelitaFire = 126,
    SFXID_NpcCarmelitaWeaponImpact = 127,
    SFXID_NpcCarmelitaMissileLoop = 128,
    SFXID_JtCharmRelease = 129,
    SFXID_JtCharmBurst = 130,
    SFXID_Snd47 = 131,
    SFXID_Snd48 = 132,
    SFXID_Snd49 = 133,
    SFXID_Snd50 = 134,
    SFXID_Snd51 = 135,
    SFXID_Snd52 = 136,
    SFXID_Snd53 = 137,
    SFXID_Snd54 = 138,
    SFXID_Snd55 = 139,
    SFXID_Snd56 = 140,
    SFXID_Snd57 = 141,
    SFXID_EnvWallBreak1_Intro = 142,
    SFXID_EnvTrashcanBreak_Intro = 143,
    SFXID_EnvAwningBounce_Intro = 144,
    SFXID_EnvCasinoSliderClose_Intro = 145,
    SFXID_EnvCasinoSliderOpen_Intro = 146,
    SFXID_EnvMetalGateCreak_Intro = 147,
    SFXID_EnvMetalGateOpen_Intro = 148,
    SFXID_EnvDesertWindLoop_Intro = 149,
    SFXID_EnvRotatingMetal_Intro = 150,
    SFXID_EnvMetalGateUnlatch_Intro = 151,
    SFXID_EnvEuroSiren1_Intro = 152,
    SFXID_NpcEuroSirenWav_Intro = 153,
    SFXID_EnvDogLoop_Intro = 154,
    SFXID_EnvDogDistantChild1_Intro = 155,
    SFXID_EnvDogDistantChild2_Intro = 156,
    SFXID_EnvDogDistantChild3_Intro = 157,
    SFXID_EnvRandomBrickFall_Intro = 158,
    SFXID_EnvElevOuterOpen_Intro = 159,
    SFXID_EnvElevOuterClose_Intro = 160,
    SFXID_EnvElevInnerDoorOpen_Intro = 161,
    SFXID_EnvElevInnerDoorClose_Intro = 162,
    SFXID_EnvGrateBreak_Intro = 163,
    SFXID_EnvTollgateBreak_Intro = 164,
    SFXID_EnvFlagflap1_Intro = 165,
    SFXID_EnvFlagflap2_Intro = 166,
    SFXID_EnvFlagflap3Loop_Intro = 167,
    SFXID_EnvIntroExtLoop_Intro = 168,
    SFXID_EnvScaffoldDestroy_Intro = 169,
    SFXID_EnvCarDestroy_Intro = 170,
    SFXID_EnvTurbine_Intro = 171,
    SFXID_EnvPlaygroundPumpLoop_Intro = 172,
    SFXID_EnvHydraulicLoop_Intro = 173,
    SFXID_EnvVanPeelOut_Intro = 174,
    SFXID_EnvVanDoorOpen_Intro = 175,
    SFXID_EnvVanDoorClose_Intro = 176,
    SFXID_Snd01_Intro = 177,
    SFXID_Snd02_Intro = 178,
    SFXID_Snd03_Intro = 179,
    SFXID_Snd04_Intro = 180,
    SFXID_Snd05_Intro = 181,
    SFXID_Snd06_Intro = 182,
    SFXID_Snd07_Intro = 183,
    SFXID_NpcSquidIdle_Underwater = 184,
    SFXID_EnvElevator_Underwater = 185,
    SFXID_NpcSquidShoot_Underwater = 186,
    SFXID_EnvGrate_Underwater = 187,
    SFXID_NpcSquidDeath_Underwater = 188,
    SFXID_EnvMachinery_Underwater = 189,
    SFXID_EnvRubberHoops_Underwater = 190,
    SFXID_Empty1_Underwater = 191,
    SFXID_Empty2_Underwater = 192,
    SFXID_EnvSwitch_Underwater = 193,
    SFXID_EnvUpDownPlatform_Underwater = 194,
    SFXID_EnvUpDownPlatformStop_Underwater = 195,
    SFXID_EnvSteam_Underwater = 196,
    SFXID_NpcFrooah_Underwater = 197,
    SFXID_RipBubbles_Underwater = 198,
    SFXID_WlrsDieFront_Underwater = 199,
    SFXID_NpcHammerAttack_Underwater = 200,
    SFXID_EnvGenerator_Underwater = 201,
    SFXID_EnvTorch_Underwater = 202,
    SFXID_NpcThrowStar_Underwater = 203,
    SFXID_NpcTorchBlow_Underwater = 204,
    SFXID_AmbWaterfall_Underwater = 205,
    SFXID_EnvSingleGull_Underwater = 206,
    SFXID_EnvGullGroup_Underwater = 207,
    SFXID_EnvFogblast_Underwater = 208,
    SFXID_EnvRainOld_Underwater = 209,
    SFXID_EnvThunder_Underwater = 210,
    SFXID_EnvCreak1_Underwater = 211,
    SFXID_EnvCreak2_Underwater = 212,
    SFXID_EnvCreak3_Underwater = 213,
    SFXID_EnvWhistleSteam_Underwater = 214,
    SFXID_EnvWhistleToots_Underwater = 215,
    SFXID_EnvEngineRumble_Underwater = 216,
    SFXID_EnvGearClicking_Underwater = 217,
    SFXID_EnvBouy_Underwater = 218,
    SFXID_EnvBubble1_Underwater = 219,
    SFXID_EnvBubble2_Underwater = 220,
    SFXID_EnvBubble3_Underwater = 221,
    SFXID_EnvBubble4_Underwater = 222,
    SFXID_EnvEngineDeep_Underwater = 223,
    SFXID_EnvTurbine_Underwater = 224,
    SFXID_EnvFireBurst_Underwater = 225,
    SFXID_EnvFeetShuffling_Underwater = 226,
    SFXID_EnvPaper1_Underwater = 227,
    SFXID_EnvPaper2_Underwater = 228,
    SFXID_EnvPaper3_Underwater = 229,
    SFXID_EnvWaterSloshing1_Underwater = 230,
    SFXID_EnvWaterSloshing2_Underwater = 231,
    SFXID_EnvDrip1_Underwater = 232,
    SFXID_EnvDrip2_Underwater = 233,
    SFXID_EnvDrip3_Underwater = 234,
    SFXID_NpcDeathMwoah_Underwater = 235,
    SFXID_NpcLaugh_Underwater = 236,
    SFXID_NpcWeld_Underwater = 237,
    SFXID_NpcBelch_Underwater = 238,
    SFXID_EnvRainOnRoof_Underwater = 239,
    SFXID_NpcSquidHock_Underwater = 240,
    SFXID_NpcSquidSpit_Underwater = 241,
    SFXID_NpcSquidSpitSplat_Underwater = 242,
    SFXID_NpcWalrusGrowl_Underwater = 243,
    SFXID_BoatCreak1_Underwater = 244,
    SFXID_BoatCreak2_Underwater = 245,
    SFXID_EnvHamsterWheel_Underwater = 246,
    SFXID_NpcCrabAttackR_Underwater = 247,
    SFXID_EnvHooksMoving_Underwater = 248,
    SFXID_EnvRotatingMetal_Underwater = 249,
    SFXID_EnvGate_Underwater = 250,
    SFXID_NpcSquidHock1_Underwater = 251,
    SFXID_NpcSquidHock2_Underwater = 252,
    SFXID_NpcSquidDeathBoyd_Underwater = 253,
    SFXID_NpcSquidFootfall1_Underwater = 254,
    SFXID_NpcSquidFootfall2_Underwater = 255,
    SFXID_NpcWalrusTauntHammer1_Underwater = 256,
    SFXID_NpcWalrusDeathvox_Underwater = 257,
    SFXID_EnvHammerImpact1_Underwater = 258,
    SFXID_NpcWelderTorch1_Underwater = 259,
    SFXID_NpcWalrusTauntBurp1_Underwater = 260,
    SFXID_NpcWalrusAttackStar1_Underwater = 261,
    SFXID_NpcWalrusTauntLaugh4_Underwater = 262,
    SFXID_NpcWalrusAttackFlopJump_Underwater = 263,
    SFXID_NpcWalrusAttackFlopLand_Underwater = 264,
    SFXID_NpcWalrusInhale3_Underwater = 265,
    SFXID_NpcWalrusAttackHamA_Underwater = 266,
    SFXID_NpcWalrusAttackHamB_Underwater = 267,
    SFXID_NpcWalrusFlopImpact_Underwater = 268,
    SFXID_NpcWalrusStarTwirl_Underwater = 269,
    SFXID_NpcWalrusStarBuzz_Underwater = 270,
    SFXID_EnvDrip1Loop_Underwater = 271,
    SFXID_EnvDrip2Loop_Underwater = 272,
    SFXID_EnvDrip3Loop_Underwater = 273,
    SFXID_NpcHammerGrunt_Underwater = 274,
    SFXID_EnvRandomDripsLoop_Underwater = 275,
    SFXID_EnvElecGenLoop_Underwater = 276,
    SFXID_EnvRainLoop_Underwater = 277,
    SFXID_EnvSkulldoorOpen_Underwater = 278,
    SFXID_EnvSkulldoorClose_Underwater = 279,
    SFXID_EnvVandrop_Underwater = 280,
    SFXID_EnvCrankshaftBlade_Underwater = 281,
    SFXID_EnvCrankshaftPumpLoop_Underwater = 282,
    SFXID_EnvHydraulicUp_Underwater = 283,
    SFXID_EnvHydraulicDown_Underwater = 284,
    SFXID_EnvMetalDoorOpen_Underwater = 285,
    SFXID_Snd15_Underwater = 286,
    SFXID_Snd16_Underwater = 287,
    SFXID_Snd17_Underwater = 288,
    SFXID_EnvElevator_Muggshot = 289,
    SFXID_AmbWaterfall_Muggshot = 290,
    SFXID_EnvCoin1_Muggshot = 291,
    SFXID_EnvCrowdNoise_Muggshot = 292,
    SFXID_EnvCoin2_Muggshot = 293,
    SFXID_EnvChips1_Muggshot = 294,
    SFXID_EnvDogBark_Muggshot = 295,
    SFXID_EnvChips2_Muggshot = 296,
    SFXID_EnvSlotHandle_Muggshot = 297,
    SFXID_EnvCardsDeal_Muggshot = 298,
    SFXID_EnvCardsShuffle_Muggshot = 299,
    SFXID_EnvRouletteWheel_Muggshot = 300,
    SFXID_EnvSlotBeep1_Muggshot = 301,
    SFXID_EnvSlotBeep2_Muggshot = 302,
    SFXID_EnvSlotBeep3_Muggshot = 303,
    SFXID_EnvFountainSmall_Muggshot = 304,
    SFXID_EnvTraffic_Muggshot = 305,
    SFXID_EnvCarHorn_Muggshot = 306,
    SFXID_EnvSiren_Muggshot = 307,
    SFXID_EnvTruck_Muggshot = 308,
    SFXID_EnvRotatingMetal_Muggshot = 309,
    SFXID_NpcDeathDoberman1_Muggshot = 310,
    SFXID_NpcDeathDoberman2_Muggshot = 311,
    SFXID_NpcDobermanGrowl_Muggshot = 312,
    SFXID_NpcDobermanShout_Muggshot = 313,
    SFXID_NpcGunClick_Muggshot = 314,
    SFXID_NpcMachinegun_Muggshot = 315,
    SFXID_NpcDobermanHowl_Muggshot = 316,
    SFXID_EnvRubberHoops_Muggshot = 317,
    SFXID_EnvDrip3_Muggshot = 318,
    SFXID_EnvTurbine_Muggshot = 319,
    SFXID_WlrsDieFront_Muggshot = 320,
    SFXID_EnvWaterSloshing1_Muggshot = 321,
    SFXID_EnvUpDownPlatformStop_Muggshot = 322,
    SFXID_NpcLouBonk_Muggshot = 323,
    SFXID_NpcLouIdleWhack_Muggshot = 324,
    SFXID_NpcLouAttack_Muggshot = 325,
    SFXID_NpcDogScratch_Muggshot = 326,
    SFXID_NpcLouDoh_Muggshot = 327,
    SFXID_NpcLouScratchSigh1_Muggshot = 328,
    SFXID_NpcLouScratchSigh2_Muggshot = 329,
    SFXID_NpcLouDeath_Muggshot = 330,
    SFXID_EnvTorch_Muggshot = 331,
    SFXID_NpcCardShuffleLong2_Muggshot = 332,
    SFXID_NpcDogGrowl2_Muggshot = 333,
    SFXID_NpcDogDeath2_Muggshot = 334,
    SFXID_NpcDogScratch4_Muggshot = 335,
    SFXID_NpcDogChoke1_Muggshot = 336,
    SFXID_NpcDogDoh3_Muggshot = 337,
    SFXID_NpcDogBark6_Muggshot = 338,
    SFXID_NpcDogAttackExertion4_Muggshot = 339,
    SFXID_NpcDobExhale05_Muggshot = 340,
    SFXID_NpcDeckCutUp2_Muggshot = 341,
    SFXID_NpcDeckCutDwn1_Muggshot = 342,
    SFXID_NpcCardThrowShort5_Muggshot = 343,
    SFXID_NpcDogHowl1_Muggshot = 344,
    SFXID_NpcDogRushTaunt_Muggshot = 345,
    SFXID_NpcClubToss1_Muggshot = 346,
    SFXID_EnvCrusherImp1_Muggshot = 347,
    SFXID_EnvCarEngine1_Muggshot = 348,
    SFXID_NpcJailSwing_Muggshot = 349,
    SFXID_EnvCarSkid_Muggshot = 350,
    SFXID_EnvDesertWindLoop_Muggshot = 351,
    SFXID_EnvMetalGateOpen_Muggshot = 352,
    SFXID_EnvMetalGateCreak_Muggshot = 353,
    SFXID_EnvMetalGateUnlatch_Muggshot = 354,
    SFXID_EnvCasinoSliderOpen_Muggshot = 355,
    SFXID_EnvCasinoSliderClose_Muggshot = 356,
    SFXID_EnvBirdiesLoop_Muggshot = 357,
    SFXID_EnvWallBreak1_Muggshot = 358,
    SFXID_EnvTrashcanBreak_Muggshot = 359,
    SFXID_EnvRaceIdle_Muggshot = 360,
    SFXID_EnvRaceRunning_Muggshot = 361,
    SFXID_EnvRaceMurrayIdle_Muggshot = 362,
    SFXID_EnvRaceMurrayRevving_Muggshot = 363,
    SFXID_EnvSalsa_Muggshot = 364,
    SFXID_SndRaceCarBoost_Muggshot = 365,
    SFXID_EnvAwningBounce_Muggshot = 366,
    SFXID_EnvMetalCreak_Muggshot = 367,
    SFXID_EnvBigGlassBreak_Muggshot = 368,
    SFXID_EnvSniperFire_Muggshot = 369,
    SFXID_EnvVandropMs_Muggshot = 370,
    SFXID_EnvSkylightBreak_Muggshot = 371,
    SFXID_EnvWallBall_Muggshot = 372,
    SFXID_EnvGrateBreak_Muggshot = 373,
    SFXID_EnvSniperImpact_Muggshot = 374,
    SFXID_Snd03_Muggshot = 375,
    SFXID_Snd04_Muggshot = 376,
    SFXID_Snd05_Muggshot = 377,
    SFXID_Snd06_Muggshot = 378,
    SFXID_Snd07_Muggshot = 379,
    SFXID_Snd08_Muggshot = 380,
    SFXID_Snd09_Muggshot = 381,
    SFXID_Snd10_Muggshot = 382,
    SFXID_Snd11_Muggshot = 383,
    SFXID_Snd12_Muggshot = 384,
    SFXID_EnvBubble1_Voodoo = 385,
    SFXID_EnvBubble2_Voodoo = 386,
    SFXID_EnvBubble3_Voodoo = 387,
    SFXID_EnvChips1_Voodoo = 388,
    SFXID_EnvSwitch_Voodoo = 389,
    SFXID_EnvDrip3_Voodoo = 390,
    SFXID_EnvGenerator_Voodoo = 391,
    SFXID_NpcGhostDeath_Voodoo = 392,
    SFXID_NpcGhostMoan_Voodoo = 393,
    SFXID_NpcMosquitoBuzz_Voodoo = 394,
    SFXID_NpcMosquitoSuck_Voodoo = 395,
    SFXID_NpcMosquitoDeath_Voodoo = 396,
    SFXID_NpcMosquitoGag_Voodoo = 397,
    SFXID_NpcMosquitoSpew_Voodoo = 398,
    SFXID_NpcTurtleCower_Voodoo = 399,
    SFXID_NpcTurtleDeath_Voodoo = 400,
    SFXID_NpcTurtleBall_Voodoo = 401,
    SFXID_NpcTurtleSizzleLoop_Voodoo = 402,
    SFXID_EnvSwampLoop_Voodoo = 403,
    SFXID_EnvSwampThing2_Voodoo = 404,
    SFXID_EnvSwampThing1_Voodoo = 405,
    SFXID_EnvSwampThing3_Voodoo = 406,
    SFXID_EnvSwampThing4_Voodoo = 407,
    SFXID_NpcWeasleyWalkLeft_Voodoo = 408,
    SFXID_NpcWeasleyWalkRight_Voodoo = 409,
    SFXID_NpcWeasleyLooking_Voodoo = 410,
    SFXID_NpcWeasleyLaugh_Voodoo = 411,
    SFXID_NpcWeasleyGolf_Voodoo = 412,
    SFXID_NpcWeasleyAttackVox_Voodoo = 413,
    SFXID_NpcWeasleyDeath1_Voodoo = 414,
    SFXID_NpcWeasleLaunch_Voodoo = 415,
    SFXID_NpcWeasleyWheeze_Voodoo = 416,
    SFXID_NpcSpiderDrop_Voodoo = 417,
    SFXID_NpcSpiderDeath_Voodoo = 418,
    SFXID_NpcSpiderChomp_Voodoo = 419,
    SFXID_EnvFireLoop_Voodoo = 420,
    SFXID_NpcFireTwinLoop_Voodoo = 421,
    SFXID_Snd1_Voodoo = 422,
    SFXID_Snd2_Voodoo = 423,
    SFXID_Snd3_Voodoo = 424,
    SFXID_Snd4_Voodoo = 425,
    SFXID_Snd5_Voodoo = 426,
    SFXID_Snd6_Voodoo = 427,
    SFXID_Snd7_Voodoo = 428,
    SFXID_Snd8_Voodoo = 429,
    SFXID_Snd9_Voodoo = 430,
    SFXID_Snd10_Voodoo = 431,
    SFXID_Snd11_Voodoo = 432,
    SFXID_Snd12_Voodoo = 433,
    SFXID_Snd13_Voodoo = 434,
    SFXID_Snd14_Voodoo = 435,
    SFXID_Snd15_Voodoo = 436,
    SFXID_Snd01_Clockwerk = 437,
    SFXID_Snd02_Clockwerk = 438,
    SFXID_Snd03_Clockwerk = 439,
    SFXID_Snd04_Clockwerk = 440,
    SFXID_Snd05_Clockwerk = 441,
    SFXID_Snd06_Clockwerk = 442,
    SFXID_Snd07_Clockwerk = 443,
    SFXID_Snd08_Clockwerk = 444,
    SFXID_Snd09_Clockwerk = 445,
    SFXID_Snd10_Clockwerk = 446,
    SFXID_Max = 447
};

/**
 * @brief ??? Kind
 *
 * Categorizes sound effects into groups.
*/
enum MVGK {
    MVGK_Nil = -1,
    MVGK_Effects = 0,
    MVGK_Music = 1,
    MVGK_Dialog = 2,
    MVGK_User1 = 3,
    MVGK_User2 = 4,
    MVGK_User3 = 5,
    MVGK_User4 = 6,
    MVGK_External = 7,
    MVGK_Global = 8,
    MVGK_Max = 9
};

/**
 * @brief ??? Unknown
 *
 * @todo Figure out what this is.
*/
struct ISI {
    enum SFXID sfxid;
    struct LM lmRepeat;
    struct LM lmRepDist;
};

/**
 * @brief ??? Unknown
 *
 * @todo Figure out what this is.
*/
struct AMB
{
    // ...
};

/**
 * @brief Starts playing a sound effect.
 *
 * @param sfxid Sound effect ID
 * @param ppamb ??? Unknown
 * @param palo ??? Unknown
 * @param ppos Position vector
 * @param sStart ??? Unknown
 * @param sFull ??? Unknown
 * @param uVolAtSource Volume at source
 * @param frq Frequency
 * @param uDoppler Doppler effect
 * @param plmRepeat ??? Unknown
 * @param plmRepDis ??? Unknown
 *
 * @todo Figure out what the ppamb and palo parameters are.
 * @todo Figure out what the sStart and sFull parameters are.
 * @todo Figure out what the plmRepeat and plmRepDis parameters are.
 * @todo Implement this function.
*/
void StartSound(SFXID sfxid, AMB **ppamb, ALO *palo, VECTOR *ppos, float sStart, float sFull, float uVolAtSource, float frq, float uDoppler, LM *plmRepeat, LM *plmRepDis);

#endif // SOUND_H
