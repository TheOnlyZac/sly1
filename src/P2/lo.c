#include <lo.h>
#include <sw.h>
#include <alo.h>
#include <brx.h>
#include <util.h>
#include <find.h>
#include <game.h>
#include <memory.h>
#include <spliceobj.h>
#include <splice/gc.h>
#include <splice/ref.h>
#include <splice/vecmat.h>

extern CGc g_gc;

void InitLo(LO *plo)
{
    plo->pvtlo->pfnSetLoDefaults(plo);
    plo->pvtlo->pfnAddLo(plo);
}

void PostLoLoad(LO *plo)
{
    HandleLoSpliceEvent(plo, 0, 0, (void **)nullptr);
}

void AddLo(LO *plo)
{
    DL *pdl;
    if (plo->paloParent)
    {
        pdl = &plo->paloParent->dlChild;
    }
    else
    {
        pdl = &plo->psw->dlChild;
    }

    bool fLoInDl = FFindDlEntry(pdl, plo);
    if (fLoInDl)
        return;

    AppendDlEntry(pdl, plo);

    bool fLoInWorld = FIsLoInWorld(plo);
    if (fLoInWorld)
    {
        plo->pvtlo->pfnAddLoHierarchy(plo);
    }
}

void AddLoHierarchy(LO *plo)
{
    plo->pvtlo->pfnOnLoAdd(plo);
    plo->pvtlo->pfnSendLoMessage(plo, MSGID_added, plo);
}

void OnLoAdd(LO *plo)
{
    return;
}

void RemoveLo(LO *plo)
{
    DL *pdl;
    if (plo->paloParent)
    {
        pdl = &plo->paloParent->dlChild;
    }
    else
    {
        pdl = &plo->psw->dlChild;
    }

    bool fLoInDl = FFindDlEntry(pdl, plo);
    if (!fLoInDl)
        return;

    bool fLoInWorld = FIsLoInWorld(plo);
    if (fLoInWorld)
    {
        RemoveDlEntry(pdl, plo);
        plo->pvtlo->pfnRemoveLoHierarchy(plo);
    }
    else
    {
        RemoveDlEntry(pdl, plo);
    }
}

void DeferLoRemove(LO *plo)
{
    ALO *palo;
    if((plo->pvtlo->grfcid & 1U) == 0)
    {
        palo = (ALO *)plo->paloParent;
    }
    else
    {
        palo = (ALO *)plo;
    }

    if (palo)
    {
        DLR *pdlr = (DLR *)PvAllocSwImpl(sizeof(DLR));
        pdlr->oidChild = plo->oid;
        pdlr->pdlrNext = STRUCT_OFFSET(palo, 0x2c4, DLR *); // palo->pdlrFirst
        STRUCT_OFFSET(palo, 0x2c4, DLR *) = pdlr; // palo->pdlrFirst
    }
}

void SetLoSuckHideLimits(LO *plo, LM *plmUSuck)
{
    bool fHideLo = FCheckLm(plmUSuck, g_plsCur->uSuck);

    if (fHideLo)
    {
        DeferLoRemove(plo);
    }
}

void RemoveLoHierarchy(LO *plo)
{
    plo->pvtlo->pfnOnLoRemove(plo);
    plo->pvtlo->pfnSendLoMessage(plo, MSGID_removed, plo);
}

void OnLoRemove(LO *plo)
{
    return;
}

void SnipLo(LO *plo)
{
    bool fIsLoInWorld = FIsLoInWorld(plo);
    if (!fIsLoInWorld)
        return;

    if (plo->pvtlo->pfnBindLo)
    {
        plo->pvtlo->pfnBindLo(plo);
    }

    plo->pvtlo->pfnPostLoLoad(plo);
    plo->pvtlo->pfnRemoveLo(plo);
}

int FFindLoParent(LO *plo, ALO *paloParent)
{
    if (!plo)
    {
        return 0;
    }

    while (plo)
    {
        if (plo == paloParent)
        {
            return 1;
        }

        plo = plo->paloParent;
    }

    return (paloParent == nullptr);
}

