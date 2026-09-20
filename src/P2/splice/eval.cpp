#include <splice/eval.h>
#include <splice/pair.h>
#include <splicemap.h>
#include <text.h>
#include <sw.h>

CRef RefEvalSymbol(CPair *ppair, CFrame *pframe)
{
    CRef cref;
    pframe->FFindBinding(ppair->m_ref.m_tag.m_symid, 1, &cref);
    return cref;
}

CRef RefEvalSet(CPair *ppair, CFrame *pframe)
{
    CRef cref;

    CPair *ppairVar = ppair->m_ref.m_tag.m_ppair->m_ppairNext;
    cref = RefEval(ppairVar->m_ppairNext, pframe);
    cref = pframe->RefSetBinding(ppairVar->m_ref.m_tag.m_symid, &cref);

    return cref;
}

CRef RefEvalDefine(CPair *ppair, CFrame *pframe)
{
    CRef cref;

    CPair *ppairVar = ppair->m_ref.m_tag.m_ppair->m_ppairNext;
    cref = RefEval(ppairVar->m_ppairNext, pframe);
    cref = pframe->RefAddBinding(ppairVar->m_ref.m_tag.m_symid, &cref);

    return cref;
}

CRef RefEvalAssert(CPair *ppair, CFrame *pframe)
{
    CRef cref;

    CPair *pValue = ppair->m_ref.m_tag.m_ppair->m_ppairNext;
    CPair *pExpr = pValue->m_ppairNext;

    cref = RefEval(pValue, pframe);
    if (!cref.m_tag.m_bool)
    {
        /* Failed assertion */
        CPair *pWhat = pExpr->m_ref.m_tag.m_ppair->m_ppairNext;
        printf("Splice assert: ");
        RefOpPrint(1, &pWhat->m_ref, pframe);
    }

    cref.SetTag(TAGK_Void);
    return cref;
}

CRef RefEvalIf(CPair *ppair, CFrame *pframe)
{
    CRef cref;

    CPair *pCondition = ppair->m_ref.m_tag.m_ppair->m_ppairNext;
    CPair *pTrue = pCondition->m_ppairNext;
    CPair *pElse = pTrue->m_ppairNext;

    cref = RefEval(pCondition, pframe);

    if (cref.m_tag.m_bool == 1)
    {
        cref = RefEval(pTrue, pframe);
    }
    else if (pElse != NULL)
    {
        cref = RefEval(pElse, pframe);
    }
    else
    {
        cref.SetTag(TAGK_Void);
    }

    return cref;
}

CRef RefEvalOr(CPair *ppair, CFrame *pframe)
{
    CRef cref;

    /* Loop over all arguments and short circuit at the first true
       or non-bool element (which is considered to be truthy) */
    for (CPair* ppairArg = ppair->m_ref.m_tag.m_ppair->m_ppairNext;
         ppairArg != NULL;
         ppairArg = ppairArg->m_ppairNext)
    {

        cref = RefEval(ppairArg, pframe);
        if (cref.m_tagk != TAGK_Bool || cref.m_tag.m_bool != 0)
        {
            return cref;
        }
    }

    cref.SetBool(0);
    return cref;
}

CRef RefEvalAnd(CPair *ppair, CFrame *pframe)
{
    CRef cref;
    cref.SetBool(1);

    /* Loop over all arguments and short circuit at the first false
       element (non-bool args are considered truthy) */
    for (CPair* ppairArg = ppair->m_ref.m_tag.m_ppair->m_ppairNext;
         ppairArg != NULL;
         ppairArg = ppairArg->m_ppairNext)
    {

        cref = RefEval(ppairArg, pframe);
        if (cref.m_tagk != TAGK_Bool)
        {
            continue;
        }

        if (cref.m_tag.m_bool == 0)
        {
            return cref;
        }
    }

    return cref;
}

CRef RefEvalCond(CPair *ppair, CFrame *pframe)
{
    CRef cref;
    CRef crefTest;

    cref.SetTag(TAGK_Void);

    CPair *pClauseList = ppair->m_ref.m_tag.m_ppair->m_ppairNext;
    while (pClauseList != NULL)
    {
        CPair *pClause = pClauseList->m_ref.m_tag.m_ppair;
        int fMatch;

        /* Check if we have a match, which is either trivially true for an "else",
           or if the condition evaluates to true. */
        if (pClause->m_ref.m_tagk == TAGK_Else)
        {
            fMatch = 1;
        }
        else
        {
            crefTest = RefEval(pClause, pframe);
            fMatch = 0;
            if (crefTest.m_tagk != TAGK_Bool || crefTest.m_tag.m_bool != 0)
            {
                fMatch = 1;
            }

            if (fMatch && pClause->m_ppairNext == NULL)
            {
                cref = crefTest;
            }
        }

        /* If we have a match, then execute all expressions and return. */
        if (fMatch)
        {
            pClause = pClause->m_ppairNext;
            while (pClause != NULL)
            {
                cref = RefEval(pClause, pframe);
                pClause = pClause->m_ppairNext;
            }
            pClauseList = NULL;
        }
        else
        {
            pClauseList = pClauseList->m_ppairNext;
        }
    }

    return cref;
}

