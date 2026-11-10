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
extern const MATRIX4 g_mat4Identity;
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

/**
 * @todo 18 differing lines of 144: register choice for the 200 constant and the copy pointers in the second default block. The default EMITO/EMITV/tail live in D_0027C010, D_0027C0A0 and D_00261F80 with init guards D_00261F70/74. Names are guesses.
 */
INCLUDE_ASM("asm/nonmatchings/P2/emitter", InitEmitb__FP5EMITB);

#ifdef SKIP_ASM
void InitEmitb(EMITB *pemitb)
{
    if (!D_00261F70)
    {
        EMITO *pdst = &D_0027C010;
        EMITO emito;
        memset(&emito, 0, sizeof(EMITO));
        STRUCT_OFFSET(&emito, 0x10, qword) = STRUCT_OFFSET(&D_00248D30, 0, qword);
        STRUCT_OFFSET(&emito, 0x50, qword) = STRUCT_OFFSET(&g_normalX, 0, qword);
        STRUCT_OFFSET(&emito, 0x80, qword) = STRUCT_OFFSET(&D_00248D30, 0, qword);
        *pdst = emito;
        D_00261F70 = 1;
    }
    if (!D_00261F74)
    {
        EMITV *pdst2 = &D_0027C0A0;
        EMITV emitv;
        memset(&emitv, 0, sizeof(EMITV));
        STRUCT_OFFSET(&emitv, 0, float) = 750.0f;
        STRUCT_OFFSET(&emitv, 0x18, float) = -1500.0f;
        STRUCT_OFFSET(&emitv, 4, float) = 750.0f;
        STRUCT_OFFSET(&emitv, 0x30, qword) = STRUCT_OFFSET(&g_normalZ, 0, qword);
        STRUCT_OFFSET(&emitv, 0x50, float) = 1.0f;
        STRUCT_OFFSET(&emitv, 0x54, float) = 1.0f;
        STRUCT_OFFSET(&emitv, 0x70, float) = 1.0f;
        STRUCT_OFFSET(&emitv, 0x78, float) = -1.0f;
        STRUCT_OFFSET(&emitv, 8, float) = 1.0f;
        STRUCT_OFFSET(&emitv, 0x4c, int) = 200;
        STRUCT_OFFSET(&emitv, 0x20, float) = -1.0f;
        *pdst2 = emitv;
        D_00261F74 = 1;
    }
    memset(pemitb, 0, sizeof(EMITB));
    pemitb->cref = 1;
    pemitb->emito = D_0027C010;
    pemitb->emitv = D_0027C0A0;
    STRUCT_OFFSET(pemitb, 0x120, EMITBTAIL) = D_00261F80;
}
#endif

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

/**
 * @todo 128 differing lines of 150: structure matches, differences are the callee saved register split (emitmesh/ptri swapped) and the loop counters. VU0 volatile asm. Names are guesses.
 */
INCLUDE_ASM("asm/nonmatchings/P2/emitter", LoadEmitmeshFromBrx__FP8EMITMESHP18CBinaryInputStream);

#ifdef SKIP_ASM
void LoadEmitmeshFromBrx(EMITMESH *pemitmesh, CBinaryInputStream *pbis)
{
    STRUCT_OFFSET(pemitmesh, 0, int) = pbis->U16Read();
    STRUCT_OFFSET(pemitmesh, 4, VECTOR *) = (VECTOR *)PvAllocSwImpl(STRUCT_OFFSET(pemitmesh, 0, int) * 16);
    STRUCT_OFFSET(pemitmesh, 0x10, VECTOR *) = (VECTOR *)PvAllocSwClearImpl(STRUCT_OFFSET(pemitmesh, 0, int) * 16);
    for (int i = 0; i < STRUCT_OFFSET(pemitmesh, 0, int); i++)
        pbis->ReadVector(&STRUCT_OFFSET(pemitmesh, 4, VECTOR *)[i]);
    STRUCT_OFFSET(pemitmesh, 8, int) = pbis->U16Read();
    STRUCT_OFFSET(pemitmesh, 0xc, int *) = (int *)PvAllocSwImpl(STRUCT_OFFSET(pemitmesh, 8, int) * 16);
    STRUCT_OFFSET(pemitmesh, 0x14, float) = 0.0f;
    for (int i = 0; i < STRUCT_OFFSET(pemitmesh, 8, int); i++)
    {
        int *ptri = STRUCT_OFFSET(pemitmesh, 0xc, int *) + i * 4;
        for (int k = 0; k < 3; k++)
            ptri[k] = pbis->U16Read();
        float area = pbis->F32Read();
        STRUCT_OFFSET(ptri, 0xc, float) = area;
        STRUCT_OFFSET(pemitmesh, 0x14, float) += area;
        VECTOR *pv = STRUCT_OFFSET(pemitmesh, 4, VECTOR *);
        VECTOR *p0 = &pv[ptri[0]];
        VECTOR *p1 = &pv[ptri[1]];
        VECTOR *p2 = &pv[ptri[2]];
        asm volatile("lqc2 $vf3,%0" : : "m"(*p0));
        asm volatile("lqc2 $vf2,%0" : : "m"(*p1));
        asm volatile("lqc2 $vf1,%0" : : "m"(*p2));
        asm volatile("vsub.xyzw $vf2,$vf2,$vf3");
        asm volatile("vsub.xyzw $vf1,$vf1,$vf3");
        asm volatile("vopmula.xyz ACC,$vf2,$vf1");
        asm volatile("vopmsub.xyz $vf2,$vf1,$vf2");
        asm volatile("vsub.w $vf2,$vf2,$vf2");
        int *pidx = ptri;
        for (int k = 0; k < 3;)
        {
            asm volatile("");
            VECTOR *pn = &STRUCT_OFFSET(pemitmesh, 0x10, VECTOR *)[*pidx++];
            k++;
            asm volatile("lqc2 $vf1,%0" : : "m"(*pn));
            asm volatile("vadd.xyzw $vf1,$vf1,$vf2");
            asm volatile("sqc2 $vf1,%0" : "=m"(*pn));
        }
    }
    pbis->ReadVector((VECTOR *)&STRUCT_OFFSET(pemitmesh, 0x20, int));
    for (int i = 0; i < STRUCT_OFFSET(pemitmesh, 0, int); i++)
    {
        VECTOR *pn = &STRUCT_OFFSET(pemitmesh, 0x10, VECTOR *)[i];
        qword nz = STRUCT_OFFSET(&g_normalZ, 0, qword);
        float len;
        int q;
        asm volatile("lqc2 $vf3,%0" : : "m"(*pn));
        asm volatile("vmul.xyz $vf1,$vf3,$vf3");
        asm volatile("vaddw.x $vf2,$vf0,$vf0w");
        asm volatile("vadday.x ACC,$vf1,$vf1y");
        asm volatile("vmaddz.x $vf1,$vf2,$vf1z");
        asm volatile("vsqrt Q,$vf1x");
        asm volatile("vwaitq");
        asm volatile("vaddq.x $vf1,$vf0,Q");
        asm volatile("qmfc2.ni %0,$vf1" : "=r"(q));
        asm("mtc1 %1,%0" : "=f"(len) : "r"(q));
        if (len < 0.0001f)
        {
            asm volatile("qmtc2.ni %0,$vf1" : : "r"(nz));
        }
        else
        {
            asm volatile("vdiv Q,$vf0w,$vf1x");
            asm volatile("vwaitq");
            asm volatile("vmulq.xyzw $vf1,$vf3,Q");
        }
        asm volatile("sqc2 $vf1,%0" : "=m"(*pn));
    }
}
#endif

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

