#include <tn.h>
#include <sw.h>
#include <freeze.h>

INCLUDE_ASM("asm/nonmatchings/P2/tn", PtnfnFromTn__FP2TN);

INCLUDE_ASM("asm/nonmatchings/P2/tn", GetTnfnNose__FP4TNFNP6CPDEFIP6VECTORP2TN);

INCLUDE_ASM("asm/nonmatchings/P2/tn", InitTn__FP2TN);

void OnTnRemove(TN *ptn)
{
    OnAloRemove(ptn);
    SetTnTns(ptn, TNS_Out);
    ClearSwCallbacks(ptn->psw, 2, (PFNMQ)nullptr, ptn, MSGID_Nil, nullptr);
}

INCLUDE_ASM("asm/nonmatchings/P2/tn", LoadTnFromBrx__FP2TNP18CBinaryInputStream);

void PostTnLoad(TN *ptn)
{
    PostAloLoad(ptn);
}

INCLUDE_ASM("asm/nonmatchings/P2/tn", SetTnTns__FP2TN3TNS);

/**
 * @todo Rename.
 */
void FUN_001e2840(TN *ptn, TNS tns)
{
    // NOTE: Doesn't match if this is the other way around.
    if (tns == STRUCT_OFFSET(ptn, 0x398, TNS))
    {
        return;
    }

    STRUCT_OFFSET(ptn, 0x398, TNS) = tns;
    UpdateTnCallback(ptn, MSGID_callback, nullptr);
}

INCLUDE_ASM("asm/nonmatchings/P2/tn", UpdateTnCallback__FP2TN5MSGIDPv);

void UpdateTn(TN *ptn, float dt)
{
    UpdateAlo(ptn, dt);
    if (STRUCT_OFFSET(ptn, 0x398, TNS) != TNS_Out) // ptn->tns
    {
        PostSwCallback(ptn->psw, UpdateTnCallback, ptn, MSGID_callback, nullptr);
    }
}

void RenderTnSelf(TN *ptn, CM *pcm, RO *pro)
{
    RenderAloSelf(ptn, pcm, pro);
}

void FreezeTn(TN *ptn, int fFreeze)
{
    FreezeAlo(ptn, fFreeze);
    if (fFreeze)
    {
        SetTnTns(ptn, TNS_Out);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/tn", FUN_001e29e8);

INCLUDE_ASM("asm/nonmatchings/P2/tn", CalculateTnCrv__FP2TNP6VECTORN21);

INCLUDE_ASM("asm/nonmatchings/P2/tn", CalculateTnPos__FP2TNP6VECTORffP3CLQP2LM4FTNDT1);

INCLUDE_ASM("asm/nonmatchings/P2/tn", ActivateCptn__FP4CPTNPv);

INCLUDE_ASM("asm/nonmatchings/P2/tn", DeactivateCptn__FP4CPTNPv);

void SetCptn(CPTN *pcptn, void *pv)
{
    return;
}

void RevokeCptn(CPTN *pcptn, void *pv)
{
    return;
}

INCLUDE_ASM("asm/nonmatchings/P2/tn", FUN_001e30e8);

INCLUDE_ASM("asm/nonmatchings/P2/tn", UpdateCptn__FP4CPTNP6CPDEFIP3JOYf);

INCLUDE_ASM("asm/nonmatchings/P2/tn", FUN_001e4578);

INCLUDE_ASM("asm/nonmatchings/P2/tn", FUN_001e4880);

INCLUDE_ASM("asm/nonmatchings/P2/tn", FUN_001e4888);

INCLUDE_ASM("asm/nonmatchings/P2/tn", LoadTbspFromBrx__FP18CBinaryInputStreamPiPP5TSURFT1PP4TBSP);

INCLUDE_ASM("asm/nonmatchings/P2/tn", FCheckTbspPoint__FP4TBSPP6VECTOR);
