#include <hide.h>
#include <dl.h>

extern DL g_dlHshape;
extern DL g_dlHpnt;
extern DL g_dlHbsk;

void StartupHide()
{
    InitDl(&g_dlHshape, 0x38);
    InitDl(&g_dlHpnt, 0x50);
    InitDl(&g_dlHbsk, 0x558);
}

INCLUDE_ASM("asm/nonmatchings/P2/hide", ResetHideList__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/hide", InitHshape__FP6HSHAPE);

INCLUDE_ASM("asm/nonmatchings/P2/hide", OnHshapeAdd__FP6HSHAPE);

INCLUDE_ASM("asm/nonmatchings/P2/hide", OnHshapeRemove__FP6HSHAPE);

INCLUDE_ASM("asm/nonmatchings/P2/hide", BindHshape__FP6HSHAPE);

INCLUDE_ASM("asm/nonmatchings/P2/hide", CloneHshape__FP6HSHAPET0);

INCLUDE_ASM("asm/nonmatchings/P2/hide", GetHshapeHidePos__FP6HSHAPEfP6VECTORPf);

INCLUDE_ASM("asm/nonmatchings/P2/hide", GetHshapeClosestHidePos__FP6HSHAPEPfP6VECTORT1);

INCLUDE_ASM("asm/nonmatchings/P2/hide", InitHpnt__FP4HPNT);

INCLUDE_ASM("asm/nonmatchings/P2/hide", OnHpntAdd__FP4HPNT);

INCLUDE_ASM("asm/nonmatchings/P2/hide", OnHpntRemove__FP4HPNT);

INCLUDE_ASM("asm/nonmatchings/P2/hide", BindHpnt__FP4HPNT);

INCLUDE_ASM("asm/nonmatchings/P2/hide", CloneHpnt__FP4HPNTT0);

INCLUDE_ASM("asm/nonmatchings/P2/hide", GetHpntClosestHidePos__FP4HPNTP6VECTORPf);

INCLUDE_ASM("asm/nonmatchings/P2/hide", FUN_0016a320);

INCLUDE_ASM("asm/nonmatchings/P2/hide", InitHbsk__FP4HBSK);

INCLUDE_ASM("asm/nonmatchings/P2/hide", LoadHbskFromBrx__FP4HBSKP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/hide", OnHbskAdd__FP4HBSK);

INCLUDE_ASM("asm/nonmatchings/P2/hide", OnHbskRemove__FP4HBSK);

INCLUDE_ASM("asm/nonmatchings/P2/hide", CloneHbsk__FP4HBSKT0);

INCLUDE_ASM("asm/nonmatchings/P2/hide", FIgnoreHbskIntersection__FP4HBSKP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/hide", PresetHbskAccel__FP4HBSKf);

INCLUDE_ASM("asm/nonmatchings/P2/hide", SetHbskHbsks__FP4HBSK5HBSKS);

INCLUDE_ASM("asm/nonmatchings/P2/hide", CdartStuckHbsk__FP4HBSK);

INCLUDE_ASM("asm/nonmatchings/P2/hide", PdartOldestHbskStuck__FP4HBSK);

INCLUDE_ASM("asm/nonmatchings/P2/hide", GetHbskClosestHidePos__FP4HBSKP6VECTORPf);
