////////////////////////////////////////////////////////////////
// Voodoo boss AKA Mz. Ruby (P2/vb.c) 
////////////////////////////////////////////////////////////////

#include "common.h"
#include <sce/memset.h>
#include <jt.h>
#include <lo.h>
#include <po.h>
#include <so.h>
#include <vb.h>


struct STEPGUARD;
struct XFM;


INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001EB460);

void func_001EB518(SO *pso, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(pso, pbis);
    SnipAloObjects(pso, 1, &D_00275C90);
}

void func_001EB550(void *pv)
{
    struct Block32
    {
        int a __attribute__((mode(TI)));
        int b __attribute__((mode(TI)));
    };

    char *pjt;
    struct Block32 *dst;
    struct Block32 *src;
    struct Block32 *end;

    pjt = (char *)g_pjt;
    dst = (struct Block32 *)((char *)pv + 0x580);
    end = (struct Block32 *)(pjt + 0x600);
    src = (struct Block32 *)(pjt + 0x580);

    do
    {
        *dst = *src;
        src = src + 1;
        dst = dst + 1;
    }
    while (src != end);

    STRUCT_OFFSET(pv, 0x604, int) = STRUCT_OFFSET(g_pjt, 0x604, int);
}

void func_001EB598(ALO *palo)
{
    PostAloLoad(palo);
    SnipAloObjects(palo, 4, &D_00275CA0);
    STRUCT_OFFSET(palo, 0x614, void *) =
        PsmaApplySm(STRUCT_OFFSET(palo, 0x610, SM *), palo, (OID)0x4CA, 1);
    PostSwCallback(
        STRUCT_OFFSET(palo, 0x14, SW *),
        (void (*)(void *, MSGID, void *))func_001EB550,
        palo,
        (MSGID)0,
        (void *)0);
}

void func_001EB608(PO *ppo, int n, PO *ppoOther)
{
    LO *plo;

    OnPoActive(ppo, n, ppoOther);
    plo = PloFindSwObjectByClass(STRUCT_OFFSET(ppo, 0x14, SW *), 5, (CID)0x13, (LO *)0);

    if (n != 0)
    {
        SetSmaGoal(STRUCT_OFFSET(ppo, 0x614, SMA *), (OID)0x4CB);
        STRUCT_OFFSET(plo, 0xC3C, void *) = ppo;
        STRUCT_OFFSET(ppo, 0x68C, LO *) = plo;
    }
    else
    {
        SetSmaGoal(STRUCT_OFFSET(ppo, 0x614, SMA *), (OID)0x4CA);
        STRUCT_OFFSET(g_pjt, 0x26D0, float) = 2.0f;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001EB698);

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001EB748);

int func_001EBC88(void *pv)
{
    if ((g_grfcht & 1) != 0)
        return 1;

    if (IsSwHandsOff(STRUCT_OFFSET(pv, 0x14, SW *)) == 0)
        return STRUCT_OFFSET(pv, 0x688, int) != 0;

    return 1;
}

void func_001EBCD8(void *pvb, void *pv)
{
    struct U8 { char a[8]; };
    struct U8 *dst;
    int c = STRUCT_OFFSET(pvb, 0x630, int);

    dst = (struct U8 *)((char *)pvb + ((c << 3) + 0x634));
    STRUCT_OFFSET(pvb, 0x630, int) = c + 1;
    *dst = *(struct U8 *)pv;
}

int func_001EBD08(void)
{
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001EBD10);

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001EBDD0);

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001EBEB0);

void func_001EBF40(void *pv, CBinaryInputStream *pbis)
{
    OID *poid;
    void **ppv;
    int i;

    LoadStepguardFromBrx((STEPGUARD *)pv, pbis);

    poid = &D_00275CF8;
    ppv = (void **)((char *)pv + 0xC10);
    i = 3;
    do
    {
        *ppv = PasegFindStepguard((STEPGUARD *)pv, *poid);
        poid = poid + 1;
        ppv = ppv + 1;
        i = i - 1;
    }
    while (i >= 0);
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001EBFB0);

void func_001EC098(PO *ppo)
{
    OnPoRemove(ppo);
}

