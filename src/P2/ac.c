#include <ac.h>
#include <bez.h>
#include <memory.h>

/**
 * @todo Implement ACP vtables.
 */
extern int g_vtacpb;
extern int g_vtacpc;
extern int g_vtacpbl;

/**
 * @todo Implement ACR vtables.
 */
extern int g_vtacrc;
extern int g_vtacrb;
extern int g_vtacrbl;

/**
 * @todo Implement ACS vtables.
 */
extern int g_vtacsc;
extern int g_vtacsb;

/**
 * @todo Implement ACG vtables.
 */
extern int g_vtacgb;
extern int g_vtacgbw;
extern int g_vtacgblt;
extern int g_vtacgblp;
extern int g_vtacgl;

INCLUDE_ASM("asm/nonmatchings/P2/ac", FindKey__FfiiiPcPfT5PPv);
#ifdef SKIP_ASM
/**
 * @todo 99.61% match.
 */
void FindKey(float t, GRFEVAL grfeval, int cbKey, int ckey, char *abKey, float *pdt, float *pdtSeg, void **ppv)
{
    int iKeyHi = ckey;
    int iKeyLo = 1;
    if (ckey != 1)
    {
        while (iKeyLo != iKeyHi)
        {
            int iKey = (iKeyHi + iKeyLo) / 2;
            float tKey = *(float *)(abKey + cbKey * iKey);

            if (tKey > t)
            {
                iKeyHi = iKey;
            }
            else
            {
                iKeyLo = iKey + 1;
            }
        }
    }

    if (iKeyLo >= ckey)
    {
        iKeyLo = ckey - 1;
    }

    char *pbKey = abKey + cbKey * (iKeyLo - 1);
    if ((grfeval & 1) != 0 && *(float *)pbKey == t)
    {
        pbKey -= cbKey;
        if (pbKey < abKey)
        {
            pbKey += (ckey - 1) * cbKey;
            t = *(float *)(pbKey + cbKey);
        }
    }

    if (pdt)
    {
        *pdt = t - *(float *)pbKey;
    }
    if (pdtSeg)
    {
        *pdtSeg = *(float *)(pbKey + cbKey) - *(float *)pbKey;
    }

    *ppv = pbKey;
}
#endif // SKIP_ASM

void EvaluateAcp(ACP *pacp, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *ppos, VECTOR *pv)
{
    return;
}

void GetAcpTimes(ACP *pacp, int *pct, float **pat)
{
    *pct = 0;
    if (pat)
    {
        *pat = NULL;
    }
}

void EvaluateAcr(ACR *pacr, ALO *palo, float t, float svt, GRFEVAL grfeval, MATRIX3 *pmat, VECTOR *pw)
{
    return;
}

void EvaluateAcrEul(ACR *pacr, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *peul, VECTOR *pdeul)
{
    return;
}

void GetAcrTimes(ACR *pacr, int *pct, float **pat)
{
    *pct = 0;
    if (pat)
    {
        *pat = NULL;
    }
}

void EvaluateAcs(ACS *pacs, ALO *palo, float t, GRFEVAL grfeval, MATRIX3 *pmat)
{
    return;
}

void GetAcsTimes(ACS *pacs, int *pct, float **pat)
{
    *pct = 0;
    if (pat)
    {
        *pat = NULL;
    }
}

void EvaluateAcg(ACG *pacg, ALO *palo, float t, float svt, GRFEVAL grfeval, float *pg, float *pdg)
{
    return;
}

void GetAcgTimes(ACG *pacg, int *pct, float **pat)
{
    *pct = 0;
    if (pat)
    {
        *pat = NULL;
    }
}

void LoadAcgbFromBrx(ACGB *pacgb, CBinaryInputStream *pbis)
{
    pacgb->ckgb = (int)pbis->U16Read();
    pacgb->akgb = (KGB *)PvAllocSwImpl(pacgb->ckgb * sizeof(KGB));

    for (int i = 0; i < pacgb->ckgb; i++)
    {
        KGB *pkgb = &pacgb->akgb[i];

        pkgb->t = (float)pbis->S16Read() * 0.016666668f;
        pkgb->g = pbis->F32Read();

        pkgb->kgbtIn.kgbtk = (KGBTK)pbis->S8Read();
        pkgb->kgbtOut.kgbtk = (KGBTK)pbis->S8Read();

        pkgb->kgbtIn.gSlope = pbis->F32Read();
        pkgb->kgbtOut.gSlope = pbis->F32Read();
    }
}

