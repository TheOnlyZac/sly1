#include <emitter.h>
#include <rip.h>
#include <blip.h>
#include <util.h>
#include <memory.h>

extern float DAT_0024a124;

INCLUDE_ASM("asm/nonmatchings/P2/emitter", InitEmitb__FP5EMITB);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", InitEmitter__FP7EMITTER);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", LoadEmitmeshFromBrx__FP8EMITMESHP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", LoadEmitblipColorsFromBrx__FP8EMITBLIPiP2LOP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", LoadEmitterFromBrx__FP7EMITTERP18CBinaryInputStream);

void CloneEmitter(EMITTER *pemitter, EMITTER *pemitterBase)
{
    CloneAlo(pemitter, pemitterBase);
    STRUCT_OFFSET(pemitter, 0x2d0, EMITB *)->cref++;
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", BindEmitterCallback__FP7EMITTER5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", BindEmitter__FP7EMITTER);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", PostEmitterLoad__FP7EMITTER);

void HandleEmitterMessage(EMITTER *pemitter, MSGID msgid, void *pv)
{
    if (msgid == MSGID_removed)
    {
        if (pv == STRUCT_OFFSET(pemitter, 0x344, void *))
        {
            (*(void (**)(void *, EMITTER *))((char *)*(void **)pv + 0x70))(pv, pemitter);
            STRUCT_OFFSET(pemitter, 0x344, void *) = 0;
        }
        else if (pv == STRUCT_OFFSET(pemitter, 0x348, void *))
        {
            (*(void (**)(void *, EMITTER *))((char *)*(void **)pv + 0x70))(pv, pemitter);
            STRUCT_OFFSET(pemitter, 0x348, void *) = 0;
        }
    }
}

EMITB *PemitbCopyOnWrite(EMITB *pemitb)
{
    EMITB *pemitbNew;

    if (pemitb->cref < 2)
    {
        return pemitb;
    }

    pemitbNew = (EMITB *)PvAllocSwCopyImpl(0x200, pemitb);

    if (STRUCT_OFFSET(pemitb, 0x10, int) == 3)
    {
        if (STRUCT_OFFSET(pemitb, 0x24, void *) != 0)
        {
            STRUCT_OFFSET(pemitbNew, 0x24, void *) =
                PvAllocSwCopyImpl(0x28 * STRUCT_OFFSET(pemitb, 0x20, int), STRUCT_OFFSET(pemitb, 0x24, void *));
        }
    }

    pemitbNew->cref = 1;
    pemitb->cref--;

    return pemitbNew;
}

EMITB *PemitbEnsureEmitter(EMITTER *pemitter, ENSK ensk)
{
    if (ensk == ENSK_Set)
    {
        STRUCT_OFFSET(pemitter, 0x34c, int) = 1; // pemitter->fValuesChanged
        STRUCT_OFFSET(pemitter, 0x2d0, EMITB *) = PemitbCopyOnWrite(STRUCT_OFFSET(pemitter, 0x2d0, EMITB *));
    }

    return STRUCT_OFFSET(pemitter, 0x2d0, EMITB *); // pemitter->pemitb
}

EMITTER *PemitterEnsureEmitter(EMITTER *pemitter, ENSK ensk)
{
    if (ensk == ENSK_Set)
    {
        STRUCT_OFFSET(pemitter, 0x34c, int) = 1; // pemitter->fValuesChanged
    }

    return pemitter;
}

void AddEmitterSkeleton(EMITTER *pemitter, OID oid, OID oidOther, float sRadius, float gDensity, float sRadiusOther, float gDensityOther)
{
    EMITB *pemitb = PemitbEnsureEmitter(pemitter, ENSK_Set);
    AddEmitoSkeleton(&pemitb->emito, oid, oidOther, sRadius, gDensity, sRadiusOther, gDensityOther, pemitter);
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", ModifyEmitterParticles__FP7EMITTER);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", UpdateEmitter__FP7EMITTERf);

extern "C" {
void FUN_00155f28(SO *pso)
{
    SO *psoParent;

    if ((STRUCT_OFFSET(pso, 0x2c8, unsigned long long) & 0xC000000) == 0x8000000)
    {
        return;
    }

    psoParent = STRUCT_OFFSET(pso, 0x18, SO *);
    while (psoParent != 0)
    {
        if ((STRUCT_OFFSET(psoParent, 0x2c8, unsigned long long) & 0xC000000) == 0x8000000)
        {
            break;
        }
        psoParent = STRUCT_OFFSET(psoParent, 0x18, SO *);
    }

    if (psoParent == 0)
    {
        return;
    }

    STRUCT_OFFSET(pso, 0x88, int) = STRUCT_OFFSET(psoParent, 0x88, int);
}
}

