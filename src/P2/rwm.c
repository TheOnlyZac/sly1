#include <rwm.h>
#include <sce/memset.h>
#include <memory.h>
#include <find.h>
#include <alo.h>
#include <xform.h>
#include <mat.h>
#include <gcc/math.h>

INCLUDE_ASM("asm/nonmatchings/P2/rwm", InitRwm__FP3RWM);

void OnRwmRemove(RWM *prwm)
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

extern "C" void FUN_001a84c8(RWM *prwmDst, RWM *prwmSrc)
{
    CloneLo((LO *)prwmDst, (LO *)prwmSrc);
    if (STRUCT_OFFSET(prwmDst, 0x3c, void *) != 0 &&
        STRUCT_OFFSET(STRUCT_OFFSET(prwmDst, 0x3c, void *), 0x4, int) != 0)
    {
        if (STRUCT_OFFSET(STRUCT_OFFSET(prwmSrc, 0x3c, void *), 0x8, int) == 0)
        {
            STRUCT_OFFSET(STRUCT_OFFSET(prwmSrc, 0x3c, void *), 0x8, int) = 1;
            InitDl((DL *)((uint8_t *)STRUCT_OFFSET(prwmSrc, 0x3c, void *) + 0x14), 0x18);
        }
        STRUCT_OFFSET(prwmDst, 0x3c, void *) = 0;
        FUN_001a8110(prwmDst);
        STRUCT_OFFSET(STRUCT_OFFSET(prwmDst, 0x3c, void *), 0x4, int) = 1;
        STRUCT_OFFSET(STRUCT_OFFSET(prwmDst, 0x3c, void *), 0x8, int) = 2;
        STRUCT_OFFSET(STRUCT_OFFSET(prwmDst, 0x3c, void *), 0x14, RWM *) = prwmSrc;
        AppendDlEntry((DL *)((uint8_t *)STRUCT_OFFSET(prwmSrc, 0x3c, void *) + 0x14),
                      STRUCT_OFFSET(prwmDst, 0x3c, void *));
    }
    else
    {
        STRUCT_OFFSET(prwmDst, 0x38, void *) =
            PvAllocSwCopyImpl(STRUCT_OFFSET(prwmSrc, 0x34, int) * 0x14,
                              STRUCT_OFFSET(prwmSrc, 0x38, void *));
    }
}

void PostRwmLoad(RWM *prwm)
{
    LO *plo;
    OID oid;

    PostLoLoad((LO *)prwm);
    if (STRUCT_OFFSET(prwm, 0x168, int) != 0)
        return;
    STRUCT_OFFSET(prwm, 0x168, int) = 1;

    oid = STRUCT_OFFSET(prwm, 0x4c, OID);
    if (oid != OID_Nil)
    {
        plo = PloFindSwNearest(STRUCT_OFFSET(prwm, 0x14, SW *), oid, (LO *)prwm);
        if (plo != 0)
        {
            if (FIsBasicDerivedFrom((BASIC *)plo, CID_WARP))
                STRUCT_OFFSET(prwm, 0x60, LO *) = plo;
            else if (FIsBasicDerivedFrom((BASIC *)plo, (CID)0x73))
                STRUCT_OFFSET(prwm, 0x64, LO *) = plo;
            else if (FIsBasicDerivedFrom((BASIC *)plo, CID_ALO))
                STRUCT_OFFSET(prwm, 0x68, LO *) = plo;
        }
    }

    oid = STRUCT_OFFSET(prwm, 0x50, OID);
    if (oid != OID_Nil)
    {
        plo = PloFindSwNearest(STRUCT_OFFSET(prwm, 0x14, SW *), oid, (LO *)prwm);
        if (plo != 0)
        {
            if (FIsBasicDerivedFrom((BASIC *)plo, CID_ALO))
                STRUCT_OFFSET(prwm, 0xe0, LO *) = plo;
            else if (FIsBasicDerivedFrom((BASIC *)plo, (CID)0x75))
                STRUCT_OFFSET(prwm, 0xe4, LO *) = plo;
        }
    }

    oid = STRUCT_OFFSET(prwm, 0x54, OID);
    if (oid != OID_Nil)
    {
        plo = PloFindSwNearest(STRUCT_OFFSET(prwm, 0x14, SW *), oid, (LO *)prwm);
        if (plo != 0)
        {
            if (FIsBasicDerivedFrom((BASIC *)plo, (CID)0x73))
                STRUCT_OFFSET(prwm, 0x160, LO *) = plo;
            else if (FIsBasicDerivedFrom((BASIC *)plo, CID_ALO))
                STRUCT_OFFSET(prwm, 0x164, LO *) = plo;
        }
    }

    oid = STRUCT_OFFSET(prwm, 0x58, OID);
    if (oid != OID_Nil)
    {
        STRUCT_OFFSET(prwm, 0x5c, LO *) =
            PloFindSwNearest(STRUCT_OFFSET(prwm, 0x14, SW *), oid, (LO *)prwm);
    }
}

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

void GetRwacPanImpl(RWAC *prwac, float *pradPan, ALO *palo) asm("GetRwacPan__FP4RWACPf");

void GetRwacPanImpl(RWAC *prwac, float *pradPan, ALO *palo)
{
    MATRIX3 mat;

    XFM *pxfm = STRUCT_OFFSET(prwac, 0x10, XFM *);
    if (pxfm != 0)
    {
        GetXfmMat(pxfm, &mat);
        ConvertAloMat(0, palo, &mat, &mat);
        *pradPan = atan2f(mat.mat[0][1], mat.mat[0][0]);
    }
    else
    {
        MATRIX3 *pmat = STRUCT_OFFSET(prwac, 0x14, MATRIX3 *);
        if (pmat != 0)
        {
            ConvertAloMat(0, palo, (MATRIX3 *)((uint8_t *)pmat + 0x110), &mat);
            *pradPan = atan2f(mat.mat[0][1], mat.mat[0][0]);
        }
        else
        {
            *pradPan = STRUCT_OFFSET(prwac, 0x8, float);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rwm", GetRwacTilt__FP4RWACPf);
