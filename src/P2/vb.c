#include <vb.h>
#include <jt.h>
#include <ui.h>
#include <find.h>
#include <asega.h>
#include <memory.h>
#include <sce/memset.h>

extern char D_00625760;
extern char g_unkblot7;
extern SNIP D_00275C90;
extern SNIP D_00275CA0;
extern OID D_00275CF8;

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001EB460);

void FUN_001EB518(SO *pso, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(pso, pbis);
    SnipAloObjects(pso, 1, &D_00275C90);
}

void FUN_001EB550(void *pv, MSGID msgid, void *pvContext)
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

void FUN_001EB598(ALO *palo)
{
    PostAloLoad(palo);
    SnipAloObjects(palo, 4, &D_00275CA0);

    STRUCT_OFFSET(palo, 0x614, void *) = PsmaApplySm(STRUCT_OFFSET(palo, 0x610, SM *), palo, (OID)0x4CA, 1);

    PostSwCallback(palo->psw, FUN_001EB550, palo, MSGID_callback, NULL);
}

void FUN_001EB608(PO *ppo, int n, PO *ppoOther)
{
    OnPoActive(ppo, n, ppoOther);

    LO *plo = PloFindSwObjectByClass(ppo->psw, 5, (CID)0x13, (LO *)0);
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

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001EB698);

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001EB748);

int FUN_001EBC88(void *pv)
{
    if ((g_grfcht & 1) != 0)
        return 1;

    if (IsSwHandsOff(STRUCT_OFFSET(pv, 0x14, SW *)) == 0)
        return STRUCT_OFFSET(pv, 0x688, int) != 0;

    return 1;
}

void FUN_001EBCD8(void *pvb, void *pv)
{
    struct U8 { char a[8]; };
    struct U8 *dst;
    int c = STRUCT_OFFSET(pvb, 0x630, int);

    dst = (struct U8 *)((char *)pvb + ((c << 3) + 0x634));
    STRUCT_OFFSET(pvb, 0x630, int) = c + 1;
    *dst = *(struct U8 *)pv;
}

int FUN_001EBD08()
{
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001EBD10);

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001EBDD0);

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001EBEB0);

void FUN_001EBF40(void *pv, CBinaryInputStream *pbis)
{
    STEPGUARD *pstepguard = (STEPGUARD *)pv;
    LoadStepguardFromBrx(pstepguard, pbis);

    OID *poid = &D_00275CF8;
    void **ppv = (void **)((char *)pstepguard + 0xC10);

    for (int i = 3; i >= 0; i--)
    {
        *ppv = PasegFindStepguard(pstepguard, *poid);
        poid++;
        ppv++;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001EBFB0);

void FUN_001EC098(PO *ppo)
{
    OnPoRemove(ppo);
}

void FUN_001EC0B8(PO *ppo)
{
    OnPoAdd(ppo);
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001EC0D8);

int FUN_001EC188()
{
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001EC190);

void FUN_001EC380(ALO *palo, CM *pcm, RO *pro)
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

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001EC3D8);

void FUN_001EC478(void *pv, int nSgs)
{
    int nState;
    OID oid;
    OID oidGoal;

    OnStepguardExitingSgs((STEPGUARD *)pv, (SGS)nSgs);

    nState = STRUCT_OFFSET(pv, 0x724, int);
    if (nState != 0xE)
    {
        if (nState != 0x10)
            return;

        STRUCT_OFFSET(pv, 0xC94, int) = 0;
        GetSmaCur(STRUCT_OFFSET(pv, 0xC54, SMA *), &oid);

        switch (oid)
        {
        case (OID)0x4EE:
            oidGoal = (OID)0x4EF;
            break;
        case (OID)0x4F1:
            oidGoal = (OID)0x4F2;
            break;
        case (OID)0x4F4:
            oidGoal = (OID)0x4F5;
            break;
        }
        SetSmaGoal(STRUCT_OFFSET(pv, 0xC54, SMA *), oidGoal);
        return;
    }

    STRUCT_OFFSET(pv, 0xC94, int) = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001EC528);

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001EC570);

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001EC7A8);

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001EC828);

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001ECB18);

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001ECBC8);

void FUN_001ECDF8(void *pv)
{
    OID oid;
    void *pvUnk;

    GetSmaCur(STRUCT_OFFSET(pv, 0xC54, SMA *), &oid);

    pvUnk = (void *)0;
    switch (oid)
    {
    case (OID)0x4EE:
    case (OID)0x4F1:
    case (OID)0x4F4:
    case (OID)0x4F7:
        pvUnk = FUN_001e9970();
        break;
    }

    if (pvUnk != (void *)0)
    {
        ((void (*)(void *))STRUCT_OFFSET(STRUCT_OFFSET(&g_unkblot7, 0, void *), 0x38, void *))(&g_unkblot7);
        return;
    }
    ((void (*)(void *))STRUCT_OFFSET(STRUCT_OFFSET(&g_unkblot7, 0, void *), 0x3C, void *))(&g_unkblot7);
}

