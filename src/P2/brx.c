#include <brx.h>
#include <bis.h>
#include <find.h>
#include <memory.h>
#include <splicemap.h>

extern EOPID g_aeopid[];
extern ARYSPLOPT g_mpcidarysplopt[162];
extern VT *g_mpcidpvt[162];

void StartupBrx()
{
    BuildEopids();
}

LO *PloNew(CID cid, SW *psw, ALO *paloParent, OID oid, int isplice)
{
    VTLO *pvtlo = (VTLO *)(g_mpcidpvt[cid]);
    LO *plo = (LO *)PvAllocSwClearImpl(pvtlo->cb);
    plo->pvtlo = pvtlo;
    plo->oid = oid;

    if (cid == (CID)0x6c) // TODO: CID_SW in may 19.
    {
        psw = (SW *)plo;
        InitSwDlHash((SW *)plo);
    }
    plo->paloParent = paloParent;

    plo->psw = psw;
    plo->pframe = PframeFromIsplice(isplice, psw);

    DL *pdl = PdlFromSwOid(plo->psw, plo->oid);
    AppendDlEntry(pdl, plo);

    plo->ploCidNext = plo->psw->aploCidHead[cid];
    plo->psw->aploCidHead[cid] = plo;

    plo->pvtlo->pfnInitLo(plo);
    return plo;
}

INCLUDE_ASM("asm/nonmatchings/P2/brx", LoadOptionFromBrx__FPvP5EOPIDP18CBinaryInputStream);

void LoadOptionsFromBrx(void *pvStruct, CBinaryInputStream *pbis)
{
    while (true)
    {
        short eopid = pbis->S16Read();
        if (eopid < 0)
        {
            break;
        }
        LoadOptionFromBrx(pvStruct, &g_aeopid[eopid], pbis);
    }
}

int IploFromStockOid(int oid)
{
    return (oid >= 12 && oid <= 42) ? (oid - 12) : -1;
}

void LoadSwObjectsFromBrx(SW *psw, ALO *paloParent, CBinaryInputStream *pbis)
{
    short cobject = pbis->S16Read();

    for (int i = 0; i < cobject; i++)
    {
        CID cid = (CID)pbis->S16Read();
        OID oid = (OID)pbis->S16Read();
        int isplice = (int)pbis->S16Read();

        LO *plo = PloNew(cid, psw, paloParent, oid, isplice);
        plo->pvtlo->pfnLoadLoFromBrx(plo, pbis);

        int iplo = IploFromStockOid(oid);
        if (iplo > -1)
        {
            psw->aploStock[iplo] = plo;
            SnipLo(plo);
        }
    }
}

/**
 * @todo 83.34% match.
 */
INCLUDE_ASM("asm/nonmatchings/P2/brx", SetLoDefaults__FP2LO);
#ifdef SKIP_ASM
void SetLoDefaults(LO *plo)
{
    ARYSPLOPT *parysplopt = &g_mpcidarysplopt[plo->pvtbasic->cid];

    for (int i = parysplopt->csplopt; i > 0; i--)
    {
        EOPID *peopid = parysplopt->asplopt[i].peopid;
        if ((peopid->grfeopid & 0x800) == 0)
        {
            continue;
        }

        CBinaryInputStream bis(NULL, 0, 0);
        bis.OpenMemory(4, &peopid->optdat);
        LoadOptionFromBrx(plo, peopid, &bis);
    }
}
#endif // SKIP_ASM
