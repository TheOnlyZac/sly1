#include <emitter.h>
#include <sw.h>
#include <clock.h>
#include <sound.h>
#include <blip.h>
#include <rip.h>
#include <util.h>
#include <memory.h>
#include <so.h>
#include <sce/memset.h>

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

void BindEmitterCallback(EMITTER *pemitter, MSGID msgid, void *pvData)
{
    typedef void (*PFN)(EMITTER *, void *);
    STRUCT_OFFSET(pemitter->pvtlo, 0x64, PFN)(pemitter, STRUCT_OFFSET(STRUCT_OFFSET(pemitter, 0x2d0, EMITB *), 0x7c, void *));
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", BindEmitter__FP7EMITTER);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", PostEmitterLoad__FP7EMITTER);

void HandleEmitterMessage(EMITTER *pemitter, MSGID msgid, void *pv)
{
    typedef void (*PFN)(void *, EMITTER *);
    if (msgid == MSGID_removed)
    {
        if (pv == STRUCT_OFFSET(pemitter, 0x344, void *))
        {
            STRUCT_OFFSET(STRUCT_OFFSET(pv, 0, void *), 0x70, PFN)(pv, pemitter);
            STRUCT_OFFSET(pemitter, 0x344, void *) = 0;
        }
        else if (pv == STRUCT_OFFSET(pemitter, 0x348, void *))
        {
            STRUCT_OFFSET(STRUCT_OFFSET(pv, 0, void *), 0x70, PFN)(pv, pemitter);
            STRUCT_OFFSET(pemitter, 0x348, void *) = 0;
        }
    }
}

EMITB *PemitbCopyOnWrite(EMITB *pemitb)
{
    if (pemitb->cref >= 2)
    {
        EMITB *pemitbNew = (EMITB *)PvAllocSwCopyImpl(0x200, pemitb);
        if (STRUCT_OFFSET(pemitb, 0x10, int) == 3)
        {
            if (STRUCT_OFFSET(pemitb, 0x24, void *))
            {
                STRUCT_OFFSET(pemitbNew, 0x24, void *) = PvAllocSwCopyImpl(STRUCT_OFFSET(pemitb, 0x20, int) * 0x28, STRUCT_OFFSET(pemitb, 0x24, void *));
            }
        }
        pemitbNew->cref = 1;
        pemitb->cref--;
        return pemitbNew;
    }
    return pemitb;
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

int FPausedEmitter(EMITTER *pemitter)
{
    if (g_clock.t < STRUCT_OFFSET(pemitter, 0x340, float)) // pemitter->tUnpause
        return 1;
    int v = STRUCT_OFFSET(pemitter, 0x2d4, int);
    if (v < 2)
    {
        if (v >= 0)
        {
            if (STRUCT_OFFSET(pemitter, 0x2d8, int) == 0)
                return 1;
        }
    }
    return 0;
}

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
    if (STRUCT_OFFSET(pemitter, 0x348, BLIPG *))
        SetBlipgEmitb(STRUCT_OFFSET(pemitter, 0x348, BLIPG *), STRUCT_OFFSET(pemitter, 0x2d0, EMITB *));
    if (STRUCT_OFFSET(pemitter, 0x344, RIPG *))
        SetRipgEmitb(STRUCT_OFFSET(pemitter, 0x344, RIPG *), STRUCT_OFFSET(pemitter, 0x2d0, EMITB *));
    float g;
    if (STRUCT_OFFSET(pemitter, 0x2d4, int) == 3)
        g = GRandInRange(STRUCT_OFFSET(pemitter, 0x2dc, float), STRUCT_OFFSET(pemitter, 0x2e0, float)) * 60.0f;
    else
        g = GRandInRange(STRUCT_OFFSET(pemitter, 0x2dc, float), STRUCT_OFFSET(pemitter, 0x2e0, float));
    STRUCT_OFFSET(pemitter, 0x328, float) = g;
}