void EvaluateAcgb(ACGB *pacgb, ALO *palo, float t, float svt, GRFEVAL grfeval, float *pg, float *pdg)
{
    float dt, dtSeg;
    KGB *pkgb;
    FindKey(t, grfeval, sizeof(KGB), pacgb->ckgb, (char *)pacgb->akgb, &dt, &dtSeg, (void **)&pkgb);

    if (pkgb->kgbtOut.kgbtk == KGBTK_Step)
    {
        if (pg)
        {
            *pg = pkgb->g;
        }
        if (pdg)
        {
            *pdg = 0.0f;
        }
    }
    else
    {
        EvaluateBezierFloat(dtSeg, dt, svt, pkgb->g, pkgb->kgbtOut.gSlope, pkgb[1].g, pkgb[1].kgbtIn.gSlope, pg, pdg, NULL);
    }
}

void GetAcgbTimes(ACGB *pacgb, int *pct, float **pat)
{
    *pct = pacgb->ckgb;

    if (pat)
    {
        *pat = (float *)PvAllocStackImpl(*pct * sizeof(float));

        for (int i = 0; i < *pct; i++)
        {
            (*pat)[i] = pacgb->akgb[i].t;
        }
    }
}

void LoadAcgbwFromBrx(ACGBW *pacgbw, CBinaryInputStream *pbis)
{
    pacgbw->ckgbw = (int)pbis->U16Read();
    pacgbw->akgbw = (KGBW *)PvAllocSwImpl(pacgbw->ckgbw * sizeof(KGBW));

    for (int i = 0; i < pacgbw->ckgbw; i++)
    {
        KGBW *pkgbw = &pacgbw->akgbw[i];

        pkgbw->t = (float)pbis->S16Read() * 0.016666668f;
        pkgbw->g = pbis->F32Read();

        pkgbw->kgbwtIn.kgbtk = (KGBTK)pbis->S8Read();
        pkgbw->kgbwtOut.kgbtk = (KGBTK)pbis->S8Read();

        pkgbw->kgbwtIn.dt = pbis->F32Read();
        pkgbw->kgbwtIn.g = pkgbw->g - pbis->F32Read();

        pkgbw->kgbwtOut.dt = pbis->F32Read();
        pkgbw->kgbwtOut.g = pkgbw->g + pbis->F32Read();
    }
}

void EvaluateAcgbw(ACGBW *pacgbw, ALO *palo, float t, float svt, GRFEVAL grfeval, float *pg, float *pdg)
{
    float dt, dtSeg;
    KGBW *pkgbw;
    FindKey(t, grfeval, sizeof(KGBW), pacgbw->ckgbw, (char *)pacgbw->akgbw, &dt, &dtSeg, (void **)&pkgbw);

    if (pkgbw->kgbwtOut.kgbtk == KGBTK_Step)
    {
        if (pg)
        {
            *pg = pkgbw->g;
        }
        if (pdg)
        {
            *pdg = 0.0f;
        }
    }
    else
    {
        EvaluateBezierWeightedFloat(
            dtSeg, dt, svt,
            pkgbw[0].g, pkgbw[0].kgbwtOut.dt, pkgbw[0].kgbwtOut.g,
            pkgbw[1].g, pkgbw[1].kgbwtIn.dt, pkgbw[1].kgbwtIn.g,
            pg, pdg, NULL
        );
    }
}

void GetAcgbwTimes(ACGBW *pacgbw, int *pct, float **pat)
{
    *pct = pacgbw->ckgbw;

    if (pat)
    {
        *pat = (float *)PvAllocStackImpl(*pct * sizeof(float));

        for (int i = 0; i < *pct; i++)
        {
            (*pat)[i] = pacgbw->akgbw[i].t;
        }
    }
}

