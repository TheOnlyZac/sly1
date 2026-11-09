#include <hide.h>
#include <dl.h>
#include <jt.h>
#include <memory.h>
#include <basic.h>
#include <mat.h>

// Float constants in .rodata, both are FLT_MAX.
extern DLI *s_pdliFirst;
extern MATRIX3 g_matIdentity;
extern VECTOR D_00248D30;
extern float D_0024A794;
extern float D_0024A798;

DL g_dlHshape = {0};
DL g_dlHpnt = {0};
DL g_dlHbsk = {0};

void StartupHide()
{
    InitDl(&g_dlHshape, 0x38);
    InitDl(&g_dlHpnt, 0x50);
    InitDl(&g_dlHbsk, 0x558);
}

void ResetHideList()
{
    ClearDl(&g_dlHshape);
    ClearDl(&g_dlHpnt);
    ClearDl(&g_dlHbsk);
}

void InitHshape(HSHAPE *phshape)
{
    InitLo(phshape);
    phshape->oidTarget = OID_Nil;
    phshape->unk4c = 1;
    phshape->unk50 = 3;
    phshape->unk58 = D_0024A794;
}

void OnHshapeAdd(HSHAPE *phshape)
{
    OnLoAdd(phshape);
    AppendDlEntry(&g_dlHshape, phshape);
}

void OnHshapeRemove(HSHAPE *phshape)
{
    OnLoRemove(phshape);
    RemoveDlEntry(&g_dlHshape, phshape);
}

void BindHshape(HSHAPE *phshape)
{
    if (phshape->oidTarget != OID_Nil)
    {
        LO *plo = PloFindSwNearest(phshape->psw, phshape->oidTarget, phshape->paloParent);
        phshape->ploTarget = plo;
        STRUCT_OFFSET(plo, 0x398, int) = 0;
    }
}

void CloneHshape(HSHAPE *phshape, HSHAPE *phshapeBase)
{
    DLE dle = phshape->dleHshape;
    CloneLo(phshape, phshapeBase);
    phshape->dleHshape = dle;
}

INCLUDE_ASM("asm/nonmatchings/P2/hide", GetHshapeHidePos__FP6HSHAPEfP6VECTORPf);

INCLUDE_ASM("asm/nonmatchings/P2/hide", GetHshapeClosestHidePos__FP6HSHAPEPfP6VECTORT1);

void InitHpnt(HPNT *phpnt)
{
    InitLo(phpnt);
    phpnt->oidTarget = OID_Nil;
    phpnt->unk68 = 1;
    phpnt->unk70 = D_0024A798;
}

void OnHpntAdd(HPNT *phpnt)
{
    OnLoAdd(phpnt);
    AppendDlEntry(&g_dlHpnt, phpnt);
}

void OnHpntRemove(HPNT *phpnt)
{
    OnLoRemove(phpnt);
    RemoveDlEntry(&g_dlHpnt, phpnt);
}

void BindHpnt(HPNT *phpnt)
{
    if (phpnt->oidTarget != OID_Nil)
    {
        LO *plo = PloFindSwNearest(phpnt->psw, phpnt->oidTarget, phpnt->paloParent);
        phpnt->ploTarget = plo;
        STRUCT_OFFSET(plo, 0x398, int) = 0;
    }
}

void CloneHpnt(HPNT *phpnt, HPNT *phpntBase)
{
    DLE dle = phpnt->dleHpnt;
    CloneLo(phpnt, phpntBase);
    phpnt->dleHpnt = dle;
}

INCLUDE_ASM("asm/nonmatchings/P2/hide", GetHpntClosestHidePos__FP4HPNTP6VECTORPf);

INCLUDE_ASM("asm/nonmatchings/P2/hide", FUN_0016a320);

void InitHbsk(HBSK *phbsk)
{
    InitSo(phbsk);
    SetAloRotationSpring(phbsk, 3.0f);
    SetAloRotationDamping(phbsk, 3.0f);
    SetAloPositionSmooth(phbsk, 3.0f);
    SetAloRotationSmooth(phbsk, 2.0f);
    STRUCT_OFFSET(phbsk, 0x568, float) = 300.0f;
}

