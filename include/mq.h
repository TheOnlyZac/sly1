/**
 * @file mq.h
 *
 * @brief Message queue(?)
 */
#ifndef MQ_H
#define MQ_H

#include "common.h"

/**
 * @brief Message ID
 *
 * @note Based on values from May 19, may not be accurate to release.
 */
enum MSGID
{
    MSGID_Nil = -1,
    MSGID_callback = 0,
    MSGID_added = 1,
    MSGID_removed = 2,
    MSGID_translated = 3,
    MSGID_rotated = 4,
    MSGID_asega_limit = 5,
    MSGID_asega_retracted = 6,
    MSGID_asega_wrapped = 7,
    MSGID_sfx_start = 8,
    MSGID_sfx_end = 9,
    MSGID_water_entered = 10,
    MSGID_water_left = 11,
    MSGID_button_trigger = 12,
    MSGID_button_untrigger = 13,
    MSGID_break_break = 14,
    MSGID_break_piece = 15,
    MSGID_rip_removed = 16,
    MSGID_color_change = 17,
    MSGID_user_message = 18,
    MSGID_label = 19,
    MSGID_sma_transition = 20,
    MSGID_waypoint = 21,
    MSGID_waypoint_transition = 22,
    MSGID_damaged = 23,
    MSGID_param_read = 24,
    MSGID_param_write = 25,
    MSGID_Max = 26
};

/**
 * @brief Message queue(?)
 */
struct MQ
{
    void *pfnmq;
    void *pvContext;
    MSGID msgid;
    void *pvCallbackData;
    MQ *pmqnext;
};

#endif // MQ_H