void FUN_001ECE98(void *pv, int n)
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

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001ECF10);

void FUN_001ED018(void *pvb, int n)
{
    STRUCT_OFFSET(pvb, 0xC34, int) = n;
}

void FUN_001ED020(void *pvb)
{
    FUN_001ED210(STRUCT_OFFSET(pvb, 0xC38, void *));
    STRUCT_OFFSET(pvb, 0xC38, void *) = 0;
}

void FUN_001ED050(void *pvb, int n)
{
    STRUCT_OFFSET(pvb, 0xC5C, int) = n;
    STRUCT_OFFSET(pvb, 0xC8C, float) = 60.0f / (float)n;
}

void FUN_001ED070(void *pvb, int n)
{
    STRUCT_OFFSET(pvb, 0xC60, int) = n;
    STRUCT_OFFSET(pvb, 0xC64, float) = STRUCT_OFFSET(pvb, 0xC88, float) * (float)n;
}

void FUN_001ED090(void *pvb, void *pasega, void *pv)
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
    STRUCT_OFFSET(slot, 4, void *) = pv;
    STRUCT_OFFSET(slot, 0, void *) = pasega;
    SubscribeAsegaObject((ASEGA *)pasega, (LO *)pvb);
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001ED0D8);

void FUN_001ED168(LO *plo)
{
    InitLo(plo);
    STRUCT_OFFSET(plo, 0x38, void *) = PvAllocSwImpl(0xC00);
}

void FUN_001ED198(LO *plo)
{
    PostLoLoad(plo);
    STRUCT_OFFSET(plo, 0x40, LO *) = PloFindSwObjectByClass(plo->psw, 5, (CID)0x13, NULL);
}

void FUN_001ED1D8(void *pv)
{
    STRUCT_OFFSET(pv, 0x3C, int) = 0;
    STRUCT_OFFSET(pv, 0x44, int) = STRUCT_OFFSET(STRUCT_OFFSET(pv, 0x40, void *), 0xC70, int);
    HandleLoSpliceEvent((LO *)pv, 0x1A, 0, NULL);
}

void FUN_001ED210(void *pv)
{
    HandleLoSpliceEvent((LO *)pv, 0x1C, 0, NULL);

    int n = 5;
    FUN_001ED318(pv, &n);

    if (STRUCT_OFFSET(STRUCT_OFFSET(pv, 0x40, void *), 0xC3C, int) != 0)
    {
        n = 3;
        FUN_001ED318(pv, &n);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001ED278);

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001ED318__FPvPi);

void *FUN_001ED4C8(void *pvb, int n, void *pv, float g)
{
    int c = STRUCT_OFFSET(pvb, 0x34, int);
    void *ret;

    if (c < 0xC0)
    {
        char *slot = STRUCT_OFFSET(pvb, 0x38, char *);

        slot += c << 4;
        STRUCT_OFFSET(pvb, 0x34, int) = c + 1;
        memset(slot, 0, 0x10);
        STRUCT_OFFSET(slot, 0, int) = n;
        STRUCT_OFFSET(slot, 4, void *) = pv;
        STRUCT_OFFSET(slot, 8, float) = g;
        ret = slot;
    }
    else
    {
        ret = &D_00625760;
    }

    return ret;
}

void FUN_001ED558(void *pvb, void *pv, void *pv3, float g)
{
    void *p = FUN_001ED4C8(pvb, 0, pv, g);
    STRUCT_OFFSET(p, 0xC, void *) = pv3;
}

void FUN_001ED588(void *pvb, void *pv, void *pv3, float g)
{
    void *p = FUN_001ED4C8(pvb, 1, pv, g);
    STRUCT_OFFSET(p, 0xC, void *) = pv3;
}

void FUN_001ED5B8(void *pvb, void *pv, float g)
{
    FUN_001ED4C8(pvb, 2, pv, g);
}

void FUN_001ED5D8(void *pvb, void *pv, float g)
{
    FUN_001ED4C8(pvb, 3, pv, g);
}

void FUN_001ED5F8(void *pvb, void *pv, float g)
{
    FUN_001ED4C8(pvb, 4, pv, g);
}

void FUN_001ED618(void *pvb, void *pv, float g)
{
    FUN_001ED4C8(pvb, 5, pv, g);
}

INCLUDE_ASM("asm/nonmatchings/P2/vb", FUN_001ED638);
