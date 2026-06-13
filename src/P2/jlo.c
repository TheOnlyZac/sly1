#include <jlo.h>
#include <mat.h>
#include <find.h>
#include <pnt.h>
#include <rwm.h>

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

    g_pjloCur = NULL;
}

INCLUDE_ASM("asm/nonmatchings/P2/jlo", LoadJloFromBrx__FP3JLOP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", PostJloLoad__FP3JLO);

extern "C" {
void FUN_0016d040(JLO *pjlo, OID oid)
{
    JLOVOL *pjlovol;

    STRUCT_OFFSET(pjlo, 0x578, OID) = oid;
    pjlovol = (JLOVOL *)PloFindSwNearest(pjlo->psw, oid, pjlo);
    if (pjlovol != NULL)
    {
        SetJloJlovol(pjlo, pjlovol);
        LandJlo(pjlo);
        if (STRUCT_OFFSET(pjlovol, 0x7AC, int) != 0)
            SetJloJlos(pjlo, JLOS_Idle);
        else
            SetJloJlos(pjlo, JLOS_Taunt);
    }
}
}

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

EXC *PexcSetExcitement(int gexc);
void UnsetExcitementHyst(EXC *pexc);

void SetJloJlovol(JLO *pjlo, JLOVOL *pjlovol)
{
    if (pjlovol == STRUCT_OFFSET(pjlo, 0x558, JLOVOL *))
        return;

    void *p3 = NULL;
    if (pjlovol != NULL)
        p3 = STRUCT_OFFSET(pjlovol, 0x7AC, void *);

    if (p3 != STRUCT_OFFSET(pjlo, 0x5D0, void *))
    {
        STRUCT_OFFSET(pjlo, 0x5D0, void *) = p3;
        STRUCT_OFFSET(pjlo, 0x5D4, int) = 3;
    }

    STRUCT_OFFSET(pjlo, 0x558, JLOVOL *) = pjlovol;

    if (p3 != NULL)
    {
        RWM *prwm = STRUCT_OFFSET(pjlo, 0x570, RWM *);
        STRUCT_OFFSET(prwm, 0x44, int) = STRUCT_OFFSET(STRUCT_OFFSET(pjlovol, 0x7AC, void *), 0x318, int);
        ReloadRwm(STRUCT_OFFSET(pjlo, 0x570, RWM *));
        if (STRUCT_OFFSET(pjlo, 0x5BC, EXC *) == NULL)
            STRUCT_OFFSET(pjlo, 0x5BC, EXC *) = PexcSetExcitement(0x6B);
    }
    else
    {
        if (STRUCT_OFFSET(pjlo, 0x5BC, EXC *) != NULL)
        {
            UnsetExcitementHyst(STRUCT_OFFSET(pjlo, 0x5BC, EXC *));
            STRUCT_OFFSET(pjlo, 0x5BC, EXC *) = NULL;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/jlo", FireJlo__FP3JLO);

void LandJlo(JLO *pjlo)
{
    extern VECTOR D_00248D30;
    VECTOR pos;

    SetSoConstraints(pjlo, CT_Locked, NULL, CT_Locked, NULL);
    (*(void (**)(ALO *, VECTOR *))(*(uint8_t **)pjlo + 0x90))(pjlo, &D_00248D30);
    (*(void (**)(ALO *, VECTOR *))(*(uint8_t **)pjlo + 0x94))(pjlo, &D_00248D30);
    GetPntPos(STRUCT_OFFSET(STRUCT_OFFSET(pjlo, 0x558, void *), 0x7A4, PNT *), &pos);
    pos.z += STRUCT_OFFSET(pjlo, 0x56C, float);
    (*(void (**)(ALO *, VECTOR *))(*(uint8_t **)pjlo + 0x84))(pjlo, &pos);
}

INCLUDE_ASM("asm/nonmatchings/P2/jlo", JumpJlo__FP3JLO);

extern "C" void PreloadVag1(void *pv);
extern char D_002482D8[];

extern "C" void FUN_0016d928(JLO *pjlo)
{
    if (STRUCT_OFFSET(pjlo, 0x5c0, int) != 0)
    {
        if (!FVagPlaying())
        {
            if (NRandInRange(0, 100) < 20)
            {
                int n = NRandInRange(0, 6);
                PreloadVag1(&D_002482D8[n << 5]);
                STRUCT_OFFSET(pjlo, 0x5cc, int) = 1;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/jlo", FUN_0016d9a8);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", HandleJloMessage__FP3JLO5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/jlo", SetJloJlos__FP3JLO4JLOS);

void ActivateJlo(JLO *pjlo)
{
    g_pjloCur = pjlo;
}

void DeactivateJlo(JLO *pjlo)
{
    g_pjloCur = NULL;
}

void InitJloc(JLOC *pjloc)
{
    InitAlo(pjloc);
    STRUCT_OFFSET(pjloc, 0x31C, float) = 2.25f;
    STRUCT_OFFSET(pjloc, 0x320, float) = 2.0f;
    STRUCT_OFFSET(pjloc, 0x324, float) = 0.8f;
    STRUCT_OFFSET(pjloc, 0x328, float) = 4.0f;
    STRUCT_OFFSET(pjloc, 0x32C, float) = 0.5f;
    STRUCT_OFFSET(pjloc, 0x330, float) = 1000.0f;
    STRUCT_OFFSET(pjloc, 0x334, float) = 2000.0f;
}

void LoadJlocFromBrx(JLOC *pjloc, CBinaryInputStream *pbis)
{
    LoadAloFromBrx(pjloc, pbis);

    uint cplo = CploFindSwObjectsByClass(pjloc->psw, FSO_FindChild | FSO_ReturnActualCount, (CID)0x73, pjloc, 0x10, &STRUCT_OFFSET(pjloc, 0x2D0, LO *));
    STRUCT_OFFSET(pjloc, 0x310, uint) = cplo;
    if (cplo > 0x10)
        STRUCT_OFFSET(pjloc, 0x310, uint) = 0x10;
}

void PostJlocLoad(JLOC *pjloc)
{
    PostAloLoad(pjloc);
    pjloc->pvtlo->pfnRemoveLo(pjloc);
}

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
