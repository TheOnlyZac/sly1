#include <jlo.h>
#include <mat.h>

extern JLO *g_pjloCur;
extern VECTOR g_normalZ; // TODO: This should be elsewhere.

void InitJlo(JLO *pjlo)
{
    InitSo(pjlo);
    STRUCT_OFFSET(pjlo, 0x578, JLOS) = JLOS_Nil; // pjlo->jlos
    STRUCT_OFFSET(pjlo, 0x598, OID) = OID_Nil; // pjlo->oidJlovolStart
    STRUCT_OFFSET(pjlo, 0x5c4, float) = 3000.0f;
    STRUCT_OFFSET(pjlo, 0x5c8, float) = 1000.0f;

    InitDl(&STRUCT_OFFSET(pjlo, 0x55c, DL), 0x7b0); // pjlo->dlJlovol

    SMP *psmp = &STRUCT_OFFSET(pjlo, 0x5b0, SMP);
    STRUCT_OFFSET(psmp, 0x00, float) = 25.0f; // pjlo->smpSpin.ag[0]
    STRUCT_OFFSET(psmp, 0x04, float) = 0.0f; // pjlo->smpSpin.svSlow
    STRUCT_OFFSET(psmp, 0x08, float) = 0.25f; // pjlo->smpSpin.dtFast

    g_pjloCur = (JLO *)nullptr;
}

INCLUDE_ASM("asm/nonmatchings/P2/jlo", LoadJloFromBrx__FP3JLOP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", PostJloLoad__FP3JLO);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", FUN_0016d040);

void PresetJloAccel(JLO *pjlo, float dt)
{
    PresetSoAccel(pjlo, dt);
    if (STRUCT_OFFSET(pjlo, 0x5d8, int) == 0)
    {
        MATRIX3 matTarget;
        LoadRotateMatrixRad(STRUCT_OFFSET(pjlo, 0x5a0, float), &g_normalZ, &matTarget);
        AccelSoTowardMatSmooth(pjlo, dt, &matTarget, &STRUCT_OFFSET(pjlo, 0x5b0, SMP));
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/jlo", UpdateJlo__FP3JLOf);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", JlosNextJlo__FP3JLO);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", SetJloJlovol__FP3JLOP6JLOVOL);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", FireJlo__FP3JLO);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", LandJlo__FP3JLO);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", JumpJlo__FP3JLO);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", FUN_0016d928);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", FUN_0016d9a8);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", HandleJloMessage__FP3JLO5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", SetJloJlos__FP3JLO4JLOS);

void ActivateJlo(JLO *pjlo)
{
    g_pjloCur = pjlo;
}

void DeactivateJlo(JLO *pjlo)
{
    g_pjloCur = (JLO *)nullptr;
}

INCLUDE_ASM("asm/nonmatchings/P2/jlo", InitJloc__FP4JLOC);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", LoadJlocFromBrx__FP4JLOCP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", PostJlocLoad__FP4JLOC);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", PxfmChooseJloc__FP4JLOC);

void InitJlovol(JLOVOL *pjlovol)
{
    InitVolbtn(pjlovol);
    STRUCT_OFFSET(pjlovol, 0x7a0, OID) = OID_Nil; // pjlovol->oidJloc
    STRUCT_OFFSET(pjlovol, 0x7a8, OID) = OID_Nil; // pjlovol->oidLand
    STRUCT_OFFSET(pjlovol, 0x6e8, float) = 0.0f; // pjlovol->btn.dtRepush
}

INCLUDE_ASM("asm/nonmatchings/P2/jlo", BindJlovol__FP6JLOVOL);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", HandleJlovolMessage__FP6JLOVOL5MSGIDPv);
