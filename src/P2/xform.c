#include <xform.h>
#include <button.h>
#include <brx.h>
#include <sw.h>
#include <cm.h>
#include <find.h>
#include <memory.h>
#include <po.h>

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
    ConvertAloPos(pproxyApply, NULL, &pxfm->posLocal, &pxfm->posLocal);
    ConvertAloMat(pproxyApply, NULL, &pxfm->matLocal, &pxfm->matLocal);
}

INCLUDE_ASM("asm/nonmatchings/P2/xform", ConvertXfmLocalToWorld__FP3XFMP6VECTORT1);

void GetXfmPos(XFM *pxfm, VECTOR *ppos)
{
    ConvertAloPos(pxfm->paloParent, NULL, &pxfm->posLocal, ppos);
}

void GetXfmMat(XFM *pxfm, MATRIX3 *pmat)
{
    ConvertAloMat(pxfm->paloParent, NULL, &pxfm->matLocal, pmat);
}

INCLUDE_ASM("asm/nonmatchings/P2/xform", PwarpFromOid__F3OIDT0);

INCLUDE_ASM("asm/nonmatchings/P2/xform", LoadWarpFromBrx__FP4WARPP18CBinaryInputStream);

void CloneWarp(WARP *pwarp, WARP *pwarpBase)
{
    int i;

    CloneLo(pwarp, pwarpBase);

    STRUCT_OFFSET(pwarp, 0xa4, LO **) = (LO **)PvAllocSwImpl(STRUCT_OFFSET(pwarp, 0xa0, int) * 4);

    for (i = 0; i < STRUCT_OFFSET(pwarp, 0xa0, int); i++)
    {
        LO *ploClone = PloCloneLo(STRUCT_OFFSET(pwarpBase, 0xa4, LO **)[i], pwarp->psw, NULL);
        STRUCT_OFFSET(pwarp, 0xa4, LO **)[i] = ploClone;
    }
}

void PostWarpLoad(WARP *pwarp)
{
    int i;

    PostLoLoad(pwarp);

    for (i = 0; i < STRUCT_OFFSET(pwarp, 0xa0, int); i++)
    {
        LO *plo = STRUCT_OFFSET(pwarp, 0xa4, LO **)[i];
        // @todo clean up this vtable call
        (*(void (**)(LO *, ALO *))((char *)plo->pvtlo + 0x64))(plo, pwarp->paloParent);
        SnipLo(plo);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/xform", TriggerWarp__FP4WARP);

void SetWarpRsmg(WARP *pwarp, int fOnTrigger, OID oidRoot, OID oidSM, OID oidGoal)
{
    // pwarp->arsmg & pwarp->crsmg
    FAddRsmg(&STRUCT_OFFSET(pwarp, 0xb8, RSMG), 4, &STRUCT_OFFSET(pwarp, 0xb4, int), fOnTrigger, oidRoot, oidSM, oidGoal);
}

int FUN_001F4308(WARP *pwarp, float g)
{
    STRUCT_OFFSET(pwarp, 0x9c, float) = g;
    STRUCT_OFFSET(pwarp, 0x98, int) = 1;
    return 1;
}

void TeleportSwPlayer(SW *psw, OID oidWarp, OID oidWarpContext)
{
    WARP *pwarp = PwarpFromOid(oidWarp, oidWarpContext);
    if (pwarp != NULL)
    {
        TriggerWarp(pwarp);
        return;
    }

    if (PpoCur() != NULL)
        return;

    PO *ppo = PpoStart();
    if (ppo != NULL)
        SwitchToPo(ppo);
}

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

void PostCameraLoad(CAMERA *pcamera)
{
    PostAloLoad(pcamera);

    if (pcamera->oidTarget != OID_Nil)
    {
        LO *plo = PloFindSwObject(pcamera->psw, 0x104, pcamera->oidTarget, pcamera);
        if (plo)
        {
            if (plo->pvtlo->grfcid & 1)
            {
                pcamera->paloTarget = (ALO *)plo;
            }
            else if (FIsBasicDerivedFrom(plo, (CID)0x7e))
            {
                pcamera->ppntTarget = (PNT *)plo;
            }
        }
    }
}

void EnableCamera(CAMERA *pcamera)
{
    if (STRUCT_OFFSET(pcamera, 0x310, int) == 0) // pcamera->fSetCplcy
    {
        // g_pcm->cpaseg
        SetCmPolicy(g_pcm, CPP_Animated, &STRUCT_OFFSET(g_pcm, 0x510, CPLCY), NULL, pcamera);
        STRUCT_OFFSET(pcamera, 0x310, int) = 1; // pcamera->fSetCplcy
    }
}

void DisableCamera(CAMERA *pcamera)
{
    if (STRUCT_OFFSET(pcamera, 0x310, int) != 0) // pcamera->fSetCplcy
    {
        // g_pcm->cpaseg
        RevokeCmPolicy(g_pcm, 0x0b, CPP_Animated, &STRUCT_OFFSET(g_pcm, 0x510, CPLCY), NULL, pcamera);
        STRUCT_OFFSET(pcamera, 0x310, int) = 0; // pcamera->fSetCplcy
    }
}
