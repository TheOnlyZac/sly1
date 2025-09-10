/**
 * @file cid.h
 *
 * @brief Class IDs.
 */
#ifndef CID_H
#define CID_H

#include "common.h"

/**
 * @brief Class ID.
 *
 * @note Values are based on May 19 build so are likely incomplete and/or inaccurate.
 */
enum CID
{
    CID_Nil      = -1,  // None
    CID_BASIC    = 0,   // BASIC
    CID_LO       = 1,   // LO
    CID_ALO      = 2,   // LIGHTWEIGHT
    CID_SO       = 3,   // OBJECT
    CID_MS       = 4,   // MERGED_STATICS
    CID_PO       = 5,   // PO
    CID_STEP     = 6,   // STEP_FIGURE
    CID_JT       = 7,   // JT
    CID_STEPGUARD= 8,   // STEP_GUARD
    CID_SMARTGUARD=9,   // SMART_GUARD
    CID_GOMER    = 10,  // GOMER
    CID_UBG      = 11,  // UW_BOSS_GOMER
    CID_MBG      = 12,  // MS_BOSS_GUARD
    CID_BHG      = 13,  // BLOODHOUND
    CID_MURRAY   = 14,  // MURRAY
    CID_PUFFC    = 15,  // PUFFER_COLLECTION
    CID_CRFOD    = 16,  // CRUSHER_FODDER
    CID_CRFODB   = 17,  // CRUSHER_FODDER_BAIT
    CID_CRFODK   = 18,  // CRUSHER_FODDER_KAM
    CID_TANK     = 19,  // HOVER_TANK
    CID_JP       = 20,  // JET_PACK
    CID_HG       = 21,  // HANG_GLIDER
    CID_MECHA    = 22,  // MECHA
    CID_ROV      = 23,  // RIP_OFF_VEHICLE
    CID_TURRET   = 24,  // TURRET
    CID_VAULT    = 25,  // VAULT
    CID_PUFFER   = 26,  // PUFFER
    // CID_MGV      = 27,  // MOUTH_GAME_VEHICLE
    CID_SUV      = 28,  // SMASHUP_VEHICLE
    // CID_CYCLE    = 29,  // CYCLE
    CID_LGN      = 30,  // LIGHT_GUN
    CID_JACK     = 31,  // JACK_HAMMER
    CID_RIPG     = 32,  // RIPG
    CID_WATER    = 33,  // WATER
    CID_BRK      = 34,  // _BRK
    CID_BREAK    = 35,  // BREAKABLE
    CID_ALBRK    = 36,  // ALARM_BREAKABLE
    CID_CAN      = 37,  // CANNON
    CID_DARTGUN  = 38,  // DARTGUN
    CID_SWP      = 39,  // SWOOPER
    CID_FRAGILE  = 40,  // FRAGILE
    CID_ZAPBREAK = 41,  // ZAPBREAK
    CID_BRKP     = 42,  // BREAKABLE_PIECE
    CID_BUTTON   = 43,  // BUTTON
    CID_VOLBTN   = 44,  // VOL_BUTTON
    CID_JLOVOL   = 45,  // JLO_VOLUME
    CID_SQUISH   = 46,  // SQUISH
    CID_BONE     = 47,  // BONE
    CID_SPRIZE   = 48,  // _SPRIZE
    CID_SCPRIZE  = 49,  // _SCPRIZE
    CID_LIFETKN  = 50,  // EXTRA_LIFE_TOKEN
    CID_CLUE     = 51,  // CLUE
    CID_ALARM    = 52,  // ALARM
    CID_SENSOR   = 53,  // _SENSOR
    CID_LASEN    = 54,  // LASER_SENSOR
    CID_CAMSEN   = 55,  // CAMERA_SENSOR
    CID_PRSEN    = 56,  // PRESSURE_SENSOR
    CID_BARRIER  = 57,  // BARRIER
    CID_IKH      = 58,  // IK_HANDLE
    CID_TZP      = 59,  // TOUCH_ZAPPER
    CID_VOLZP    = 60,  // VOL_ZAPPER
    CID_CNVO     = 61,  // CONVEYOR
    CID_HBSK     = 62,  // HIDE_BASKET
    CID_BOMB     = 63,  // BOMB
    CID_MISSILE  = 64,  // MISSILE
    CID_ACCMISS  = 65,  // ACCEL_MISSILE
    CID_TARMISS  = 66,  // TARGET_MISSILE
    CID_SPLMISS  = 67,  // SPLINE_MISSILE
    CID_GROUNDMISS=68,  // GROUND_MISSILE
    CID_FLY      = 69,  // FLY
    CID_RAT      = 70,  // RAT
    CID_ROH      = 71,  // RIP_OFF_HARVESTER
    CID_ROC      = 72,  // RIP_OFF_COLLECTIBLE
    CID_ROST     = 73,  // RIP_OFF_SPAWN_TUNN
    CID_ROP      = 74,  // RIP_OFF_PRIZE
    CID_DART     = 75,  // DART
    CID_UBV      = 76,  // UW_BOSS_VEHICLE
    CID_UBP      = 77,  // UW_BOSS_PAD
    CID_DSP      = 78,  // OBJECT_DISPENSER
    CID_JLO      = 79,  // JLO
    CID_PUFFT    = 80,  // PUFFER_TORCH
    CID_MRKV     = 81,  // MURK_VOLUME
    CID_LGNB     = 82,  // LIGHT_GUN_BOSS
    CID_BLIPG    = 83,  // BLIPG
    CID_CAMERA   = 84,  // CAMERA
    CID_LBONE    = 85,  // LIGHTWEIGHT_BONE
    CID_EMITTER  = 86,  // EMITTER
    CID_LIGHT    = 87,  // LIGHT
    CID_SCH      = 88,  // SPLINE_CONSTRAINT_
    CID_LIKH     = 89,  // LIGHTWEIGHT_IK_HAN
    CID_CHKPNT   = 90,  // CHECK_POINT
    CID_PROXY    = 91,  // PROXY
    CID_SKY      = 92,  // SKY
    CID_DPRIZE   = 93,  // _DPRIZE
    CID_CHARM    = 94,  // CHARM
    CID_COIN     = 95,  // COIN
    CID_KEY      = 96,  // KEY
    CID_GOLD     = 97,  // GOLD
    CID_LOCK     = 98,  // LOCK
    CID_LOCKG    = 99,  // LOCK_GROUP
    CID_TAIL     = 100, // TAIL
    CID_ROB      = 101, // RIP_OFF_BRAIN
    CID_FLASH    = 102, // FLASHLIGHT
    CID_DYSH     = 103, // DYNAMIC_SHADOW
    CID_SCENTMAP = 104, // SCENT_MAP
    CID_WAYPOINT = 105, // WAY_POINT
    CID_TN       = 106, // NEW_TUNNEL
    CID_JLOC     = 107, // JLO_CLUSTER
    CID_DIALOG   = 108, // DIALOG
    CID_SPEAKER  = 109, // SPEAKER
    CID_ROPE     = 110, // ROPE
    CID_WM       = 111, // WORLD_MAP
    CID_PUFFB    = 112, // PUFFER_BRAIN
    CID_CRBRAIN  = 113, // CRUSHER_BRAIN
    // CID_MGC      = 114, // MOUTH_GAME_COLLECT
    CID_JACKB    = 115, // JACK_BOSS
    CID_JACKN    = 116, // JACK_NPC
    CID_JACKF    = 117, // JACK_FRAGMENT
    CID_SW       = 118, // WORLD
    CID_CM       = 119, // _CAMERA
    CID_SHAPE    = 120, // SHAPE
    CID_HSHAPE   = 121, // HIDE_SHAPE
    CID_PIPE     = 122, // PIPE
    CID_RAIL     = 123, // RAIL
    CID_LANDING  = 124, // LANDING
    CID_XFM      = 125, // TRANSFORM
    CID_WARP     = 126, // WARP
    CID_TARGET   = 127, // TARGET
    CID_HND      = 128, // HANDLE
    CID_EXPL     = 129, // _EXPLODE_BASE
    CID_EXPLG    = 130, // EXPLODE_GROUP
    CID_EXPLO    = 131, // BLACK_HOLE
    CID_EXPLS    = 132, // EXPLODE_STYLE
    CID_VOL      = 133, // VOLUME
    CID_RATHOLE  = 134, // RATHOLE
    CID_PUFFV    = 135, // PUFFER_VOLUME
    CID_EXIT     = 136, // EXIT
    CID_PNT      = 137, // POINT
    CID_PNTSV    = 138, // POINT_WITH_SPEED
    CID_PNTS     = 139, // POINT_WITH_DISTANCE
    CID_PNTVEC   = 140, // POINT_WITH_VECTOR
    CID_HPNT     = 141, // HIDE_POINT
    CID_JMT      = 142, // JUMP_TARGET
    CID_SPIRE    = 143, // SPIRE
    CID_SCAN     = 144, // SCAN_ITEM
    CID_ASEG     = 145, // ANIMATION_SEGMENT
    CID_ASEGBL   = 146, // ASEGBL
    CID_MAP      = 147, // MAP_2D
    CID__VISZONE = 148, // VISIBILITY_ZONE
    CID_VISMAP   = 149, // VISMAP
    CID_FRZG     = 150, // FREEZE_GROUP
    CID_SM       = 151, // STATE_MACHINE
    CID_SGG      = 152, // STEP_GUARD_GROUP
    CID_PATHZONE = 153, // PATH_ZONE
    CID_RCHM     = 154, // REACH_MAP
    CID_RWM      = 155, // AMMO_MANAGER
    CID_WR       = 156, // SPACE_WARP
    CID_KEYHOLE  = 157, // KEYHOLE
    CID_JSG      = 158, // SCRIPT
    CID_ASEGA    = 159, // ANIMATION_SEGMENT_APPLICATION
    CID_SMA      = 160, // STATE_MACHINE_APPLICATION
    CID__FCST    = 161, // FOSTER_CONSTRAINT
    CID_Max      = 162  // Max value
};

#endif // CID_H
