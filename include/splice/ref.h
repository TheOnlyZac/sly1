/**
 * @file splice/ref.h
 */
#ifndef SPLICE_REF_H
#define SPLICE_REF_H

#include "common.h"
#include <splice/pair.h>
#include <splice/proc.h>
#include <splice/method.h>
#include <splice/bif.h>
#include <basic.h>
#include <util.h>

enum TAGK
{
    TAGK_Nil = -1,
    TAGK_None = 0,
    TAGK_Set = 1,
    TAGK_Define = 2,
    TAGK_DefineMacro = 3,
    TAGK_DefineMacroLambda = 4,
    TAGK_Assert = 5,
    TAGK_If = 6,
    TAGK_Or = 7,
    TAGK_And = 8,
    TAGK_Cond = 9,
    TAGK_Else = 10,
    TAGK_Case = 11,
    TAGK_Let = 12,
    TAGK_While = 13,
    TAGK_Lambda = 14,
    TAGK_Begin = 15,
    TAGK_Import = 16,
    TAGK_Quote = 17,
    TAGK_Dot = 18,
    TAGK_Pipe = 19,
    TAGK_S32 = 20,
    TAGK_F32 = 21,
    TAGK_Vector = 22,
    TAGK_Matrix = 23,
    TAGK_Clq = 24,
    TAGK_Lm = 25,
    TAGK_Smp = 26,
    TAGK_Bool = 27,
    TAGK_Symid = 28,
    TAGK_Bifk = 29,
    TAGK_Pair = 30,
    TAGK_Proc = 31,
    TAGK_Basic = 32,
    TAGK_Method = 33,
    TAGK_Void = 34,
    TAGK_Err = 35,
    TAGK_Max = 36
};

union TAG
{
    int m_n;
    float m_g;
    int m_bool;
    uint m_symid;
    BIFK m_bifk;
    CPair* m_ppair;
    CProc* m_pproc;
    VECTOR* m_pvector;
    MATRIX4* m_pmatrix;
    CLQ* m_pclq;
    LM* m_plm;
    SMP* m_psmp;
    BASIC* m_pbasic;
    CMethod* m_pmethod;
};

class CRef
{
public:
    CRef();
    CRef(const CRef &ref);
    ~CRef();
    CRef &operator=(const CRef &ref);
    bool operator==(const CRef &ref) const;
    void CloneTo(CRef *prefClone, CFrame *pframeClone) const;
    void Decref();
    void Incref();
    void SetTag(TAGK tagk);
    void SetS32(s32 n);
    void SetF32(f32 g);
    void SetBool(int fBool);
    void SetSymid(u32 symid);
    void SetBifk(BIFK bifk);
    void SetPair(CPair *ppair);
    void SetProc(CProc *pproc);
    void SetVector(VECTOR *pvector);
    void SetMatrix(MATRIX4 *pmatrix);
    void SetClq(CLQ *pclq);
    void SetLm(LM *plm);
    void SetSmp(SMP *psmp);
    void SetBasic(BASIC *pbasic);
    void SetMethod(CMethod *pmethod);
    s32 RefCoerceS32() const;
    f32 RefCoerceF32() const;

private:
    TAGK m_tagk;
    TAG m_tag;
};

#endif // SPLICE_REF_H
