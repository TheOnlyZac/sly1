#include <hide.h>
#include <dl.h>
#include <dart.h>
#include <memory.h>

extern DL g_dlHshape;
extern DL g_dlHpnt;
extern DL g_dlHbsk;

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

INCLUDE_ASM("asm/nonmatchings/P2/hide", InitHshape__FP6HSHAPE);

INCLUDE_ASM("asm/nonmatchings/P2/hide", OnHshapeAdd__FP6HSHAPE);

INCLUDE_ASM("asm/nonmatchings/P2/hide", OnHshapeRemove__FP6HSHAPE);

INCLUDE_ASM("asm/nonmatchings/P2/hide", BindHshape__FP6HSHAPE);

struct HSHAPE;

void CloneHshape(HSHAPE *phshape, HSHAPE *phshapeBase)
{
    DLE dle = STRUCT_OFFSET(phshape, 0x38, DLE);
    CloneLo((LO *)phshape, (LO *)phshapeBase);
    STRUCT_OFFSET(phshape, 0x38, DLE) = dle;
}

INCLUDE_ASM("asm/nonmatchings/P2/hide", GetHshapeHidePos__FP6HSHAPEfP6VECTORPf);

INCLUDE_ASM("asm/nonmatchings/P2/hide", GetHshapeClosestHidePos__FP6HSHAPEPfP6VECTORT1);

INCLUDE_ASM("asm/nonmatchings/P2/hide", InitHpnt__FP4HPNT);

INCLUDE_ASM("asm/nonmatchings/P2/hide", OnHpntAdd__FP4HPNT);

INCLUDE_ASM("asm/nonmatchings/P2/hide", OnHpntRemove__FP4HPNT);

INCLUDE_ASM("asm/nonmatchings/P2/hide", BindHpnt__FP4HPNT);

INCLUDE_ASM("asm/nonmatchings/P2/hide", CloneHpnt__FP4HPNTT0);

INCLUDE_ASM("asm/nonmatchings/P2/hide", GetHpntClosestHidePos__FP4HPNTP6VECTORPf);

INCLUDE_ASM("asm/nonmatchings/P2/hide", FUN_0016a320);

void InitHbsk(HBSK *phbsk)
{
    InitSo((SO *)phbsk);
    SetAloRotationSpring((ALO *)phbsk, 3.0f);
    SetAloRotationDamping((ALO *)phbsk, 3.0f);
    SetAloPositionSmooth((ALO *)phbsk, 3.0f);
    SetAloRotationSmooth((ALO *)phbsk, 2.0f);
    STRUCT_OFFSET(phbsk, 0x568, float) = 300.0f;
}

extern qword D_002483D0[3];

void LoadHbskFromBrx(HBSK *phbsk, CBinaryInputStream *pbis)
{
    LoadSoFromBrx((SO *)phbsk, pbis);

    if (STRUCT_OFFSET(phbsk, 0x224, void *) == 0)
        STRUCT_OFFSET(phbsk, 0x224, void *) = PvAllocSwClearImpl(0xC0);

    STRUCT_OFFSET(STRUCT_OFFSET(phbsk, 0x224, void *), 0xB0, int) |= 1;

    void *pv = STRUCT_OFFSET(phbsk, 0x224, void *);
    STRUCT_OFFSET(pv, 0x0, qword) = D_002483D0[0];
    STRUCT_OFFSET(pv, 0x10, qword) = D_002483D0[1];
    STRUCT_OFFSET(pv, 0x20, qword) = D_002483D0[2];
}

void OnHbskAdd(HBSK *phbsk)
{
    OnSoAdd((SO *)phbsk);
    AppendDlEntry(&g_dlHbsk, phbsk);
}

void OnHbskRemove(HBSK *phbsk)
{
    OnSoRemove((SO *)phbsk);
    RemoveDlEntry(&g_dlHbsk, phbsk);
}

INCLUDE_ASM("asm/nonmatchings/P2/hide", CloneHbsk__FP4HBSKT0);

INCLUDE_ASM("asm/nonmatchings/P2/hide", FIgnoreHbskIntersection__FP4HBSKP2SO);

void PresetHbskAccel(HBSK *phbsk, float dt)
{
    MATRIX3 matUpright;

    PresetSoAccel((SO *)phbsk, dt);
    if (STRUCT_OFFSET(phbsk, 0x550, int) == 0)
    {
        TiltMatUpright((MATRIX3 *)((uint8_t *)phbsk + 0xD0), 0, &matUpright);
        AccelSoTowardMatSpring((SO *)phbsk, &matUpright,
                               STRUCT_OFFSET(phbsk, 0x214, CLQ *), &D_00248D30,
                               STRUCT_OFFSET(phbsk, 0x218, CLQ *), dt);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/hide", SetHbskHbsks__FP4HBSK5HBSKS);

INCLUDE_ASM("asm/nonmatchings/P2/hide", CdartStuckHbsk__FP4HBSK);

INCLUDE_ASM("asm/nonmatchings/P2/hide", PdartOldestHbskStuck__FP4HBSK);

INCLUDE_ASM("asm/nonmatchings/P2/hide", GetHbskClosestHidePos__FP4HBSKP6VECTORPf);
