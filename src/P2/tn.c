#include <tn.h>
#include <sw.h>
#include <freeze.h>
#include <po.h>
#include <jt.h>

extern TNFN D_00275980;
extern VECTOR D_00275A10;
extern char D_00275A20[8];

TNFN *PtnfnFromTn(TN *ptn)
{
    return ptn == NULL ? &D_00275980 : (TNFN *)((uint8_t *)ptn + 0x2F0);
}

INCLUDE_ASM("asm/nonmatchings/P2/tn", GetTnfnNose__FP4TNFNP6CPDEFIP6VECTORP2TN);

struct TNFN_DATA { char rgb[0x90]; };

INCLUDE_ASM("asm/nonmatchings/P2/tn", InitTn__FP2TN);
#ifdef SKIP_ASM
void InitTn(TN *ptn)
{
    uint64_t flags;

    InitAlo(ptn);

    *(struct TNFN_DATA *)((char *)ptn + 0x2F0) = *(struct TNFN_DATA *)&D_00275980;

    flags = STRUCT_OFFSET(ptn, 0x2C8, uint64_t);
    flags &= ~((uint64_t)0x300 << 32);
    flags |= ((uint64_t)0x8000 << 25);

    STRUCT_OFFSET(ptn, 0x420, float) = 2.0f;
    STRUCT_OFFSET(ptn, 0x424, float) = 1.0f;
    STRUCT_OFFSET(ptn, 0x2C8, uint64_t) = flags;
    STRUCT_OFFSET(ptn, 0x428, float) = 2.0f;
    STRUCT_OFFSET(ptn, 0x42C, float) = 1.0f;
    STRUCT_OFFSET(ptn, 0x430, int) = -1;

    *(VECTOR *)((char *)ptn + 0x450) = D_00275A10;
    *(uint64_t *)((char *)ptn + 0x460) = *(uint64_t *)D_00275A20;
    STRUCT_OFFSET(ptn, 0x398, int) = -1;
}
#endif // SKIP_ASM

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
#ifdef SKIP_ASM
void SetTnTns(TN *ptn, TNS tns)
{
    if (STRUCT_OFFSET(ptn, 0x394, TNS) == tns)
        return;

    if (tns == TNS_Out)
    {
        RevokeCmPolicy(g_pcm, 8, CPP_Nil, NULL, NULL, ptn);
        HandleLoSpliceEvent(ptn, 3, 0, NULL);
        STRUCT_OFFSET(ptn, 0x394, TNS) = tns;
    }
    else if (tns == TNS_In)
    {
        SetCmPolicy(g_pcm, (CPP)(STRUCT_OFFSET(ptn, 0x388, int) + 2),
                    &STRUCT_OFFSET(g_pcm, 0x520, CPLCY),
                    STRUCT_OFFSET(ptn, 0x2D0, SO *), ptn);
        HandleLoSpliceEvent(ptn, 2, 0, NULL);
        STRUCT_OFFSET(ptn, 0x394, TNS) = tns;
    }
    else
    {
        STRUCT_OFFSET(ptn, 0x394, TNS) = tns;
    }

    STRUCT_OFFSET(ptn, 0x39C, float) = g_clock.t;
}
#endif // SKIP_ASM

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
#ifdef SKIP_ASM
void UpdateTnCallback(TN *ptn, MSGID msgid, void *pv)
{
    PO *ppo = PpoCur();
    if (ppo == NULL)
        return;

    if (ppo != STRUCT_OFFSET(ptn, 0x2D0, PO *))
    {
        SetTnTns(ptn, TNS_Out);
        STRUCT_OFFSET(ptn, 0x2D0, PO *) = ppo;
    }

    VECTOR posLocal;
    TNS tns = STRUCT_OFFSET(ptn, 0x398, TNS);
    if (tns == TNS_Nil)
    {
        ConvertAloPos(NULL, ptn, (VECTOR *)((char *)ppo + 0x140), &posLocal);
        tns = (TNS)(FCheckTbspPoint(STRUCT_OFFSET(ptn, 0x2E0, TBSP *), &posLocal) != 0);
    }

    if (STRUCT_OFFSET(ptn, 0x384, int) == 0 && ppo == (PO *)g_pjt &&
        STRUCT_OFFSET(ppo, 0x2220, int) == 2 && g_pcm->field41_0x224 == 0 &&
        STRUCT_OFFSET(ptn, 0x398, TNS) == TNS_Nil)
    {
        return;
    }

    SetTnTns(ptn, tns);
}
#endif // SKIP_ASM

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

void FUN_001e29e8(TN *ptn, float g)
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

float FUN_001e4880(int a, int b, int c, void *p)
{
    return STRUCT_OFFSET(p, 0x20, float);
}

INCLUDE_ASM("asm/nonmatchings/P2/tn", FUN_001e4888);

INCLUDE_ASM("asm/nonmatchings/P2/tn", LoadTbspFromBrx__FP18CBinaryInputStreamPiPP5TSURFT1PP4TBSP);

INCLUDE_ASM("asm/nonmatchings/P2/tn", FCheckTbspPoint__FP4TBSPP6VECTOR);
