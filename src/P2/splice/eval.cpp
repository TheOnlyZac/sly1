#include <splice/eval.h>
#include <splice/ref.h>
#include <splice/pair.h>
#include <splice/frame.h>

CRef RefEvalSymbol(CPair *ppair, CFrame *pframe)
{
    CRef ref;
    pframe->FFindBinding(ppair->m_ref.m_tag.m_symid, 1, &ref);
    return ref;
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/eval", RefEvalSet__FP5CPairP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/eval", RefEvalDefine__FP5CPairP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/eval", RefEvalAssert__FP5CPairP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/eval", RefEvalIf__FP5CPairP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/eval", RefEvalOr__FP5CPairP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/eval", RefEvalAnd__FP5CPairP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/eval", RefEvalCond__FP5CPairP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/eval", RefEvalCase__FP5CPairP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/eval", RefEvalLet__FP5CPairP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/eval", RefEvalWhile__FP5CPairP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/eval", RefEvalLambda__FP5CPairP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/eval", RefEvalLambdaBody__FP5CPairP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/eval", RefEvalBegin__FP5CPairP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/eval", RefEvalApply__FP5CPairP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/eval", RefEvalImport__FP5CPairP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/eval", RefEval__FP5CPairP6CFrame);
