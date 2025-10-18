#include <xform.h>
#include <button.h>
#include <brx.h>
#include <sw.h>
#include <cm.h>

INCLUDE_ASM("asm/nonmatchings/P2/xform", InitXfm__FP3XFM);

void LoadXfmFromBrx(XFM *pxfm, CBinaryInputStream *pbis)
{
    pbis->ReadMatrix(&pxfm->matLocal);
    pbis->ReadVector(&pxfm->posLocal);
    LoadOptionsFromBrx(pxfm, pbis);
}

void SetXfmParent(XFM *pxfm, ALO *paloParent)
{
    ConvertAloPos(pxfm->paloParent, paloParent, &pxfm->posLocal, &pxfm->posLocal);
    ConvertAloMat(pxfm->paloParent, paloParent, &pxfm->matLocal, &pxfm->matLocal);
    SetLoParent(pxfm, paloParent);
}

void ApplyXfmProxy(XFM *pxfm, PROXY *pproxyApply)
{
    ConvertAloPos(pproxyApply, (ALO *)nullptr, &pxfm->posLocal, &pxfm->posLocal);
    ConvertAloMat(pproxyApply, (ALO *)nullptr, &pxfm->matLocal, &pxfm->matLocal);
}

INCLUDE_ASM("asm/nonmatchings/P2/xform", ConvertXfmLocalToWorld__FP3XFMP6VECTORT1);

void GetXfmPos(XFM *pxfm, VECTOR *ppos)
{
    ConvertAloPos(pxfm->paloParent, (ALO *)nullptr, &pxfm->posLocal, ppos);
}

void GetXfmMat(XFM *pxfm, MATRIX3 *pmat)
{
    ConvertAloMat(pxfm->paloParent, (ALO *)nullptr, &pxfm->matLocal, pmat);
}

INCLUDE_ASM("asm/nonmatchings/P2/xform", PwarpFromOid__F3OIDT0);

INCLUDE_ASM("asm/nonmatchings/P2/xform", LoadWarpFromBrx__FP4WARPP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/xform", CloneWarp__FP4WARPT0);

INCLUDE_ASM("asm/nonmatchings/P2/xform", PostWarpLoad__FP4WARP);

INCLUDE_ASM("asm/nonmatchings/P2/xform", TriggerWarp__FP4WARP);

void SetWarpRsmg(WARP *pwarp, int fOnTrigger, OID oidRoot, OID oidSM, OID oidGoal)
{
    // pwarp->arsmg & pwarp->crsmg
    FAddRsmg(&STRUCT_OFFSET(pwarp, 0xb8, RSMG), 4, &STRUCT_OFFSET(pwarp, 0xb4, int), fOnTrigger, oidRoot, oidSM, oidGoal);
}

INCLUDE_ASM("asm/nonmatchings/P2/xform", FUN_001F4308);

INCLUDE_ASM("asm/nonmatchings/P2/xform", TeleportSwPlayer__FP2SW3OIDT1);

INCLUDE_ASM("asm/nonmatchings/P2/xform", PexitDefault__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/xform", TriggerDefaultExit__Fi5WIPEK);

INCLUDE_ASM("asm/nonmatchings/P2/xform", LoadExitFromBrx__FP4EXITP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/xform", PostExitLoad__FP4EXIT);

void SetExitExits(EXIT *pexit, EXITS exits)
{
    if (exits == STRUCT_OFFSET(pexit, 0x2e4, EXITS)) // pexit->exits
    {
        return;
    }

    // pexit->exits
    if (STRUCT_OFFSET(pexit, 0x2e4, EXITS) == EXITS_Totals && exits != EXITS_Exiting)
    {
        g_totals.pvttotals->pfnHideBlot(&g_totals);
    }

    if (exits != EXITS_Exiting)
    {
        STRUCT_OFFSET(pexit, 0x2e4, EXITS) = exits; // pexit->exits
        STRUCT_OFFSET(pexit, 0x2e8, float) = g_clock.t; // pexit->tExits
        return;
    }

    uint64_t tmp = STRUCT_OFFSET(pexit, 0x2c8, uint64_t);
    STRUCT_OFFSET(pexit, 0x2c8, uint64_t) = (tmp & ~0x30000000000ULL) | (0x8000ULL << 0x19);

    IncrementSwHandsOff(pexit->psw);

    STRUCT_OFFSET(pexit, 0x2e4, EXITS) = exits; // pexit->exits
    STRUCT_OFFSET(pexit, 0x2e8, float) = g_clock.t; // pexit->tExits
}

INCLUDE_ASM("asm/nonmatchings/P2/xform", TriggerExit__FP4EXIT);

INCLUDE_ASM("asm/nonmatchings/P2/xform", WipeExit__FP4EXIT);

INCLUDE_ASM("asm/nonmatchings/P2/xform", UpdateExit__FfP4EXIT);

void InitCamera(CAMERA *pcamera)
{
    InitAlo(pcamera);
    STRUCT_OFFSET(pcamera, 0x2d0, OID) = OID_Nil; // pcamera->oidTarget
}

INCLUDE_ASM("asm/nonmatchings/P2/xform", PostCameraLoad__FP6CAMERA);

void EnableCamera(CAMERA *pcamera)
{
    if (STRUCT_OFFSET(pcamera, 0x310, int) == 0) // pcamera->fSetCplcy
    {
        // g_pcm->cpaseg
        SetCmPolicy(g_pcm, CPP_Animated, &STRUCT_OFFSET(g_pcm, 0x510, CPLCY), (SO *)nullptr, pcamera);
        STRUCT_OFFSET(pcamera, 0x310, int) = 1; // pcamera->fSetCplcy
    }
}

void DisableCamera(CAMERA *pcamera)
{
    if (STRUCT_OFFSET(pcamera, 0x310, int) != 0) // pcamera->fSetCplcy
    {
        // g_pcm->cpaseg
        RevokeCmPolicy(g_pcm, 0x0b, CPP_Animated, &STRUCT_OFFSET(g_pcm, 0x510, CPLCY), (SO *)nullptr, pcamera);
        STRUCT_OFFSET(pcamera, 0x310, int) = 0; // pcamera->fSetCplcy
    }
}
