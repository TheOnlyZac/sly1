#include <emitter.h>

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

INCLUDE_ASM("asm/nonmatchings/P2/emitter", HandleEmitterMessage__FP7EMITTER5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", PemitbCopyOnWrite__FP5EMITB);

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

INCLUDE_ASM("asm/nonmatchings/P2/emitter", FUN_00155f28);

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

INCLUDE_ASM("asm/nonmatchings/P2/emitter", OnEmitterValuesChanged__FP7EMITTER);

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

INCLUDE_ASM("asm/nonmatchings/P2/emitter", StockSplashSmall__FP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", AddEmitoSkeleton__FP5EMITO3OIDT1ffffP2LO);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", BindEmitb__FP5EMITBP2LO);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", SetEmitdvEmitb__FP6EMITDVP5EMITB);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", CalculateEmitdvMatrix__FP6EMITDVfP7MATRIX4);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", PostExplLoad__FP4EXPL);

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

INCLUDE_ASM("asm/nonmatchings/P2/emitter", CloneExplo__FP5EXPLOT0);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", BindExplo__FP5EXPLO);

void ExplodeExploExplso(EXPLO *pexplo, EXPLSO *pexplso)
{
    return;
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", AddExploSkeleton__FP5EXPLO3OIDT1ffff);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", PemitbEnsureExplo__FP5EXPLO4ENSK);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", InitExpls__FP5EXPLS);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", BindExpls__FP5EXPLS);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", HandleExplsMessage__FP5EXPLS5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", ExplodeExplsExplso__FP5EXPLSP6EXPLSO);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", PsfxEnsureExpls__FP5EXPLS4ENSK);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", FireExplsExplso__FP5EXPLSP6EXPLSO);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", InferExpl__FPP4EXPLP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", FireSwTimedExplodeStyles__FP2SW);

// junk_00159668
JUNK_ADDIU(10);
JUNK_WORD(0x7c450000);
JUNK_WORD(0x48220800);
