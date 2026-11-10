/**
 * @file suv.h
 *
 * @brief Smash-up vehicle (the van and other racecars).
 */
#ifndef SUV_H
#define SUV_H

#include "common.h"
#include <po.h>
#include <shape.h>
#include <vol.h>
#include <sw.h>
#include <util.h>
#include <step.h>
#include <stepguard.h>
#include <math.h>
#include <memory.h>
#include <game.h>
#include <difficulty.h>

/**
 * @class SMASHUP_VEHICLE
 * @brief Vehicles used in At the Dog Track, A Desperate Race, and Burning Rubber (not A Hazardous Path).
 *
 * @todo What is the base class?
 */
// Forward.
struct EXPL;

enum SUVS // guess
{
    SUVS_Nil = -1,
    SUVS_Max = 3
};

struct SUVFEAT;
// Feature entry, 0x28 bytes (all names guesses).
struct SUVFEAT
{
    int fActive;
    VOL *pvol;
    int unk8;
    int iOrder; // guess
    float s; // guess
    SUVFEAT *pfeatNext; // guess
    float a;
    float b;
    EXPL *pexpl;
    EXPL *pexpl2;
};

struct SUV : public PO
{
    // fields accessed via STRUCT_OFFSET until layout is known
};

void InitSuv(SUV *psuv);
void UpdateSuvShapes(SUV *psuv);
void UpdateSuvXfWorld(SUV *psuv);
void UpdateSuvInternalXps(SUV *psuv);
void GetSuvCpdefi(SUV *psuv, float dt, CPDEFI *pcpdefi);
void BoostSuv(SUV *psuv);
float DsGetTrackRelative(float a, float b, float c);
void AddSuvFeature(SUV *psuv, VOL *pvol, float a, float b, EXPL *pexpl, EXPL *pexpl2);
void SetSuvSuvs(SUV *psuv, SUVS suvs);
void ResetSuv(SUV *psuv);
int FIsSuvAheadOf(SUV *psuv, SUV *psuvOther);
void CollectSuvPrize(SUV *psuv, PCK pck, ALO *palo);
void UpdateSuvBounds(SUV *psuv);
void OnSuvActive(SUV *psuv, int fActive, PO *ppoOther);
void SetSuvLine(SUV *psuv, SHAPE *pshape);
void SetSuvTrack(SUV *psuv, SHAPE *pshape);
void AddSuvCheckPoint(SUV *psuv, VOL *pvol);
void HandleSuvMessage(SUV *psuv, MSGID msgid, void *pv);
void UpdateSuvWheels(SUV *psuv);
void UpdateSuv(SUV *psuv, float dt);
void UpdateSuvBalance(SUV *psuv);
void UpdateSuvLine(SUV *psuv, int *pfNoXps); // guess
void UpdateSuvHeading(SUV *psuv);
void UpdateSuvSounds(SUV *psuv, float dt);
void UpdateSuvExpls(SUV *psuv);
void UpdateSuvVolumes(SUV *psuv, int fNoXps); // guess
void UpdateSuvPuncher(SUV *psuv);
void FUN_001d9338(SUV *psuv);
void FUN_001da170(SUV *psuv);
float GExcludeAlm(int clm, LM *alm, float g);

#endif // SUV_H