void SetLoParent(LO *plo, ALO *paloParent)
{
    plo->pvtlo->pfnRemoveLo(plo);
    plo->paloParent = paloParent;
    plo->pvtlo->pfnAddLo(plo);
}

int FIsLoInWorld(LO *plo)
{
    while (plo)
    {
        ALO *paloParent = plo->paloParent;

        if (paloParent)
        {
            if (!FFindDlEntry(&paloParent->dlChild, plo))
            {
                return 0;
            }
        }
        else
        {
            if (!FFindDlEntry(&plo->psw->dlChild, plo))
            {
                return 0;
            }
        }

        plo = paloParent;
    }

    return 1;
}

void GetLoInWorld(LO *plo, int *pfInWorld)
{
    *pfInWorld = FIsLoInWorld(plo);
}

JUNK_ADDIU(30);

LO *PloCloneLo(LO *plo, SW *psw, ALO *paloParent)
{
    LO *ploClone = PloNew(plo->pvtbasic->cid, psw, paloParent, plo->oid, -1);
    ploClone->pvtlo->pfnCloneLoHierarchy(ploClone, plo);
    return ploClone;
}

void CloneLoHierarchy(LO *plo, LO *ploBase)
{
    plo->pvtlo->pfnCloneLo(plo, ploBase);
}

void CloneLo(LO *plo, LO *ploBase)
{
    if (ploBase->psidebag)
    {
        CSidebag *psidebag = PsidebagNew();
        ploBase->psidebag->CloneTo(psidebag);
        plo->psidebag = psidebag;
        g_gc.AddRootSidebag(psidebag);
    }

    SW *psw = plo->psw;

    // Adjusted arguments for target assembly alignment
    CopyAb(&STRUCT_OFFSET(plo, 0x34, void *), &STRUCT_OFFSET(ploBase, 0x34, void *), ploBase->pvtlo->cb - 0x34);

    DL *pdl = PdlFromSwOid(psw, plo->oid);
    RemoveDlEntry(pdl, plo);
    pdl = PdlFromSwOid(psw, ploBase->oid);
    AppendDlEntry(pdl, plo);

    plo->oid = ploBase->oid;

    if (ploBase->pframe)
    {
        g_gc.UpdateRecyclable();
        CFrame *pframe = PframeNew();
        ploBase->pframe->CloneTo(pframe);
        plo->pframe = pframe;
        g_gc.AddRootFrame(pframe);
    }

    plo->ppxr = ploBase->ppxr;
}

void SubscribeSwPpmqStruct(SW *psw, MQ **ppmqFirst, PFNMQ pfnmq, void *pvContext)
{
    MQ *pmq = PmqAllocSw(psw);
    pmq->pfnmq = pfnmq;
    pmq->pvContext = pvContext;
    pmq->pmqnext = *ppmqFirst;
    *ppmqFirst = pmq;
}

void UnsubscribeSwPpmqStruct(SW *psw, MQ **ppmqFirst, PFNMQ pfnmq, void *pvContext)
{
    MQ *pmq;

    while (pmq = *ppmqFirst)
    {
        MQ *pmqTarget;
        MQ **ppmqList = ppmqFirst;

        if (pmq->pfnmq == pfnmq && pmq->pvContext == pvContext)
        {
            *ppmqFirst = pmq->pmqnext;
            pmq->pmqnext = (MQ*)nullptr;
            pmqTarget = pmq;
            FreeSwMqList(psw, pmqTarget);
            break;
        }

        pmqTarget = *ppmqList;
        pmq = pmqTarget;
        ppmqFirst = &pmq->pmqnext;
    }
}

void SubscribeLoStruct(LO *plo, PFNMQ pfnmq, void *pvContext)
{
    SubscribeSwPpmqStruct(plo->psw, &plo->pmqFirst, pfnmq, pvContext);
}

void UnsubscribeLoStruct(LO *plo, PFNMQ pfnmq, void *pvContext)
{
    UnsubscribeSwPpmqStruct(plo->psw, &plo->pmqFirst, pfnmq, pvContext);
}

