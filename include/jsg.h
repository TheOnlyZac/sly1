/**
 * @brief jsg.h
 */
#ifndef JSG_H
#define JSG_H

#include "common.h"
#include <asega.h>
#include <oid.h>
#include <vec.h>
#include <lo.h>
#include <tn.h>
#include <jt.h>

/**
 * @brief (?) kind.
 */
enum FTAK
{
    FTAK_Nil = -1,
    FTAK_None = 0,
    FTAK_Reach = 1,
    FTAK_Sweep = 2,
    FTAK_Whack = 2,
    FTAK_Smash = 4,
    FTAK_Rush = 8,
    FTAK_Bomb = 16,
    FTAK_Gun = 16,
    FTAK_Max = 17,
    FTAK_Shock = 32
};

/**
 * @brief Script element(?) kind.
 */
enum JSGEK
{
    JSGEK_Nil = -1,
    JSGEK_Context = 0,
    JSGEK_Cut = 1,
    JSGEK_Label = 2,
    JSGEK_Tunnel = 3,
    JSGEK_Pause = 4,
    JSGEK_Jump = 5,
    JSGEK_Run = 6,
    JSGEK_Climb = 7,
    JSGEK_Attack = 8,
    JSGEK_Aseg = 9,
    JSGEK_Focus = 10,
    JSGEK_Clock = 11,
    JSGEK_Unknown = 12,
    JSGEK_Max = 13
};

/**
 * @brief Script jump(?) kind.
 */
enum JSGJK
{
    JSGJK_Nil = -1,
    JSGJK_Fall = 0,
    JSGJK_Jump = 1,
    JSGJK_DoubleJump = 2,
    JSGJK_Max = 3
};

/**
 * @brief Script leap(?) kind.
 */
enum JSGLK
{
    JSGLK_Nil = -1,
    JSGLK_Normal = 0,
    JSGLK_Big = 1,
    JSGLK_Max = 2
};

/**
 * @brief Script element(?).
 */
struct JSGE
{
    JSGEK jsgek;
    OID oid;
    int fAsync;
    union
    {
        struct
        {
            OID oid;
        } label;
        struct
        {
            float dtPause;
        } pause;
        struct
        {
            JSGJK jsgjk;
            JSGLK jsglk;
        } jump;
        struct
        {
            float uRun;
        } run;
        struct
        {
            float uClimb;
        } climb;
        struct
        {
            FTAK ftak;
        } attack;
        struct
        {
            float rdt;
        } clock;
    };
};

/**
 * @class SCRIPT
 * @brief Object representing a script of some kind.
 */
struct JSG : public LO
{
    int cjsge;
    JSGE *ajsge;
    JT *pjt;
    int ijsgeCur;
    float tCur;
    JSGE *pjsgeJoy;
    LO *ploContext;
    ASEGA *pasegaCur;
    LO *ploFocus;
    TN *ptnCur;
    int fHideTn;
    undefined4 unk1;
    undefined4 unk2;
    undefined4 unk3;
};

/**
 * @brief Initializes the given script.
 */
void InitJsg(JSG *pjsg);

void GetJsgLocation(JSG *pjsg, LO *plo, VECTOR *ppos, float *prad);

void SetJsgFocus(JSG *pjsg, LO *plo);

void SetJsgTn(JSG *pjsg, TN *ptn);

void NextJsgJsge(JSG *pjsg);

int FIsJsgJsgeComplete(JSG *pjsg, JSGE *pjsge);

void UpdateJsgJsge(JSG *pjsg);

void ReadJsgJoystick(JSG *pjsg, JOY *pjoy);

/**
 * @brief Updates the script and returns true if there are still script elements to execute.
 *
 * @return 1 if count of script elements > 0, and current script element index < count of script elements.
 * @return 0 otherwise.
 */
int FIsJsgActive(JSG *pjsg);

/**
 * @brief Retracts the script and clears the count of script elements.
 */
void ClearJsg(JSG *pjsg);

void ApplyJsg(JSG *pjsg, JT *pjt);

void RetractJsg(JSG *pjsg);

JSGE *PjsgeAllocJsg(JSG *pjsg, JSGEK jsgek, OID oid, int fAsync);

