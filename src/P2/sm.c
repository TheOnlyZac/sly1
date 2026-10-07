#include <sm.h>
#include <sw.h>
#include <brx.h>
#include <asega.h>
#include <memory.h>

void LoadSmFromBrx(SM *psm, CBinaryInputStream *pbis)
{
    InitDl(&psm->dlSma, 8);

    psm->csms = pbis->U8Read();
    psm->asms = (SMS *)PvAllocSwImpl(psm->csms * sizeof(SMS));

    int isms; // NOTE: Needed for correct register usage.
    for (isms = 0; isms < psm->csms; isms++)
    {
        SMS *psms = &psm->asms[isms];
        psms->oid = (OID)pbis->S16Read();
        psms->oidNext = (OID)pbis->S16Read();
    }

    for (isms = 0; isms < psm->csms; isms++)
    {
        SMS *psms = &psm->asms[isms];
        if (psms->oidNext != OID_Nil)
        {
            psms->ismsNext = IsmsFindSmRequired(psm, psms->oidNext);
        }
    }

    psm->csmt = pbis->U8Read();
    psm->asmt = (SMT *)PvAllocSwImpl(psm->csmt * sizeof(SMT));

    int ismt; // NOTE: Needed for correct register usage.
    for (ismt = 0; ismt < psm->csmt; ismt++)
    {
        SMT *psmt = &psm->asmt[ismt];
        psmt->fAseg = pbis->S8Read();
        psmt->ismsFrom = IsmsFindSmRequired(psm, (OID)pbis->S16Read());
        psmt->ismsTo = IsmsFindSmRequired(psm, (OID)pbis->S16Read());
        psmt->grfsmt = pbis->S32Read();
        psmt->gProbability = pbis->F32Read();
    }

    LoadOptionsFromBrx(psm, pbis);
    pbis->S16Read();

    for (ismt = 0; ismt < psm->csmt; ismt++)
    {
        SMT *psmt = &psm->asmt[ismt];
        if (psmt->fAseg)
        {
            CID cid = (CID)pbis->S16Read();
            OID oid = (OID)pbis->S16Read();
            short isplice = pbis->S16Read();

            LO *plo = PloNew(cid, psm->psw, psm->paloParent, oid, isplice);
            psmt->paseg = (ASEG *)plo;
            plo->pvtlo->pfnLoadLoFromBrx(plo, pbis);
            SnipLo(plo);
        }
    }
}

