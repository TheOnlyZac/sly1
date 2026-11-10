/**
 * @file aseg.h
 */
#ifndef ASEG_H
#define ASEG_H

#include "common.h"
#include <waypoint.h>
#include <util.h>
#include <sm.h>

// Forward.
struct OVR;
struct CHN;
struct ASEGA;
struct EA;

/**
 * @brief Unknown.
 */
enum IAK
{
    IAK_Nil = -1,
    IAK_Time = 0,
    IAK_Proportion = 1,
    IAK_Nearest = 2,
    IAK_Max = 3
};

/**
 * @brief Unknown.
 */
enum SEEK
{
    SEEK_Nil = -1,
    SEEK_Start = 0,
    SEEK_Current = 1,
    SEEK_End = 2,
    SEEK_EndDoEvents = 3,
    SEEK_Max = 4
};

/**
 * @brief Unknown.
 */
struct CHN
{
    // ...
};

/**
 * @brief Per channel data of an animation segment (name and fields are guesses).
 */
struct ACHN
{
    /* 0x00 */ undefined4 unk0;
    /* 0x04 */ CHN *pchnPos;
    /* 0x08 */ CHN *pchnRot;
    /* 0x0c */ void *punkPos;
    /* 0x10 */ undefined4 unk10;
    /* 0x14 */ undefined4 unk14;
    /* 0x18 */ void *punkRot;
};

/**
 * @class ANIMATION_SEGMENT
 * @brief Object representing an animation segment.
 */
struct ASEG : public LO
{
    /* 0x34 */ float tMax;
    /* 0x38 */ STRUCT_PADDING(1);
    /* 0x3c */ ACHN *pachn; // one entry per action segment (name is a guess)
    /* 0x40 */ STRUCT_PADDING(7);
    /* 0x5c */ int cea;
    /* 0x60 */ EA *aea;
    /* 0x64 */ STRUCT_PADDING(2);
    /* 0x6c */ DL dlAsega;
    /* 0x78 */ STRUCT_PADDING(2);
    /* 0x80 */ CLQ clqMasterSuck;
    /* 0x90 */ LM lmMasterSuck;
    /* 0x98 */ float svtMasterSuck;
    /* 0x9c */ CHN *pchnStrip;
};

/**
 * @brief Animation segment something(?).
 */
struct ASEGD
{
    /* 0x00 */ ASEG *paseg;
    /* 0x04 */ OID oidAseg;
    /* 0x08 */ IAK iak;
    /* 0x0c */ float tLocal;
    /* 0x10 */ float svtLocal;
};

/**
 * @class ASEGBL
 * @brief Animation segment blend(?).
 */
struct ASEGBL : public ASEG
{
    // ...
};

/**
 * @brief Animation segment event kind, the value of EA::eak. Selects the case in HandleAsegaEvent.
 *
 * @note Every name here is a guess from what the handler does. Pairs like ShowObject/HideObject
 * are swapped when the segment plays backward over its own events.
 */
enum EAK
{
    EAK_Nil = -1,
    EAK_Sound = 0,
    EAK_StopSound = 1,
    EAK_ContinueMusic = 2,
    EAK_PauseMusic = 3,
    EAK_SetTimeSpeed = 4,
    EAK_SetSpeed = 5,
    EAK_Dialog = 6,
    EAK_SetTimeSpeedAlt = 7,
    EAK_Retract = 8,
    EAK_ShowObject = 9,
    EAK_HideObject = 10,
    EAK_Hold = 11,
    EAK_EnableCamera = 12,
    EAK_DisableCamera = 13,
    EAK_HandsOff = 14,
    EAK_HandsOn = 15,
    EAK_SoConstraints = 16,
    EAK_ActAckBegin = 17,
    EAK_ActAckEnd = 18,
    EAK_PuppetOn = 19,
    EAK_PuppetOff = 20,
    EAK_ErrorBeginA = 21,
    EAK_ErrorEndA = 22,
    EAK_ErrorBeginB = 23,
    EAK_ErrorEndB = 24,
    EAK_ActivateWipe = 25,
    EAK_SetWipeButtonTrans = 26,
    EAK_DefaultExit = 27,
    EAK_ApplyAseg = 28,
    EAK_PosOn = 29,
    EAK_PosOff = 30,
    EAK_RotOn = 31,
    EAK_RotOff = 32,
    EAK_StartTimer = 33,
    EAK_StopTimer = 34,
    EAK_EvalPos = 35,
    EAK_EvalRot = 36,
    EAK_JoyRumble = 37,
    EAK_SendLoMessage = 38,
    EAK_SendAsegaMessage13 = 39,
    EAK_SpliceEvent = 40,
    EAK_SendAsegaMessage15 = 41,
    EAK_PauseForVag = 42,
    EAK_StopVag = 43,
    EAK_PreloadVag = 44,
    EAK_PoseCombo = 45,
    EAK_ApplySm = 46,
    EAK_RetractSm = 47,
    EAK_ProjectAlo = 48,
    EAK_Unk49 = 49,
    EAK_Unk50 = 50,
    EAK_Mpeg = 51,
    EAK_PlaceCredit = 52,
    EAK_VacateCredit = 53,
    EAK_SetCreditLine = 54,
    EAK_UiMode0 = 55,
    EAK_UiMode1 = 56,
    EAK_Darken = 57,
    EAK_DarkenSmooth = 58,
    EAK_Jsg = 59,
    EAK_Max = 60
};

