#include <splicemap.h>
#include <splice/serialize.h>
#include <splice/eval.h>
#include <splice/gc.h>
#include <memory.h>

extern int g_fLoadDebugInfo;

void LoadSwSpliceFromBrx(SW *psw, CBinaryInputStream *pbis)
{
    CRef cref;

    int csplc = pbis->U32Read();
    psw->csplcSplice = csplc;
    psw->asplcSplice = (SPLC*) PvAllocSwImpl(csplc * sizeof(SPLC));

    int symidScheduledCallbackList = pbis->U32Read();

    /* In the debug build, this is used for some extra symid metadata */
    int symidExtraMetadata = pbis->U32Read();

    /* This loop index reused in both loops, so we need to declare it here */
    int isplc;
    for (isplc = 0; isplc < psw->csplcSplice; isplc++)
    {
        SPLC *psplc = &psw->asplcSplice[isplc];
        psplc->ppairCompile = PpairSerializeIn(pbis);
        psplc->pframe = NULL;

        if (g_fLoadDebugInfo != 0)
        {
            pbis->Unknown1();
            pbis->Unknown1();
            pbis->Unknown1();
        }
    }

    /* Parse debug information, if present. */
    if (g_fLoadDebugInfo != 0)
    {
        for (int i = 0; i < symidScheduledCallbackList; i++)
        {
            pbis->Unknown1();
        }
        for (int i = 0; i < symidExtraMetadata; i++)
        {
            pbis->Unknown1();
        }
    }

    CFrame *pframe = PframeNew();
    psw->pframe = pframe;
    g_gc.AddRootFrame(pframe);

    psw->symidScheduledCallbackList = symidScheduledCallbackList;
    cref.SetTag(TAGK_None);
    psw->pframe->RefAddBinding(psw->symidScheduledCallbackList, &cref);

    for (isplc = 0; isplc < psw->csplcSplice; isplc++)
    {
        CRef cref;
        cref = RefEvalModule(isplc, psw);
    }
}

CFrame *PframeFromIsplice(int isplice, SW *psw)
{
    if (isplice == -1)
    {
        return NULL;
    }

    CFrame *pframe = psw->asplcSplice[isplice].pframe;
    if (pframe != NULL)
    {
        g_gc.AddRootFrame(pframe);
    }

    return pframe;
}

CRef RefEvalModule(int isplice, SW *psw)
{
    CRef cref;

    if (psw->asplcSplice[isplice].ppairCompile &&
        !psw->asplcSplice[isplice].pframe)
    {
        psw->asplcSplice[isplice].pframe = PframeNew();
        cref = RefEval(psw->asplcSplice[isplice].ppairCompile, psw->asplcSplice[isplice].pframe);
    }

    cref.SetTag(TAGK_Void);
    return cref;
}