void EvaluateAcgl(ACGL *pacgl, ALO *palo, float t, float svt, GRFEVAL grfeval, float *pg, float *pdg)
{
    float dt, dtSeg;
    KGL *pkgl;
    FindKey(t, grfeval, sizeof(KGL), pacgl->ckgl, (char *)pacgl->akgl, &dt, &dtSeg, (void **)&pkgl);

    if (dtSeg < 0.0001f)
    {
        if (pg)
        {
            *pg = pkgl->g;
        }
        if (pdg)
        {
            *pdg = 0.0f;
        }
    }
    else
    {
        if (pg)
        {
            *pg = (1.0f - dt / dtSeg) * pkgl->g + (dt / dtSeg) * pkgl[1].g;
        }
        if (pdg)
        {
            *pdg = (svt * (pkgl[1].g - pkgl->g)) / dtSeg;
        }
    }
}

void LoadAcglFromBrx(ACGL *pacgl, CBinaryInputStream *pbis)
{
    pacgl->ckgl = (int)pbis->U16Read();
    pacgl->akgl = (KGL *)PvAllocSwImpl(pacgl->ckgl * sizeof(KGL));

    for (int i = 0; i < pacgl->ckgl; i++)
    {
        KGL *pkgl = &pacgl->akgl[i];
        pkgl->t = (float)pbis->S16Read() * 0.016666668f;
        pkgl->g = pbis->F32Read();
    }
}

