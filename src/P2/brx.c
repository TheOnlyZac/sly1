#include <brx.h>
#include <bis.h>

extern EOPID g_aeopid[];

void StartupBrx()
{
    BuildEopids();
}

INCLUDE_ASM("asm/nonmatchings/P2/brx", PloNew__F3CIDP2SWP3ALO3OIDi);
#ifdef SKIP_ASM
/**
 * @todo 2.19% matched.
 */
LO *PloNew(CID cid, SW *psw, ALO *paloParent, OID oid, int isplice)
{
    return psw;
}
#endif

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

uint IploFromStockOid(int oid)
{
    int iplo;

    // Ensure oid is a stock object (OID between 12 and 42)
    if (oid >= 12 && oid <= 42)
    {
        iplo = oid - 12;
    }
    else
    {
        iplo = -1;
    }

    return iplo;
}

INCLUDE_ASM("asm/nonmatchings/P2/brx", LoadSwObjectsFromBrx__FP2SWP3ALOP18CBinaryInputStream);

struct EOPIDENTRY
{
    void *unk;
    EOPID *peopid;
};

struct LODEFTAB
{
    int ceopid;
    EOPIDENTRY *prgeopidentry;
};

extern "C" LODEFTAB D_00244950[];

INCLUDE_ASM("asm/nonmatchings/P2/brx", SetLoDefaults__FP2LO);
#ifdef SKIP_ASM
void SetLoDefaults(LO *plo)
{
    CID cid = plo->pvtlo->cid;
    int ceopid = D_00244950[cid].ceopid;
    if (ceopid > 0)
    {
        EOPIDENTRY *peopidentry = D_00244950[cid].prgeopidentry;
        do
        {
            EOPID *peopid = peopidentry->peopid;
            if (peopid->grfeopid & 0x800)
            {
                CBinaryInputStream bis(NULL, 0, 0);
                bis.OpenMemory(4, &peopid->optdat);
                LoadOptionFromBrx(plo, peopid, &bis);
            }
            ceopid--;
            peopidentry++;
        } while (ceopid != 0);
    }
}
#endif // SKIP_ASM
