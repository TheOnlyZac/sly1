#include <emitter.h>
#include <sw.h>
#include <clock.h>
#include <sound.h>
#include <blip.h>
#include <rip.h>
#include <util.h>
#include <memory.h>
#include <so.h>
#include <crv.h>
#include <bis.h>
#include <find.h>
#include <dl.h>
#include <basic.h>
#include <brx.h>
#include <cid.h>
#include <slotheap.h>
#include <sce/memset.h>

extern float DAT_0024a124;
extern VECTOR g_normalX;
extern VECTOR g_normalZ;

struct EMITBTAIL
{
    STRUCT_PADDING(52); // 0xd0 bytes, EMITB from 0x120
} __attribute__((aligned(16)));

extern int D_00261F70; // guard for D_0027C010 (guess)
extern int D_00261F74; // guard for D_0027C0A0 (guess)
extern EMITBTAIL D_00261F80; // default values for EMITB from 0x120 (guess)
extern EMITO D_0027C010; // default EMITO (guess)
extern EMITV D_0027C0A0; // default EMITV (guess)
extern VECTOR D_00248D30; // zero vector (guess)

INCLUDE_ASM("asm/nonmatchings/P2/emitter", InitEmitb__FP5EMITB);

void InitEmitter(EMITTER *pemitter)
{
    InitAlo(pemitter);
    STRUCT_OFFSET(pemitter, 0x2d8, int) = -1;
    STRUCT_OFFSET(pemitter, 0x2e0, float) = 10.0f;
    STRUCT_OFFSET(pemitter, 0x2f8, int) = -1;
    STRUCT_OFFSET(pemitter, 0x2fc, int) = -1;
    STRUCT_OFFSET(pemitter, 0x304, int) = -1;
    STRUCT_OFFSET(pemitter, 0x2dc, float) = 10.0f;
    STRUCT_OFFSET(pemitter, 0x300, int) = -1;
    STRUCT_OFFSET(pemitter, 0x30c, int) = -1;
    STRUCT_OFFSET(pemitter, 0x2d4, int) = -1;
    STRUCT_OFFSET(pemitter, 0x340, float) = -1.0f;
    STRUCT_OFFSET(pemitter, 0x310, int) = -1;
    InitDl((DL *)&STRUCT_OFFSET(pemitter, 0x314, int), 0x320);
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", LoadEmitmeshFromBrx__FP8EMITMESHP18CBinaryInputStream);

void LoadEmitblipColorsFromBrx(EMITBLIP *pemitblip, int crgba, LO *ploEmit, CBinaryInputStream *pbis)
{
    int c = 32;
    if (crgba <= 31)
        c = crgba;
    STRUCT_OFFSET(pemitblip, 0x4c, int) = c;
    STRUCT_OFFSET(pemitblip, 0x50, RGBA *) = (RGBA *)PvAllocSwImpl(c * 4);
    STRUCT_OFFSET(pemitblip, 0x54, int) = pbis->U8Read();
    for (int i = 0; i < crgba; i++)
    {
        uint u = pbis->U32Read();
        if (i < STRUCT_OFFSET(pemitblip, 0x4c, int))
            STRUCT_OFFSET(pemitblip, 0x50, RGBA *)[i] = *(RGBA *)&u;
    }
}

void LoadEmitterFromBrx(EMITTER *pemitter, CBinaryInputStream *pbis)
{
    EMITB *pemitb = (EMITB *)PvAllocSwImpl(0x200);
    STRUCT_OFFSET(pemitter, 0x2d0, EMITB *) = pemitb;
    InitEmitb(pemitb);
    LoadAloFromBrx(pemitter, pbis);
    CRVK crvk = (CRVK)pbis->S8Read();
    if (crvk != CRVK_Nil)
    {
        CRV *pcrv = PcrvNew(crvk);
        STRUCT_OFFSET(STRUCT_OFFSET(pemitter, 0x2d0, EMITB *), 0x20, CRV *) = pcrv;
        void (*pfn)(CRV *, CBinaryInputStream *) = pcrv->pvtcrv->pfnLoadCrvFromBrx;
        if (pfn)
            pfn(pcrv, pbis);
    }
    if (STRUCT_OFFSET(STRUCT_OFFSET(pemitter, 0x2d0, EMITB *), 0x10, int) == 4)
        LoadEmitmeshFromBrx(&STRUCT_OFFSET(STRUCT_OFFSET(pemitter, 0x2d0, EMITB *), 0x20, EMITMESH), pbis);
    int c = pbis->U16Read();
    if (c)
        LoadEmitblipColorsFromBrx(&STRUCT_OFFSET(PemitbEnsureEmitter(pemitter, ENSK_Set), 0x130, EMITBLIP), c, pemitter, pbis);
}

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

#ifdef SKIP_ASM
// @todo 95% matched (3 differing lines): target re-materializes the -1 constant for the second oid compare
void BindEmitter(EMITTER *pemitter)
{
    BindAlo(pemitter);
    EMITB *pemitb;
    if (STRUCT_OFFSET(pemitter, 0x2f8, long long) == -1 &&
        STRUCT_OFFSET(pemitter, 0x304, OID) == OID_Nil &&
        STRUCT_OFFSET(pemitter, 0x30c, OID) == OID_Nil &&
        STRUCT_OFFSET(pemitter, 0x300, OID) == OID_Nil &&
        STRUCT_OFFSET(STRUCT_OFFSET(pemitter, 0x2d0, EMITB *), 0x10, int) != 3 &&
        (STRUCT_OFFSET(STRUCT_OFFSET(pemitter, 0x2d0, EMITB *), 0x120, int) != 0 ||
         STRUCT_OFFSET(STRUCT_OFFSET(pemitter, 0x2d0, EMITB *), 0x188, OID) == OID_Nil))
    {
    }
    else
    {
        pemitb = PemitbEnsureEmitter(pemitter, ENSK_Set);
        if (STRUCT_OFFSET(pemitter, 0x2f8, OID) != OID_Nil)
        {
            LO *plo = PloFindSwObject(pemitter->psw, 0x104, STRUCT_OFFSET(pemitter, 0x2f8, OID), pemitter);
            STRUCT_OFFSET(pemitb, 0x7c, LO *) = plo;
            if (plo)
                PostSwCallback(pemitter->psw, (PFNMQ)BindEmitterCallback, pemitter, MSGID_callback, 0);
        }
        if (STRUCT_OFFSET(pemitter, 0x2fc, OID) != OID_Nil)
            STRUCT_OFFSET(pemitb, 0x1d8, LO *) = PloFindSwObject(pemitter->psw, 0x104, STRUCT_OFFSET(pemitter, 0x2fc, OID), pemitter);
        if (STRUCT_OFFSET(pemitter, 0x304, OID) != OID_Nil)
            STRUCT_OFFSET(pemitb, 0x1dc, LO *) = PloFindSwObject(pemitter->psw, 0x104, STRUCT_OFFSET(pemitter, 0x304, OID), pemitter);
        if (STRUCT_OFFSET(pemitter, 0x300, OID) != OID_Nil)
        {
            LO *plo = PloFindSwObject(pemitter->psw, 0x104, STRUCT_OFFSET(pemitter, 0x300, OID), pemitter);
            if (FIsBasicDerivedFrom(plo, (CID)3))
                STRUCT_OFFSET(pemitb, 0x1e0, LO *) = plo;
        }
        if (STRUCT_OFFSET(pemitter, 0x30c, OID) != OID_Nil)
        {
            LO *plo = PloFindSwObject(pemitter->psw, 0x104, STRUCT_OFFSET(pemitter, 0x30c, OID), pemitter);
            STRUCT_OFFSET(pemitb, 0x20, int) = STRUCT_OFFSET(plo, 0x34, int);
            STRUCT_OFFSET(pemitb, 0x7c, int) = STRUCT_OFFSET(plo, 0x18, int);
        }
    }
    BindEmitb(STRUCT_OFFSET(pemitter, 0x2d0, EMITB *), pemitter);
}
#endif

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

extern "C" void FUN_00155f28(EMITTER *pemitter)
{
    if ((STRUCT_OFFSET(pemitter, 0x2c8, ulong) & 0xC000000) != 0x8000000)
    {
        ALO *palo;
        for (palo = pemitter->paloParent; palo; palo = palo->paloParent)
        {
            if ((STRUCT_OFFSET(palo, 0x2c8, ulong) & 0xC000000) == 0x8000000)
                break;
        }
        if (palo)
            STRUCT_OFFSET(pemitter, 0x88, int) = STRUCT_OFFSET(palo, 0x88, int);
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

void ConvertEmitoPosVec(EMITO *pemito, VECTOR *ppos, VECTOR *pvec)
{
    if (STRUCT_OFFSET(pemito, 0x6c, ALO *))
    {
        ConvertAloPos(STRUCT_OFFSET(pemito, 0x6c, ALO *), 0, ppos, ppos);
        if (STRUCT_OFFSET(pemito, 0x70, int) != 3)
        {
            ConvertAloVec(STRUCT_OFFSET(pemito, 0x6c, ALO *), 0, pvec, pvec);
            int k = STRUCT_OFFSET(pemito, 0x70, int);
            if (k != 2)
            {
                VECTOR *p = ppos;
                if (k != 1)
                    p = &STRUCT_OFFSET(STRUCT_OFFSET(pemito, 0x6c, ALO *), 0x140, VECTOR);
                VECTOR vec;
                CalculateAloMovement(STRUCT_OFFSET(pemito, 0x6c, ALO *), 0, p, &vec, 0, 0, 0);
                asm("lqc2 $vf1,%1\n\tlqc2 $vf2,%2\n\tvadd.xyzw $vf1,$vf1,$vf2\n\tsqc2 $vf1,%0" : "=m"(*pvec) : "m"(*pvec), "m"(vec));
            }
        }
    }
}

void CalculateEmitvx(int cParticlePerRing, LM *plmTilt, int cParticle, EMITVX *pemitvx)
{
    if (cParticlePerRing > 0)
        STRUCT_OFFSET(pemitvx, 0, int) = cParticlePerRing < cParticle ? cParticlePerRing : cParticle;
    else
        STRUCT_OFFSET(pemitvx, 0, int) = cParticle;
    int cm1 = cParticle - 1;
    int cRing = (cm1 + STRUCT_OFFSET(pemitvx, 0, int)) / STRUCT_OFFSET(pemitvx, 0, int);
    float rad = RadNormalize(STRUCT_OFFSET(plmTilt, 4, float) - STRUCT_OFFSET(plmTilt, 0, float));
    float radStep = rad / (float)cRing;
    STRUCT_OFFSET(pemitvx, 8, float) = 6.2831855f / (float)STRUCT_OFFSET(pemitvx, 0, int);
    STRUCT_OFFSET(pemitvx, 4, float) = radStep;
    STRUCT_OFFSET(pemitvx, 0xc, float) = STRUCT_OFFSET(plmTilt, 0, float) + radStep * 0.5f;
    STRUCT_OFFSET(pemitvx, 0x10, float) = GRandInRange(0.0f, 6.2831855f);
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", ChooseEmitVelocity__FP6EMITVXffP2LMP6VECTORiT4);

/**
 * VU0 inline asm with a fake data dependency keeps the scheduling, the spill store is an artifact of the original.
 */
void ChooseEmitvVelocityAge(EMITV *pemitv, EMITVX *pemitvx, EMITO *pemito, int iParticle, VECTOR *ppos, VECTOR *pnormal, VECTOR *pv, float *ptCreated, float *ptDestroy)
{
    ChooseEmitVelocity(pemitvx, STRUCT_OFFSET(pemitv, 0x50, float), STRUCT_OFFSET(pemitv, 8, float), (LM *)pemitv, pnormal, iParticle, pv);
    float t = g_clock.t - GRandInRange(STRUCT_OFFSET(pemitv, 0x60, float), STRUCT_OFFSET(pemitv, 0x64, float));
    *ptCreated = t;
    *ptDestroy = t + STRUCT_OFFSET(pemitv, 0x54, float);
    float r = GRandInRange(STRUCT_OFFSET(pemitv, 0x58, float), STRUCT_OFFSET(pemitv, 0x5c, float));
    if (r != 0.0f)
    {
        VECTOR spill;
        asm("mfc1 $2,%1\n\tlqc2 $vf2,%2\n\tqmtc2.ni $2,$vf3\n\tlqc2 $vf1,0(%3)\n\tvadda.xyzw ACC,$vf1,$vf0\n\tvmaddx.xyzw $vf1,$vf2,$vf3x\n\tsqc2 $vf3,%0\n\tsqc2 $vf1,0(%3)" : "=m"(spill) : "f"(r), "m"(*pv), "r"(ppos) : "$2", "memory");
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", EmitRips__FP5EMITBP5EMITGiP6VECTORT3PfT5);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", EmitBlips__FP5EMITBP5EMITGiP6VECTORT3PfT5T3T3);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", OriginateParticles__FiP5EMITBP7EMITGEN);

INCLUDE_ASM("asm/nonmatchings/P2/emitter", OriginateSplineSinkParticles__FiP5EMITBR7EMITGENT2);

void EmitParticles(int cParticle, EMITB *pemitb, EMITG *pemitg)
{
    if (cParticle)
    {
        InitStackImpl();
        EMITGEN emitgen;
        EMITGEN emitgenTarget;
        emitgen.fUnknown = 1;
        OriginateParticles(cParticle, pemitb, &emitgen);
        if (STRUCT_OFFSET(pemitb, 0x120, int) == 1)
        {
            EmitRips(pemitb, pemitg, cParticle, emitgen.apos, emitgen.av, emitgen.atCreated, emitgen.atDestroy);
        }
        else
        {
            if (STRUCT_OFFSET(pemitb, 0x130, int) == 2)
            {
                OriginateSplineSinkParticles(cParticle, pemitb, emitgen, emitgenTarget);
            }
            else
            {
                emitgenTarget.apos = 0;
                emitgenTarget.av = 0;
            }
            EmitBlips(pemitb, pemitg, cParticle, emitgen.apos, emitgen.av, emitgen.atCreated, emitgen.atDestroy, emitgenTarget.apos, emitgenTarget.av);
        }
        FreeStackImpl();
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", EmitRipsSphere__FP6VECTORT0iP7EMITRIPP5EMITVPP4RIPGP2LO);

#ifdef SKIP_ASM
// @todo ~50% matched (85 differing lines): gcc keeps &emitg in an extra callee saved register, frame is 16 bytes too big
void EmitRipsSphere(VECTOR *ppos, VECTOR *pnormal, int crip, EMITRIP *pemitrip, EMITV *pemitv, RIPG **ppripg, LO *ploSubscribe)
{
    EMITB emitb;
    EMITG emitg;
    InitEmitb(&emitb);
    memset(&emitg, 0, sizeof(EMITG));
    STRUCT_OFFSET(&emitb, 0x20, qword) = STRUCT_OFFSET(ppos, 0, qword);
    STRUCT_OFFSET(&emitb, 0x60, qword) = STRUCT_OFFSET(pnormal, 0, qword);
    emitb.emitv = *pemitv;
    emitg.ppripg = ppripg;
    emitg.ploSubscribe = ploSubscribe;
    emitb.unk120 = 1;
    emitb.emitrip = *pemitrip;
    EmitParticles(crip, &emitb, &emitg);
}
#endif

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

/**
 * @todo 26 differing lines of 88: VU0 asm volatile statements, the original keeps the loop counter copy before the first asm and has a different register split (pemitb/i+1). Names are guesses.
 */
INCLUDE_ASM("asm/nonmatchings/P2/emitter", BindEmitb__FP5EMITBP2LO);

#ifdef SKIP_ASM
void BindEmitb(EMITB *pemitb, LO *plo)
{
    if (STRUCT_OFFSET(pemitb, 0x120, int) == 0 && STRUCT_OFFSET(pemitb, 0x188, OID) != OID_Nil)
        STRUCT_OFFSET(pemitb, 0x18c, LO *) = PloFindSwObject(plo->psw, 0x104, STRUCT_OFFSET(pemitb, 0x188, OID), plo);
    if (STRUCT_OFFSET(pemitb, 0x10, int) == 3)
    {
        float fSum = 0.0f;
        for (int i = 0; i < STRUCT_OFFSET(pemitb, 0x20, int); i++)
        {
            char *pe = STRUCT_OFFSET(pemitb, 0x24, char *) + i * 0x28;
            for (int j = 0; j < 2; j++)
                STRUCT_OFFSET(pe, 0x18 + j * 4, LO *) = PloFindSwObject(plo->psw, 0x104, STRUCT_OFFSET(pe, j * 4, OID), plo);
            asm volatile("lqc2 $vf2,%0" : : "m"(STRUCT_OFFSET(STRUCT_OFFSET(pe, 0x1c, LO *), 0x140, qword)));
            asm volatile("lqc2 $vf1,%0" : : "m"(STRUCT_OFFSET(STRUCT_OFFSET(pe, 0x18, LO *), 0x140, qword)));
            asm volatile("vsub.xyzw $vf1,$vf1,$vf2");
            float a = STRUCT_OFFSET(pe, 8, float);
            asm volatile("vmul.xyz $vf1,$vf1,$vf1");
            asm volatile("vaddw.x $vf2,$vf0,$vf0w");
            asm volatile("vadday.x ACC,$vf1,$vf1y");
            asm volatile("vmaddz.x $vf1,$vf2,$vf1z");
            float b = STRUCT_OFFSET(pe, 0xc, float);
            asm volatile(".word 0x4A0103BD");
            asm volatile("vwaitq");
            asm volatile("vaddq.x $vf1,$vf0,Q");
            int q;
            asm volatile("qmfc2.ni %0,$vf1" : "=r"(q));
            float len;
            asm("mtc1 %1,%0" : "=f"(len) : "r"(q));
            STRUCT_OFFSET(pe, 0x20, float) = len;
            float h = len * 0.5f;
            float t = h * (a + b);
            STRUCT_OFFSET(pe, 0x24, float) = t;
            fSum += t;
        }
        STRUCT_OFFSET(pemitb, 0x28, float) = fSum;
    }
}
#endif

/**
 * VU0 inline asm. The fake dependency variable is pinned to a scratch register so it does not disturb the register allocation. Normalizes the vector at 0xd0 of the emitb into 0x30 of the emitdv, falling back to g_normalZ for a tiny length. Field meanings are unknown.
 */
void SetEmitdvEmitb(EMITDV *pemitdv, EMITB *pemitb)
{
    STRUCT_OFFSET(pemitdv, 0, float) = STRUCT_OFFSET(pemitb, 0xc0, float);
    STRUCT_OFFSET(pemitdv, 0x10, qword) = STRUCT_OFFSET(pemitb, 0xb0, qword);
    STRUCT_OFFSET(pemitdv, 0x20, float) = STRUCT_OFFSET(pemitb, 0xc4, float);
    qword *pn = &STRUCT_OFFSET(pemitdv, 0x30, qword);
    qword nz = STRUCT_OFFSET(&g_normalZ, 0, qword);
    float len;
    register int ch asm("$8");
    asm("lqc2 $vf3,%1" : "=r"(ch) : "m"(STRUCT_OFFSET(pemitb, 0xd0, qword)));
    asm("vmul.xyz $vf1,$vf3,$vf3\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z" : "=r"(ch) : "r"(ch));
    asm(".word 0x4A0103BD" : "=r"(ch) : "r"(ch));
    asm("vwaitq" : "=r"(ch) : "r"(ch));
    asm("vaddq.x $vf1,$vf0,Q" : "=r"(ch) : "r"(ch));
    asm("qmfc2.ni $2,$vf1\n\tmtc1 $2,%0" : "=f"(len) : "r"(ch) : "$2");
    if (len < 0.0001f)
    {
        asm("qmtc2.ni %1,$vf1" : "=r"(ch) : "r"(nz), "r"(ch));
    }
    else
    {
        asm("vdiv Q,$vf0w,$vf1x" : "=r"(ch) : "r"(ch));
        asm("vwaitq" : "=r"(ch) : "r"(ch));
        asm("vmulq.xyzw $vf1,$vf3,Q" : "=r"(ch) : "r"(ch));
    }
    asm("sqc2 $vf1,%0" : "=m"(*pn) : "r"(ch));
    STRUCT_OFFSET(pemitdv, 0x40, int) = STRUCT_OFFSET(pemitb, 0xe0, int);
    STRUCT_OFFSET(pemitdv, 0x44, int) = STRUCT_OFFSET(pemitb, 0x7c, int);
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", CalculateEmitdvMatrix__FP6EMITDVfP7MATRIX4);

void PostExplLoad(EXPL *pexpl)
{
    typedef void (*PFN)(EXPL *);
    PostLoLoad(pexpl);
    STRUCT_OFFSET(pexpl->pvtlo, 0x1c, PFN)(pexpl);
}

/**
 * @todo 4 differing lines of 64: VU0 volatile asm statements; the original fills the final loop branch delay slot with the last sqc2 and aligns the loop top. Names are guesses.
 */
INCLUDE_ASM("asm/nonmatchings/P2/emitter", CalculateExplTransform__FP4EXPLP6VECTORP7MATRIX3);

#ifdef SKIP_ASM
void CalculateExplTransform(EXPL *pexpl, VECTOR *ppos, MATRIX3 *pmat)
{
    STRUCT_OFFSET(ppos, 0, qword) = STRUCT_OFFSET(&D_00248D30, 0, qword);
    STRUCT_OFFSET(pmat, 0, qword) = STRUCT_OFFSET(pexpl, 0x50, qword);
    STRUCT_OFFSET(pmat, 0x10, qword) = STRUCT_OFFSET(pexpl, 0x60, qword);
    STRUCT_OFFSET(pmat, 0x20, qword) = STRUCT_OFFSET(pexpl, 0x70, qword);
    VECTOR sA[3], sB[3];
    while (STRUCT_OFFSET(pexpl, 0x80, EXPL *))
    {
        EXPL *pp = STRUCT_OFFSET(pexpl, 0x80, EXPL *);
        asm volatile("lqc2 $vf3,%0" : : "m"(STRUCT_OFFSET(pexpl, 0x40, qword)));
        MATRIX3 *pm = (MATRIX3 *)((char *)pp + 0x50);
        asm volatile("lqc2 $vf5,%0" : : "m"(STRUCT_OFFSET(pp, 0x50, qword)));
        asm volatile("lqc2 $vf4,%0" : : "m"(STRUCT_OFFSET(pm, 0x20, qword)));
        asm volatile("lqc2 $vf2,%0" : : "m"(STRUCT_OFFSET(pm, 0x10, qword)));
        asm volatile("lqc2 $vf1,%0" : : "m"(*ppos));
        asm volatile("vmulax.xyz ACC,$vf5,$vf3x");
        asm volatile("vmadday.xyz ACC,$vf2,$vf3y");
        asm volatile("vmaddz.xyz $vf3,$vf4,$vf3z");
        asm volatile("vmulax.xyz ACC,$vf5,$vf1x");
        asm volatile("vmadday.xyz ACC,$vf2,$vf1y");
        asm volatile("vmaddz.xyz $vf1,$vf4,$vf1z");
        asm volatile("vadd.xyzw $vf1,$vf1,$vf3");
        asm volatile("sqc2 $vf1,%0" : "=m"(*ppos));
        pp = STRUCT_OFFSET(pexpl, 0x80, EXPL *);
        asm volatile("lqc2 $vf5,%0" : : "m"(STRUCT_OFFSET(pmat, 0x10, qword)));
        pm = (MATRIX3 *)((char *)pp + 0x50);
        asm volatile("lqc2 $vf4,%0" : : "m"(STRUCT_OFFSET(pp, 0x50, qword)));
        asm volatile("lqc2 $vf2,%0" : : "m"(STRUCT_OFFSET(pm, 0x20, qword)));
        asm volatile("lqc2 $vf1,%0" : : "m"(STRUCT_OFFSET(pm, 0x10, qword)));
        asm volatile("lqc2 $vf6,%0" : : "m"(STRUCT_OFFSET(pmat, 0, qword)));
        asm volatile("vmulax.xyz ACC,$vf4,$vf5x");
        asm volatile("vmadday.xyz ACC,$vf1,$vf5y");
        asm volatile("vmaddz.xyz $vf5,$vf2,$vf5z");
        asm volatile("lqc2 $vf3,%0" : : "m"(STRUCT_OFFSET(pmat, 0x20, qword)));
        asm volatile("vmulax.xyz ACC,$vf4,$vf6x");
        asm volatile("vmadday.xyz ACC,$vf1,$vf6y");
        asm volatile("vmaddz.xyz $vf6,$vf2,$vf6z");
        asm volatile("vmulax.xyz ACC,$vf4,$vf3x");
        asm volatile("vmadday.xyz ACC,$vf1,$vf3y");
        asm volatile("vmaddz.xyz $vf4,$vf2,$vf3z");
        asm volatile("sqc2 $vf5,%0" : "=m"(STRUCT_OFFSET(pmat, 0x10, qword)));
        asm volatile("sqc2 $vf4,%0" : "=m"(STRUCT_OFFSET(pmat, 0x20, qword)));
        asm volatile("sqc2 $vf6,%0" : "=m"(STRUCT_OFFSET(pmat, 0, qword)));
        asm volatile("sqc2 $vf6,%0" : "=m"(sA[0]));
        asm volatile("sqc2 $vf5,%0" : "=m"(sA[1]));
        asm volatile("sqc2 $vf4,%0" : "=m"(sA[2]));
        asm volatile("sqc2 $vf6,%0" : "=m"(sB[0]));
        pexpl = STRUCT_OFFSET(pexpl, 0x80, EXPL *);
        asm volatile("sqc2 $vf5,%0" : "=m"(sB[1]));
        asm("sqc2 $vf4,%0" : "=m"(sB[2]));
    }
    asm volatile("lqc2 $vf2,%0" : : "m"(STRUCT_OFFSET(pexpl, 0x40, qword)));
    asm volatile("lqc2 $vf1,%0" : : "m"(*ppos));
    asm volatile("vadd.xyzw $vf1,$vf1,$vf2");
    asm volatile("sqc2 $vf1,%0" : "=m"(*ppos));
}
#endif

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

void LoadExplgFromBrx(EXPLG *pexplg, CBinaryInputStream *pbis)
{
    typedef void (*PFNLOAD)(LO *, CBinaryInputStream *);
    typedef void (*PFN)(LO *);
    LoadXfmFromBrx(pexplg, pbis);
    int cplo = pbis->S16Read();
    for (int iplo = 0; iplo < cplo; iplo++)
    {
        CID cid = (CID)pbis->S16Read();
        OID oid = (OID)pbis->S16Read();
        int isplice = pbis->S16Read();
        LO *plo = PloNew(cid, pexplg->psw, pexplg->paloParent, oid, isplice);
        STRUCT_OFFSET(plo->pvtlo, 0x38, PFNLOAD)(plo, pbis);
        LO *aplo[8];
        int cpl;
        if (plo->pvtlo->grfcid & 0x100)
        {
            cpl = 0;
            for (void *p = STRUCT_OFFSET(plo, 0x2d0, void *); p; p = STRUCT_OFFSET(p, 8, void *))
            {
                if ((uint)cpl < 8)
                    aplo[cpl++] = STRUCT_OFFSET(p, 0, LO *);
            }
        }
        else
        {
            aplo[0] = plo;
            cpl = 1;
        }
        for (int ipl = 0; ipl < cpl; ipl++)
        {
            LO *pl = aplo[ipl];
            LO **paplo = &STRUCT_OFFSET(pexplg, 0x94, LO *);
            if (FIsBasicDerivedFrom(pl, (CID)0x78) || FIsBasicDerivedFrom(pl, (CID)0x7a))
            {
                STRUCT_OFFSET(pl->pvtlo, 0x1c, PFN)(pl);
                uint c = STRUCT_OFFSET(pexplg, 0x90, uint);
                if (c < 8)
                {
                    LO **pp = paplo + c; *pp = pl;
                    STRUCT_OFFSET(pexplg, 0x90, uint) = c + 1;
                    STRUCT_OFFSET(pl, 0x80, void *) = pexplg;
                }
            }
        }
    }
}

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

void LoadExploFromBrx(EXPLO *pexplo, CBinaryInputStream *pbis)
{
    EMITB *pemitb = (EMITB *)PvAllocSwClearImpl(0x200);
    STRUCT_OFFSET(pexplo, 0x90, EMITB *) = pemitb;
    InitEmitb(pemitb);
    LoadXfmFromBrx(pexplo, pbis);
    CRVK crvk = (CRVK)pbis->S8Read();
    if (crvk != CRVK_Nil)
    {
        EMITB *pemitbSet = PemitbEnsureExplo(pexplo, ENSK_Set);
        CRV *pcrv = PcrvNew(crvk);
        STRUCT_OFFSET(pemitbSet, 0x20, CRV *) = pcrv;
        void (*pfn)(CRV *, CBinaryInputStream *) = pcrv->pvtcrv->pfnLoadCrvFromBrx;
        if (pfn)
            pfn(pcrv, pbis);
    }
    if (STRUCT_OFFSET(STRUCT_OFFSET(pexplo, 0x90, EMITB *), 0x10, int) == 4)
        LoadEmitmeshFromBrx(&STRUCT_OFFSET(STRUCT_OFFSET(pexplo, 0x90, EMITB *), 0x20, EMITMESH), pbis);
    int c = pbis->U16Read();
    if (c)
        LoadEmitblipColorsFromBrx(&STRUCT_OFFSET(PemitbEnsureExplo(pexplo, ENSK_Set), 0x130, EMITBLIP), c, pexplo, pbis);
}

void CloneExplo(EXPLO *pexplo, EXPLO *pexploBase)
{
    CloneLo(pexplo, pexploBase);
    STRUCT_OFFSET(pexplo, 0x90, EMITB *)->cref++;
}

void BindExplo(EXPLO *pexplo)
{
    if (STRUCT_OFFSET(pexplo, 0x94, OID) == OID_Nil &&
        STRUCT_OFFSET(pexplo, 0x98, OID) == OID_Nil &&
        STRUCT_OFFSET(STRUCT_OFFSET(pexplo, 0x90, EMITB *), 0x10, int) != 3 &&
        (STRUCT_OFFSET(STRUCT_OFFSET(pexplo, 0x90, EMITB *), 0x120, int) != 0 ||
         STRUCT_OFFSET(STRUCT_OFFSET(pexplo, 0x90, EMITB *), 0x188, OID) == OID_Nil))
    {
    }
    else
    {
        EMITB *pemitb = PemitbEnsureExplo(pexplo, ENSK_Set);
        if (STRUCT_OFFSET(pexplo, 0x94, OID) != OID_Nil)
            STRUCT_OFFSET(pemitb, 0x7c, LO *) = PloFindSwObject(pexplo->psw, 0x104, STRUCT_OFFSET(pexplo, 0x94, OID), pexplo);
        if (STRUCT_OFFSET(pexplo, 0x98, OID) != OID_Nil)
        {
            LO *plo = PloFindSwObject(pexplo->psw, 0x104, STRUCT_OFFSET(pexplo, 0x98, OID), pexplo);
            STRUCT_OFFSET(pemitb, 0x20, int) = STRUCT_OFFSET(plo, 0x34, int);
            STRUCT_OFFSET(pemitb, 0x7c, int) = STRUCT_OFFSET(plo, 0x18, int);
        }
    }
    BindEmitb(STRUCT_OFFSET(pexplo, 0x90, EMITB *), pexplo);
}

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

void InitExpls(EXPLS *pexpls)
{
    InitExplo(pexpls);
    STRUCT_OFFSET(pexpls, 0xac, int) = -1;
    STRUCT_OFFSET(pexpls, 0xb0, int) = -1;
    STRUCT_OFFSET(pexpls, 0xb4, int) = -1;
}

void BindExpls(EXPLS *pexpls)
{
    BindExplo(pexpls);
    if (STRUCT_OFFSET(pexpls, 0xac, OID) != OID_Nil || STRUCT_OFFSET(pexpls, 0xb0, long long) != -1)
    {
        EMITB *pemitb = PemitbEnsureExplo(pexpls, ENSK_Set);
        if (STRUCT_OFFSET(pexpls, 0xac, OID) != OID_Nil)
            STRUCT_OFFSET(pemitb, 0x1d8, LO *) = PloFindSwObject(pexpls->psw, 0x104, STRUCT_OFFSET(pexpls, 0xac, OID), pexpls);
        if (STRUCT_OFFSET(pexpls, 0xb0, OID) != OID_Nil)
            STRUCT_OFFSET(pemitb, 0x1dc, LO *) = PloFindSwObject(pexpls->psw, 0x104, STRUCT_OFFSET(pexpls, 0xb0, OID), pexpls);
        if (STRUCT_OFFSET(pexpls, 0xb4, OID) != OID_Nil)
        {
            LO *plo = PloFindSwObject(pexpls->psw, 0x104, STRUCT_OFFSET(pexpls, 0xb4, OID), pexpls);
            if (FIsBasicDerivedFrom(plo, (CID)3))
                STRUCT_OFFSET(pemitb, 0x1e0, LO *) = plo;
        }
    }
}

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

void ExplodeExplsExplso(EXPLS *pexpls, EXPLSO *pexplso)
{
    int fQueued = 0;
    if (0.0f < STRUCT_OFFSET(pexpls, 0xb8, float))
    {
        EXPLSTE *pexplste = (EXPLSTE *)PvAllocSlotheapUnsafe(&pexpls->psw->slotheapExplste);
        if (pexplste)
        {
            pexplste->pexpls = pexpls;
            pexplste->explso = *pexplso;
            fQueued = 1;
            pexplste->tFire = g_clock.t + STRUCT_OFFSET(pexpls, 0xb8, float);
            ClearDle(&pexplste->dle);
            AppendDlEntry(&pexpls->psw->dlExplste, pexplste);
        }
    }
    if (!fQueued)
        FireExplsExplso(pexpls, pexplso);
}

SFX *PsfxEnsureExpls(EXPLS *pexpls, ENSK ensk)
{
    if (!STRUCT_OFFSET(pexpls, 0xa0, SFX *))
    {
        NewSfx(&STRUCT_OFFSET(pexpls, 0xa0, SFX *));
    }
    return STRUCT_OFFSET(pexpls, 0xa0, SFX *);
}

INCLUDE_ASM("asm/nonmatchings/P2/emitter", FireExplsExplso__FP5EXPLSP6EXPLSO);

void InferExpl(EXPL **ppexpl, ALO *palo)
{
    LO *aplo[32];
    int c = CploFindSwObjectsByClass(palo->psw, 0x202, (CID)0x77, palo, 32, aplo);
    switch (c)
    {
    case 0:
        *ppexpl = 0;
        break;
    case 1:
        *ppexpl = (EXPL *)aplo[0];
        break;
    default:
        typedef void (*PFN)(LO *);
        EXPLG *pexplg = (EXPLG *)PloNew((CID)0x78, palo->psw, palo, (OID)0x202, -1);
        int i = 0;
        int n = 8;
        if (c <= 7)
            n = c;
        STRUCT_OFFSET(pexplg, 0x90, int) = n;
        CopyAb(&STRUCT_OFFSET(pexplg, 0x94, int), aplo, n * 4);
        for (LO **pplo = aplo; i < c; i++, pplo++)
        {
            LO *plo = *pplo;
            if (i < STRUCT_OFFSET(pexplg, 0x90, int))
                STRUCT_OFFSET(plo, 0x80, void *) = pexplg;
            STRUCT_OFFSET(plo->pvtlo, 0x1c, PFN)(plo);
        }
        *ppexpl = pexplg;
    }
}

void FireSwTimedExplodeStyles(SW *psw)
{
    DLI dli(&psw->dlExplste);
    for (EXPLSTE *pexplste = (EXPLSTE *)dli.PvNext(); pexplste; pexplste = (EXPLSTE *)dli.PvNext())
    {
        if (g_clock.t < pexplste->tFire)
            continue;
        FireExplsExplso(pexplste->pexpls, &pexplste->explso);
        RemoveDlEntry(&psw->dlExplste, pexplste);
        FreeSlotheapPv(&psw->slotheapExplste, pexplste);
    }
}

JUNK_NOP();

// junk_00159668
JUNK_ADDIU(10);
JUNK_WORD(0x7c450000);
JUNK_WORD(0x48220800);
