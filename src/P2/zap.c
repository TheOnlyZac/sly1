#include <zap.h>
#include <memory.h>
#include <po.h>

void InitTzp(TZP *ptzp)
{
    InitSo(ptzp);
    InitZpd(&STRUCT_OFFSET(ptzp, 0x550, ZPD), ptzp);
    STRUCT_OFFSET(ptzp, 0x4e0, ZOK) = ZOK_Zap;
    STRUCT_OFFSET(ptzp, 0x538, ulong) &= 0xffffff0fffffffff; // ptzp->bspcCamera.absp
    STRUCT_OFFSET(ptzp, 0x538, ulong) |= 0x2000000000;
}

void PostTzpLoad(TZP *ptzp)
{
    PostAloLoad(ptzp);
    PostZpdLoad(&STRUCT_OFFSET(ptzp, 0x550, ZPD)); // ptzp->zpd
}

INCLUDE_ASM("asm/nonmatchings/P2/zap", UpdateTzp__FP3TZPf);

void CloneTzp(TZP *ptzp, TZP *ptzpBase)
{
    CloneSo(ptzp, ptzpBase);
    STRUCT_OFFSET(ptzp, 0x550, ZPD).pso = ptzp; // ptzp->zpd
}

void RenderTzpAll(TZP *ptzp, CM *pcm, RO *pro)
{
    RenderAloAll(ptzp, pcm, pro);
}

int FInflictTzpZap(TZP *ptzp, XP *pxp, ZPR *pzpr)
{
    InflictZpdZap(&STRUCT_OFFSET(ptzp, 0x550, ZPD), pxp, pzpr); // ptzp->zpd
    return 1;
}

ZPD *PzpdEnsureTzp(TZP *ptzp, ENSK ensk)
{
    return &STRUCT_OFFSET(ptzp, 0x550, ZPD); // ptzp->zpd
}

/**
 * @todo Rename function and figure out what does it actually do.
 */
void FUN_001F5210(TZP *ptzp)
{
    STRUCT_OFFSET(ptzp, 0x5e4, int) = 0;
}

void InitVolzp(VOLZP *pvolzp)
{
    InitTzp(pvolzp);
    STRUCT_OFFSET(pvolzp, 0x538, ulong) |= 0x80000000000; // ptzp->bspcCamera.absp
    SetSoConstraints(pvolzp, CT_Locked, (VECTOR *)nullptr, CT_Locked, (VECTOR *)nullptr);
}

INCLUDE_ASM("asm/nonmatchings/P2/zap", UpdateVolzp__FP5VOLZPf);

void InitZpd(ZPD *pzpd, SO *pso)
{
    pzpd->pso = pso;
    pzpd->zpk = ZPK_Blunt;
    pzpd->dzThrow = 150.0f;
}

INCLUDE_ASM("asm/nonmatchings/P2/zap", PostZpdLoad__FP3ZPD);

INCLUDE_ASM("asm/nonmatchings/P2/zap", ApplyZpdThrow__FP3ZPDP2PO);

void InflictZpdZap(ZPD *pzpd, XP *pxp, ZPR *pzpr)
{
    PpoCur();
    pzpr->zpk = pzpd->zpk;
    pzpr->pv = pzpd;
    pzpr->pfnzap = ApplyZpdThrow;
    HandleLoSpliceEvent(pzpd->pso, 2, 0, (void **)nullptr);
}

void AddZpdZapObject(ZPD *pzpd, OID oid)
{
    if ((uint)pzpd->coidThrow >= 32)
        return;

    pzpd->aoidThrow[pzpd->coidThrow++] = oid;
}

void AddZpdZapLo(ZPD *pzpd, LO *plo)
{
    if ((uint)pzpd->cploThrow >= 32)
        return;

    // TODO: Figure out the CIDs.
    if (!FIsBasicDerivedFrom(plo, (CID)0x7e) && !FIsBasicDerivedFrom(plo, (CID)0x6e) &&
        !FIsBasicDerivedFrom(plo, (CID)0x76) && !FIsBasicDerivedFrom(plo, (CID)0x70) &&
        !FIsBasicDerivedFrom(plo, (CID)0x71) && !FIsBasicDerivedFrom(plo, (CID)0x81))
        return;

    pzpd->aploThrow[pzpd->cploThrow++] = plo;
}

/**
 * @brief 85.69% match.
 * https://decomp.me/scratch/oApAh
 */
INCLUDE_ASM("asm/nonmatchings/P2/zap", RemoveZpdZapLo__FP3ZPDP2LO);
#ifdef SKIP_ASM
void RemoveZpdZapLo(ZPD *pzpd, LO *plo)
{
    int cploThrow = pzpd->cploThrow;
    if (cploThrow <= 0)
        return;
    
    int i = 0;
    if (pzpd->aploThrow[i] != plo)
    {
        while (i < cploThrow && pzpd->aploThrow[i] != plo)
        {
            i++;
        }
    }

    if (i < cploThrow)
    {
        // I think this should be copying from pzpd->aploThrow[i] to pzpd->aploThrow[i + 1]?
        CopyAb(&pzpd->aploThrow[i], &pzpd->aploThrow[i], (cploThrow - i - 1) * sizeof(*pzpd->aploThrow));
        pzpd->cploThrow--;
    }
}
#endif // SKIP_ASM
