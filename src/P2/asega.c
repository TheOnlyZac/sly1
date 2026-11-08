#include <asega.h>
#include <sw.h>
#include <actseg.h>

extern VTBASIC g_vtasega;

ASEGA *PasegaNew(SW *psw)
{
    ASEGA *pasega = (ASEGA *)PvAllocSlotheapClearImpl(&psw->slotheapAsega);
    pasega->pvtbasic = &g_vtasega;
    InitDl(&pasega->dlActseg, 0x20);
    pasega->punk60 = pasega->unk64;
    return pasega;
}

void SetAsegaHandsOff(ASEGA *pasega, int fHandsOff)
{
    if (fHandsOff == pasega->fHandsOff)
        return;

    if (fHandsOff)
    {
        IncrementSwHandsOff(g_psw);
    }
    else
    {
        DecrementSwHandsOff(g_psw);
    }

    pasega->fHandsOff = fHandsOff;
}

INCLUDE_ASM("asm/nonmatchings/P2/asega", UpdateAsegaIeaCur__FP5ASEGA);

ACTSEG *PactsegFindAsega(ASEGA *pasega, OID oid)
{
    VECTOR vec; // unused, but needed to match the original stack frame
    for (ACTSEG *pactseg = (ACTSEG *)pasega->dlActseg.head; pactseg != 0; pactseg = (ACTSEG *)pactseg->dleAsega.next)
    {
        if (FMatchesLoName(pactseg->palo, oid))
        {
            return pactseg;
        }
    }
    return 0;
}

JUNK_NOP();
JUNK_ADDIU(10);

INCLUDE_ASM("asm/nonmatchings/P2/asega", HandleAsegaEvent__FP5ASEGAP2EAPi);

INCLUDE_ASM("asm/nonmatchings/P2/asega", HandleAsegaEventsFF__FP5ASEGAP4ASEGPi);

INCLUDE_ASM("asm/nonmatchings/P2/asega", HandleAsegaEvents__FP5ASEGAP4ASEGPi);

void RemoveAsega(ASEGA *pasega)
{
    RemoveDlEntry(&g_psw->dlAsegaPending, pasega);
    FreeSlotheapPv(&g_psw->slotheapAsega, pasega);
}

INCLUDE_ASM("asm/nonmatchings/P2/asega", RetractAsega__FP5ASEGA);

void FUN_0012e928(ASEGA *pasega, OID oid, int grfra)
{
    ACTSEG *pactseg = PactsegFindAsega(pasega, oid);
    if (pactseg != 0)
    {
        pactseg->pvtact->pfnRetractAct(pactseg, grfra);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/asega", UFromEaErrorFunc__FP2EAf);

INCLUDE_ASM("asm/nonmatchings/P2/asega", FWrapAsegaTime__FP5ASEGAPfT1);

INCLUDE_ASM("asm/nonmatchings/P2/asega", UpdateAsega__FP5ASEGAf);

INCLUDE_ASM("asm/nonmatchings/P2/asega", SeekAsega__FP5ASEGA4SEEKff);

void SnapAsega(ASEGA *pasega, int fForce)
{
    VECTOR vec; // unused, but needed to match the original stack frame
    for (ACTSEG *pactseg = (ACTSEG *)pasega->dlActseg.head; pactseg != 0; pactseg = (ACTSEG *)pactseg->dleAsega.next)
    {
        SnapAct(pactseg, fForce);
    }
}

void AdaptAsega(ASEGA *pasega)
{
    VECTOR vec; // unused, but needed to match the original stack frame
    for (ACTSEG *pactseg = (ACTSEG *)pasega->dlActseg.head; pactseg != 0; pactseg = (ACTSEG *)pactseg->dleAsega.next)
    {
        AdaptAct(pactseg);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/asega", FindChnClosestPointLocal__FP3CHNP3ALOP6VECTORfffPfT2T2);

void SetAsegaSpeed(ASEGA *pasega, float svt)
{
    float svtScaled = svt * pasega->svtMaster;
    pasega->svtLocal = svtScaled * pasega->paseg->svtMasterSuck;
}

void SetAsegaMasterSpeed(ASEGA *pasega, float svtMaster)
{
    float svtScale = pasega->svtMaster * pasega->paseg->svtMasterSuck;
    float svt = pasega->svtLocal;
    if (svtScale != 0.0f)
    {
        svt = svt / svtScale;
    }
    pasega->svtMaster = svtMaster;
    SetAsegaSpeed(pasega, svt);
}

void SetAsegaPriority(ASEGA *pasega, int nPriority)
{
    VECTOR vec; // unused, but needed to match the original 64-byte stack frame
    for (ACTSEG *pactseg = (ACTSEG *)pasega->dlActseg.head; pactseg != 0; pactseg = (ACTSEG *)pactseg->dleAsega.next)
    {
        pactseg->nPriority = nPriority;
        ResortAloActList(pactseg->palo);
    }
}

void SendAsegaMessage(ASEGA *pasega, MSGID msgid, void *pv)
{
    LO *plo = pasega->plo;
    if (plo != 0)
    {
        plo->pvtlo->pfnSendLoMessage(plo, msgid, pv);
    }
    MQ *pmq = pasega->pmqFirst;
    while (pmq != 0)
    {
        MQ *pmqNext = pmq->pmqNext;
        pmq->pfnmq(pmq->pvContext, msgid, pv);
        pmq = pmqNext;
    }
}

void SubscribeAsegaStruct(ASEGA *pasega, PFNMQ pfnmq, void *pvContext)
{
    SubscribeSwPpmqStruct(pasega->paseg->psw, &pasega->pmqFirst, pfnmq, pvContext);
}

void SubscribeAsegaObject(ASEGA *pasega, LO *ploTarget)
{
    SubscribeSwPpmqStruct(pasega->paseg->psw, &pasega->pmqFirst, (PFNMQ)ploTarget->pvtlo->pfnHandleLoMessage, ploTarget);
}