void SubscribeLoObject(LO *plo, LO *ploTarget)
{
    SubscribeSwPpmqStruct(plo->psw, &plo->pmqFirst, ploTarget->pvtlo->pfnHandleLoMessage, ploTarget);
}

void UnsubscribeLoObject(LO *plo, LO *ploTarget)
{
    UnsubscribeSwPpmqStruct(plo->psw, &plo->pmqFirst, ploTarget->pvtlo->pfnHandleLoMessage, ploTarget);
}

void SendLoMessage(LO *plo, MSGID msgid, void *pv)
{
    if (plo->pvtlo->pfnHandleLoMessage)
    {
        plo->pvtlo->pfnHandleLoMessage(plo, msgid, pv);
    }

    MQ *pmq = plo->pmqFirst;

    while (pmq)
    {
        PFNMQ pfnmq = pmq->pfnmq;
        void *pmqContext = pmq->pvContext;

        pmq = pmq->pmqnext;

        pfnmq(pmqContext, msgid, pv);
    }
}

void LoadLoFromBrx(LO *plo, CBinaryInputStream *pbis)
{
    LoadOptionsFromBrx(plo, pbis);
}

int FMatchesLoName(LO *plo, OID oid)
{
    if (oid == OID_Nil)
    {
        return 0;
    }

    if (plo->oid == oid || (plo->ppxr && plo->ppxr->oidProxyRoot == oid))
    {
        return 1;
    }

    return 0;
}

OID OidProxyLo(LO *plo)
{
    if (plo->ppxr)
    {
        return plo->ppxr->oidProxyRoot;
    }

    return OID_Nil;
}

OID OidProxyLoPreferred(LO *plo)
{
    if (plo->ppxr)
    {
        return plo->ppxr->oidProxyRoot;
    }

    return plo->oid;
}

void GetLoOidProxy(LO *plo, OID *poid)
{
    *poid = OidProxyLo(plo);
}

INCLUDE_ASM("asm/nonmatchings/P2/lo", PostSpliceEventCallback__FP2LOUiPv);

INCLUDE_ASM("asm/nonmatchings/P2/lo", FFilterSpliceEvent__FP2LO7SYMEVIDiPPv);

INCLUDE_ASM("asm/nonmatchings/P2/lo", HandleLoSpliceEvent__FP2LOUiiPPv);

void EnsureLoSidebagBool(LO *plo, OPTID optid, int f)
{
    CRef ref = CRef();
    ref.SetBool(f);
    RefEnsureOption(plo, optid, &ref);
}

void EnsureLoSidebagInt(LO *plo, OPTID optid, int n)
{
    CRef ref = CRef();
    ref.SetS32(n);
    RefEnsureOption(plo, optid, &ref);
}

void EnsureLoSidebagFloat(LO *plo, OPTID optid, float g)
{
    CRef ref = CRef();
    ref.SetF32(g);
    RefEnsureOption(plo, optid, &ref);
}

INCLUDE_ASM("asm/nonmatchings/P2/lo", EnsureLoSidebagClq__FP2LO5OPTIDP3CLQ);

INCLUDE_ASM("asm/nonmatchings/P2/lo", EnsureLoSidebagLm__FP2LO5OPTIDP2LM);

void EnsureLoSidebagOid(LO *plo, OPTID optid, OID oid)
{
    CRef ref = CRef();
    ref.SetS32(oid);
    RefEnsureOption(plo, optid, &ref);
}

/**
 * @todo 92.29% match.
 * https://decomp.me/scratch/uhZNV
 */
INCLUDE_ASM("asm/nonmatchings/P2/lo", EnsureLoSidebagVector__FP2LO5OPTIDP6VECTOR);
#ifdef SKIP_ASM
void EnsureLoSidebagVector(LO *plo, OPTID optid, VECTOR *pvec)
{
    CRef ref = CRef();
    VECTOR *pvector = PvectorNew();
    *pvector = *pvec;
    ref.SetVector(pvector);
    RefEnsureOption(plo, optid, &ref);
}
#endif // SKIP_ASM