CRef RefEvalCase(CPair *ppair, CFrame *pframe)
{
    CRef cref;
    CRef aref[2];
    CRef crefEqv;

    cref.SetTag(TAGK_Void);

    CPair *ppairKey = ppair->m_ref.m_tag.m_ppair->m_ppairNext;
    aref[0] = RefEval(ppairKey, pframe);

    CPair *pClauseList = ppairKey->m_ppairNext;
    while (pClauseList != NULL)
    {
        CPair *pClause = pClauseList->m_ref.m_tag.m_ppair;
        int fMatch;

        /* Check if we have a match, which is either trivially true for an "else",
           or if one of the data conditions matches. */
        if (pClause->m_ref.m_tagk == TAGK_Else)
        {
            fMatch = 1;
        }
        else
        {
            fMatch = 0;
            CPair *pDatumList = pClause->m_ref.m_tag.m_ppair;
            while (pDatumList != NULL)
            {
                aref[1] = pDatumList->m_ref;
                crefEqv = RefOpEqv(2, aref, pframe);
                if (crefEqv.m_tagk == TAGK_Bool && crefEqv.m_tag.m_bool != 0)
                {
                    fMatch = 1;
                    pDatumList = NULL;
                }
                else
                {
                    pDatumList = pDatumList->m_ppairNext;
                }
            }
        }

        /* If we have a match, then execute all expressions and return. */
        if (fMatch)
        {
            pClause = pClause->m_ppairNext;
            while (pClause != NULL)
            {
                cref = RefEval(pClause, pframe);
                pClause = pClause->m_ppairNext;
            }
            pClauseList = NULL;
        }
        else
        {
            pClauseList = pClauseList->m_ppairNext;
        }
    }

    return cref;
}

CRef RefEvalLet(CPair *ppair, CFrame *pframe)
{
    CRef cref;
    CRef cEval, cBinding;

    CPair* pDefinitions = ppair->m_ref.m_tag.m_ppair->m_ppairNext;
    CFrame* pCurrentFrame;

    /* Loop through each variable definition and add them to a new binding frame. */
    if (pDefinitions->m_ref.m_tagk == TAGK_Pair)
    {
        pCurrentFrame = PframeNew();

        CPair* pDefinition = pDefinitions->m_ref.m_tag.m_ppair;
        while (pDefinition != NULL)
        {
            CPair* pDefPair = pDefinition->m_ref.m_tag.m_ppair;
            cEval = RefEval(pDefPair->m_ppairNext, pframe);
            cBinding = pCurrentFrame->RefAddBinding(pDefPair->m_ref.m_tag.m_symid, &cEval);

            pDefinition = pDefinition->m_ppairNext;
        }

        pCurrentFrame->SetSingleParent(pframe);
    }
    else
    {
        pCurrentFrame = pframe;
    }

    /* Evaluate all body expressions */
    CPair* pBody = pDefinitions->m_ppairNext;
    while (pBody != NULL)
    {
        cref = RefEval(pBody, pCurrentFrame);
        pBody = pBody->m_ppairNext;
    }

    return cref;
}

CRef RefEvalWhile(CPair *ppair, CFrame *pframe)
{
    CRef cref;

    CPair* pCond = ppair->m_ref.m_tag.m_ppair->m_ppairNext;
    CPair* pBody = pCond->m_ppairNext;

    /* Keeping looping until we get an explicit FALSE value */
    while (true)
    {
        cref = RefEval(pCond, pframe);

        if (cref.m_tagk == TAGK_Bool && cref.m_tag.m_bool == 0)
        {
            break;
        }

        cref = RefEval(pBody, pframe);
    }

    cref.SetTag(TAGK_Void);
    return cref;
}