/**
 * @todo 95 differing lines of 284: structure matches (switch with shared case 2/3 tail, clone of the emitter). Differences are branch layout of the first state selection, 2D/3D volume branch scheduling and the order of the clone field copies. Names and offsets are guesses.
 */
INCLUDE_ASM("asm/nonmatchings/P2/emitter", PostEmitterLoad__FP7EMITTER);

#ifdef SKIP_ASM
struct FPAIR { float a, b; };
extern float D_0024A120;
extern "C" void FUN_00155f28(EMITTER *pemitter);

void PostEmitterLoad(EMITTER *pemitter)
{
    PostAloLoad(pemitter);
    if (STRUCT_OFFSET(STRUCT_OFFSET(pemitter, 0x2d0, EMITB *), 0x1b0, int) != -1)
        STRUCT_OFFSET(STRUCT_OFFSET(pemitter, 0x2d0, EMITB *), 0x120, int) = 1;
    if (STRUCT_OFFSET(pemitter, 0x2d4, int) == -1)
    {
        if (STRUCT_OFFSET(pemitter, 0x2e8, float) != 0.0f)
            goto set3;
        if (STRUCT_OFFSET(pemitter, 0x308, int) == 0)
            goto set01;
    set3:
        STRUCT_OFFSET(pemitter, 0x2d4, int) = 3;
        goto done;
    set01:
        STRUCT_OFFSET(pemitter, 0x2d4, int) = STRUCT_OFFSET(pemitter, 0x2f4, float) == 0.0f ? 0 : 1;
    }
done:
    switch (STRUCT_OFFSET(pemitter, 0x2d4, int))
    {
    case 2:
        STRUCT_OFFSET(pemitter, 0x330, float) = D_0024A120;
        STRUCT_OFFSET(pemitter, 0x328, float) = GRandInRange(STRUCT_OFFSET(pemitter, 0x2dc, float), STRUCT_OFFSET(pemitter, 0x2e0, float));
        goto tail;
    case 3:
        STRUCT_OFFSET(pemitter, 0x330, float) = D_0024A120;
        STRUCT_OFFSET(pemitter, 0x328, float) = GRandInRange(STRUCT_OFFSET(pemitter, 0x2dc, float), STRUCT_OFFSET(pemitter, 0x2e0, float)) * 60.0f;
    tail:
        if (STRUCT_OFFSET(pemitter, 0x308, int))
            PauseEmitterIndefinite(pemitter);
        else if (GRandInRange(0.0f, 1.0f) <= STRUCT_OFFSET(pemitter, 0x2e8, float))
            PauseEmitter(pemitter, GRandInRange(STRUCT_OFFSET(pemitter, 0x2ec, float), STRUCT_OFFSET(pemitter, 0x2f0, float)));
        break;
    case 0:
    case 1:
        STRUCT_OFFSET(pemitter, 0x330, float) = 1.0f;
        STRUCT_OFFSET(pemitter, 0x32c, float) = 1.0f;
        STRUCT_OFFSET(pemitter, 0x328, float) = GRandInRange(STRUCT_OFFSET(pemitter, 0x2dc, float), STRUCT_OFFSET(pemitter, 0x2e0, float));
        break;
    }
    STRUCT_OFFSET(pemitter, 0x334, float) = 1.0f;
    EMITB *pemitb = STRUCT_OFFSET(pemitter, 0x2d0, EMITB *);
    if (STRUCT_OFFSET(pemitb, 0x10, int) == 1)
    {
        float *pf = &STRUCT_OFFSET(pemitb, 0x20, float);
        if (STRUCT_OFFSET(pemitter, 0x2f8, OID) != OID_Nil)
        {
            float dx = fabsf(pf[4] - STRUCT_OFFSET(pemitb, 0x20, float));
            float dy = fabsf(pf[5] - pf[1]);
            float dz = fabsf(pf[6] - pf[2]);
            float m;
            if (dy < dx)
                m = dx > dz ? dx : dz;
            else
                m = dy > dz ? dy : dz;
            STRUCT_OFFSET(pemitter, 0x338, float) = m * 0.5f;
        }
        if (STRUCT_OFFSET(pemitter, 0x2e4, int))
        {
            float v;
            if (STRUCT_OFFSET(pemitter, 0x2f4, float) != 0.0f)
                v = (pf[4] - pf[0]) * (pf[5] - pf[1]) * (pf[6] - pf[2]) * 0.000001f;
            else
                v = (pf[5] - pf[1]) * (pf[6] - pf[2]) * 0.0001f;
            STRUCT_OFFSET(pemitter, 0x334, float) = v;
        }
    }
    if (STRUCT_OFFSET(pemitter, 0x310, OID) != OID_Nil)
    {
        EMITTER *pnew = (EMITTER *)PloFindSwChild(pemitter->psw, STRUCT_OFFSET(pemitter, 0x310, OID), 0);
        if (pnew)
        {
            STRUCT_OFFSET(pemitter, 0x34c, int) = 0;
        }
        else
        {
            pnew = (EMITTER *)PloNew((CID)0x50, pemitter->psw, 0, STRUCT_OFFSET(pemitter, 0x310, OID), -1);
            EMITB *pb = (EMITB *)PvAllocSwImpl(0x200);
            STRUCT_OFFSET(pnew, 0x2d0, EMITB *) = pb;
            *pb = *STRUCT_OFFSET(pemitter, 0x2d0, EMITB *);
            STRUCT_OFFSET(STRUCT_OFFSET(pnew, 0x2d0, EMITB *), 0x7c, int) = 0;
            STRUCT_OFFSET(pnew, 0x2d4, int) = STRUCT_OFFSET(pemitter, 0x2d4, int);
            STRUCT_OFFSET(pnew, 0x2d8, int) = STRUCT_OFFSET(pemitter, 0x2d8, int);
            STRUCT_OFFSET(pnew, 0x2dc, FPAIR) = STRUCT_OFFSET(pemitter, 0x2dc, FPAIR);
            STRUCT_OFFSET(pnew, 0x2e4, int) = STRUCT_OFFSET(pemitter, 0x2e4, int);
            STRUCT_OFFSET(pnew, 0x2e8, float) = STRUCT_OFFSET(pemitter, 0x2e8, float);
            STRUCT_OFFSET(pnew, 0x2ec, FPAIR) = STRUCT_OFFSET(pemitter, 0x2ec, FPAIR);
            STRUCT_OFFSET(pnew, 0x2f4, float) = STRUCT_OFFSET(pemitter, 0x2f4, float);
            STRUCT_OFFSET(pnew, 0x308, int) = STRUCT_OFFSET(pemitter, 0x308, int);
            STRUCT_OFFSET(pnew, 0x2c8, ulong) = (STRUCT_OFFSET(pnew, 0x2c8, ulong) | ((ulong)1 << 32)) & ~((ulong)0x300 << 32) | ((ulong)1 << 40);
            qword *pq = &STRUCT_OFFSET(pnew, 0x110, qword);
            pq[0] = STRUCT_OFFSET(pemitter, 0xd0, qword);
            pq[1] = STRUCT_OFFSET(pemitter, 0xe0, qword);
            pq[2] = STRUCT_OFFSET(pemitter, 0xf0, qword);
            STRUCT_OFFSET(pnew, 0xd0, qword) = STRUCT_OFFSET(pemitter, 0xd0, qword);
            STRUCT_OFFSET(pnew, 0xe0, qword) = pq[1];
            STRUCT_OFFSET(pnew, 0xf0, qword) = pq[2];
            typedef void (*PFN)(EMITTER *);
            PFN pfn = STRUCT_OFFSET(pnew->pvtlo, 0x4c, PFN);
            if (pfn)
                pfn(pnew);
            STRUCT_OFFSET(pemitter, 0x34c, int) = 0;
        }
        AppendDlEntry((DL *)&STRUCT_OFFSET(pnew, 0x314, int), pemitter);
        FUN_00155f28(pemitter);
    }
}
#endif

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

