#include <aseg.h>
#include <asega.h>

void StartupAseg()
{
    return;
}

INCLUDE_ASM("asm/nonmatchings/P2/aseg", InitAseg__FP4ASEG);

INCLUDE_ASM("asm/nonmatchings/P2/aseg", LoadAsegFromBrx__FP4ASEGP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/aseg", LoadAsegEventsFromBrx__FP4ASEGP18CBinaryInputStreamiPiPP2EA);

void CloneAseg(ASEG *paseg, LO *ploBase)
{
    CloneLo(paseg, ploBase);
}

INCLUDE_ASM("asm/nonmatchings/P2/aseg", PostAsegLoad__FP4ASEG);

INCLUDE_ASM("asm/nonmatchings/P2/aseg", PostAsegLoadCallback__FP4ASEG5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/aseg", ApplyAsegOvr__FP4ASEGP3ALOiP3OVRffiPP5ASEGA);

void ApplyAseg(ASEG *paseg, ALO *paloAsegRoot, float tLocal, float svtLocal, GRFAPL grfapl, ASEGA **ppasega)
{
    ApplyAsegOvr(paseg, paloAsegRoot, 0, (OVR *)nullptr, tLocal, svtLocal, grfapl, ppasega);
}

ASEGA *PasegaApplyAseg(ASEG *paseg, ALO *paloAsegRoot, float tLocal, float svtLocal, GRFAPL grfapl)
{
    ASEGA *pasega;
    ApplyAsegOvr(paseg, paloAsegRoot, 0, (OVR *)nullptr, tLocal, svtLocal, grfapl, &pasega);
    return pasega;
}

INCLUDE_ASM("asm/nonmatchings/P2/aseg", PasegaFindAseg__FP4ASEGP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/aseg", EnsureAseg__FP4ASEGP3ALO4SEEKffiPP5ASEGA);

ASEGA *PasegaEnsureAseg(ASEG *paseg, ALO *paloRoot, SEEK seek, float t, float svt, GRFAPL grfapl)
{
    ASEGA *pasega;
    EnsureAseg(paseg, paloRoot, seek, t, svt, grfapl, &pasega);
    return pasega;
}

void ApplyAsegCur(ASEG *paseg, ALO *paloRoot, float t, float svt, GRFAPL grfapl, ASEGA **ppasega)
{
    if (*ppasega)
    {
        RetractAsega(*ppasega);
        *ppasega = (ASEGA *)nullptr;
    }
    if (paseg)
    {
        ApplyAseg(paseg, paloRoot, t, svt, grfapl, ppasega);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/aseg", FWipingAseg__FP4ASEG);

INCLUDE_ASM("asm/nonmatchings/P2/aseg", FindAsegClosestPoint__FP4ASEGP3ALOP6VECTORfPfT2T2);

INCLUDE_ASM("asm/nonmatchings/P2/aseg", PeaFindAsegLabel__FP4ASEG3OID);

float TFindAsegLabel(ASEG *paseg, OID oidLabel)
{
    EA *pea = PeaFindAsegLabel(paseg, oidLabel);
    if (pea)
    {
        return pea->tLocal;
    }

    return 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/P2/aseg", PchnFindAseg__FP4ASEGP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/aseg", PredictAsegEffect__FP4ASEGffP3ALOT3iP6VECTORP7MATRIX3T6T6);

INCLUDE_ASM("asm/nonmatchings/P2/aseg", GetAsegWaypoints__FP4ASEGP3ALOPiPPP8WAYPOINT);

INCLUDE_ASM("asm/nonmatchings/P2/aseg", StripAsegChn__FP4ASEGP3CHN);

void StripAsegAlo(ASEG *aseg, ALO *alo)
{
    if (aseg->pchnStrip)
    {
        return;
    }

    CHN *chn = PchnFindAseg(aseg, alo);
    if (chn)
    {
        StripAsegChn(aseg, chn);
    }
}

void LoadAsegblFromBrx(ASEGBL *pasegbl, CBinaryInputStream *pbis)
{
    return;
}

void PostAsegblLoad(ASEGBL *pasegbl)
{
    return;
}

void CloneAsegbl(ASEGBL *pasegbl, LO *ploBase)
{
    return;
}