/**
 * @brief Apply the script to a JT context and mark it active.
 *
 * @param pjsg Script instance.
 * @param pjt JT context to attach the script to.
 */
void ApplyJsg(JSG *pjsg, JT *pjt);

/**
 * @brief Retract the script from its JT context and stop it.
 *
 * @param pjsg Script instance.
 */
void RetractJsg(JSG *pjsg);

/**
 * @brief Allocate and initialize a new script element (JSGE).
 *
 *
 * @param pjsg Script instance.
 * @param jsgek Type of script element to allocate.
 * @param oid Object id associated with the element.
 * @param fAsync Whether the element is asynchronous.
 *
 * @returns Returns a pointer to an initialized JSGE within the script's array, or
 * a pointer to a static fallback if the script is full.
 */
JSGE *PjsgeAllocJsg(JSG *pjsg, JSGEK jsgek, OID oid, int fAsync);

/**
 * @brief Add a context element to the script sequence.
 *
 * @param pjsg Script instance.
 * @param oid Object to use as context.
 */
void AddJsgContext(JSG *pjsg, OID oid);

/**
 * @brief Add a cut element to the script sequence.
 *
 * @param pjsg Script instance.
 * @param oid Object marking the cut.
 */
void AddJsgCut(JSG *pjsg, OID oid);

/**
 * @brief Add a focus element to the script sequence.
 *
 * @param pjsg Script instance.
 * @param oid Object to focus on.
 */
void AddJsgFocus(JSG *pjsg, OID oid);

/**
 * @brief Add a label element to the script sequence.
 *
 * @param pjsg Script instance.
 * @param oid Label object ID.
 */
void AddJsgLabel(JSG *pjsg, OID oid);

/**
 * @brief Add a tunnel element to the script sequence.
 *
 * @param pjsg Script instance.
 * @param oid Tunnel node to use.
 */
void AddJsgTunnel(JSG *pjsg, OID oid);

/**
 * @brief Add a pause element to the script sequence.
 *
 * @param pjsg Script instance.
 * @param oid Object ID for pause context.
 * @param dtPause Duration to pause.
 */
void AddJsgPause(JSG *pjsg, OID oid, float dtPause);

/**
 * @brief Add an animation segment (ASEGA) element.
 *
 * @param pjsg Script instance.
 * @param oid Animation sequence ID.
 * @param fAsync Whether the segment runs asynchronously.
 */
void AddJsgAseg(JSG *pjsg, OID oid, int fAsync);

/**
 * @brief Add a jump action to the script sequence.
 *
 * @param pjsg Script instance.
 * @param oid Object ID to perform jump.
 * @param jsgjk Jump kind.
 * @param jsglk Leap size kind.
 * @param fAsync Whether the action is asynchronous.
 */
void AddJsgJump(JSG *pjsg, OID oid, JSGJK jsgjk, JSGLK jsglk, int fAsync);

/**
 * @brief Add a run action to the script sequence.
 *
 * @param pjsg Script instance.
 * @param oid Object ID to run.
 * @param uRun Speed of run.
 * @param fAsync Whether the action is asynchronous.
 */
void AddJsgRun(JSG *pjsg, OID oid, float uRun, int fAsync);

/**
 * @brief Add a climb action to the script sequence.
 *
 * @param pjsg Script instance.
 * @param oid Object ID to climb.
 * @param uClimb Climb speed.
 * @param fAsync Whether the action is asynchronous.
 */
void AddJsgClimb(JSG *pjsg, OID oid, float uClimb, int fAsync);

/**
 * @brief Add an attack action to the script sequence.
 *
 * @param pjsg Script instance.
 * @param oid Object ID to attack with.
 * @param ftak Attack kind.
 * @param fAsync Whether the attack is asynchronous.
 */
void AddJsgAttack(JSG *pjsg, OID oid, FTAK ftak, int fAsync);

/**
 * @brief Add a clock rate change to the script sequence.
 *
 * @param pjsg Script instance.
 * @param rdt Rate delta time factor.
 */
void AddJsgClock(JSG *pjsg, float rdt);

#endif // JSG_H