void PostSmLoad(SM *psm)
{
    PostLoLoad(psm);
    if (psm->fDefault)
    {
        PostSwCallback(psm->psw, PostSmLoadCallback, psm, MSGID_callback, NULL);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sm", PostSmLoadCallback__FP2SM5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/sm", PsmaApplySm__FP2SMP3ALO3OIDi);

INCLUDE_ASM("asm/nonmatchings/P2/sm", PsmaFindSm__FP2SMP3ALO);

int IsmsFindSmOptional(SM *psm, OID oid)
{
    for (int i = 0; i < psm->csms; i++)
    {
        SMS *psms = &psm->asms[i];
        if (psms->oid == oid)
        {
            return i;
        }
    }

    return -1;
}

int IsmsFindSmRequired(SM *psm, OID oid)
{
    int isms = IsmsFindSmOptional(psm, oid);
    return (isms > 0) ? isms : 0;
}

OID OidFromSmIsms(SM *psm, int isms)
{
    return psm->asms[isms].oid;
}

void RetractSma(SMA *psma)
{
    SM *psm = psma->psm;
    if (psma->pasegaCur)
    {
        RetractAsega(psma->pasegaCur);
        psma->pasegaCur = NULL;
    }

    FreeSwMqList(psma->psm->psw, psma->pmqFirst);
    psma->pmqFirst = NULL;

    RemoveDlEntry(&psma->psm->dlSma, psma);
    RemoveDlEntry(&psma->psm->psw->dlSma, psma);
    FreeSlotheapPv(&psma->psm->psw->slotheapSma, psma);

    HandleLoSpliceEvent(psm, 0x12, 0, NULL);
}

INCLUDE_ASM("asm/nonmatchings/P2/sm", SetSmaGoal__FP3SMA3OID);

void GetSmaGoal(SMA *psma, OID *poid)
{
    *poid = (psma->ismsGoal >= 0) ? psma->psm->asms[psma->ismsGoal].oid : OID_Nil;
}

void GetSmaCur(SMA *psma, OID *poid)
{
    *poid = (psma->ismsCur >= 0) ? psma->psm->asms[psma->ismsCur].oid : OID_Nil;
}

void GetSmaNext(SMA *psma, OID *poid)
{
    *poid = (psma->ismsNext >= 0) ? psma->psm->asms[psma->ismsNext].oid : OID_Nil;
}

void SetSmaSvt(SMA *psma, float svt)
{
    psma->svtLocal = svt;
    if (psma->pasegaCur)
    {
        SetAsegaSpeed(psma->pasegaCur, svt);
    }
}

void SeekSma(SMA *psma, OID oid)
{
    int ismsTo = IsmsFindSmRequired(psma->psm, oid);

    if (psma->ismsCur != ismsTo || (psma->ismsGoal != ismsTo && psma->ismsGoal != -1))
    {
        NotifySmaSpliceOnEnterState(psma, psma->ismsCur, ismsTo);
        psma->ismsGoal = ismsTo;
        psma->ismsCur = ismsTo;
        psma->ismsNext = -1;
        ChooseSmaTransition(psma);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sm", ChooseSmaTransition__FP3SMA);

void EndSmaTransition(SMA *psma)
{
    NotifySmaSpliceOnEnterState(psma, psma->ismsCur, psma->ismsNext);
    psma->ismsCur = psma->ismsNext;
    psma->ismsNext = -1;
}

void HandleSmaMessage(SMA *psma, MSGID msgid, void *pv)
{
    if (msgid == MSGID_asega_limit && pv == psma->pasegaCur)
    {
        EndSmaTransition(psma);
        ChooseSmaTransition(psma);
    }
}

void SkipSma(SMA *psma, float dtSkip)
{
    while (true)
    {
        ASEGA *pasega = psma->pasegaCur;
        if (!pasega)
        {
            break;
        }

        float diff = pasega->paseg->tMax - pasega->tLocal;
        if (dtSkip < diff)
        {
            SeekAsega(pasega, SEEK_Current, dtSkip, 1.0f);
            break;
        }
        dtSkip -= diff;

        EndSmaTransition(psma);
        ChooseSmaTransition(psma);
    }
}

void SendSmaMessage(SMA *psma, MSGID msgid, void *pv)
{
    if (psma->paloRoot)
    {
        psma->paloRoot->pvtlo->pfnSendLoMessage(psma->paloRoot, msgid, pv);
    }

    MQ *pmq = psma->pmqFirst;
    while (pmq)
    {
        PFNMQ pfnmq = pmq->pfnmq;
        void *pvContext = pmq->pvContext;
        pmq = pmq->pmqNext;
        pfnmq(pvContext, msgid, pv);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sm", FUN_001b6df8);

void NotifySmaSpliceOnEnterState(SMA *psma, int ismsFrom, int ismsTo)
{
    OID oidStateFrom = (ismsFrom >= 0) ? psma->psm->asms[ismsFrom].oid : OID_Nil;
    OID oidStateTo = (ismsTo >= 0) ? psma->psm->asms[ismsTo].oid : OID_Nil;

    void *apvArgs[3];
    apvArgs[0] = &psma;
    apvArgs[1] = &oidStateFrom;
    apvArgs[2] = &oidStateTo;
    HandleLoSpliceEvent(psma->psm, 0xe, sizeof(apvArgs) / sizeof(*apvArgs), apvArgs);
}