/**
 * Wraps the particle positions of the emitter cells into a box around the emitter. VU0 volatile asm in source order, the empty asms keep gcc from filling the branch delay slots so the assembler does it like the original. vUnused only matches the frame size. Names are guesses.
 */
void ModifyEmitterParticles(EMITTER *pemitter)
{
    float r = STRUCT_OFFSET(pemitter, 0x338, float);
    if (r > 0.0001f)
    {
        VECTOR vRange;
        VECTOR vLo;
        VECTOR vHi;
        VECTOR vDelta;
        VECTOR vUnused;
        qword b;
        asm("mfc1 $3,%1\n\tpextlw $3,$3,$3\n\tpextlw %0,$3,$3" : "=r"(b) : "f"(r) : "$3");
        EMITB *pemitb = STRUCT_OFFSET(pemitter, 0x2d0, EMITB *);
        asm volatile("qmtc2.ni %0,$vf2" : : "r"(b));
        asm volatile("sqc2 $vf2,%0" : "=m"(vRange));
        LO *plo = STRUCT_OFFSET(pemitb, 0x7c, LO *);
        asm volatile("qmtc2.ni %0,$vf3" : : "r"(b));
        if (plo)
        {
            asm volatile("lqc2 $vf1,%0" : : "m"(STRUCT_OFFSET(plo, 0x140, qword)));
            asm volatile("vsub.xyzw $vf1,$vf1,$vf2");
            asm volatile("sqc2 $vf1,%0" : "=m"(vLo));
            asm volatile("lqc2 $vf1,%0" : : "m"(STRUCT_OFFSET(STRUCT_OFFSET(pemitb, 0x7c, LO *), 0x140, qword)));
            asm volatile("vadd.xyzw $vf1,$vf1,$vf2");
            asm volatile("sqc2 $vf1,%0" : "=m"(vHi));
        }
        else
        {
            asm volatile("");
            float m1 = -1.0f;
            asm volatile("sq %1,%0" : "=m"(vHi) : "r"(b));
            asm volatile("mfc1 $4,%0\n\tqmtc2.ni $4,$vf1" : : "f"(m1) : "$4");
            asm volatile("vmulx.xyzw $vf2,$vf3,$vf1x");
            asm volatile("sqc2 $vf1,%0" : "=m"(vDelta));
            asm volatile("sqc2 $vf2,%0" : "=m"(vLo));
        }
        asm volatile("");
        float r2 = STRUCT_OFFSET(pemitter, 0x338, float);
        pemitb = STRUCT_OFFSET(pemitter, 0x2d0, EMITB *);
        r2 += r2;
        qword b2;
        asm("mfc1 $3,%1\n\tpextlw $3,$3,$3\n\tpextlw %0,$3,$3" : "=r"(b2) : "f"(r2) : "$3");
        STRUCT_OFFSET(&vRange, 0, qword) = b2;
        if (STRUCT_OFFSET(pemitb, 0x120, int) == 0)
        {
            char *pgrid = STRUCT_OFFSET(pemitter, 0x348, char *);
            if (pgrid)
            {
                char *pcell = STRUCT_OFFSET(pgrid, 0x624, char *);
                if (pcell)
                {
                    int stride = 0x840;
                    do
                    {
                        float *pfb = (float *)(pcell + STRUCT_OFFSET(pcell, 0x1080, int) * stride);
                        float *pbase = pfb;
                        for (int j = 0; j < STRUCT_OFFSET(pcell, 0x1084, int); j++)
                        {
                            float *pf = pbase + j * 4;
                            float f = pf[0];
                            if (f < vLo.x || vHi.x < f)
                            {
                                vDelta.x = vLo.x + GModPositive(f - vLo.x, vRange.x) - pf[0];
                                pf[0] += vDelta.x;
                            }
                            f = pf[1];
                            if (f < vLo.y || vHi.y < f)
                            {
                                vDelta.y = vLo.y + GModPositive(f - vLo.y, vRange.y) - pf[1];
                                pf[1] += vDelta.y;
                            }
                            f = pf[2];
                            if (f < vLo.z || vHi.z < f)
                            {
                                vDelta.z = vLo.z + GModPositive(f - vLo.z, vRange.z) - pf[2];
                                pf[2] += vDelta.z;
                            }
                        }
                        pcell = STRUCT_OFFSET(pcell, 0x1090, char *);
                    } while (pcell);
                }
            }
        }
    }
}

/**
 * @todo 88 differing lines of 317: structure matches (switch case order 3,2,0,1, in range test with VU0 asm). Remaining: gcc keeps the emitg address in a callee saved register while the original recomputes it, the in range flag branch shape, and the n clamp. Names and offsets are guesses.
 */
