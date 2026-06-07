#include <tn.h>
#include <sw.h>
#include <freeze.h>

extern TNFN D_00275980;

TNFN *PtnfnFromTn(TN *ptn)
{
    if (ptn == NULL)
        return &D_00275980;
    return (TNFN *)((uint8_t *)ptn + 0x2F0);
}

INCLUDE_ASM("asm/nonmatchings/P2/tn", GetTnfnNose__FP4TNFNP6CPDEFIP6VECTORP2TN);

INCLUDE_ASM("asm/nonmatchings/P2/tn", InitTn__FP2TN);

void OnTnRemove(TN *ptn)
{
    OnAloRemove(ptn);
    SetTnTns(ptn, TNS_Out);
    ClearSwCallbacks(ptn->psw, 2, NULL, ptn, MSGID_Nil, NULL);
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
    UpdateTnCallback(ptn, MSGID_callback, NULL);
}

INCLUDE_ASM("asm/nonmatchings/P2/tn", UpdateTnCallback__FP2TN5MSGIDPv);

void UpdateTn(TN *ptn, float dt)
{
    UpdateAlo(ptn, dt);
    if (STRUCT_OFFSET(ptn, 0x398, TNS) != TNS_Out) // ptn->tns
    {
        PostSwCallback(ptn->psw, UpdateTnCallback, ptn, MSGID_callback, NULL);
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

extern "C" void FUN_001e29e8(TN *ptn, float g)
{
    STRUCT_OFFSET(ptn, 0x364, float) = g;
    STRUCT_OFFSET(ptn, 0x368, float) = 1.0f;
    STRUCT_OFFSET(ptn, 0x360, float) = g;
}

INCLUDE_ASM("asm/nonmatchings/P2/tn", CalculateTnCrv__FP2TNP6VECTORN21);

INCLUDE_ASM("asm/nonmatchings/P2/tn", CalculateTnPos__FP2TNP6VECTORffP3CLQP2LM4FTNDT1);

INCLUDE_ASM("asm/nonmatchings/P2/tn", ActivateCptn__FP4CPTNPv);

void DeactivateCptn(CPTN *pcptn, void *pv)
{
    TN *ptn = pcptn->ptn;
    if (ptn != NULL)
    {
        if (STRUCT_OFFSET(ptn, 0x438, float) != 0.0f)
        {
            STRUCT_OFFSET(g_pcm, 0x1c8, float) = STRUCT_OFFSET(ptn, 0x43c, float);
        }
    }
    pcptn->ptn = NULL;
}

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

extern "C" float FUN_001e4880(int a, int b, int c, void *p)
{
    return STRUCT_OFFSET(p, 0x20, float);
}

INCLUDE_ASM("asm/nonmatchings/P2/tn", FUN_001e4888);

INCLUDE_ASM("asm/nonmatchings/P2/tn", LoadTbspFromBrx__FP18CBinaryInputStreamPiPP5TSURFT1PP4TBSP);

INCLUDE_ASM("asm/nonmatchings/P2/tn", FCheckTbspPoint__FP4TBSPP6VECTOR);