/**
 * @brief Two shorts, for event arguments that are packed in pairs.
 */
struct EAS
{
    short s0;
    short s2;
};

/**
 * @brief Unknown.
 */
struct EA
{
    /* 0x00 */ float tLocal;
    /* 0x04 */ int eak; // EAK, event kind (name is a guess)
    /* 0x08 */ union
    {
        int n8;
        float g8;
        OID oid8;
        void *pv8;
        EAS sh8;
    };
    /* 0x0c */ union
    {
        int nC;
        float gC;
        OID oidC;
        void *pvC;
        EAS shC;
    };
};

/**
 * @brief Supposed to start the ASEG system, but it doesn't do anything.
 */
void StartupAseg();

void InitAseg(ASEG *paseg);

void LoadAsegFromBrx(ASEG *paseg, CBinaryInputStream *pbis);

void LoadAsegEventsFromBrx(ASEG *paseg, CBinaryInputStream *pbis, int fFrame, int *pcea, EA **paea);

void CloneAseg(ASEG *paseg, LO *ploBase);

void PostAsegLoad(ASEG *paseg);

void PostAsegLoadCallback(ASEG *paseg, MSGID msgid, void *pvData);

void ApplyAsegOvr(ASEG *paseg, ALO *paloAsegRoot, int covr, OVR *aovr, float tLocal, float svtLocal, GRFAPL grfapl, ASEGA **ppasega);

void ApplyAseg(ASEG *paseg, ALO *paloAsegRoot, float tLocal, float svtLocal, GRFAPL grfapl, ASEGA **ppasega);

ASEGA *PasegaApplyAseg(ASEG *paseg, ALO *paloAsegRoot, float tLocal, float svtLocal, GRFAPL grfapl);

ASEGA *PasegaFindAseg(ASEG *paseg, ALO *paloRoot);

void EnsureAseg(ASEG *paseg, ALO *paloRoot, SEEK seek, float t, float svt, GRFAPL grfapl, ASEGA **ppasega);

ASEGA *PasegaEnsureAseg(ASEG *paseg, ALO *paloRoot, SEEK seek, float t, float svt, GRFAPL grfapl);

void ApplyAsegCur(ASEG *paseg, ALO *paloRoot, float t, float svt, GRFAPL grfapl, ASEGA **ppasega);

int FWipingAseg(ASEG *paseg);

void FindAsegClosestPoint(ASEG *paseg, ALO *palo, VECTOR *ppos, float t, float *ptClosest, VECTOR *pposClosest, VECTOR *pvClosest);

EA *PeaFindAsegLabel(ASEG *paseg, OID oidLabel);

float TFindAsegLabel(ASEG *paseg, OID oidLabel);

CHN *PchnFindAseg(ASEG *paseg, ALO *palo);

void PredictAsegEffect(ASEG *paseg, float t, float svt, ALO *paloLeaf, ALO *paloBasis, int cpaloPredict, VECTOR *apos, MATRIX3 *amat, VECTOR *av, VECTOR *aw);

void GetAsegWaypoints(ASEG *paseg, ALO *paloContext, int *pcpwaypoint, WAYPOINT ***papwaypoint);

void StripAsegChn(ASEG *paseg, CHN *pchn);

void StripAsegAlo(ASEG *paseg, ALO *palo);

/**
 * @brief Does nothing.
 */
void LoadAsegblFromBrx(ASEGBL *pasegbl, CBinaryInputStream *pbis);

/**
 * @brief Does nothing.
 */
void PostAsegblLoad(ASEGBL *pasegbl);

/**
 * @brief Does nothing.
 */
void CloneAsegbl(ASEGBL *pasegbl, LO *ploBase);

#endif // ASEG_H
