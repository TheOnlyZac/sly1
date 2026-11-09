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
    JTS_Nil = -1,
    JTS_Stand = 0,
    JTS_Run = 1,
    JTS_Jump = 2,
    JTS_Zap = 3,
    JTS_Sidestep = 4,
    JTS_Hide = 5,
    JTS_Pipe = 6,
    JTS_Edge = 7,
    JTS_Celebrate = 8,
    JTS_Rush = 9,
    JTS_Puppet = 10,
    JTS_Peek = 11,
    JTS_Ball = 12,
    JTS_Max = 13
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
    JTBS_Zap_Water = 36,
    // ...
    JTBS_Unk_54 = 54,
    JTBS_Unk_55 = 55

};

/**
 * @brief JT Health State.
 */
enum JTHS
{
    JTHS_Nil = -1,
    JTHS_Normal = 0,
    JTHS_Damaged = 1,
    JTHS_Dead = 2,
    JTHS_Max = 3
};

/**
 * @brief JT cane state.
 *
 * @note Copied from May proto, may be outdated/out of order.
 */
enum JTCS
{
    // ...
};

/**
 * @brief JT hide kind?
 */
enum JTHK
{
    JTHK_Nil = -1,
    JTHK_Flatten = 0,
    JTHK_Duck = 1,
    JTHK_Basket = 2,
    JTHK_Nonchalant = 3,
    JTHK_Rail = 4,
    JTHK_Spire = 5,
    JTHK_Reach = 6,
    JTHK_Vault = 7,
    JTHK_Max = 8
};

/**
 * @brief JT pipe direction kind.
 */
enum JTPDK
{
    JTPDK_Nil = -1,
    JTPDK_Up = 0,
    JTPDK_Down = 1,
    JTPDK_Max = 2
};

/**
 * @class JT
 * @brief Jewel thief (AKA Sly Cooper).
 *
 * JT = "jewel thief" = codename for Sly.
 */
struct JT : public STEP
{
    /* 0x0720 */ // BLRUN ablrunRun[6];
    /* 0x0900 */ // ASEGBL *pasegblRun;

    STRUCT_PADDING(918);

    /* 0x1518 */ ALO *paloMine;

    STRUCT_PADDING(832);
    undefined2 padding1_extra;

    /* 0x2220 */ JTS jts;
    int unk_0x2224;
    /* 0x2228 */ JTBS jtbs;

    STRUCT_PADDING(328);
    undefined1 padding2_extra;

    /* 0x2750 */ int unk_0x2750;
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

/**
 * @brief Gets the torque constraint type for JT: free while zapped or in state 13, otherwise locked.
 *
 * @param pjt Pointer to JT instance.
 * @return Constraint type (CT).
 *
 * @note Meaning of state 13 (JTS_Max) is a guess; may be an invalid/sentinel state.
 */
CT CtTorqueJt(JT *pjt);

struct WKR;

/**
 * @brief Comparison function (qsort style) for two WKR entries by their sort value (gSort).
 *
 * @param pwkr0 First WKR.
 * @param pwkr1 Second WKR.
 * @return 1 if pwkr0 sorts greater than pwkr1, otherwise -1.
 */
int NCmpWkr(WKR *pwkr0, WKR *pwkr1);

struct ASEGA;

/**
 * @brief Puts JT into the puppet-related state: JTS_Peek (11) if an ASEGA is given, else JTS_Stand.
 *
 * @param pjt Pointer to JT instance.
 * @param pasega Animation segment (ASEGA) driving the puppet; may be null.
 *
 * @note Name is from the symbol; the exact semantics (JTS_Peek vs puppet) are inferred from the constant 11.
 */
void SetJtPuppet(JT *pjt, ASEGA *pasega);

/**
 * @brief Updates the previous world position of JT and clears the extra-bounds position count (0x21cc).
 *
 * @param pjt Pointer to JT instance.
 */
void UpdateJtPosWorldPrev(JT *pjt);

/**
 * @brief Updates the JT bounds, then extends them to cover each extra position (array at 0x21d0, count at 0x21cc).
 *
 * @param pjt Pointer to JT instance.
 *
 * @note The field layout of the extra positions is a guess.
 */
void UpdateJtBounds(JT *pjt);

/**
 * @brief Collects a prize; JT enters the rush state (key: attack, gold: bounce).
 *
 * @param pjt Pointer to JT instance.
 * @param pck Prize kind.
 * @param paloOther The object the prize came from.
 */
void CollectJtPrize(JT *pjt, PCK pck, ALO *paloOther);

/**
 * @brief Sets the field at 0x2bd8 to the given value and clears the field at 0x4b8.
 *
 * @param pjt Pointer to JT instance.
 * @param n Value stored at 0x2bd8.
 *
 * @note Name and meaning are unknown; purely mechanical description.
 */
void FUN_00177828(JT *pjt, int n);

struct PO;

/**
 * @brief Active-state handler for JT: forwards to OnPoActive, then sets the steppower to the last selected one (or Nil when inactive).
 *
 * @param pjt Pointer to JT instance.
 * @param fActive Whether JT became active.
 * @param ppoOther Other PO (passed through).
 *
 * @note Name is unknown (likely OnJtActive); the third parameter type is a guess.
 */
void FUN_00173708(JT *pjt, int fActive, PO *ppoOther);

/**
 * @brief Checks whether JT is currently in a state where the sound base applies (not a ball/electric zap, and the camera policy is inactive).
 *
 * @param pjt Pointer to JT instance.
 * @return Nonzero if the sound base condition holds.
 *
 * @note Meaning is a guess from the name and the checks performed.
 */
int FIsJtSoundBase(JT *pjt);

struct DIALOG;

/**
 * @brief Plays a dialog: pushes the binoculars blot for dialog kinds 1 and 2, otherwise requests a JT state change (state 12 / body state 0x21) carrying the dialog.
 *
 * @param pjt Pointer to JT instance.
 * @param pdialog Dialog to play.
 *
 * @note Fields at 0x2254..0x225c (pending state request) and 0x2bd0 (dialog) are unnamed guesses.
 */
void PlayJtDialog(JT *pjt, DIALOG *pdialog);

/**
 * @brief Applies pending JT state change requests (grfjtsc flags at 0x2254): state, cane state and a follow-up call.
 *
 * @param pjt Pointer to JT instance.
 *
 * @note The "grfjtsc" name is from the symbol; flag meanings are inferred.
 */
extern "C" void HandleJtGrfjtsc(JT *pjt);

/**
 * @brief Unhooks JT from a rail/pipe-like state and drops it into the jump/fall state.
 *
 * @param pjt Pointer to JT instance.
 *
 * @note Semantics inferred from the states handled (Zap, Pipe, Edge); may be inaccurate.
 */
void UnhookJt(JT *pjt);

struct CBinaryInputStream;

/**
 * @brief Loads JT from a BRX stream, snips its objects, infers its explosion and sets the global g_pjt.
 *
 * @param pjt Pointer to JT instance.
 * @param pbis Input stream.
 *
 * @note The snip table (D_00262E40) is declared as an unnamed extern.
 */
void LoadJtFromBrx(JT *pjt, CBinaryInputStream *pbis);

/**
 * @brief Resets JT extra-bound positions: stores the previous/current positions (0x21d0..0x21f0, count 3) and updates the bounds.
 *
 * @param pjt Pointer to JT instance.
 *
 * @note Name and meaning unknown; likely a pre-update step related to UpdateJtBounds. Purely a guess.
 */
void FUN_00172b08(JT *pjt);

extern JT *g_pjt;

#endif // JT_H
