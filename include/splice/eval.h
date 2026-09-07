/**
 * @file splice/eval.h
 */
#ifndef SPLICE_EVAL_H
#define SPLICE_EVAL_H

#include "common.h"
#include <splice/ref.h>

// Forward declarations.
class CPair;
class CFrame;

CRef RefEvalSymbol(CPair *ppair, CFrame *pframe);

CRef RefEvalSet(CPair *ppair, CFrame *pframe);

CRef RefEvalDefine(CPair *ppair, CFrame *pframe);

CRef RefEvalAssert(CPair *ppair, CFrame *pframe);

CRef RefEvalIf(CPair *ppair, CFrame *pframe);

CRef RefEvalOr(CPair *ppair, CFrame *pframe);

CRef RefEvalAnd(CPair *ppair, CFrame *pframe);

CRef RefEvalCond(CPair *ppair, CFrame *pframe);

CRef RefEvalCase(CPair *ppair, CFrame *pframe);

CRef RefEvalLet(CPair *ppair, CFrame *pframe);

CRef RefEvalWhile(CPair *ppair, CFrame *pframe);

CRef RefEvalLambda(CPair *ppair, CFrame *pframe);

CRef RefEvalLambdaBody(CPair *ppair, CFrame *pframe);

CRef RefEvalBegin(CPair *ppair, CFrame *pframe);

CRef RefEvalApply(CPair *ppair, CFrame *pframe);

CRef RefEvalImport(CPair *ppair, CFrame *pframe);

CRef RefEval(CPair *ppair, CFrame *pframe);

#endif // SPLICE_EVAL_H
