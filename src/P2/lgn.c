#include <lgn.h>
#include <suv.h>
#include <ac.h>
#include <memory.h>
#include <math.h>
#include <so.h>

void InitLgn(LGN *plgn)
{
    InitSuv((SUV *)plgn);
    STRUCT_OFFSET(plgn, 0xbf4, float) = -10.0f; // plgn->tFlash
}

INCLUDE_ASM("asm/nonmatchings/P2/lgn", PostLgnLoad__FP3LGN);

INCLUDE_ASM("asm/nonmatchings/P2/lgn", UpdateLgnActive__FP3LGNP3JOYf);

INCLUDE_ASM("asm/nonmatchings/P2/lgn", UpdateLgn__FP3LGNf);

INCLUDE_ASM("asm/nonmatchings/P2/lgn", FUN_00181658);

INCLUDE_ASM("asm/nonmatchings/P2/lgn", OnLgnActive__FP3LGNiP2PO);

INCLUDE_ASM("asm/nonmatchings/P2/lgn", RenderLgnAll__FP3LGNP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/lgn", GetLgnCpdefi__FP3LGNfP6CPDEFI);

INCLUDE_ASM("asm/nonmatchings/P2/lgn", FInvulnerableLgn__FP3LGN3ZPK);

JTHS JthsCurrentLgn(LGN *plgn)
{
    return (JTHS)(STRUCT_OFFSET(plgn, 0xbf0, int) != 0); // plgn->fFlash
}

void UseLgnCharm(LGN *plgn)
{
    UsePoCharm((PO *)plgn);
    SetLgnLgns(plgn, LGNS_Active);
}

extern VECTOR D_00264180;
extern float D_00264190;

void ApplyLgnThrow(LGN *plgn, PO *ppo)
{
    VECTOR posTarget;
    VECTOR v;

    ConvertAloPos((ALO *)plgn, NULL, &D_00264180, &posTarget);
    CalculateSoTrajectoryApex((SO *)ppo, &posTarget, D_00264190, &v);
    (*(void (**)(SO *, VECTOR *))(*(uint8_t **)ppo + 0x90))((SO *)ppo, &v);
    STRUCT_OFFSET(ppo, 0x638, float) = RadNormalize(atan2f(v.y, v.x) + 3.1415927f);
    FixStepAngularVelocity((STEP *)ppo);
    SetJtJts((JT *)ppo, JTS_Sidestep, (JTBS)0x2B);
}

INCLUDE_ASM("asm/nonmatchings/P2/lgn", FTakeLgnDamage__FP3LGNP3ZPR);

INCLUDE_ASM("asm/nonmatchings/P2/lgn", HandleLgnMessage__FP3LGN5MSGIDPv);

void FUN_00181d88(uint8_t *param_1)
{
    FUN_001bc4d8(param_1, param_1 + 0xC04);
}

INCLUDE_ASM("asm/nonmatchings/P2/lgn", SetLgnLgns__FP3LGN4LGNS);

INCLUDE_ASM("asm/nonmatchings/P2/lgn", UpdateLgnrAim__FP4LGNRP3JOY);

INCLUDE_ASM("asm/nonmatchings/P2/lgn", DrawLgnr__FP4LGNR);

INCLUDE_ASM("asm/nonmatchings/P2/lgn", InitSwp__FP3SWP);

extern SNIP D_00264230;

void PostSwpLoad(SWP *pswp)
{
    PostBrkLoad((BRK *)pswp);
    SnipAloObjects((ALO *)pswp, 2, &D_00264230);
    STRUCT_OFFSET(pswp, 0x6c8, SMA *) =
        PsmaApplySm(STRUCT_OFFSET(pswp, 0x6c4, SM *), (ALO *)pswp, (OID)0x36e, 0);
    ACG *pacg = PacgNew((ACGK) 0);
    STRUCT_OFFSET(pswp, 0x6e8, ACG *) = pacg;
    STRUCT_OFFSET(pacg, 0x8, int) = 0;
    STRUCT_OFFSET(STRUCT_OFFSET(pswp, 0x6e8, ACG *), 0xc, void *) = PvAllocSwImpl(0xc00);
}

INCLUDE_ASM("asm/nonmatchings/P2/lgn", UpdateSwp__FP3SWPf);

INCLUDE_ASM("asm/nonmatchings/P2/lgn", ProjectSwpTransform__FP3SWPfi);

INCLUDE_ASM("asm/nonmatchings/P2/lgn", SetSwpShape__FP3SWPP5SHAPEf);