void PauseEmitter(EMITTER *pemitter, float dtPause)
{
    STRUCT_OFFSET(pemitter, 0x340, float) = g_clock.t + dtPause; // pemitter->tUnpause
}

void PauseEmitterIndefinite(EMITTER *pemitter)
{
    STRUCT_OFFSET(pemitter, 0x340, float) = DAT_0024a124; // pemitter->tUnpause
}

void UnpauseEmitter(EMITTER *pemitter)
{
    STRUCT_OFFSET(pemitter, 0x340, float) = -1.0f; // pemitter->tUnpause
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", FPausedEmitter__FP7EMITTER);

void SetEmitterEnabled(EMITTER *pemitter, int fEnabled)
{
    if (fEnabled)
    {
        UnpauseEmitter(pemitter);
        return;
    }

    PauseEmitterIndefinite(pemitter);
}

void GetEmitterEnabled(EMITTER *pemitter, int *pfEnabled)
{
    *pfEnabled = !FPausedEmitter(pemitter);
}

void GetEmitterPaused(EMITTER *pemitter, int *pfPaused)
{
    *pfPaused = FPausedEmitter(pemitter);
}

void OnEmitterValuesChanged(EMITTER *pemitter)
{
    STRUCT_OFFSET(pemitter, 0x34c, int) = 0; // pemitter->fValuesChanged

    if (STRUCT_OFFSET(pemitter, 0x348, BLIPG *) != 0)
    {
        SetBlipgEmitb(STRUCT_OFFSET(pemitter, 0x348, BLIPG *), STRUCT_OFFSET(pemitter, 0x2d0, EMITB *));
    }

    if (STRUCT_OFFSET(pemitter, 0x344, RIPG *) != 0)
    {
        SetRipgEmitb(STRUCT_OFFSET(pemitter, 0x344, RIPG *), STRUCT_OFFSET(pemitter, 0x2d0, EMITB *));
    }

    if (STRUCT_OFFSET(pemitter, 0x2d4, int) == 3)
    {
        STRUCT_OFFSET(pemitter, 0x328, float) = GRandInRange(STRUCT_OFFSET(pemitter, 0x2dc, float), STRUCT_OFFSET(pemitter, 0x2e0, float)) * 60.0f;
    }
    else
    {
        STRUCT_OFFSET(pemitter, 0x328, float) = GRandInRange(STRUCT_OFFSET(pemitter, 0x2dc, float), STRUCT_OFFSET(pemitter, 0x2e0, float));
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", SetEmitterParticleCount__FP7EMITTERi);

void SetEmitterAutoPause(EMITTER *pemitter, int fAutoPause)
{
    STRUCT_OFFSET(pemitter, 0x308, int) = fAutoPause; // pemitter->fAutoPause
    STRUCT_OFFSET(pemitter, 0x34c, int) = 1; // pemitter->fValuesChanged
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", SetEmitbRipt__FP5EMITB4RIPT);

void SetEmitterRipt(EMITTER *pemitter, RIPT ript)
{
    EMITB *pemitb = PemitbEnsureEmitter(pemitter, ENSK_Set);
    SetEmitbRipt(pemitb, ript);
}

void SetExploRipt(EXPLO *pexplo, RIPT ript)
{
    EMITB *pemitb = PemitbEnsureExplo(pexplo, ENSK_Set);
    SetEmitbRipt(pemitb, ript);
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", WakeSoWater__FP2SOP5WATERfP6VECTORT3ff);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", StandardSmokeCloud__FP6VECTORf);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", ChooseEmitoPos__FP5EMITOiiP6VECTORT3);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", ConvertEmitoPosVec__FP5EMITOP6VECTORT1);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", CalculateEmitvx__FiP2LMiP6EMITVX);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", ChooseEmitVelocity__FP6EMITVXffP2LMP6VECTORiT4);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", ChooseEmitvVelocityAge__FP5EMITVP6EMITVXP5EMITOiP6VECTORN24PfT7);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", EmitRips__FP5EMITBP5EMITGiP6VECTORT3PfT5);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", EmitBlips__FP5EMITBP5EMITGiP6VECTORT3PfT5T3T3);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", OriginateParticles__FiP5EMITBP7EMITGEN);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", OriginateSplineSinkParticles__FiP5EMITBR7EMITGENT2);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", EmitParticles__FiP5EMITBP5EMITG);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", EmitRipsSphere__FP6VECTORT0iP7EMITRIPP5EMITVPP4RIPGP2LO);

JUNK_WORD(0x27bd0290); // junk_00157FF0