INCLUDE_ASM("asm/nonmatchings/P2/emitter", UpdateEmitter__FP7EMITTERf);

#ifdef SKIP_ASM
void UpdateEmitter(EMITTER *pemitter, float dt)
{
    if (STRUCT_OFFSET(pemitter, 0x34c, int))
        OnEmitterValuesChanged(pemitter);
    UpdateAlo(pemitter, dt);
    if (STRUCT_OFFSET(pemitter, 0x310, OID) != OID_Nil)
        return;
    if (!FIsDlEmpty((DL *)&STRUCT_OFFSET(pemitter, 0x314, int)))
    {
        LO *plo = STRUCT_OFFSET(pemitter, 0x314, LO *);
        if (!plo)
            return;
        do
        {
            if (!(STRUCT_OFFSET(plo, 0x2c8, ulong) & ((ulong)0x8000 << 23)) && FIsLoInWorld(plo))
            {
                if (!STRUCT_OFFSET(plo, 0x18, int))
                    goto update;
                float r = STRUCT_OFFSET(plo, 0x80, float) * STRUCT_OFFSET(g_pcm, 0xb0, float);
                float d2;
                asm volatile("lqc2 $vf3,%0" : : "m"(STRUCT_OFFSET(g_pcm, 0x40, qword)));
                asm volatile("lqc2 $vf1,%0" : : "m"(STRUCT_OFFSET(plo, 0x140, qword)));
                asm volatile("vsub.xyzw $vf1,$vf1,$vf3");
                asm volatile("vmul.xyz $vf1,$vf1,$vf1");
                asm volatile("vaddw.x $vf2,$vf0,$vf0w");
                asm volatile("vadday.x ACC,$vf1,$vf1y");
                asm volatile("vmaddz.x $vf1,$vf2,$vf1z");
                r = r * r;
                int q;
                asm volatile("qmfc2.ni %0,$vf1" : "=r"(q));
                asm("mtc1 %1,%0" : "=f"(d2) : "r"(q));
                int fIn = 1;
                if (d2 >= r)
                    fIn = 0;
                if (fIn)
                    goto update;
            }
            plo = STRUCT_OFFSET(plo, 0x320, LO *);
        } while (plo);
        return;
    }
    else if (STRUCT_OFFSET(pemitter, 0x18, int))
    {
        float r = STRUCT_OFFSET(pemitter, 0x80, float) * STRUCT_OFFSET(g_pcm, 0xb0, float);
        float d2;
        asm volatile("lqc2 $vf1,%0" : : "m"(STRUCT_OFFSET(pemitter, 0x140, qword)));
        asm volatile("lqc2 $vf2,%0" : : "m"(STRUCT_OFFSET(g_pcm, 0x40, qword)));
        asm volatile("vsub.xyzw $vf1,$vf1,$vf2");
        asm volatile("vmul.xyz $vf1,$vf1,$vf1");
        asm volatile("vaddw.x $vf3,$vf0,$vf0w");
        asm volatile("vadday.x ACC,$vf1,$vf1y");
        asm volatile("vmaddz.x $vf1,$vf3,$vf1z");
        int q;
        r = r * r;
        asm volatile("qmfc2.ni %0,$vf1" : "=r"(q));
        asm("mtc1 %1,%0" : "=f"(d2) : "r"(q));
        int fIn = 1;
        if (d2 >= r)
            fIn = 0;
        if (fIn)
            return;
    }
update:
    if (FPausedEmitter(pemitter))
        return;
    int n = 0;
    switch (STRUCT_OFFSET(pemitter, 0x2d4, int))
    {
    case 3:
    {
        float f = STRUCT_OFFSET(pemitter, 0x33c, float) + STRUCT_OFFSET(pemitter, 0x328, float) * STRUCT_OFFSET(pemitter, 0x334, float) * dt;
        n = (int)f;
        STRUCT_OFFSET(pemitter, 0x33c, float) = f - (float)n;
        if (1.0f < (float)n)
        {
            int lim = STRUCT_OFFSET(pemitter, 0x2d8, int);
            if (lim >= 0)
            {
                n = n < lim ? n : lim;
                STRUCT_OFFSET(pemitter, 0x2d8, int) = lim - n;
            }
            if (STRUCT_OFFSET(pemitter, 0x308, int))
                PauseEmitterIndefinite(pemitter);
            else if (GRandInRange(0.0f, 1.0f) <= STRUCT_OFFSET(pemitter, 0x2e8, float))
                PauseEmitter(pemitter, GRandInRange(STRUCT_OFFSET(pemitter, 0x2ec, float), STRUCT_OFFSET(pemitter, 0x2f0, float)));
            STRUCT_OFFSET(pemitter, 0x328, float) = GRandInRange(STRUCT_OFFSET(pemitter, 0x2dc, float), STRUCT_OFFSET(pemitter, 0x2e0, float)) * 60.0f;
        }
        break;
    }
    case 2:
    {
        n = (int)STRUCT_OFFSET(pemitter, 0x328, float);
        int lim = STRUCT_OFFSET(pemitter, 0x2d8, int);
        if (lim >= 0)
        {
            n = n < lim ? n : lim;
            STRUCT_OFFSET(pemitter, 0x2d8, int) = lim - n;
        }
        if (STRUCT_OFFSET(pemitter, 0x308, int))
            PauseEmitterIndefinite(pemitter);
        else if (GRandInRange(0.0f, 1.0f) <= STRUCT_OFFSET(pemitter, 0x2e8, float))
            PauseEmitter(pemitter, GRandInRange(STRUCT_OFFSET(pemitter, 0x2ec, float), STRUCT_OFFSET(pemitter, 0x2f0, float)));
        STRUCT_OFFSET(pemitter, 0x328, float) = GRandInRange(STRUCT_OFFSET(pemitter, 0x2dc, float), STRUCT_OFFSET(pemitter, 0x2e0, float));
        break;
    }
    case 0:
    {
        float f = STRUCT_OFFSET(pemitter, 0x33c, float) + STRUCT_OFFSET(pemitter, 0x328, float) * STRUCT_OFFSET(pemitter, 0x334, float) * dt;
        n = (int)f;
        STRUCT_OFFSET(pemitter, 0x33c, float) = f - (float)n;
        if (n)
        {
            int lim = STRUCT_OFFSET(pemitter, 0x2d8, int);
            if (lim >= 0)
            {
                n = n < lim ? n : lim;
                STRUCT_OFFSET(pemitter, 0x2d8, int) = lim - n;
            }
        }
        break;
    }
    case 1:
    {
        n = (int)(STRUCT_OFFSET(pemitter, 0x2f4, float) * STRUCT_OFFSET(pemitter, 0x334, float));
        int base;
        if (STRUCT_OFFSET(STRUCT_OFFSET(pemitter, 0x2d0, EMITB *), 0x120, int) == 0)
        {
            void *pgrid = STRUCT_OFFSET(pemitter, 0x348, void *);
            base = pgrid ? STRUCT_OFFSET(pgrid, 0x620, int) : 0;
        }
        else
        {
            DL *pdl = STRUCT_OFFSET(pemitter, 0x344, DL *);
            base = pdl ? CPvDl((DL *)((char *)pdl + 0x558)) : 0;
        }
        int d = n - base;
        n = 0;
        if (d > 0)
            n = d;
        break;
    }
    }
    if (n)
    {
        struct
        {
            int pad[4];
            void *pa;
            void *pb;
            void *pc;
        } emitg;
        memset(&emitg.pa, 0, 12);
        emitg.pa = &STRUCT_OFFSET(pemitter, 0x348, int);
        emitg.pb = &STRUCT_OFFSET(pemitter, 0x344, int);
        emitg.pc = pemitter;
        LO *ploOld = STRUCT_OFFSET(STRUCT_OFFSET(pemitter, 0x2d0, EMITB *), 0x7c, LO *);
        if (STRUCT_OFFSET(pemitter, 0x2f8, OID) == OID_Nil)
            STRUCT_OFFSET(STRUCT_OFFSET(pemitter, 0x2d0, EMITB *), 0x7c, EMITTER *) = pemitter;
        EmitParticles(n, STRUCT_OFFSET(pemitter, 0x2d0, EMITB *), (EMITG *)&emitg.pa);
        STRUCT_OFFSET(STRUCT_OFFSET(pemitter, 0x2d0, EMITB *), 0x7c, LO *) = ploOld;
    }
    if (STRUCT_OFFSET(pemitter, 0x330, float) <= g_clock.t)
    {
        STRUCT_OFFSET(pemitter, 0x328, float) = GRandInRange(STRUCT_OFFSET(pemitter, 0x2dc, float), STRUCT_OFFSET(pemitter, 0x2e0, float));
        STRUCT_OFFSET(pemitter, 0x330, float) = g_clock.t + STRUCT_OFFSET(pemitter, 0x32c, float);
    }
    ModifyEmitterParticles(pemitter);
}
#endif

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