CRef RefEvalLambda(CPair *ppair, CFrame *pframe)
{
    CRef cref;

    CPair* pPair = ppair->m_ref.m_tag.m_ppair->m_ppairNext;
    CPair* pCodeExpr = pPair->m_ppairNext;

    /* Create a new procedure with optional arguments */
    CProc* pProc = PprocNew();
    pProc->m_pframe = pframe;
    if (pPair->m_ref.m_tagk == TAGK_None)
    {
        pProc->m_ppair = NULL;
    }
    else
    {
        pProc->m_ppair = pPair->m_ref.m_tag.m_ppair;
    }

    pProc->m_ppairCodeExpr = pCodeExpr;
    int fVarArg = 0;
    int crefReq = 0;

    /* Count the number of arguments */
    CPair* pCur = pProc->m_ppair;
    while (pCur != NULL)
    {
        if (pCur->m_ref.m_tagk == TAGK_Pipe)
        {
            fVarArg = 1;
            pCur = NULL;
        }
        else
        {
            pCur = pCur->m_ppairNext;
            crefReq++;
        }
    }
    pProc->m_crefReq = crefReq;
    pProc->m_fVarArg = fVarArg;

    cref.SetProc(pProc);
    return cref;
}

CRef RefEvalLambdaBody(CPair *ppair, CFrame *pframe)
{
    CRef cref;

    CPair* pCurrent = ppair;
    do
    {
        cref = RefEval(pCurrent, pframe);
        pCurrent = pCurrent->m_ppairNext;
    }
    while (pCurrent != NULL);

    return cref;
}

CRef RefEvalBegin(CPair *ppair, CFrame *pframe)
{
    CRef cref;

    cref.SetTag(TAGK_Void);
    CPair* pPair = ppair->m_ref.m_tag.m_ppair->m_ppairNext;
    while (pPair != NULL)
    {
        cref = RefEval(pPair, pframe);
        pPair = pPair->m_ppairNext;
    }

    return cref;
}

/**
 * @todo: 99.5259% matching
 * There are several mismatched registers in the variadic arguments loop
 * and TAGK_Proc case, as well as one swapped pair of instructions in the latter.
 */
INCLUDE_ASM("asm/nonmatchings/P2/splice/eval", RefEvalApply__FP5CPairP6CFrame);
#ifdef SKIP_ASM
CRef RefEvalApply(CPair *ppair, CFrame *pframe)
{
    CRef cref;
    CRef crefResult;
    CRef arefs[32];

    CPair *pPair = ppair->m_ref.m_tag.m_ppair;
    cref = RefEval(pPair, pframe);

    int crefReq;
    int carg;
    int fVarArg;
    int cparam;
    BIF *pEntry;
    CMethod *pMethod;
    CProc *pProc;

    if (cref.m_tagk == TAGK_Bifk)
    {
        /* Built-in function */
        pEntry = &g_mpbifkbif[cref.m_tag.m_bifk];
        crefReq = pEntry->crefReq;
        fVarArg = pEntry->fVarArg;
    }
    else if (cref.m_tagk == TAGK_Method)
    {
        /* Method */
        pMethod = cref.m_tag.m_pmethod;
        fVarArg = 0;
        crefReq = pMethod->m_crefReq;
    }
    else
    {
        /* Procedure */
        pProc = cref.m_tag.m_pproc;
        crefReq = pProc->m_crefReq;
        fVarArg = pProc->m_fVarArg;
    }

    pPair = pPair->m_ppairNext;

    /* Flatten cref arguments into an array */
    cparam = crefReq + (fVarArg != 0);
    carg = crefReq;
    int i;
    for (i = 0; i < carg; i++)
    {
        crefResult = RefEval(pPair, pframe);
        arefs[i] = crefResult;
        pPair = pPair->m_ppairNext;
    }

    /* If we have variadic arguments, then place them into a list
       that gets passed as the last argument. */
    if (fVarArg)
    {
        CPair *pRest = pPair;

        CPair *pTail = NULL;
        CPair *pHead = NULL;

        while (pRest != NULL)
        {
            pPair = PpairNew();
            pPair->m_ref = RefEval(pRest, pframe);
            if (pTail != NULL)
            {
                pTail->m_ppairNext = pPair;
                pTail = pPair;
            }
            else
            {
                pTail = pPair;
                pHead = pTail;
            }
            pRest = pRest->m_ppairNext;
            carg++;
        }

        if (pHead != NULL)
        {
            arefs[i].SetPair(pHead);
        }
        else
        {
            arefs[i].SetTag(TAGK_None);
        }
    }

    /* Dispatch based on the original call */
    switch (cref.m_tagk)
    {
        case TAGK_Bifk:
        {
            crefResult = pEntry->pfnbif(carg, arefs, pframe);
            break;
        }

        case TAGK_Proc:
        {
            pProc = cref.m_tag.m_pproc;
            CFrame *pFrameNew = PframeNew();
            pFrameNew->SetSingleParent(pProc->m_pframe);
            pPair = pProc->m_ppair;

            if (cparam > 0)
            {
                TAGK tagkPipe = TAGK_Pipe;
                CRef *pArg = arefs;
                int cparamRem = cparam;

                while (cparamRem != 0)
                {
                    CRef crefBinding;
                    if (pPair->m_ref.m_tagk == tagkPipe)
                    {
                        pPair = pPair->m_ppairNext;
                    }
                    crefBinding = pFrameNew->RefAddBinding(pPair->m_ref.m_tag.m_symid, pArg);
                    cparamRem--;
                    pArg++;
                    pPair = pPair->m_ppairNext;
                }
            }
            crefResult = RefEvalLambdaBody(pProc->m_ppairCodeExpr, pFrameNew);
            break;
        }

        case TAGK_Method:
        {
            crefResult = pMethod->m_pfnthunk(pMethod->m_pbasic, carg, arefs);
            break;
        }

        default:
        {
            break;
        }
    }

    return crefResult;
}
#endif