void SetEmitterParticleCount(EMITTER *pemitter, int cParticle)
{
    int v = STRUCT_OFFSET(pemitter, 0x2d4, int);
    if (v != -1)
    {
        if (v == 0)
        {
            if (cParticle == 0)
                PauseEmitterIndefinite(pemitter);
            else if (cParticle == -1)
                UnpauseEmitter(pemitter);
            else
                STRUCT_OFFSET(pemitter, 0x2d8, int) = cParticle;
        }
    }
    else
        STRUCT_OFFSET(pemitter, 0x2d8, int) = cParticle;
    STRUCT_OFFSET(pemitter, 0x34c, int) = 1;
}

void SetEmitterAutoPause(EMITTER *pemitter, int fAutoPause)
{
    STRUCT_OFFSET(pemitter, 0x308, int) = fAutoPause; // pemitter->fAutoPause
    STRUCT_OFFSET(pemitter, 0x34c, int) = 1; // pemitter->fValuesChanged
}

void SetEmitbRipt(EMITB *pemitb, RIPT ript)
{
    STRUCT_OFFSET(pemitb, 0x1b0, RIPT) = ript;
    memset(&STRUCT_OFFSET(pemitb, 0x1f0, int), 0, 0xc);
    if (ript != RIPT_Shrapnel)
    {
        if (ript == RIPT_Emitter)
        {
            STRUCT_OFFSET(pemitb, 0x1f0, int) = -1;
            STRUCT_OFFSET(pemitb, 0x1f4, float) = 10.0f;
        }
    }
    else
    {
        STRUCT_OFFSET(pemitb, 0x1f0, float) = 25.0f;
        STRUCT_OFFSET(pemitb, 0x1f4, float) = 0.8f;
        STRUCT_OFFSET(pemitb, 0x1f8, float) = 0.8f;
    }
}

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

void StandardSmokeCloud(VECTOR *ppos, float sRadius)
{
    typedef void (*PFN)(void *, void *);
    void *pexpl = STRUCT_OFFSET(g_psw, 0x1d0c, void *);
    if (pexpl)
    {
        EXPLSO explso;
        explso.grfexplso = 0xc;
        STRUCT_OFFSET(&explso, 0x20, qword) = STRUCT_OFFSET(ppos, 0, qword);
        explso.rScale = 0.0f;
        explso.sRadius = sRadius;
        STRUCT_OFFSET(STRUCT_OFFSET(pexpl, 0, void *), 0x7c, PFN)(pexpl, &explso);
    }
}

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

void StockSplashBig(VECTOR *ppos, float gScale, SO *psoTouch)
{
    typedef void (*PFN)(LO *, EXPLSO *);
    EXPLG *pexplg = STRUCT_OFFSET(g_psw, 0x1ce8, EXPLG *);
    if (pexplg)
    {
        for (int i = 0; i < STRUCT_OFFSET(pexplg, 0x90, int); i++)
        {
            EXPLSO explso;
            LO *plo = (&STRUCT_OFFSET(pexplg, 0x94, LO *))[i];
            explso.grfexplso = 4;
            STRUCT_OFFSET(&explso, 0x20, qword) = STRUCT_OFFSET(ppos, 0, qword);
            void *pemitb = STRUCT_OFFSET(plo, 0x90, void *);
            if (STRUCT_OFFSET(pemitb, 0x120, int) == 1)
            {
                int ript = STRUCT_OFFSET(pemitb, 0x1b0, int);
                if (ript != 2)
                {
                    if (ript == 4)
                    {
                        explso.grfexplso = 0x14;
                        explso.rScale = gScale;
                    }
                }
                else
                {
                    explso.grfexplso = 0x24;
                    explso.psoTouch = psoTouch;
                }
            }
            STRUCT_OFFSET(plo->pvtlo, 0x7c, PFN)(plo, &explso);
        }
    }
}