/**
 * @todo 10 differing lines of 109: volatile VU0 asm; remaining diffs are call delay slot choices (RadNormalize and SetVectorSphere argument moves) and the lq $31 epilogue order. Names from the header, GetNormalVectors argument roles are guesses.
 */
INCLUDE_ASM("asm/nonmatchings/P2/emitter", ChooseEmitVelocity__FP6EMITVXffP2LMP6VECTORiT4);

#ifdef SKIP_ASM
void ChooseEmitVelocity(EMITVX *pemitvx, float uRandom, float rSvz, LM *plmSv, VECTOR *pvecNormal, int iParticle, VECTOR *pv)
{
    int cPer = STRUCT_OFFSET(pemitvx, 0, int);
    int iRing = iParticle / cPer;
    int iInRing = iParticle % cPer;
    float radTilt = STRUCT_OFFSET(pemitvx, 0xc, float) + (float)iRing * STRUCT_OFFSET(pemitvx, 4, float);
    float radPan = STRUCT_OFFSET(pemitvx, 0x10, float) + (float)iInRing * STRUCT_OFFSET(pemitvx, 8, float);
    if (uRandom != 0.0f)
    {
        radTilt += uRandom * GRandInRange(-0.5f, 0.5f) * STRUCT_OFFSET(pemitvx, 4, float);
        radPan += uRandom * GRandInRange(-0.5f, 0.5f) * STRUCT_OFFSET(pemitvx, 8, float);
    }
    radTilt = RadNormalize(radTilt + 1.5707964f);
    radPan = RadNormalize(radPan);
    VECTOR avec[3];
    VECTOR n;
    SetVectorSphere(&avec[0], radPan, radTilt, GRandInRange(STRUCT_OFFSET(plmSv, 0, float), STRUCT_OFFSET(plmSv, 4, float)));
    avec[0].z *= rSvz;
    STRUCT_OFFSET(&n, 0, qword) = STRUCT_OFFSET(pvecNormal, 0, qword);
    GetNormalVectors(&n, &avec[1], &g_normalX, &g_normalZ);
    asm volatile("lqc2 $vf2,%0" : : "m"(avec[0]));
    asm volatile("lqc2 $vf4,%0" : : "m"(avec[1]));
    asm volatile("lqc2 $vf3,%0" : : "m"(avec[2]));
    asm volatile("lqc2 $vf1,%0" : : "m"(n));
    asm volatile("vmulax.xyz ACC,$vf4,$vf2x");
    asm volatile("vmadday.xyz ACC,$vf3,$vf2y");
    asm volatile("vmaddz.xyz $vf2,$vf1,$vf2z");
    asm volatile("sqc2 $vf2,%0" : "=m"(*pv));
}
#endif

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

/**
 * @todo 187 differing lines of 194 but same frame size: the original spills crip/apos/av/atCreated/atDestroy to the stack without strength reducing the indexing, here simulated with volatile locals. Vtable slots and field offsets are guesses.
 */
INCLUDE_ASM("asm/nonmatchings/P2/emitter", EmitRips__FP5EMITBP5EMITGiP6VECTORT3PfT5);

