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

struct DZ;

/**
 * @brief JT override of AdjustStepDz. In the sidestep state with flag 0x10 set, clamps the DZ value at 0x30 to a speed-scaled limit; otherwise defers to AdjustStepDzBase.
 *
 * @param pjt Pointer to JT instance.
 * @param grfadj Adjust flags.
 * @param pdz Delta-Z (DZ) being adjusted.
 * @param ixpd XP index.
 * @param dt Frame delta time (unused).
 *
 * @note Field meanings (0x358/0x368 on JT, 0x30 on DZ) and the two float constants are unnamed guesses.
 */
void AdjustJtDz(JT *pjt, GRFADJ grfadj, DZ *pdz, int ixpd, float dt);

struct XP;

/**
 * @brief JT override of FCheckStepXpBase: in state 13 applies a custom check, otherwise defers to FCheckStepXpBase.
 *
 * @param pjt Pointer to JT instance.
 * @param pxp Contact (XP) to check.
 * @param ixpd XP index.
 * @return Nonzero if the XP passes the check.
 *
 * @note Semantics inferred from the asm only; state 13 (JTS_Max) and the XP fields at 0x88/0x9c are guesses.
 */
int FCheckJtXpBase(JT *pjt, XP *pxp, int ixpd);

/**
 * @brief Throws JT toward a target position: computes the muzzle velocity from a point 75 units below JT, applies it, and enters the thrown jump state.
 *
 * @param pjt Pointer to JT instance.
 * @param pposTarget Target position.
 * @param radVert Launch angle (radians) passed to FCalculateMuzzleVelocity.
 * @param gSpin Spin multiplier; zero also clears the field at 0x2498.
 *
 * @note Parameter meanings are inferred from the callee; the vtable call uses slot 0x90 (SetSoVelocityVec).
 */
void ThrowJt(JT *pjt, VECTOR *pposTarget, float radVert, float gSpin);

/**
 * @brief Updates the JT world transform, then runs the unnamed FUN_001c4618 step on two extremities (fields 0x610/0x614) unless JT is in a pipe/edge sub-state.
 *
 * @param pjt Pointer to JT instance.
 *
 * @note Name and meaning are unknown (possibly hands/feet limit update); purely a guess.
 */
void FUN_00172530(JT *pjt);

/**
 * @brief Enables or disables the JT ACTADJ objects (animation adjusters, pointers at 0x2500..0x2510) and notifies the five related objects via virtual call 0xbc.
 *
 * @param pjt Pointer to JT instance.
 * @param grfea Enable flags: bit 0 controls the first three adjusters, bit 1 the last two.
 *
 * @note Parameter name, the byte at +0x10 of each adjuster (9 = on, -1 = off) and the meaning of vcall 0xbc are guesses.
 */
void EnableJtActadj(JT *pjt, int grfea);

/**
 * @brief Updates the JT tool (cane) spin angle: advances it by the spin rate, or smooths it back to rest (2*pi wrap) when the rate is zero.
 *
 * @param pjt Pointer to JT instance.
 *
 * @note Field names/offsets (0x242c rate, 0x2430 smoothing state, 0x2434 angle) are guesses.
 */
void UpdateJtTool(JT *pjt);

/**
 * @brief Returns the first of JT effect objects (at 0x25d8, 0x25e0, 0x25dc, 0x25e4, 0x25e8) that is in the world, writing a small kind index to pn.
 *
 * @param pjt Pointer to JT instance.
 * @param pn Output kind index (0, 1 or 2).
 * @return The effect object pointer (as int), or 0 if none is in the world.
 *
 * @note Return type is really a pointer (likely SO *); kept as int to match. Semantics are guesses.
 */
int PsoGetJtEffect(JT *pjt, int *pn);

/**
 * @brief JT override of AdjustStepNewXp: sets the two floats at 0x94/0x98 on the new contact (XP) from state-dependent constants, then divides the first by a JT scale (0x700).
 *
 * @param pjt Pointer to JT instance.
 * @param pxp New contact (XP) to adjust.
 * @param ixpd XP index (unused).
 *
 * @note Field meanings of the XP floats and the constants are unknown; the vtable call at 0x168 is probably FCheckXpBase.
 */
void AdjustJtNewXp(JT *pjt, XP *pxp, int ixpd);

/**
 * @brief Chooses the physics object (SO pointer from the tables at 0x1390 / 0x13d4 / 0x1418) for the current JT state and applies it with SetStepPhys.
 *
 * @param pjt Pointer to JT instance.
 *
 * @note Table layout and the fallback chain (D_00263930) are inferred from the asm. In the sidestep case the original leaves the chosen
 * physics pointer uninitialised when the body state is -1; this is reproduced here.
 */
void ChooseJtPhys(JT *pjt);

struct XMG;
struct ACTADJ;
struct MATRIX3;

/**
 * @brief Calculates the tool (cane) spin matrix at the given angle; not yet matched, meaning inferred from the name.
 */
void CalculateJtToolSpin(JT *pjt, float rad, MATRIX3 *pmat);

/**
 * @brief Turns JT toward its target (field 0x2200 / 0x2208), updating the heading at 0x638.
 *
 * @param pjt Pointer to JT instance.
 * @return Nonzero if a target existed and the turn was applied.
 *
 * @note Not yet matched; meaning inferred from the asm.
 */
int FTurnJtToTarget(JT *pjt);

/**
 * @brief Rebuilds a JT XMG for one extremity (hand/foot?); not yet matched, parameter meanings are guesses.
 */
void RebuildJtXmg(JT *pjt, ALO *palo, float g, ALO *palo2, ACTADJ *pactadj, XMG *pxmg);

/**
 * @brief Checks whether a JT XMG matches an ACTADJ; not yet matched, meaning is a guess.
 */
int FMatchJtXmg(JT *pjt, XMG *pxmg, ACTADJ *pactadj);

/**
 * @brief Updates JT while standing: turns toward the target or follows the moving basis, rebuilds the two XMGs and, if they stop matching, seeks the SMA to its first frame (once).
 *
 * @param pjt Pointer to JT instance.
 *
 * @note Many fields (0x628/0x62c, 0x1188/0x118c, 0x2234) are unnamed; behaviour description is inferred from the asm.
 */
void UpdateJtStand(JT *pjt);

struct CM;
struct RO;

/**
 * @brief JT self render step (probably RenderJtSelf): refreshes the extremity XMGs, draws the spinning tool (cane) as four ghosted copies, then renders the step self, squeak trim and zap effect.
 *
 * @param pjt Pointer to JT instance.
 * @param pcm Camera.
 * @param pro Render options.
 *
 * @note Name is a guess/unknown. The tool object is at field 0x61c; its vtable slot 0xa0 is called with a copy of the RO whose alpha is quartered.
 */
void FUN_001725e0(JT *pjt, CM *pcm, RO *pro);

extern JT *g_pjt;

#endif // JT_H