void func_001EC0B8(PO *ppo)
{
    OnPoAdd(ppo);
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001EC0D8);

int func_001EC188(void)
{
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001EC190);

void func_001EC380(ALO *palo, CM *pcm, RO *pro)
{
    struct {
        char a[0x50];
    } ro;

    if (STRUCT_OFFSET(palo, 0x724, int) == 0x10)
    {
        DupAloRo(palo, pro, (RO *)&ro);
        STRUCT_OFFSET(&ro, 0x44, int) = 0;
        pro = (RO *)&ro;
    }

    RenderAloAll(palo, pcm, pro);
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001EC3D8);

void func_001EC478(void *pv, int nSgs)
{
    int nState;
    OID oid;
    OID oidGoal;

    OnStepguardExitingSgs((STEPGUARD *)pv, (SGS)nSgs);

    nState = STRUCT_OFFSET(pv, 0x724, int);
    if (nState == 0xE)
        goto clear_e;
    if (nState != 0x10)
        return;

    STRUCT_OFFSET(pv, 0xC94, int) = 0;
    GetSmaCur(STRUCT_OFFSET(pv, 0xC54, SMA *), &oid);

        if (oid == (OID)0x4F1)
        goto goal_4f2;
    if (oid >= (OID)0x4F2)
        goto hi;

    if (oid == (OID)0x4EE)
    {
        oidGoal = (OID)0x4EF;
        goto set;
    }
    goto set_miss;

hi:
    if (oid == (OID)0x4F4)
    {
        oidGoal = (OID)0x4F5;
        goto set;
    }
    goto set_miss;

goal_4f2:
    oidGoal = (OID)0x4F2;
set:
    SetSmaGoal(STRUCT_OFFSET(pv, 0xC54, SMA *), oidGoal);
    return;

set_miss:
    SetSmaGoal(STRUCT_OFFSET(pv, 0xC54, SMA *), oidGoal);
    return;

clear_e:
    STRUCT_OFFSET(pv, 0xC94, int) = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001EC528);

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001EC570);

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001EC7A8);

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001EC828);

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001ECB18);

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001ECBC8);

void func_001ECDF8(void *pv)
{
    OID oid;
    void *pvUnk;

    GetSmaCur(STRUCT_OFFSET(pv, 0xC54, SMA *), &oid);

    pvUnk = (void *)0;
    if (oid == (OID)0x4F1)
        goto hit;
    if (oid < (OID)0x4F2)
    {
        if (oid == (OID)0x4EE)
            goto hit;
        goto miss;
    }
    if (oid == (OID)0x4F4)
        goto hit;
    if (oid != (OID)0x4F7)
        goto miss;

hit:
    pvUnk = FUN_001e9970();
miss:
    if (pvUnk != (void *)0)
    {
        ((void (*)(void *))STRUCT_OFFSET(STRUCT_OFFSET(&g_unkblot7, 0, void *), 0x38, void *))(&g_unkblot7);
        return;
    }
    ((void (*)(void *))STRUCT_OFFSET(STRUCT_OFFSET(&g_unkblot7, 0, void *), 0x3C, void *))(&g_unkblot7);
}

void func_001ECE98(void *pv, int n)
{
    int nState;
    void *pxfm;
    VECTOR pos;

    nState = STRUCT_OFFSET(pv, 0x724, int);
    if (nState < 0xE)
    {
        if (!(nState < 0xC))
        {
            pxfm = STRUCT_OFFSET(pv, 0xC48, void *);
            if (pxfm != 0)
            {
                GetXfmPos((XFM *)pxfm, &pos);
                SetStepguardGoal((STEPGUARD *)pv, &pos);
            }
            else
            {
                SetStepguardGoal((STEPGUARD *)pv, (VECTOR *)((char *)pv + 0x140));
            }
            return;
        }
    }

    UpdateStepguardGoal((STEPGUARD *)pv, n);
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001ECF10);

void func_001ED018(void *pvb, int n)
{
    STRUCT_OFFSET(pvb, 0xC34, int) = n;
}