void LoadHbskFromBrx(HBSK *phbsk, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(phbsk, pbis);
    if (STRUCT_OFFSET(phbsk, 0x224, void *) == NULL)
        STRUCT_OFFSET(phbsk, 0x224, void *) = PvAllocSwClearImpl(0xC0);

    STRUCT_OFFSET(STRUCT_OFFSET(phbsk, 0x224, void *), 0xB0, uint) |= 1;
    void *pv = STRUCT_OFFSET(phbsk, 0x224, void *);
    STRUCT_OFFSET(pv, 0x00, qword) = STRUCT_OFFSET(&g_matIdentity, 0x00, qword);
    STRUCT_OFFSET(pv, 0x10, qword) = STRUCT_OFFSET(&g_matIdentity, 0x10, qword);
    STRUCT_OFFSET(pv, 0x20, qword) = STRUCT_OFFSET(&g_matIdentity, 0x20, qword);
}

void OnHbskAdd(HBSK *phbsk)
{
    OnSoAdd(phbsk);
    AppendDlEntry(&g_dlHbsk, phbsk);
}

void OnHbskRemove(HBSK *phbsk)
{
    OnSoRemove(phbsk);
    RemoveDlEntry(&g_dlHbsk, phbsk);
}

void CloneHbsk(HBSK *phbsk, HBSK *phbskBase)
{
    DLE dle = STRUCT_OFFSET(phbsk, 0x558, DLE);
    CloneSo(phbsk, phbskBase);
    STRUCT_OFFSET(phbsk, 0x558, DLE) = dle;
}

int FIgnoreHbskIntersection(HBSK *phbsk, SO *psoOther)
{
    if (psoOther == g_pjt && phbsk == STRUCT_OFFSET(g_pjt, 0x23B0, HBSK *))
        return 1;

    return FIgnoreSoIntersection(phbsk, psoOther);
}

void PresetHbskAccel(HBSK *phbsk, float dt)
{
    PresetSoAccel(phbsk, dt);
    if (STRUCT_OFFSET(phbsk, 0x550, int) == HBSKS_Available)
    {
        MATRIX3 matUpright;
        TiltMatUpright(&STRUCT_OFFSET(phbsk, 0xD0, MATRIX3), NULL, &matUpright);
        AccelSoTowardMatSpring(phbsk, &matUpright, STRUCT_OFFSET(phbsk, 0x214, CLQ *), &D_00248D30, STRUCT_OFFSET(phbsk, 0x218, CLQ *), dt);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/hide", SetHbskHbsks__FP4HBSK5HBSKS);

INCLUDE_ASM("asm/nonmatchings/P2/hide", CdartStuckHbsk__FP4HBSK);
#ifdef SKIP_ASM
/**
 * @todo Loop body matches, the iterator setup is scheduled differently (22 differing lines).
 * Iterates the child list with a DLI that links itself into the global s_pdliFirst chain.
 */
struct DLIX : DLI
{
    inline DLIX(DL *pdl)
    {
        m_pdl = pdl;
        m_ppv = (void **)pdl;
        m_pdliNext = s_pdliFirst;
        s_pdliFirst = this;
        m_ibDle = pdl->ibDle;
    }
    inline ~DLIX() { s_pdliFirst = m_pdliNext; }
    inline void *PvFirst()
    {
        void *pv = m_pdl->head;
        m_ppv = (void **)((char *)pv + m_ibDle);
        return pv;
    }
    inline void *PvNext()
    {
        void *pv = *m_ppv;
        m_ppv = (void **)((char *)pv + m_ibDle);
        return pv;
    }
};

int CdartStuckHbsk(HBSK *phbsk)
{
    int cdart = 0;
    DLIX dli((DL *)((char *)phbsk + 0x34));
    for (void *pv = dli.PvFirst(); pv; pv = dli.PvNext())
    {
        if (FIsBasicDerivedFrom((BASIC *)pv, (CID)70))
        {
            if ((uint)(STRUCT_OFFSET(pv, 0x550, int) - 3) <= 1)
                cdart++;
        }
    }
    return cdart;
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/hide", PdartOldestHbskStuck__FP4HBSK);

INCLUDE_ASM("asm/nonmatchings/P2/hide", GetHbskClosestHidePos__FP4HBSKP6VECTORPf);