void GetAcglTimes(ACGL *pacgl, int *pct, float **pat)
{
    *pct = pacgl->ckgl;

    if (pat)
    {
        *pat = (float *)PvAllocStackImpl(*pct * sizeof(float));
        for (int i = 0; i < *pct; i++)
        {
            (*pat)[i] = pacgl->akgl[i].t;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateApacg__FPP3ACGP3ALOffiP6VECTORN25);

INCLUDE_ASM("asm/nonmatchings/P2/ac", LoadApacgFromBrx__FPP3ACGP6VECTORP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/ac", GetApacgTimes__FPP3ACGPiPPf);

void EvaluateAkvb(int ckvb, KVB *akvb, float t, float svt, GRFEVAL grfeval, VECTOR *pvec, VECTOR *pdvec)
{
    float dt, dtSeg;
    KVB *pkvb;
    FindKey(t, grfeval, sizeof(KVB), ckvb, (char *)akvb, &dt, &dtSeg, (void **)(&pkvb));
    EvaluateBezierPos(dtSeg, dt, svt, &pkvb->vec, &pkvb->dvecOut, &pkvb[1].vec, &pkvb[1].dvecIn, pvec, pdvec, NULL);
}

void LoadAkvbFromBrx(int *pckvb, KVB **pakvb, CBinaryInputStream *pbis)
{
    int ckvb = (int)pbis->U16Read();
    KVB *akvb = (KVB *)PvAllocSwImpl(ckvb * sizeof(KVB));

    for (int i = 0; i < ckvb; i++)
    {
        KVB *pkvb = &akvb[i];
        pkvb->t = (float)pbis->S16Read() * 0.016666668f;
        pbis->ReadVector(&pkvb->vec);
        pbis->ReadVector(&pkvb->dvecIn);
        pbis->ReadVector(&pkvb->dvecOut);
    }

    *pckvb = ckvb;
    *pakvb = akvb;
}

void GetAkvbTimes(int ckvb, KVB *akvb, int *pct, float **pat)
{
    *pct = ckvb;

    if (pat)
    {
        *pat = (float *)PvAllocStackImpl(*pct * sizeof(float));
        for (int i = 0; i < *pct; i++)
        {
            (*pat)[i] = akvb[i].t;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcpc__FP4ACPCP3ALOffiP6VECTORT5);

INCLUDE_ASM("asm/nonmatchings/P2/ac", LoadAcpcFromBrx__FP4ACPCP18CBinaryInputStream);

void GetAcpcTimes(ACPC *pacpc, int *pct, float **pat)
{
    GetApacgTimes(pacpc->apacg, pct, pat);
}

void EvaluateAcpb(ACPB *pacpb, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *ppos, VECTOR *pv)
{
    EvaluateAkvb(pacpb->ckvb, pacpb->akvb, t, svt, grfeval, ppos, pv);

    if (palo && palo->pvtalo->pfnAdjustAloPosition)
    {
        palo->pvtalo->pfnAdjustAloPosition(palo, ppos, pv);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/ac", LoadAcpbFromBrx__FP4ACPBP18CBinaryInputStream);

void GetAcpbTimes(ACPB *pacpb, int *pct, float **pat)
{
    GetAkvbTimes(pacpb->ckvb, pacpb->akvb, pct, pat);
}

void EvaluateAcrc(ACRC *pacrc, ALO *palo, float t, float svt, GRFEVAL grfeval, MATRIX3 *pmat, VECTOR *pw)
{
    VECTOR eul, deul;
    EvaluateApacg(pacrc->apacg, palo, t, svt, grfeval, &pacrc->eulDefault, pmat ? &eul : NULL, pw ? &deul : NULL);

    if (pmat)
    {
        LoadRotateMatrixEuler(&eul, pmat);
    }
    if (pw)
    {
        ConvertDeulToW(&eul, &deul, pw);
    }
    if (palo)
    {
        palo->pvtalo->pfnAdjustAloRotation(palo, pmat, pw);
    }
}

void EvaluateAcrcEul(ACRC *pacrc, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *peul, VECTOR *pdeul)
{
    EvaluateApacg(pacrc->apacg, palo, t, svt, grfeval, &pacrc->eulDefault, peul, pdeul);
}

INCLUDE_ASM("asm/nonmatchings/P2/ac", LoadAcrcFromBrx__FP4ACRCP18CBinaryInputStream);

void GetAcrcTimes(ACRC *pacrc, int *pct, float **pat)
{
    GetApacgTimes(pacrc->apacg, pct, pat);
}

void EvaluateAcrb(ACRB *pacrb, ALO *palo,float t, float svt, GRFEVAL grfeval, MATRIX3 *pmat, VECTOR *pw)
{
    VECTOR eul, deul;
    EvaluateAkvb(pacrb->ckvb, pacrb->akvb, t, svt, grfeval, pmat ? &eul : NULL, pw ? &deul : NULL);

    if (pmat)
    {
        LoadRotateMatrixEuler(&eul, pmat);
    }
    if (pw)
    {
        ConvertDeulToW(&eul, &deul, pw);
    }
    if (palo)
    {
        palo->pvtalo->pfnAdjustAloRotation(palo, pmat, pw);
    }
}

void EvaluateAcrbEul(ACRB *pacrb, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *peul, VECTOR *pdeul)
{
    EvaluateAkvb(pacrb->ckvb, pacrb->akvb, t, svt, grfeval, peul, pdeul);
}

void LoadAcrbFromBrx(ACRB *pacrb, CBinaryInputStream *pbis)
{
    LoadAkvbFromBrx(&pacrb->ckvb, &pacrb->akvb, pbis);
    if (pacrb->ckvb < 2)
    {
        pacrb->fContiguous = 1;
        return;
    }

    MATRIX3 matRotA, matRotB, dmat;
    LoadRotateMatrixEuler(&pacrb->akvb->vec, &matRotA);
    LoadRotateMatrixEuler(&pacrb->akvb[pacrb->ckvb - 1].vec, &matRotB);
    CalculateDmat(&matRotA, &matRotB, &dmat);

    float rad;
    VECTOR normal;
    DecomposeRotateMatrixRad(&dmat, &rad, &normal);

    pacrb->fContiguous = (rad < 0.01f);
}

void GetAcrbTimes(ACRB *pacrb, int *pct, float **pat)
{
    GetAkvbTimes(pacrb->ckvb, pacrb->akvb, pct, pat);
}

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcsc__FP4ACSCP3ALOfiP7MATRIX3);

void LoadAcscFromBrx(ACSC *pacsc, CBinaryInputStream *pbis)
{
    LoadApacgFromBrx(pacsc->apacg, &pacsc->vecDefault, pbis);
}

void GetAcscTimes(ACSC *pacsc, int *pct, float **pat)
{
    GetApacgTimes(pacsc->apacg, pct, pat);
}

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcsb__FP4ACSBP3ALOfiP7MATRIX3);

void LoadAcsbFromBrx(ACSB *pacsb, CBinaryInputStream *pbis)
{
    LoadAkvbFromBrx(&pacsb->ckvb, &pacsb->akvb, pbis);
}

void GetAcsbTimes(ACSB *pacsb, int *pct, float **pat)
{
    GetAkvbTimes(pacsb->ckvb, pacsb->akvb, pct, pat);
}

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcpbl__FP5ACPBLP3ALOffiP6VECTORT5);

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcrbl__FP5ACRBLP3ALOffiP7MATRIX3P6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcgblt__FP6ACGBLTP3ALOffiPfT5);

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcgblp__FP6ACGBLPP3ALOffiPfT5);

ACP *PacpNew(ACVK acvk)
{
    ACP *pacp;
    switch (acvk)
    {
        case ACVK_Component:
        {
            pacp = (ACP *)PvAllocSwClearImpl(sizeof(ACPC));
            STRUCT_OFFSET(pacp, 0x00, void *) = &g_vtacpc;
            break;
        }
        case ACVK_Bezier:
        {
            pacp = (ACP *)PvAllocSwClearImpl(sizeof(ACPB));
            STRUCT_OFFSET(pacp, 0x00, void *) = &g_vtacpb;
            break;
        }
        case ACVK_Blend:
        {
            pacp = (ACP *)PvAllocSwClearImpl(sizeof(ACPBL));
            STRUCT_OFFSET(pacp, 0x00, void *) = &g_vtacpbl;
            break;
        }
        default:
        {
            pacp = NULL;
            break;
        }
    }

    if (pacp)
    {
        pacp->acvk = acvk;
    }

    return pacp;
}

ACR *PacrNew(ACVK acvk)
{
    ACR *pacr;
    switch (acvk)
    {
        case ACVK_Component:
        {
            pacr = (ACR *)PvAllocSwClearImpl(sizeof(ACRC));
            STRUCT_OFFSET(pacr, 0x00, void *) = &g_vtacrc;
            break;
        }
        case ACVK_Bezier:
        {
            pacr = (ACR *)PvAllocSwClearImpl(sizeof(ACRB));
            STRUCT_OFFSET(pacr, 0x00, void *) = &g_vtacrb;
            break;
        }
        case ACVK_Blend:
        {
            pacr = (ACR *)PvAllocSwClearImpl(sizeof(ACRBL));
            STRUCT_OFFSET(pacr, 0x00, void *) = &g_vtacrbl;
            break;
        }
        default:
        {
            pacr = NULL;
            break;
        }
    }

    if (pacr)
    {
        pacr->acvk = acvk;
    }

    return pacr;
}

ACS *PacsNew(ACVK acvk)
{
    ACS *pacs;
    switch (acvk)
    {
        case ACVK_Component:
        {
            pacs = (ACS *)PvAllocSwClearImpl(sizeof(ACSC));
            STRUCT_OFFSET(pacs, 0x00, void *) = &g_vtacsc;
            break;
        }
        case ACVK_Bezier:
        {
            pacs = (ACS *)PvAllocSwClearImpl(sizeof(ACSB));
            STRUCT_OFFSET(pacs, 0x00, void *) = &g_vtacsb;
            break;
        }
        default:
        {
            pacs = NULL;
            break;
        }
    }

    if (pacs)
    {
        pacs->acvk = acvk;
    }

    return pacs;
}

ACG *PacgNew(ACGK acgk)
{
    ACG *pacg;

    switch (acgk)
    {
        case ACGK_Bezier:
        {
            pacg = (ACG *)PvAllocSwClearImpl(sizeof(ACGB));
            STRUCT_OFFSET(pacg, 0x00, void *) = &g_vtacgb;
            break;
        }
        case ACGK_BezierWeighted:
        {
            pacg = (ACG *)PvAllocSwClearImpl(sizeof(ACGBW));
            STRUCT_OFFSET(pacg, 0x00, void *) = &g_vtacgbw;
            break;
        }
        case ACGK_BlendTwist:
        {
            pacg = (ACG *)PvAllocSwClearImpl(sizeof(ACGBLT));
            STRUCT_OFFSET(pacg, 0x00, void *) = &g_vtacgblt;
            break;
        }
        case ACGK_BlendPose:
        {
            pacg = (ACG *)PvAllocSwClearImpl(sizeof(ACGBLP));
            STRUCT_OFFSET(pacg, 0x00, void *) = &g_vtacgblp;
            break;
        }
        case ACGK_Linear:
        {
            pacg = (ACG *)PvAllocSwClearImpl(sizeof(ACGL));
            STRUCT_OFFSET(pacg, 0x00, void *) = &g_vtacgl;
            break;
        }
        default:
        {
            pacg = NULL;
            break;
        }
    }

    if (pacg)
    {
        pacg->acgk = acgk;
    }

    return pacg;
}