void StockSplashSmall(VECTOR *ppos, float gScale, SO *psoTouch)
{
    typedef void (*PFN)(RIP *, VECTOR *, float, int);
    RIP *prip = PripNewRipg(RIPT_Ripple, 0);
    if (prip)
    {
        STRUCT_OFFSET(STRUCT_OFFSET(prip, 0, void *), 0, PFN)(prip, ppos, gScale, 0);
        STRUCT_OFFSET(prip, 0x1c, float) = 0.75f;
        void *p = STRUCT_OFFSET(psoTouch, 0x278, void *);
        if (p)
            STRUCT_OFFSET(prip, 0x114, int) = STRUCT_OFFSET(p, 0xc, int);
    }
}

void AddEmitoSkeleton(EMITO *pemito, OID oid, OID oidOther, float sRadius, float gDensity, float sRadiusOther, float gDensityOther, LO *ploContext)
{
    STRUCT_OFFSET(pemito, 0, int) = 3;
    if (!STRUCT_OFFSET(pemito, 0x14, void *))
        STRUCT_OFFSET(pemito, 0x14, void *) = PvAllocSwClearImpl(0x500);
    int n = STRUCT_OFFSET(pemito, 0x10, int);
    if (n < 0x20)
    {
        uint8_t *p = STRUCT_OFFSET(pemito, 0x14, uint8_t *) + n * 0x28;
        STRUCT_OFFSET(pemito, 0x10, int) = n + 1;
        STRUCT_OFFSET(p, 0, OID) = oid;
        STRUCT_OFFSET(p, 4, OID) = oidOther;
        STRUCT_OFFSET(p, 8, float) = gDensity;
        if (gDensityOther >= 0.0f)
            STRUCT_OFFSET(p, 0xc, float) = gDensityOther;
        else
            STRUCT_OFFSET(p, 0xc, float) = gDensity;
        STRUCT_OFFSET(p, 0x10, float) = sRadius;
        if (sRadiusOther >= 0.0f)
            STRUCT_OFFSET(p, 0x14, float) = sRadiusOther;
        else
            STRUCT_OFFSET(p, 0x14, float) = sRadius;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", BindEmitb__FP5EMITBP2LO);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", SetEmitdvEmitb__FP6EMITDVP5EMITB);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", CalculateEmitdvMatrix__FP6EMITDVfP7MATRIX4);

void PostExplLoad(EXPL *pexpl)
{
    typedef void (*PFN)(EXPL *);
    PostLoLoad(pexpl);
    STRUCT_OFFSET(pexpl->pvtlo, 0x1c, PFN)(pexpl);
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", CalculateExplTransform__FP4EXPLP6VECTORP7MATRIX3);

void ExplodeExpl(EXPL *pexpl)
{
    typedef void (*PFN)(EXPL *, EXPLSO *);
    EXPLSO explso;
    memset(&explso, 0, sizeof(EXPLSO));
    STRUCT_OFFSET(pexpl->pvtlo, 0x7c, PFN)(pexpl, &explso);
}

void ExplodeExplParams(EXPL *pexpl, GRFEXPLSO grfexplso, ALO *paloReference, VECTOR *pvec, VECTOR *pposOrigin, float rScale, float sRadius)
{
    typedef void (*PFN)(EXPL *, EXPLSO *);
    EXPLSO explso;
    explso.grfexplso = grfexplso;
    explso.paloReference = paloReference;
    STRUCT_OFFSET(&explso, 0x10, qword) = STRUCT_OFFSET(pvec, 0, qword);
    STRUCT_OFFSET(&explso, 0x20, qword) = STRUCT_OFFSET(pposOrigin, 0, qword);
    explso.rScale = rScale;
    explso.sRadius = sRadius;
    STRUCT_OFFSET(pexpl->pvtlo, 0x7c, PFN)(pexpl, &explso);
}

void ExplodeExplExplso(EXPL *pexpl, EXPLSO *pexplso)
{
    return;
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", LoadExplgFromBrx__FP5EXPLGP18CBinaryInputStream);

void CloneExplg(EXPLG *pexplg, EXPLG *pexplgBase)
{
    typedef void (*PFN)(LO *);
    CloneLo(pexplg, pexplgBase);
    for (int i = 0; i < STRUCT_OFFSET(pexplg, 0x90, int); i++)
    {
        LO **pplo = &(&STRUCT_OFFSET(pexplg, 0x94, LO *))[i];
        LO *plo = PloCloneLo(*pplo, pexplg->psw, pexplg->paloParent);
        STRUCT_OFFSET(plo->pvtlo, 0x1c, PFN)(plo);
        *pplo = plo;
        STRUCT_OFFSET(plo, 0x80, void *) = pexplg;
    }
}

void BindExplg(EXPLG *pexplg)
{
    for (int i = 0; i < STRUCT_OFFSET(pexplg, 0x90, int); i++)
    {
        LO *plo = (&STRUCT_OFFSET(pexplg, 0x94, LO *))[i];
        void (*pfn)(LO *) = plo->pvtlo->pfnBindLo;
        if (pfn)
            pfn(plo);
    }
}

void ExplodeExplgExplso(EXPLG *pexplg, EXPLSO *pexplso)
{
    typedef void (*PFN)(LO *, EXPLSO *);
    for (int i = 0; i < STRUCT_OFFSET(pexplg, 0x90, int); i++)
    {
        LO *plo = (&STRUCT_OFFSET(pexplg, 0x94, LO *))[i];
        STRUCT_OFFSET(plo->pvtlo, 0x7c, PFN)(plo, pexplso);
    }
}

void InitExplo(EXPLO *pexplo)
{
    InitXfm(pexplo);
    STRUCT_OFFSET(pexplo, 0x94, int) = -1;
    STRUCT_OFFSET(pexplo, 0x98, int) = -1;
}

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

INCLUDE_ASM("asm/nonmatchings/P2/emitter", AddExploSkeleton__FP5EXPLO3OIDT1ffff);

EMITB *PemitbEnsureExplo(EXPLO *pexplo, ENSK ensk)
{
    if (ensk == ENSK_Set)
    {
        STRUCT_OFFSET(pexplo, 0x90, EMITB *) = PemitbCopyOnWrite(STRUCT_OFFSET(pexplo, 0x90, EMITB *));
    }
    return STRUCT_OFFSET(pexplo, 0x90, EMITB *);
}

void InitExpls(EXPLS *pexpls)
{
    InitExplo(pexpls);
    STRUCT_OFFSET(pexpls, 0xac, int) = -1;
    STRUCT_OFFSET(pexpls, 0xb0, int) = -1;
    STRUCT_OFFSET(pexpls, 0xb4, int) = -1;
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", BindExpls__FP5EXPLS);

void HandleExplsMessage(EXPLS *pexpls, MSGID msgid, void *pv)
{
    typedef void (*PFN)(void *, EXPLS *);
    if (msgid == MSGID_removed)
    {
        if (pv == STRUCT_OFFSET(pexpls, 0xc0, void *))
        {
            STRUCT_OFFSET(STRUCT_OFFSET(pv, 0, void *), 0x70, PFN)(pv, pexpls);
            STRUCT_OFFSET(pexpls, 0xc0, void *) = 0;
        }
        else if (pv == STRUCT_OFFSET(pexpls, 0xc4, void *))
        {
            STRUCT_OFFSET(STRUCT_OFFSET(pv, 0, void *), 0x70, PFN)(pv, pexpls);
            STRUCT_OFFSET(pexpls, 0xc4, void *) = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", ExplodeExplsExplso__FP5EXPLSP6EXPLSO);

SFX *PsfxEnsureExpls(EXPLS *pexpls, ENSK ensk)
{
    if (!STRUCT_OFFSET(pexpls, 0xa0, SFX *))
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