INCLUDE_ASM("asm/nonmatchings/P2/emitter", StockSplashBig__FP6VECTORfP2SO);

void StockSplashSmall(VECTOR *ppos, float gScale, SO *psoTouch)
{
    RIP *prip = PripNewRipg(RIPT_Ripple, 0);

    if (prip)
    {
        (*(void (**)(RIP *, VECTOR *, float, SO *))(*(void **)prip))(prip, ppos, gScale, 0);
        STRUCT_OFFSET(prip, 0x1c, float) = 0.75f;

        if (STRUCT_OFFSET(psoTouch, 0x278, SO *) != 0)
        {
            STRUCT_OFFSET(prip, 0x114, int) = STRUCT_OFFSET(STRUCT_OFFSET(psoTouch, 0x278, SO *), 0xc, int);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", AddEmitoSkeleton__FP5EMITO3OIDT1ffffP2LO);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", BindEmitb__FP5EMITBP2LO);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", SetEmitdvEmitb__FP6EMITDVP5EMITB);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", CalculateEmitdvMatrix__FP6EMITDVfP7MATRIX4);

void PostExplLoad(EXPL *pexpl)
{
    PostLoLoad(pexpl);
    pexpl->pvtlo->pfnRemoveLo(pexpl);
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", CalculateExplTransform__FP4EXPLP6VECTORP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", ExplodeExpl__FP4EXPL);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", ExplodeExplParams__FP4EXPLUiP3ALOP6VECTORT3ff);

void ExplodeExplExplso(EXPL *pexpl, EXPLSO *pexplso)
{
    return;
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", LoadExplgFromBrx__FP5EXPLGP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", CloneExplg__FP5EXPLGT0);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", BindExplg__FP5EXPLG);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", ExplodeExplgExplso__FP5EXPLGP6EXPLSO);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", InitExplo__FP5EXPLO);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", LoadExploFromBrx__FP5EXPLOP18CBinaryInputStream);

void CloneExplo(EXPLO *pexplo, EXPLO *pexploBase)
{
    CloneLo(pexplo, pexploBase);
    STRUCT_OFFSET(pexplo, 0x90, EMITB *)->cref++;
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", BindExplo__FP5EXPLO);

void ExplodeExploExplso(EXPLO *pexplo, EXPLSO *pexplso)
{
    return;
}

void AddExploSkeleton(EXPLO *pexplo, OID oid, OID oidOther, float sRadius, float gDensity, float sRadiusOther, float gDensityOther)
{
	EMITB *pemitb = PemitbEnsureExplo(pexplo, ENSK_Set);
	AddEmitoSkeleton(&pemitb->emito, oid, oidOther, sRadius, gDensity, sRadiusOther, gDensityOther, pexplo);
}

EMITB *PemitbEnsureExplo(EXPLO *pexplo, ENSK ensk)
{
    if (ensk == ENSK_Set)
    {
        STRUCT_OFFSET(pexplo, 0x90, EMITB *) = PemitbCopyOnWrite(STRUCT_OFFSET(pexplo, 0x90, EMITB *));
    }

    return STRUCT_OFFSET(pexplo, 0x90, EMITB *);
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", InitExpls__FP5EXPLS);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", BindExpls__FP5EXPLS);

void HandleExplsMessage(EXPLS *pexpls, MSGID msgid, void *pv)
{
    if (msgid == MSGID_removed)
    {
        if (pv == STRUCT_OFFSET(pexpls, 0xc0, void *))
        {
            (*(void (**)(void *, EXPLS *))((char *)*(void **)pv + 0x70))(pv, pexpls);
            STRUCT_OFFSET(pexpls, 0xc0, void *) = 0;
        }
        else if (pv == STRUCT_OFFSET(pexpls, 0xc4, void *))
        {
            (*(void (**)(void *, EXPLS *))((char *)*(void **)pv + 0x70))(pv, pexpls);
            STRUCT_OFFSET(pexpls, 0xc4, void *) = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", ExplodeExplsExplso__FP5EXPLSP6EXPLSO);

SFX *PsfxEnsureExpls(EXPLS *pexpls, ENSK ensk)
{
    if (STRUCT_OFFSET(pexpls, 0xa0, SFX *) == 0)
    {
        NewSfx(&STRUCT_OFFSET(pexpls, 0xa0, SFX *));
    }

    return STRUCT_OFFSET(pexpls, 0xa0, SFX *);
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", FireExplsExplso__FP5EXPLSP6EXPLSO);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", InferExpl__FPP4EXPLP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", FireSwTimedExplodeStyles__FP2SW);

// junk_00159668
JUNK_ADDIU(10);
JUNK_WORD(0x7c450000);
JUNK_WORD(0x48220800);
