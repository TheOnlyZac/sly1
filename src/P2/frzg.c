#include <frzg.h>
#include <find.h>
#include <memory.h>

void PostFrzgLoad(FRZG *pfrzg)
{
    int i;
    MRG *pmrg = &pfrzg->mrg;
    SW *psw;

    PostLoLoad(pfrzg);
    psw = pfrzg->psw;
    pmrg->apalo = (ALO **)PvAllocSwImpl(pfrzg->coid * 4);
    for (i = 0; i < pfrzg->coid; i++)
    {
        LO *plo = PloFindSwChild(psw, pfrzg->aoid[i], pfrzg->paloParent);
        if (plo != 0)
        {
            int cpalo = pmrg->cpalo;
            pmrg->apalo[cpalo] = (ALO *)plo;
            pmrg->cpalo = cpalo + 1;
        }
    }
    AddSwMergeGroup(psw, &pfrzg->mrg);
}

void AddFrzgObject(FRZG *pfrzg, OID oid)
{
    int coid = pfrzg->coid;
    pfrzg->aoid[coid] = oid;
    pfrzg->coid = coid + 1;
}