void func_001ED020(void *pvb)
{
    func_001ED210(STRUCT_OFFSET(pvb, 0xC38, void *));
    STRUCT_OFFSET(pvb, 0xC38, void *) = 0;
}

void func_001ED050(void *pvb, int n)
{
    STRUCT_OFFSET(pvb, 0xC5C, int) = n;
    STRUCT_OFFSET(pvb, 0xC8C, float) = 60.0f / (float)n;
}

void func_001ED070(void *pvb, int n)
{
    STRUCT_OFFSET(pvb, 0xC60, int) = n;
    STRUCT_OFFSET(pvb, 0xC64, float) = STRUCT_OFFSET(pvb, 0xC88, float) * (float)n;
}

void func_001ED090(void *pvb, void *pasega, void *pv)
{
    int c;
    int off;
    char *slot;

    c = STRUCT_OFFSET(pvb, 0xC68, int);
    slot = STRUCT_OFFSET(pvb, 0xC6C, char *);
    off = c << 3;
    c = c + 1;
    slot = slot + off;
    STRUCT_OFFSET(pvb, 0xC68, int) = c;
    *(void **)(slot + 4) = pv;
    *(void **)slot = pasega;
    SubscribeAsegaObject((ASEGA *)pasega, (LO *)pvb);
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001ED0D8);

void func_001ED168(LO *plo)
{
    InitLo(plo);
    STRUCT_OFFSET(plo, 0x38, void *) = PvAllocSwImpl(0xC00);
}

void func_001ED198(LO *plo)
{
    PostLoLoad(plo);
    STRUCT_OFFSET(plo, 0x40, LO *) = PloFindSwObjectByClass(STRUCT_OFFSET(plo, 0x14, SW *), 5, (CID)0x13, (LO *)0);
}

void func_001ED1D8(void *pv)
{
    STRUCT_OFFSET(pv, 0x3C, int) = 0;
    STRUCT_OFFSET(pv, 0x44, int) = STRUCT_OFFSET(STRUCT_OFFSET(pv, 0x40, void *), 0xC70, int);
    HandleLoSpliceEvent((LO *)pv, 0x1Au, 0, (void **)0);
}

void func_001ED210(void *pv)
{
    int n;

    HandleLoSpliceEvent((LO *)pv, 0x1Cu, 0, (void **)0);

    n = 5;
    func_001ED318(pv, &n);

    if (STRUCT_OFFSET(STRUCT_OFFSET(pv, 0x40, void *), 0xC3C, int) != 0)
    {
        n = 3;
        func_001ED318(pv, &n);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001ED278);

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001ED318__FPvPi);

void *func_001ED4C8(void *pvb, int n, void *pv, float g)
{
    int c = STRUCT_OFFSET(pvb, 0x34, int);
    void *ret;

    if (c < 0xC0)
    {
        char *slot = STRUCT_OFFSET(pvb, 0x38, char *);

        slot += c << 4;
        STRUCT_OFFSET(pvb, 0x34, int) = c + 1;
        memset(slot, 0, 0x10);
        *(int *)slot = n;
        *(void **)(slot + 4) = pv;
        *(float *)(slot + 8) = g;
        ret = slot;
    }
    else
    {
        ret = &D_00625760;
    }

    return ret;
}

void func_001ED558(void *pvb, void *pv, void *pv3, float g)
{
    void *p = func_001ED4C8(pvb, 0, pv, g);
    STRUCT_OFFSET(p, 0xC, void *) = pv3;
}

void func_001ED588(void *pvb, void *pv, void *pv3, float g)
{
    void *p = func_001ED4C8(pvb, 1, pv, g);
    STRUCT_OFFSET(p, 0xC, void *) = pv3;
}

void func_001ED5B8(void *pvb, void *pv, float g)
{
    func_001ED4C8(pvb, 2, pv, g);
}

void func_001ED5D8(void *pvb, void *pv, float g)
{
    func_001ED4C8(pvb, 3, pv, g);
}

void func_001ED5F8(void *pvb, void *pv, float g)
{
    func_001ED4C8(pvb, 4, pv, g);
}

void func_001ED618(void *pvb, void *pv, float g)
{
    func_001ED4C8(pvb, 5, pv, g);
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", func_001ED638);