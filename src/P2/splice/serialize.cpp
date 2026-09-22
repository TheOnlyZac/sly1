#include <splice/serialize.h>
#include <splice/vecmat.h>
#include <splice/pair.h>
#include <util.h>
#include <sm.h>

extern int g_fLoadDebugInfo;

CPair *PpairSerializeIn(CBinaryInputStream *pstrm)
{
    uchar uctagk = pstrm->U8Read();
    if (uctagk == (unsigned char)TAGK_Nil)
    {
        return NULL;
    }

    /* Mask off the high bit of the read tag, as it indicates a recursive pair. */
    CPair *pair = PpairNew();
    int fRecurse = uctagk & 0x80;
    pair->m_ref.m_tagk = (TAGK)(uctagk & 0x7F);

    /* Throw away debug information if enabled */
    if (g_fLoadDebugInfo != 0)
    {
        pstrm->U16Read();
        pstrm->U16Read();
        pstrm->U16Read();
        pstrm->U16Read();
        pstrm->U16Read();
    }

    switch (pair->m_ref.m_tagk)
    {
        case TAGK_None:
        {
            break;
        }
        case TAGK_S32:
        {
            pair->m_ref.SetS32(pstrm->S32Read());
            break;
        }
        case TAGK_F32:
        {
            pair->m_ref.SetF32(pstrm->F32Read());
            break;
        }
        case TAGK_Bool:
        {
            pair->m_ref.SetBool(pstrm->U32Read());
            break;
        }
        case TAGK_Basic:
        {
            pair->m_ref.SetBasic((BASIC *)pstrm->U32Read());
            break;
        }
        case TAGK_Symid:
        {
            pair->m_ref.SetSymid(pstrm->U32Read());
            break;
        }
        case TAGK_Bifk:
        {
            pair->m_ref.SetBifk((BIFK)pstrm->U32Read());
            break;
        }
        case TAGK_Vector:
        {
            VECTOR *pvector = PvectorNew();
            float *pout = (float *)pvector;
            for (int i = 0; i < 3; ++i)
            {
                pout[i] = pstrm->F32Read();
            }
            pair->m_ref.m_tagk = TAGK_Nil;
            pair->m_ref.SetVector(pvector);
            break;
        }
        case TAGK_Matrix:
        {
            MATRIX4 *pmatrix = PmatrixNew();
            float *pout = (float *)pmatrix;
            for (int i = 0; i < 16; ++i)
            {
                pout[i] = pstrm->F32Read();
            }
            pair->m_ref.m_tagk = TAGK_Nil;
            pair->m_ref.SetMatrix(pmatrix);
            break;
        }
        case TAGK_Clq:
        {
            CLQ *pclq = PclqNew();
            for (int i = 0; i < 3; ++i)
            {
                pclq->ag[i] = pstrm->F32Read();
            }
            pair->m_ref.m_tagk = TAGK_Nil;
            pair->m_ref.SetClq(pclq);
            break;
        }
        case TAGK_Lm:
        {
            LM *plm = PlmNew();
            plm->gMin = pstrm->F32Read();
            plm->gMax = pstrm->F32Read();
            pair->m_ref.m_tagk = TAGK_Nil;
            pair->m_ref.SetLm(plm);
            break;
        }
        case TAGK_Smp:
        {
            SMP *psmp = PsmpNew();
            psmp->svFast = pstrm->F32Read();
            psmp->svSlow = pstrm->F32Read();
            psmp->dtFast = pstrm->F32Read();
            pair->m_ref.m_tagk = TAGK_Nil;
            pair->m_ref.SetSmp(psmp);
            break;
        }
        case TAGK_Pair:
        {
            pair->m_ref.SetPair(PpairSerializeIn(pstrm));
            break;
        }
        default:
        {
            break;
        }
    }

    /* Recurse if there is more to read. */
    if (fRecurse != 0)
    {
        pair->m_ppairNext = PpairSerializeIn(pstrm);
    }
    else
    {
        pair->m_ppairNext = NULL;
    }

    return pair;
}
