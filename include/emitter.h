/**
 * @file emitter.h
 *
 * @brief Particle emitter.
 */
#ifndef EMITTER_H
#define EMITTER_H

#include "common.h"
#include <ensure.h>
#include <xform.h>
#include <rip.h>
#include <alo.h>

// Forward.
struct EXPL;

typedef unsigned int GRFEXPLSO;

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct EMITMESH
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct EMITBLIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct EMITGEN
{
    /* 0x00 */ VECTOR *apos; // guess
    /* 0x04 */ VECTOR *av; // guess
    /* 0x08 */ float *atCreated; // guess
    /* 0x0c */ float *atDestroy; // guess
    /* 0x10 */ int fUnknown; // guess
    /* 0x14 */ STRUCT_PADDING(3);
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct EMITRIP
{
    STRUCT_PADDING(16); // 0x40 bytes
} __attribute__((aligned(16)));

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct EMITDV
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct EMITV
{
    STRUCT_PADDING(32); // 0x80 bytes
} __attribute__((aligned(16)));

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct EMITVX
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct EMITO
{
    STRUCT_PADDING(36); // 0x90 bytes, layout is a guess
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct EMITB
{
    /* 0x00 */ int cref;
    /* 0x04 */ STRUCT_PADDING(3);
    /* 0x10 */ EMITO emito;
    /* 0xa0 */ EMITV emitv; // guess
    /* 0x120 */ int unk120; // guess, compared against 1 in EmitParticles
    /* 0x124 */ STRUCT_PADDING(35);
    /* 0x1b0 */ EMITRIP emitrip; // guess
    /* 0x1f0 */ STRUCT_PADDING(4);
}; // 0x200 bytes

/**
 * @brief Emitter group?
 * @todo Implement the struct.
 */
struct EMITG
{
    /* 0x00 */ STRUCT_PADDING(1);
    /* 0x04 */ RIPG **ppripg; // guess
    /* 0x08 */ LO *ploSubscribe; // guess
};

/**
 * @brief Particle emitter.
 * @todo Implement the struct.
 */
struct EMITTER : public ALO
{
    // ...
    /* 0x308 */ int fAutoPause;
    /* 0x30c */ STRUCT_PADDING(13);
    /* 0x340 */ float tUnpause;
    /* 0x344 */ STRUCT_PADDING(2);
    /* 0x34c */ int fValuesChanged;
    // ...
};

void InitEmitb(EMITB *pemitb);

void InitEmitter(EMITTER *pemitter);

void LoadEmitmeshFromBrx(EMITMESH *pemitmesh, CBinaryInputStream *pbis);

void LoadEmitblipColorsFromBrx(EMITBLIP *pemitblip, int crgba, LO *ploEmit, CBinaryInputStream *pbis);

void LoadEmitterFromBrx(EMITTER *pemitter, CBinaryInputStream *pbis);

void CloneEmitter(EMITTER *pemitter, EMITTER *pemitterBase);

void BindEmitterCallback(EMITTER *pemitter, MSGID msgid, void *pvData);

void BindEmitter(EMITTER *pemitter);

void PostEmitterLoad(EMITTER *pemitter);

void HandleEmitterMessage(EMITTER *pemitter, MSGID msgid, void *pv);

void RenderEmitterSelf(EMITTER *pemitter, CM *pcm, RO *pro);

EMITB *PemitbCopyOnWrite(EMITB *pemitb);

EMITB *PemitbEnsureEmitter(EMITTER *pemitter, ENSK ensk);

EMITTER *PemitterEnsureEmitter(EMITTER *pemitter, ENSK ensk);

void AddEmitterSkeleton(EMITTER *pemitter, OID oid, OID oidOther, float sRadius, float gDensity, float sRadiusOther, float gDensityOther);

void ModifyEmitterParticles(EMITTER *pemitter);

void UpdateEmitter(EMITTER *pemitter, float dt);

void PauseEmitter(EMITTER *pemitter, float dtPause);

void PauseEmitterIndefinite(EMITTER *pemitter);

void UnpauseEmitter(EMITTER *pemitter);

int FPausedEmitter(EMITTER *pemitter);

void SetEmitterEnabled(EMITTER *pemitter, int fEnabled);

void GetEmitterEnabled(EMITTER *pemitter, int *pfEnabled);

void GetEmitterPaused(EMITTER *pemitter, int *pfPaused);

void OnEmitterValuesChanged(EMITTER *pemitter);

void SetEmitterParticleCount(EMITTER *pemitter, int cParticle);

void SetEmitterAutoPause(EMITTER *pemitter, int fAutoPause);

void SetEmitbRipt(EMITB *pemitb, RIPT ript);

void SetEmitterRipt(EMITTER *pemitter, RIPT ript);

void SetExploRipt(EXPLO *pexplo, RIPT ript);

void WakeSoWater(SO *pso, WATER *pwater, float dt, VECTOR *pvCurrent, VECTOR *pposSurface, float dtWakeMin, float gScale);

void StandardSmokeCloud(VECTOR *ppos, float sRadius);

void ChooseEmitoPos(EMITO *pemito, int iParticle, int cParticle, VECTOR *pposRet, VECTOR *pnormalRet);

void ConvertEmitoPosVec(EMITO *pemito, VECTOR *ppos, VECTOR *pv);

void CalculateEmitvx(int cParticlePerRing, LM *plmTilt, int cParticle, EMITVX *pemitvx);

void ChooseEmitVelocity(EMITVX *pemitvx, float uRandom, float rSvz, LM *plmSv, VECTOR *pvecNormal, int iParticle, VECTOR *pv);

void ChooseEmitvVelocityAge(EMITV *pemitv, EMITVX *pemitvx, EMITO *pemito, int iParticle, VECTOR *ppos, VECTOR *pnormal, VECTOR *pv, float *ptCreated, float *ptDestroy);

void EmitRips(EMITB *pemitb, EMITG *pemitg, int crip, VECTOR *apos, VECTOR *av, float *atCreated, float *atDestroy);

void EmitBlips(EMITB *pemitb, EMITG *pemitg, int cblipeRequested, VECTOR *apos, VECTOR *av, float *atCreated, float *atDestroy, VECTOR *aposFinal, VECTOR *avFinal);

void OriginateParticles(int cParticle, EMITB *pemitb, EMITGEN *pemitgen);

void OriginateSplineSinkParticles(int cParticle, EMITB *pemitb, EMITGEN &emitgen, EMITGEN &emitgenTarget);

void EmitParticles(int cParticle, EMITB *pemitb, EMITG *pemitg);

void EmitRipsSphere(VECTOR *ppos, VECTOR *pnormal, int crip, EMITRIP *pemitrip, EMITV *pemitv, RIPG **ppripg, LO *ploSubscribe);

void StockSplashBig(VECTOR *ppos, float gScale, SO *psoTouch);

void StockSplashSmall(VECTOR *ppos, float gScale, SO *psoTouch);

void AddEmitoSkeleton(EMITO *pemito, OID oid, OID oidOther, float sRadius, float gDensity, float sRadiusOther, float gDensityOther, LO *ploContext);

void BindEmitb(EMITB *pemitb, LO *ploContext);

void SetEmitdvEmitb(EMITDV *pemitdv, EMITB *pemitb);

void CalculateEmitdvMatrix(EMITDV *pemitdv, float dt, MATRIX4 *pmat4Dv);

void PostExplLoad(EXPL *pexpl);

void CalculateExplTransform(EXPL *pexpl, VECTOR *pposLocal, MATRIX3 *pmatLocal);

void ExplodeExpl(EXPL *pexpl);

void ExplodeExplParams(EXPL *pexpl, GRFEXPLSO grfexplso, ALO *paloReference, VECTOR *pvec, VECTOR *pposOrigin, float rScale, float sRadius);

void ExplodeExplExplso(EXPL *pexpl, EXPLSO *pexplso);

void LoadExplgFromBrx(EXPLG *pexplg, CBinaryInputStream *pbis);

void CloneExplg(EXPLG *pexplg, EXPLG *pexplgBase);

void BindExplg(EXPLG *pexplg);

void ExplodeExplgExplso(EXPLG *pexplg, EXPLSO *pexplso);

void InitExplo(EXPLO *pexplo);

void LoadExploFromBrx(EXPLO *pexplo, CBinaryInputStream *pbis);

void CloneExplo(EXPLO *pexplo, EXPLO *pexploBase);

void BindExplo(EXPLO *pexplo);

void ExplodeExploExplso(EXPLO *pexplo, EXPLSO *pexplso);

void AddExploSkeleton(EXPLO *pexplo, OID oid, OID oidOther, float sRadius, float gDensity, float sRadiusOther, float gDensityOther);

EMITB *PemitbEnsureExplo(EXPLO *pexplo, ENSK ensk);

void InitExpls(EXPLS *pexpls);

void BindExpls(EXPLS *pexpls);

void HandleExplsMessage(EXPLS *pexpls, MSGID msgid, void *pv);

void ExplodeExplsExplso(EXPLS *pexpls, EXPLSO *pexplso);

SFX *PsfxEnsureExpls(EXPLS *pexpls, ENSK ensk);

void FireExplsExplso(EXPLS *pexpls, EXPLSO *pexplso);

void InferExpl(EXPL **ppexpl, ALO *palo);

void FireSwTimedExplodeStyles(SW *psw);

#endif // EMITTER_H