#ifdef SKIP_ASM
void EmitRips(EMITB *pemitb, EMITG *pemitg, int crip, VECTOR *apos, VECTOR *av, float *atCreated, float *atDestroy)
{
    volatile int vcrip = crip;
    VECTOR *volatile vapos = apos;
    VECTOR *volatile vav = av;
    float *volatile vatc = atCreated;
    float *volatile vatd = atDestroy;
    typedef void (*PFNINIT)(RIP *, VECTOR *, float, int);
    typedef void (*PFNTRAIL)(RIP *, VECTOR *, float, int);
    typedef void (*PFNPOST)(RIP *, EMITB *);
    typedef void (*PFNSUB)(RIPG *, LO *);
    typedef void (*PFNDEL)(RIPG *);
    char *pet = (char *)pemitb + 0x120;
    LO *plo = STRUCT_OFFSET(pemitb, 0x7c, LO *);
    RIPG *pripg = 0;
    int i = 0;
    if (pemitg && pemitg->ppripg)
        pripg = *pemitg->ppripg;
    if (!pripg)
    {
        pripg = PripgNew(g_psw, STRUCT_OFFSET(pet, 0xc4, RIPGT));
        if (!pripg)
            return;
        if (pemitg && pemitg->ppripg)
            *pemitg->ppripg = pripg;
        SetRipgEmitb(pripg, pemitb);
        if (pemitg && pemitg->ploSubscribe)
            STRUCT_OFFSET(STRUCT_OFFSET(pripg, 0, void *), 0x6c, PFNSUB)(pripg, pemitg->ploSubscribe);
        if (!pripg)
            return;
    }
    DL *pdl = &STRUCT_OFFSET(pripg, 0x558, DL);
    for (; i < vcrip; i++)
    {
        RIP *prip = PripNewRipg(STRUCT_OFFSET(pet, 0x90, RIPT), pripg);
        if (!prip)
            break;
        char *pv = (char *)prip;
        STRUCT_OFFSET(STRUCT_OFFSET(prip, 0, void *), 0, PFNINIT)(prip, &vapos[i], GRandInRange(STRUCT_OFFSET(pet, 0xb0, float), STRUCT_OFFSET(pet, 0xb4, float)), STRUCT_OFFSET(pet, 0xc0, int));
        if (STRUCT_OFFSET(pet, 0xa4, float) != 0.0f || STRUCT_OFFSET(pet, 0xa8, float) != 0.0f)
        {
            STRUCT_OFFSET(prip, 0x34, float) = STRUCT_OFFSET(pet, 0xa4, float);
            STRUCT_OFFSET(prip, 0x38, float) = STRUCT_OFFSET(pet, 0xa8, float);
        }
        STRUCT_OFFSET(prip, 0xa0, qword) = STRUCT_OFFSET(&vav[i], 0, qword);
        STRUCT_OFFSET(prip, 0x18, float) = vatc[i];
        STRUCT_OFFSET(prip, 0x1c, float) = vatd[i] - vatc[i];
        STRUCT_OFFSET(prip, 0x40, qword) = STRUCT_OFFSET(pemitb, 0x110, qword);
        SetEmitdvEmitb((EMITDV *)&STRUCT_OFFSET(prip, 0xb0, int), pemitb);
        if (STRUCT_OFFSET(pet, 0xb8, int))
            STRUCT_OFFSET(prip, 0x20, int) = STRUCT_OFFSET(pet, 0xb8, int);
        if (plo)
        {
            STRUCT_OFFSET(prip, 0x50, qword) = STRUCT_OFFSET(plo, 0x110, qword);
            STRUCT_OFFSET(prip, 0x60, qword) = STRUCT_OFFSET(plo, 0x120, qword);
            STRUCT_OFFSET(prip, 0x70, qword) = STRUCT_OFFSET(plo, 0x130, qword);
        }
        if (STRUCT_OFFSET(pet, 0x94, int) != -1)
        {
            RIP *ptrail = PripNewRipg((RIPT)STRUCT_OFFSET(pet, 0x94, int), 0);
            if (ptrail)
            {
                STRUCT_OFFSET(STRUCT_OFFSET(ptrail, 0, void *), 0, PFNTRAIL)(ptrail, (VECTOR *)&STRUCT_OFFSET(prip, 0x80, int), STRUCT_OFFSET(prip, 0x30, float) * 0.5f, 0);
                SetTrailTrls((TRAIL *)ptrail, TRLS_TrackingRip, prip);
            }
        }
        STRUCT_OFFSET(STRUCT_OFFSET(prip, 0, void *), 4, PFNPOST)(prip, pemitb);
    }
    if (FIsDlEmpty(pdl))
        STRUCT_OFFSET(STRUCT_OFFSET(pripg, 0, void *), 0x1c, PFNDEL)(pripg);
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/emitter", EmitBlips__FP5EMITBP5EMITGiP6VECTORT3PfT5T3T3);

/**
 * @todo 20 differing lines of 127: volatile VU0 asm block matches, remaining diffs are that gcc strength reduces the i*16 index (target recomputes sll each iteration) and one loop top delay slot fill. EMITVX is a 0x20 byte buffer here. Names are guesses.
 */
INCLUDE_ASM("asm/nonmatchings/P2/emitter", OriginateParticles__FiP5EMITBP7EMITGEN);

#ifdef SKIP_ASM
void OriginateParticles(int cParticle, EMITB *pemitb, EMITGEN *pemitgen)
{
    int cb = cParticle * 16;
    int cf = cParticle * 4;
    qword emitvxbuf[2];
    VECTOR normal;
    int i = 0;
    STRUCT_OFFSET(pemitgen, 0, void *) = PvAllocStackImpl(cb);
    STRUCT_OFFSET(pemitgen, 4, void *) = PvAllocStackImpl(cb);
    STRUCT_OFFSET(pemitgen, 8, void *) = PvAllocStackImpl(cf);
    STRUCT_OFFSET(pemitgen, 0xc, void *) = PvAllocStackImpl(cf);
    CalculateEmitvx(STRUCT_OFFSET(pemitb, 0xec, int), (LM *)&STRUCT_OFFSET(pemitb, 0xe4, int), cParticle, (EMITVX *)emitvxbuf);
    for (; i < cParticle; i++)
    {
        ChooseEmitoPos((&pemitb->emito), i, cParticle, &pemitgen->apos[i], &normal);
        ChooseEmitvVelocityAge(&pemitb->emitv, (EMITVX *)emitvxbuf, (&pemitb->emito), i, &pemitgen->apos[i], &normal, &pemitgen->av[i], &pemitgen->atCreated[i], &pemitgen->atDestroy[i]);
        char *palo = STRUCT_OFFSET(pemitb, 0x78, char *);
        if (palo)
        {
            char *pm = palo + 0x10;
            asm volatile("lqc2 $vf5,%0" : : "m"(STRUCT_OFFSET(palo, 0x10, qword)));
            asm volatile("lqc2 $vf4,%0" : : "m"(STRUCT_OFFSET(pm, 0x10, qword)));
            VECTOR *pa = &pemitgen->apos[i];
            asm volatile("lqc2 $vf3,%0" : : "m"(*pa));
            asm volatile("lqc2 $vf1,%0" : : "m"(STRUCT_OFFSET(pm, 0x20, qword)));
            asm volatile("vmulax.xyz ACC,$vf5,$vf3x");
            asm volatile("vmadday.xyz ACC,$vf4,$vf3y");
            asm volatile("vmaddz.xyz $vf3,$vf1,$vf3z");
            asm volatile("lqc2 $vf2,%0" : : "m"(STRUCT_OFFSET(palo, 0, qword)));
            asm volatile("vadd.xyzw $vf3,$vf3,$vf2");
            asm volatile("sqc2 $vf3,%0" : "=m"(*pa));
            asm volatile("lqc2 $vf1,%0" : : "m"(STRUCT_OFFSET(palo, 0, qword)));
            VECTOR *pa2 = &pemitgen->apos[i];
            VECTOR *pv = &pemitgen->av[i];
            asm volatile("lqc2 $vf5,%0" : : "m"(*pa2));
            asm volatile("vsub.xyzw $vf5,$vf5,$vf1");
            asm volatile("lqc2 $vf6,%0" : : "m"(STRUCT_OFFSET(pm, 0x20, qword)));
            asm volatile("lqc2 $vf1,%0" : : "m"(STRUCT_OFFSET(pm, 0x10, qword)));
            asm volatile("lqc2 $vf2,%0" : : "m"(*pv));
            asm volatile("lqc2 $vf3,%0" : : "m"(STRUCT_OFFSET(palo, 0x10, qword)));
            asm volatile("vmulax.xyz ACC,$vf3,$vf2x");
            asm volatile("vmadday.xyz ACC,$vf1,$vf2y");
            asm volatile("vmaddz.xyz $vf2,$vf6,$vf2z");
            asm volatile("lqc2 $vf4,%0" : : "m"(STRUCT_OFFSET(palo, 0x40, qword)));
            asm volatile("lqc2 $vf1,%0" : : "m"(STRUCT_OFFSET(palo, 0x50, qword)));
            asm volatile("vadd.xyzw $vf2,$vf2,$vf4");
            asm volatile("vopmula.xyz ACC,$vf1,$vf5");
            asm volatile("vopmsub.xyz $vf1,$vf5,$vf1");
            asm volatile("vsub.w $vf1,$vf1,$vf1");
            asm volatile("vadd.xyzw $vf2,$vf2,$vf1");
            asm volatile("sqc2 $vf2,%0" : "=m"(*pv));
        }
        if (pemitgen->fUnknown)
            ConvertEmitoPosVec((&pemitb->emito), &pemitgen->apos[i], &pemitgen->av[i]);
    }
}
#endif

/**
 * @todo 113 differing lines of 158: same frame and block structure, VU0 asm volatile. gcc strength reduces the particle index differently (the original shares one i*16 induction register). Names and offsets are guesses.
 */
INCLUDE_ASM("asm/nonmatchings/P2/emitter", OriginateSplineSinkParticles__FiP5EMITBR7EMITGENT2);

#ifdef SKIP_ASM
extern float D_0024A144;

void OriginateSplineSinkParticles(int cParticle, EMITB *pemitb, EMITGEN &emitgen, EMITGEN &emitgenTarget)
{
    struct
    {
        VECTOR pos;
        MATRIX3 mat;
        VECTOR v;
        VECTOR w;
    } xf;
    VECTOR vPredPos, vPredV, vPredW;
    MATRIX3 matPred;
    VECTOR vSpill;
    memset(&xf, 0, 0x60);
    pemitb = STRUCT_OFFSET(pemitb, 0x18c, EMITB *);
    EMITB *pemitbTarget = STRUCT_OFFSET(pemitb, 0x90, EMITB *);
    LO *ploSave = STRUCT_OFFSET(pemitbTarget, 0x7c, LO *);
    if (STRUCT_OFFSET(pemitb, 0x94, int) == -1)
        STRUCT_OFFSET(STRUCT_OFFSET(pemitb, 0x90, EMITB *), 0x7c, int) = STRUCT_OFFSET(pemitb, 0x18, int);
    if (STRUCT_OFFSET(STRUCT_OFFSET(pemitb, 0x90, EMITB *), 0x7c, int) == STRUCT_OFFSET(pemitb, 0x18, int))
    {
        CalculateExplTransform((EXPL *)pemitb, &xf.pos, &xf.mat);
        STRUCT_OFFSET(STRUCT_OFFSET(pemitb, 0x90, EMITB *), 0x78, void *) = &xf;
    }
    emitgenTarget.fUnknown = 0;
    int i = 0;
    OriginateParticles(cParticle, STRUCT_OFFSET(pemitb, 0x90, EMITB *), &emitgenTarget);
    STRUCT_OFFSET(STRUCT_OFFSET(pemitb, 0x90, EMITB *), 0x78, int) = 0;
    float fPrev = D_0024A144;
    int ch;
    for (; i < cParticle; i++)
    {
        if (STRUCT_OFFSET(STRUCT_OFFSET(pemitb, 0x90, EMITB *), 0x7c, int))
        {
            float f = emitgen.atDestroy[i] - g_clock.t;
            if (!FFloatsNear(f, fPrev, 0.0001f))
            {
                fPrev = f;
                PredictAloTransform(STRUCT_OFFSET(STRUCT_OFFSET(pemitb, 0x90, EMITB *), 0x7c, ALO *), 0, fPrev, &vPredPos, &matPred, &vPredV, &vPredW);
            }
            VECTOR *pa = &emitgenTarget.apos[i];
            asm volatile("lqc2 $vf5,%0" : : "m"(matPred.avec[0]));
            asm volatile("lqc2 $vf4,%0" : : "m"(matPred.avec[1]));
            asm volatile("lqc2 $vf3,%0" : : "m"(*pa));
            asm volatile("lqc2 $vf1,%0" : : "m"(matPred.avec[2]));
            asm volatile("vmulax.xyz ACC,$vf5,$vf3x");
            asm volatile("vmadday.xyz ACC,$vf4,$vf3y");
            asm volatile("vmaddz.xyz $vf3,$vf1,$vf3z");
            asm volatile("lqc2 $vf2,%0" : : "m"(vPredPos));
            asm volatile("sqc2 $vf3,%0" : "=m"(vSpill));
            asm volatile("vadd.xyzw $vf2,$vf2,$vf3");
            asm volatile("sqc2 $vf2,%0" : "=m"(*pa));
            int mode = STRUCT_OFFSET(STRUCT_OFFSET(pemitb, 0x90, EMITB *), 0x80, int);
            if (mode != 3)
            {
                VECTOR *pw = &emitgenTarget.av[i];
                asm volatile("lqc2 $vf4,%0" : : "m"(matPred.avec[0]));
                asm volatile("lqc2 $vf3,%0" : : "m"(matPred.avec[1]));
                asm volatile("lqc2 $vf1,%0" : : "m"(*pw));
                asm volatile("lqc2 $vf2,%0" : : "m"(matPred.avec[2]));
                asm volatile("vmulax.xyz ACC,$vf4,$vf1x");
                asm volatile("vmadday.xyz ACC,$vf3,$vf1y");
                asm volatile("vmaddz.xyz $vf1,$vf2,$vf1z");
                asm volatile("sqc2 $vf1,%0" : "=m"(*pw));
                if (mode != 2)
                {
                    asm volatile("lqc2 $vf2,%0" : : "m"(vPredV));
                    asm volatile("lqc2 $vf3,%0" : : "m"(vPredW));
                    VECTOR *pr = mode == 1 ? pa : &vSpill;
                    asm volatile("lqc2 $vf1,%0" : : "m"(*pw));
                    asm volatile("vadd.xyzw $vf2,$vf1,$vf2");
                    asm volatile("lqc2 $vf1,%0" : : "m"(*pr));
                    asm volatile("vopmula.xyz ACC,$vf3,$vf1");
                    asm volatile("vopmsub.xyz $vf1,$vf1,$vf3");
                    asm volatile("vsub.w $vf1,$vf1,$vf1");
                    asm volatile("vadd.xyzw $vf1,$vf2,$vf1");
                    asm volatile("sqc2 $vf1,%0" : "=m"(*pw));
                }
            }
        }
        VECTOR *pw2 = &emitgenTarget.av[i];
        float neg = -1.0f;
        asm volatile("qmtc2.ni %0,$vf2" : : "r"(neg));
        asm volatile("lqc2 $vf1,%0" : : "m"(*pw2));
        asm volatile("vmulx.xyzw $vf1,$vf1,$vf2x");
        asm volatile("sqc2 $vf2,%0" : "=m"(vSpill));
        asm volatile("sqc2 $vf1,%0" : "=m"(*pw2));
    }
    STRUCT_OFFSET(STRUCT_OFFSET(pemitb, 0x90, EMITB *), 0x7c, LO *) = ploSave;
}
#endif

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
 * @todo 18 differing lines of 88: VU0 asm chain with memory clobbers and a pinned fake dependency register keeps the register split. Remaining: float load placement between the VU0 asms (the original interleaves them) and the (a+b)*(len*0.5) schedule. Names are guesses.
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
            register int ch asm("$24");
            float len;
            asm("lqc2 $vf2,%1" : "=r"(ch) : "m"(STRUCT_OFFSET(STRUCT_OFFSET(pe, 0x1c, LO *), 0x140, qword)) : "memory");
            asm("lqc2 $vf1,%1" : "=r"(ch) : "m"(STRUCT_OFFSET(STRUCT_OFFSET(pe, 0x18, LO *), 0x140, qword)), "r"(ch) : "memory");
            asm("vsub.xyzw $vf1,$vf1,$vf2" : "=r"(ch) : "r"(ch) : "memory");
            asm("vmul.xyz $vf1,$vf1,$vf1" : "=r"(ch) : "r"(ch) : "memory");
            asm("vaddw.x $vf2,$vf0,$vf0w" : "=r"(ch) : "r"(ch) : "memory");
            asm("vadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z\n\t.word 0x4A0103BD\n\tvwaitq\n\tvaddq.x $vf1,$vf0,Q" : "=r"(ch) : "r"(ch) : "memory");
            int q;
            asm("qmfc2.ni %0,$vf1" : "=r"(q) : "r"(ch));
            asm("mtc1 %1,%0" : "=f"(len) : "r"(q));
            STRUCT_OFFSET(pe, 0x20, float) = len;
            float t = (STRUCT_OFFSET(pe, 8, float) + STRUCT_OFFSET(pe, 0xc, float)) * (len * 0.5f);
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

/**
 * @todo about 113 differing lines of 108: needs operator* for MATRIX4 and VU_FLOAT (declared in mat.h, VU_FLOAT ctor inline in blip.h). Target loads g_mat4Identity once and has an extra 0x90 byte by value copy of the product passed to AddMatrix4Matrix4. Names are guesses.
 */
INCLUDE_ASM("asm/nonmatchings/P2/emitter", CalculateEmitdvMatrix__FP6EMITDVfP7MATRIX4);

#ifdef SKIP_ASM
void CalculateEmitdvMatrix(EMITDV *pemitdv, float dt, MATRIX4 *pmat4Dv)
{
    MATRIX4 matA = g_mat4Identity;
    MATRIX4 matB = g_mat4Identity;
    float s = STRUCT_OFFSET(pemitdv, 0, float);
    matA.aag[0][0] = s;
    matA.aag[1][1] = s;
    matA.aag[2][2] = s;
    matA.aag[3][0] = STRUCT_OFFSET(pemitdv, 0x10, float);
    matA.aag[3][1] = STRUCT_OFFSET(pemitdv, 0x14, float);
    matA.aag[3][2] = STRUCT_OFFSET(pemitdv, 0x18, float);
    MATRIX4 *pmatB = &matB;
    if (STRUCT_OFFSET(pemitdv, 0x20, float) != 0.0f)
    {
        VECTOR vec;
        if (STRUCT_OFFSET(pemitdv, 0x40, int) == 1 && STRUCT_OFFSET(pemitdv, 0x44, ALO *))
            ConvertAloVec(STRUCT_OFFSET(pemitdv, 0x44, ALO *), 0, &STRUCT_OFFSET(pemitdv, 0x30, VECTOR), &vec);
        else
            STRUCT_OFFSET(&vec, 0, qword) = STRUCT_OFFSET(pemitdv, 0x30, qword);
        LoadRotateMatrixRad(STRUCT_OFFSET(pemitdv, 0x20, float) * dt, &vec, (MATRIX3 *)pmatB);
    }
    MATRIX4 matC = matB * matA;
    MATRIX4 matD = matC * VU_FLOAT(dt);
    AddMatrix4Matrix4(pmatB, &matD, pmat4Dv);
}
#endif

void PostExplLoad(EXPL *pexpl)
{
    typedef void (*PFN)(EXPL *);
    PostLoLoad(pexpl);
    STRUCT_OFFSET(pexpl->pvtlo, 0x1c, PFN)(pexpl);
}

/**
 * VU0 volatile asm in source order, the volatile asms pin the surrounding loads. The empty asm and the last sqc2 inside the loop condition make the assembler fill the branch delay slot like the original. The sB/sA stores are spill artifacts. Names are guesses.
 */
void CalculateExplTransform(EXPL *pexpl, VECTOR *ppos, MATRIX3 *pmat)
{
    STRUCT_OFFSET(ppos, 0, qword) = STRUCT_OFFSET(&D_00248D30, 0, qword);
    STRUCT_OFFSET(pmat, 0, qword) = STRUCT_OFFSET(pexpl, 0x50, qword);
    STRUCT_OFFSET(pmat, 0x10, qword) = STRUCT_OFFSET(pexpl, 0x60, qword);
    STRUCT_OFFSET(pmat, 0x20, qword) = STRUCT_OFFSET(pexpl, 0x70, qword);
    VECTOR sA[3], sB[3];
    if (STRUCT_OFFSET(pexpl, 0x80, EXPL *))
    do
    {
        asm volatile("");
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
    } while (({ EXPL *tt = STRUCT_OFFSET(pexpl, 0x80, EXPL *); asm volatile("sqc2 $vf4,%0" : "=m"(sB[2])); tt; }));
    asm volatile("lqc2 $vf2,%0" : : "m"(STRUCT_OFFSET(pexpl, 0x40, qword)));
    asm volatile("lqc2 $vf1,%0" : : "m"(*ppos));
    asm volatile("vadd.xyzw $vf1,$vf1,$vf2");
    asm volatile("sqc2 $vf1,%0" : "=m"(*ppos));
}

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
