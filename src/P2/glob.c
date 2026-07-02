#include <glob.h>
#include <ik.h>
#include <vifs.h>
#include <memory.h>

void BuildGlobsetSaaArray(GLOBSET *pglobset)
{

    void **psaa = (void **)PvAllocSwImpl(STRUCT_OFFSET(pglobset, 0x50, int) * 4);
    STRUCT_OFFSET(pglobset, 0x54, void **) = psaa;

    int iDst = 0;
    for (int i = 0; i < STRUCT_OFFSET(pglobset, 0xc, int); i++)
    {
        void *p = STRUCT_OFFSET((uint8_t *)STRUCT_OFFSET(pglobset, 0x10, uint8_t *) + i * 0x70, 0x38, void *);
        if (p != 0)
            STRUCT_OFFSET(pglobset, 0x54, void **)[iDst++] = p;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/glob", LoadGlobsetFromBrx__FP7GLOBSETP18CBinaryInputStreamP3ALO);

extern char D_18C0;
extern char D_18F8;

void EnsureBuffer(int iBuffer, VIFS *pvifs)
{
    switch (iBuffer)
    {
    case 0:
        pvifs->AddVifMscal(&D_18C0);
        break;
    case 1:
        pvifs->AddVifMscal(&D_18F8);
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/glob", EnsureBufferCel__FiP4VIFS);

INCLUDE_ASM("asm/nonmatchings/P2/glob", BuildSubcel__FP7GLOBSETiP6SUBCELiP7VECTORFiP4TWEFP8SUBPOSEFT4PfP4VIFS);

INCLUDE_ASM("asm/nonmatchings/P2/glob", BuildSubglobSinglePass__FP7GLOBSETP4GLOBiP7SUBGLOBP3SHDP7VECTORFT5P4RGBAP3UVFiP4VTXFP8SUBPOSEFT5T5PfP4VIFSP4SGVR);

INCLUDE_ASM("asm/nonmatchings/P2/glob", BuildSubglobThreeWay__FP7GLOBSETP4GLOBiP7SUBGLOBP3SHDP7VECTORFT5P4RGBAP3UVFiP4VTXFP8SUBPOSEFT5T5PfP4VIFSP4SGVR);

INCLUDE_ASM("asm/nonmatchings/P2/glob", BuildSubglobLighting__FP4GLOBP7SUBGLOBP8SUBGLOBI);

INCLUDE_ASM("asm/nonmatchings/P2/glob", PostGlobsetLoad__FP7GLOBSETP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/glob", BindGlobset__FP7GLOBSETP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/glob", CloneGlobset__FP7GLOBSETP3ALOT0);

INCLUDE_ASM("asm/nonmatchings/P2/glob", CloneGlob__FP7GLOBSETP4GLOBP5GLOBI);

INCLUDE_ASM("asm/nonmatchings/P2/glob", UpdateGlobset__FP7GLOBSETP3ALOf);

void UpdateAloConstraints(ALO *palo)
{
    void *p = STRUCT_OFFSET(palo, 0x224, void *);

    if (p != NULL)
    {
        if (STRUCT_OFFSET(p, 0xb0, int) & 0x10)
        {
            if (STRUCT_OFFSET(p, 0x64, int) != 0)
            {
                SolveAloIK(STRUCT_OFFSET(p, 0x60, ALO *));
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/glob", UpdateAloInfluences__FP3ALOP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/glob", PredrawGlob__FP7GLOBSETP4GLOBP5GLOBIP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/glob", RotateVu1Buffer__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/glob", DrawGlob__FP3RPL);

INCLUDE_ASM("asm/nonmatchings/P2/glob", glob__static_initialization_and_destruction_0);

INCLUDE_ASM("asm/nonmatchings/P2/glob", _GLOBAL_$I$g_dro);
