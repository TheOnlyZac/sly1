/**
 * @file jt.h
 *
 * @brief Sly entity.
 */
#ifndef JT_H
#define JT_H

#include "common.h"
#include <step.h>

/**
 * JT state.
 *
 * @note Based on May proto, may be inaccurate.
 */
enum JTS
{
    JTS_Stand = 0,
    JTS_Run = 1,
    JTS_Jump = 2,
    JTS_Hang = 3,
    JTS_Zap = 4,
    JTS_Sidestep = 5,
    JTS_Hide = 6,
    JTS_Pipe = 7,
    JTS_Edge = 8,
    JTS_Celebrate = 9,
    JTS_Rush = 10,
    JTS_Puppet = 11,
    JTS_Peek = 12,
    JTS_Ski = 13,
    JTS_Ball = 14,
    JTS_Max = 15
};

/**
 * JT body state.
 *
 * @note Based on May proto, may be inaccurate.
 */
enum JTBS
{
    JTBS_Nil = -1,
    JTBS_Jump_Init = 0,
    JTBS_Jump_Rise = 1,
    JTBS_Jump_Fall = 2,
    JTBS_Jump_Boost = 3,
    JTBS_Jump_In = 4,
    JTBS_Jump_Out = 5,
    JTBS_Jump_Thrown = 6,
    JTBS_Jump_Smash = 7,
    JTBS_Jump_Dive = 8,
    JTBS_Jump_Target = 9,
    JTBS_Jump_Spire = 10,
    JTBS_Jump_Rail = 11,
    JTBS_Jump_Hshape = 12,
    JTBS_Jump_Hpnt = 13,
    JTBS_Hide_Stand = 14,
    JTBS_Hide_Sidestep = 15,
    JTBS_Hide_PeekLeft = 16,
    JTBS_Hide_PeekRight = 17,
    JTBS_Hide_Run = 18,
    JTBS_Hide_Spin = 19,
    JTBS_Pipe_Init = 20,
    JTBS_Pipe_Stay = 21,
    JTBS_Pipe_Up = 22,
    JTBS_Pipe_Down = 23,
    JTBS_Pipe_Spin = 24,
    JTBS_Celebrate_Key = 25,
    JTBS_Celebrate_Timed = 26,
    JTBS_Celebrate_UseKey = 27,
    JTBS_Rush_Attack = 28,
    JTBS_Rush_Bounce = 29,
    JTBS_Peek_Enter = 30,
    JTBS_Peek_Peek = 31,
    JTBS_Peek_Exit = 32,
    JTBS_Zap_Blunt = 33,
    JTBS_Zap_Electric = 34,
    JTBS_Zap_Fire = 35,
    JTBS_Zap_Water = 36
};

/**
 * JT cane state.
 *
 * @note Copied from May proto, may be outdated/out of order.
 */
enum JTCS
{
    // ...
};

/**
 * @brief Sly entity.
 *
 * JT = "jewel thief" = codename for Sly.
 *
 * @todo Match all structs it inherits from.
 */
struct JT : public STEP
{
    uchar padding[0x1248];
    LO *ploMine_1518;
    uchar padding2[0xd03];
    int unk2220;
    uchar padding3[0x52c];
    int unk2750;
};

/**
 * @brief Sets the JT state and JT body state on the given JT.
 *
 * @param pjt Pointer to the JT instance.
 * @param jts JT state value
 * @param JTBS JT body state value
 */
void SetJtJts(JT *pjt, JTS jts, JTBS jtbs);

/**
 * @brief Stubbed, does nothing.
 *
 * @param pjt Pointer to JT instance.
 * @param fProfile Profile flag.
 *
 * @deprecated
 */
void ProfileJt(JT *pjt, int fProfile);

extern JT *g_pjt;

#endif // JT_H
