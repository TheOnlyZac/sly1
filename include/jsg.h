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
 * @brief (?) kind.
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
 * @brief (?) jump kind?
 */
enum JSGJK
{
    JSGJK_Nil = -1,
    JSGJK_Fall = 0,
    JSGJK_Jump = 1,
    JSGJK_DoubleJump = 2,
    JSGJK_Max = 3
};

enum JSGLK
{
    JSGLK_Nil = -1,
    JSGLK_Normal = 0,
    JSGLK_Big = 1,
    JSGLK_Max = 2
};

/**
 * @brief Unknown.
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
 * @brief Unknown.
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

void InitJsg(JSG *pjsg);

void GetJsgLocation(JSG *pjsg, LO *plo, VECTOR *ppos, float *prad);

void SetJsgFocus(JSG *pjsg, LO *plo);

void SetJsgTn(JSG *pjsg, TN *ptn);

void NextJsgJsge(JSG *pjsg);

int FIsJsgJsgeComplete(JSG *pjsg, JSGE *pjsge);

void UpdateJsgJsge(JSG *pjsg);

void ReadJsgJoystick(JSG *pjsg, JOY *pjoy);

int FIsJsgActive(JSG *pjsg);

void ClearJsg(JSG *pjsg);

void ApplyJsg(JSG *pjsg, JT *pjt);

void RetractJsg(JSG *pjsg);

JSGE *PjsgeAllocJsg(JSG *pjsg, JSGEK jsgek, OID oid, int fAsync);

void AddJsgContext(JSG *pjsg, OID oid);

void AddJsgCut(JSG *pjsg, OID oid);

void AddJsgFocus(JSG *pjsg, OID oid);

void AddJsgLabel(JSG *pjsg, OID oid);

void AddJsgTunnel(JSG *pjsg, OID oid);

void AddJsgPause(JSG *pjsg, OID oid, float dtPause);

void AddJsgAseg(JSG *pjsg, OID oid, int fAsync);

void AddJsgJump(JSG *pjsg, OID oid, JSGJK jsgjk, JSGLK jsglk, int fAsync);

void AddJsgRun(JSG *pjsg, OID oid, float uRun, int fAsync);

void AddJsgClimb(JSG *pjsg, OID oid, float uClimb, int fAsync);

void AddJsgAttack(JSG *pjsg, OID oid, FTAK ftak, int fAsync);

void AddJsgClock(JSG *pjsg, float rdt);

#endif // JSG_H
