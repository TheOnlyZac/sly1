#include <sm.h>
#include <sw.h>
#include <aseg.h>

INCLUDE_ASM("asm/nonmatchings/P2/sm", LoadSmFromBrx__FP2SMP18CBinaryInputStream);

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

INCLUDE_ASM("asm/nonmatchings/P2/sm", IsmsFindSmOptional__FP2SM3OID);

int IsmsFindSmRequired(SM *psm, OID oid)
{
    int isms = IsmsFindSmOptional(psm, oid);
    return isms >= 0 ? isms : 0;
}

OID OidFromSmIsms(SM *psm, int isms)
{
    return psm->asms[isms].oid;
}

INCLUDE_ASM("asm/nonmatchings/P2/sm", RetractSma__FP3SMA);

INCLUDE_ASM("asm/nonmatchings/P2/sm", SetSmaGoal__FP3SMA3OID);

INCLUDE_ASM("asm/nonmatchings/P2/sm", GetSmaGoal__FP3SMAP3OID);

INCLUDE_ASM("asm/nonmatchings/P2/sm", GetSmaCur__FP3SMAP3OID);

INCLUDE_ASM("asm/nonmatchings/P2/sm", GetSmaNext__FP3SMAP3OID);

INCLUDE_ASM("asm/nonmatchings/P2/sm", SetSmaSvt__FP3SMAf);

INCLUDE_ASM("asm/nonmatchings/P2/sm", SeekSma__FP3SMA3OID);

INCLUDE_ASM("asm/nonmatchings/P2/sm", ChooseSmaTransition__FP3SMA);

void EndSmaTransition(SMA *psma)
{
    int cur = STRUCT_OFFSET(psma, 0x28, int);
    int next = STRUCT_OFFSET(psma, 0x2C, int);
    NotifySmaSpliceOnEnterState(psma, cur, next);
    int nextCopy = STRUCT_OFFSET(psma, 0x2C, int);
    STRUCT_OFFSET(psma, 0x2C, int) = -1;
    STRUCT_OFFSET(psma, 0x28, int) = nextCopy;
}

void HandleSmaMessage(SMA *psma, MSGID msgid, void *pv)
{
    if (msgid == MSGID_asega_limit) {
        if ((ASEGA*)pv == psma->pasegaCur) {
            EndSmaTransition(psma);
            ChooseSmaTransition(psma);
        }
    }
}

void SkipSma(SMA *psma, float dtSkip)
{
    ASEGA *pasega;

    extern void SeekAsega(ASEGA *pasega, SEEK seek, float t, float svt);

    while ((pasega = psma->pasegaCur) != NULL)
    {
        float diff = STRUCT_OFFSET(STRUCT_OFFSET(pasega, 0x8, uint8_t *), 0x34, float) - STRUCT_OFFSET(pasega, 0x14, float);
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
    ALO *paloRoot = psma->paloRoot;
    if (paloRoot)
    {
        paloRoot->pvtlo->pfnSendLoMessage(paloRoot, msgid, pv);
    }

    MQ *pmq = psma->pmqFirst;

    while (pmq)
    {
        PFNMQ pfnmq = pmq->pfnmq;
        void *pmqContext = pmq->pvContext;

        pmq = pmq->pmqNext;

        pfnmq(pmqContext, msgid, pv);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sm", FUN_001b6df8);

INCLUDE_ASM("asm/nonmatchings/P2/sm", NotifySmaSpliceOnEnterState__FP3SMAii);