CRef RefEvalImport(CPair *ppair, CFrame *pframe)
{
    CRef cref;

    CPair *ppairVar = ppair->m_ref.m_tag.m_ppair->m_ppairNext;
    int isplice = ppairVar->m_ref.m_tag.m_n;
    CFrame* pParentFrame = PframeFromIsplice(isplice, g_psw);

    if (pParentFrame == NULL)
    {
        cref = RefEvalModule(isplice, g_psw);
        pParentFrame = PframeFromIsplice(isplice, g_psw);
    }

    pframe->AddParent(pParentFrame);
    cref.SetTag(TAGK_Void);

    return cref;
}

CRef RefEval(CPair *ppair, CFrame *pframe)
{
    CRef cref;

    TAGK tagk = ppair->m_ref.m_tagk;
    switch (tagk)
    {
        case TAGK_None:
        case TAGK_S32:
        case TAGK_F32:
        case TAGK_Vector:
        case TAGK_Matrix:
        case TAGK_Clq:
        case TAGK_Lm:
        case TAGK_Smp:
        case TAGK_Bool:
        case TAGK_Bifk:
        case TAGK_Basic:
        case TAGK_Method:
        {
            cref = ppair->m_ref;
            break;
        }
        case TAGK_Symid:
        {
            cref = RefEvalSymbol(ppair, pframe);
            break;
        }
        case TAGK_Pair:
        {
            CPair* pRest = ppair->m_ref.m_tag.m_ppair;
            TAGK tagk_rest = pRest->m_ref.m_tagk;
            switch (tagk_rest)
            {
                case TAGK_Set:
                {
                    cref = RefEvalSet(ppair, pframe);
                    break;
                }
                case TAGK_Define:
                {
                    cref = RefEvalDefine(ppair, pframe);
                    break;
                }
                case TAGK_Assert:
                {
                    cref = RefEvalAssert(ppair, pframe);
                    break;
                }
                case TAGK_If:
                {
                    cref = RefEvalIf(ppair, pframe);
                    break;
                }
                case TAGK_Or:
                {
                    cref = RefEvalOr(ppair, pframe);
                    break;
                }
                case TAGK_And:
                {
                    cref = RefEvalAnd(ppair, pframe);
                    break;
                }
                case TAGK_Cond:
                {
                    cref = RefEvalCond(ppair, pframe);
                    break;
                }
                case TAGK_Case:
                {
                    cref = RefEvalCase(ppair, pframe);
                    break;
                }
                case TAGK_Let:
                {
                    cref = RefEvalLet(ppair, pframe);
                    break;
                }
                case TAGK_While:
                {
                    cref = RefEvalWhile(ppair, pframe);
                    break;
                }
                case TAGK_Begin:
                {
                    cref = RefEvalBegin(ppair, pframe);
                    break;
                }
                case TAGK_Lambda:
                {
                    cref = RefEvalLambda(ppair, pframe);
                    break;
                }
                case TAGK_Quote:
                {
                    cref = pRest->m_ppairNext->m_ref;
                    break;
                }
                case TAGK_Import:
                {
                    cref = RefEvalImport(ppair, pframe);
                    break;
                }
                default:
                {
                    cref = RefEvalApply(ppair, pframe);
                    break;
                }
            }
        }
    }

    return cref;
}

ALIGN_SECTION(rodata, 4);
