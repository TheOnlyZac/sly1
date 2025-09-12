#include <splice/ref.h>
#include <splice/vecmat.h>

CRef::CRef()
{
    m_tagk = TAGK_Nil;
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/ref", __4CRefRC4CRef);

CRef::~CRef()
{
    Decref();
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/ref", __as__4CRefRC4CRef);

/**
 * @todo fix misalignment
 */
INCLUDE_ASM("asm/nonmatchings/P2/splice/ref", __eq__4CRefRC4CRef);
#ifdef SKIP_ASM
bool CRef::operator==(const CRef& ref)
{
  if (m_tagk != ref.m_tagk) {
    return false;
  }
  switch(m_tagk) {
    case TAGK_F32:
        return m_tag.m_g == ref.m_tag.m_g;
    case TAGK_S32:
        return m_tag.m_n == ref.m_tag.m_n;
    case TAGK_Symid:
        return m_tag.m_symid == ref.m_tag.m_symid;
    case TAGK_Bifk:
        return m_tag.m_bifk == ref.m_tag.m_bifk;
    case TAGK_Pair:
        return m_tag.m_ppair == ref.m_tag.m_ppair;
    case TAGK_Proc:
        return m_tag.m_pproc == ref.m_tag.m_pproc;
    case TAGK_Method:
        return m_tag.m_pmethod == ref.m_tag.m_pmethod;
    case TAGK_Basic:
        return (!m_tag.m_pbasic && !ref.m_tag.m_pbasic) || (m_tag.m_pbasic && ref.m_tag.m_pbasic);
    case TAGK_Matrix:
        return memcmp(m_tag.m_pmatrix,ref.m_tag.m_pmatrix, 0x40) == 0;
    case TAGK_Lm:
        return (m_tag.m_plm->gMin == ref.m_tag.m_plm->gMin) &&
               (m_tag.m_plm->gMax == ref.m_tag.m_plm->gMax);
    case TAGK_Vector:
        return (m_tag.m_pvector->x == ref.m_tag.m_pvector->x) &&
               (m_tag.m_pvector->y == ref.m_tag.m_pvector->y) &&
               (m_tag.m_pvector->z == ref.m_tag.m_pvector->z);
    case TAGK_Clq:
        return (m_tag.m_pclq->u == ref.m_tag.m_pclq->u) &&
               (m_tag.m_pclq->v == ref.m_tag.m_pclq->v) &&
               (m_tag.m_pclq->w == ref.m_tag.m_pclq->w);
    case TAGK_Smp:
        return (m_tag.m_psmp->svFast == ref.m_tag.m_psmp->svFast) &&
               (m_tag.m_psmp->svSlow == ref.m_tag.m_psmp->svSlow) &&
               (m_tag.m_psmp->dtFast == ref.m_tag.m_psmp->dtFast);
    case TAGK_Bool:
        return m_tag.m_bool == ref.m_tag.m_bool;
    default:
        return true;
  }
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/splice/ref", CloneTo__4CRefP4CRefP6CFrame);

/**
 * @todo match rodata
 */
INCLUDE_ASM("asm/nonmatchings/P2/splice/ref", Decref__4CRef);
#ifdef SKIP_ASM
void CRef::Decref()
{
    switch(m_tagk)
    {
        case TAGK_Vector:
            DecrefVector(m_tag.m_pvector);
            break;
        case TAGK_Matrix:
            DecrefMatrix(m_tag.m_pmatrix);
            break;
        case TAGK_Clq:
            DecrefClq(m_tag.m_pclq);
            break;
        case TAGK_Lm:
            DecrefLm(m_tag.m_plm);
            break;
        case TAGK_Smp:
            DecrefSmp(m_tag.m_psmp);
            break;
    }
}
#endif // SKIP_ASM

/**
 * @todo match rodata
 */
INCLUDE_ASM("asm/nonmatchings/P2/splice/ref", Incref__4CRef);
#ifdef SKIP_ASM
void CRef::Incref()
{
    switch(m_tagk)
    {
        case TAGK_Vector:
            IncrefVector(m_tag.m_pvector);
            break;
        case TAGK_Matrix:
            IncrefMatrix(m_tag.m_pmatrix);
            break;
        case TAGK_Clq:
            IncrefClq(m_tag.m_pclq);
            break;
        case TAGK_Lm:
            IncrefLm(m_tag.m_plm);
            break;
        case TAGK_Smp:
            IncrefSmp(m_tag.m_psmp);
            break;
    }
}
#endif

void CRef::SetTag(TAGK tagk)
{
    Decref();
    m_tagk = tagk;
}

void CRef::SetS32(int n)
{
    Decref();
    m_tag.m_n = n;
    m_tagk = TAGK_S32;
}

void CRef::SetF32(float g)
{
    Decref();
    m_tag.m_g = g;
    m_tagk = TAGK_F32;
}

void CRef::SetBool(int fBool)
{
    Decref();
    if (fBool)
    {
        m_tag.m_bool = 1;
    }
    else
    {
        m_tag.m_bool = 0;
    }
    m_tagk = TAGK_Bool;
}

void CRef::SetSymid(uint symid)
{
    Decref();
    m_tag.m_symid = symid;
    m_tagk = TAGK_Symid;
}

void CRef::SetBifk(BIFK bifk)
{
    Decref();
    m_tag.m_bifk = bifk;
    m_tagk = TAGK_Bifk;
}

void CRef::SetPair(CPair* ppair)
{
    Decref();
    m_tag.m_ppair = ppair;
    m_tagk = TAGK_Pair;
}

void CRef::SetProc(CProc* pproc)
{
    Decref();
    m_tag.m_pproc = pproc;
    m_tagk = TAGK_Proc;
}

void CRef::SetVector(VECTOR* pvector)
{
    IncrefVector(pvector);
    Decref();
    m_tag.m_pvector = pvector;
    m_tagk = TAGK_Vector;
}

void CRef::SetMatrix(MATRIX4* pmatrix)
{
    IncrefMatrix(pmatrix);
    Decref();
    m_tag.m_pmatrix = pmatrix;
    m_tagk = TAGK_Matrix;
}

void CRef::SetClq(CLQ* pclq)
{
    IncrefClq(pclq);
    Decref();
    m_tag.m_pclq = pclq;
    m_tagk = TAGK_Clq;
}

void CRef::SetLm(LM* plm)
{
    IncrefLm(plm);
    Decref();
    m_tag.m_plm = plm;
    m_tagk = TAGK_Lm;
}

void CRef::SetSmp(SMP* psmp)
{
    IncrefSmp(psmp);
    Decref();
    m_tag.m_psmp = psmp;
    m_tagk = TAGK_Smp;
}

void CRef::SetBasic(BASIC* pbasic)
{
    Decref();
    m_tag.m_pbasic = pbasic;
    m_tagk = TAGK_Basic;
}

void CRef::SetMethod(CMethod* pmethod)
{
    Decref();
    m_tag.m_pmethod = pmethod;
    m_tagk = TAGK_Method;
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/ref", RefCoerceS32__4CRef);

INCLUDE_ASM("asm/nonmatchings/P2/splice/ref", RefCoerceF32__4CRef);
