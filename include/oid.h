/**
 * @file oid.h
 *
 * @brief Object IDs.
 */
#ifndef OID_H
#define OID_H

#include "common.h"

/**
 * @brief Object ID.
 */
enum OID
{
    OID_Nil = -1,
    OID_Unknown = 0x0,
    OID__MERGED_STATICS = 0x1,
    OID__VISIBILITY_MAP = 0x2,
    OID__WORLD = 0x3,
    OID__CAMERA = 0x4,
    OID_jt = 0x5,
    OID_bentley = 0x6,
    OID_murray = 0x7,

    // ...

    OID_shd_stock_shadow = 0x2c,

    // ...

    OID_EF = 0xEF,

    // ...

    OID_rat = 0x269,

    // ...

    OID_16A = 0x16A,
    OID_16B = 0x16B,
    OID_16C = 0x16C,
    OID_16D = 0x16D,

    // ...

    OID_laser_sensor_render = 0x28a,
    OID_laser_damage_render = 0x28b,
    OID_camera_damage_render = 0x28c,
    OID_camera_zap_render = 0x28d,

    // ...

    OID_sm_ubb_world = 0x2d5,
    OID_sm_ubb_pad = 0x2d6,
    OID_state_ubb_challenge = 0x2d7,
    OID_state_ubb_round_0 = 0x2d8,
    OID_state_ubb_round_1 = 0x2d9,
    OID_state_ubb_round_2 = 0x2da,
    OID_state_ubb_round_3 = 0x2db,
    OID_state_ubb_round_4 = 0x2dc,
    OID_state_ubb_victory = 0x2dd,
    OID_state_ubb_up = 0x2de,
    OID_state_ubb_down = 0x2df,

    // ...

    OID_state_ubb_dunk = 0x2e0,
    OID_pad_root_0 = 0x2e1,
    OID_pad_root_1 = 0x2e2,
    OID_pad_root_2 = 0x2e3,
    OID_pad_root_3 = 0x2e4,
    OID_pad_root_4 = 0x2e5,
    OID_pad_root_5 = 0x2e6,
    OID_xfm_ubg_middle = 0x2e7,

    // ...

    OID_aseg_missile_fire = 0x317,

    // ...
};

#endif // OID_H
