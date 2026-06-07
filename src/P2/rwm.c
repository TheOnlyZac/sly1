#include <rwm.h>
#include <sce/memset.h>
#include <memory.h>

INCLUDE_ASM("asm/nonmatchings/P2/rwm", InitRwm__FP3RWM);

extern "C" void FUN_001a93c8(RWM *prwm);

extern "C" void OnRwmRemove(RWM *prwm)
{
    OnLoRemove(prwm);
    FUN_001a93c8(prwm);
}

extern "C" {
void *FUN_001a8110(RWM *prwm)
{
    if (STRUCT_OFFSET(prwm, 0x3c, void *) == 0)
    {
        void *pv = PvAllocSwClearImpl(0x20);
        STRUCT_OFFSET(prwm, 0x3c, void *) = pv;
        STRUCT_OFFSET(pv, 0x0, RWM *) = prwm;
    }
    return STRUCT_OFFSET(prwm, 0x3c, void *);
}
}

INCLUDE_ASM("asm/nonmatchings/P2/rwm", FUN_001a8150);

INCLUDE_ASM("asm/nonmatchings/P2/rwm", InitRwmCallback__FP3RWM5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/rwm", FUN_001a84c8);

INCLUDE_ASM("asm/nonmatchings/P2/rwm", PostRwmLoad__FP3RWM);

extern "C" void FUN_001a93c8(RWM *prwm);

void FUN_001a86f8(RWM *prwm, int f)
{
    if (f != 0)
        FUN_001a93c8(prwm);
}

INCLUDE_ASM("asm/nonmatchings/P2/rwm", PrwcFindRwm__FP3RWM3OID);

void EnableRwmRwc(RWM *prwm, OID oidCache)
{
    RWC *prwc = PrwcFindRwm(prwm, oidCache);
    if (prwc != NULL)
        STRUCT_OFFSET(prwc, 0x10, int) |= 0x2;
}

void DisableRwmRwc(RWM *prwm, OID oidCache)
{
    RWC *prwc = PrwcFindRwm(prwm, oidCache);
    if (prwc != NULL)
        STRUCT_OFFSET(prwc, 0x10, int) &= ~0x2;
}

void ResizeRwmRwc(RWM *prwm, OID oidCache, int cpso)
{
    RWC *prwc = PrwcFindRwm(prwm, oidCache);
    if (prwc != NULL)
    {
        int cMax = STRUCT_OFFSET(prwc, 0xc, int);
        STRUCT_OFFSET(prwc, 0x4, int) = (cpso < cMax) ? cpso : cMax;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rwm", FIsRwmAmmo__FP3RWMP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rwm", FAvailableRwmAmmo__FP3RWMP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rwm", CycleRwmCache__FP3RWM);

INCLUDE_ASM("asm/nonmatchings/P2/rwm", ReloadRwm__FP3RWM);

INCLUDE_ASM("asm/nonmatchings/P2/rwm", FEnsureRwmLoaded__FP3RWM);

INCLUDE_ASM("asm/nonmatchings/P2/rwm", FFireRwm__FP3RWMi);

extern "C" void FUN_001a93c8(RWM *prwm)
{
    int *p = STRUCT_OFFSET(prwm, 0x3c, int *);
    STRUCT_OFFSET(prwm, 0x48, int) = 0;
    if (p != 0)
    {
        if (p[1] != 0)
            p[4] = 0;
    }
}

extern qword D_002483D0[3];

void ClearRwmFireInfo(RWM *prwm)
{
    uint8_t *p = (uint8_t *)prwm + 0x60;
    memset(p, 0, 0x80);
    STRUCT_OFFSET(p, 0x20, qword) = D_002483D0[0];
    STRUCT_OFFSET(p, 0x30, qword) = D_002483D0[1];
    STRUCT_OFFSET(p, 0x40, qword) = D_002483D0[2];
}

INCLUDE_ASM("asm/nonmatchings/P2/rwm", ClearRwmTargetInfo__FP3RWM);

void ClearRwmAimConstraints(RWM *prwm)
{
    memset((uint8_t *)prwm + 0x150, 0, 0x18);
}

INCLUDE_ASM("asm/nonmatchings/P2/rwm", GetRwfiPosMat__FP4RWFIP6VECTORP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/rwm", GetRwtiPos__FP4RWTIP6VECTORT1);

INCLUDE_ASM("asm/nonmatchings/P2/rwm", GetRwacPan__FP4RWACPf);

INCLUDE_ASM("asm/nonmatchings/P2/rwm", GetRwacTilt__FP4RWACPf);
