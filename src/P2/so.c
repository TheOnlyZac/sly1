#include <so.h>
#include <bbmark.h>

INCLUDE_ASM("asm/nonmatchings/P2/so", InitSo__FP2SO);

void OnSoAdd(SO *pso)
{
    SW *psw = pso->psw;
    void (*pfn)(SO *);

    psw->cpsoAll = psw->cpsoAll + 1;
    if (pso->paloParent == NULL)
    {
        AddSwAaobrObject(psw, pso);
        STRUCT_OFFSET(pso, 0x480, OXA *) = PoxaAllocSw(psw, pso);
        RecalcSwOxfFilterForObject(psw, pso);
        psw->cpsoRoot = psw->cpsoRoot + 1;
        AppendDlEntry(&psw->dlRoot, pso);
    }
    OnAloAdd(pso);
    EnableSoPhys(pso, 1);
    pfn = (void (*)(SO *))STRUCT_OFFSET(STRUCT_OFFSET(pso, 0x0, void *), 0x120, void *);
    pfn(pso);
    if ((STRUCT_OFFSET(pso, 0x538, uint64_t) & ((uint64_t)0x8000 << 39)) == 0) // locked, bit 54
    {
        RecalcSoLocked(STRUCT_OFFSET(pso, 0x50, SO *));
    }
    else
    {
        RecalcSoLocked(pso);
    }
    RebuildSoPhysHook(pso);
}

// NOTE: This body per-symbol matches (match.sh), but enabling it trips an
// asm-emission bug in the build: the still-INCLUDE_ASM TranslateSoToPosSafe
// gets emitted 0x14 bytes too large (zero-filled words after its vadd.xyzw),
// shifting the unit and failing the checksum. Keep it wrapped until the
// surrounding functions are decompiled or the tooling quirk is fixed.
INCLUDE_ASM("asm/nonmatchings/P2/so", OnSoRemove__FP2SO);
#ifdef SKIP_ASM
void OnSoRemove(SO *pso)
{
    SW *psw = pso->psw;
    SO *psoRoot = STRUCT_OFFSET(pso, 0x50, SO *);

    EnableSoPhys(pso, 0);
    OnAloRemove(pso);
    psw->cpsoAll = psw->cpsoAll - 1;
    if (pso->paloParent == NULL)
    {
        RemoveSwAaobrObject(psw, pso);
        FreeSwPoxa(psw, STRUCT_OFFSET(pso, 0x480, OXA *));
        psw->cpsoRoot = psw->cpsoRoot - 1;
        RemoveDlEntry(&psw->dlRoot, pso);
    }
    FreeSwStsoList(psw, STRUCT_OFFSET(pso, 0x540, STSO *));
    STRUCT_OFFSET(pso, 0x540, STSO *) = NULL; // pstsoFirst
    if ((STRUCT_OFFSET(pso, 0x538, uint64_t) & ((uint64_t)0x8000 << 39)) == 0) // locked, bit 54
    {
        if (psoRoot != pso)
        {
            RecalcSoLocked(psoRoot);
        }
    }
}
#endif

void EnableSoPhys(SO *pso, int fPhys)
{
    uint64_t grfso;
    SO *psoRoot;
    void (*pfn)(SO *);

    if (fPhys == ((STRUCT_OFFSET(pso, 0x538, uint64_t) >> 50) & 1))
    {
        return;
    }
    if (fPhys)
    {
        // append to the hierarchy root's dlPhys (root SO* at 0x50, DL at 0x2D8)
        AppendDlEntry(&STRUCT_OFFSET(STRUCT_OFFSET(pso, 0x50, SO *), 0x2D8, DL), pso);
    }
    else
    {
        RemoveDlEntry(&STRUCT_OFFSET(STRUCT_OFFSET(pso, 0x50, SO *), 0x2D8, DL), pso);
    }
    grfso = STRUCT_OFFSET(pso, 0x538, uint64_t);
    grfso &= ~((uint64_t)1 << 50); // fPhys, grfso bit 50
    grfso |= (uint64_t)(fPhys & 1) << 50;
    STRUCT_OFFSET(pso, 0x538, uint64_t) = grfso;
    InvalidateSwXpForObject(pso->psw, pso, 7);
    psoRoot = STRUCT_OFFSET(pso, 0x50, SO *);
    pfn = (void (*)(SO *))STRUCT_OFFSET(STRUCT_OFFSET(psoRoot, 0x0, void *), 0xD8, void *);
    pfn(psoRoot);
}

INCLUDE_ASM("asm/nonmatchings/P2/so", DisplaceSo__FP2SOi);

INCLUDE_ASM("asm/nonmatchings/P2/so", ImpactSo__FP2SOi);

INCLUDE_ASM("asm/nonmatchings/P2/so", PivotSo__FP2SOi);

INCLUDE_ASM("asm/nonmatchings/P2/so", ExtendSoBounds__FP2SOP6VECTORf);

INCLUDE_ASM("asm/nonmatchings/P2/so", UpdateSoBounds__FP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/so", UpdateGeomWorld__FP4GEOMT0G9VU_VECTORP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/so", UpdateSoXfWorldHierarchy__FP2SO);

// alo.h declares the literal identifier `UpdateAloXfWorld__FP3ALO`, which both
// double-mangles if called and poisons the plain name `UpdateAloXfWorld` for
// GCC 2.95; bind a local alias to the real mangled symbol instead.
extern void _UpdateAloXfWorld(ALO *palo) __asm__("UpdateAloXfWorld__FP3ALO");

void UpdateSoXfWorld(SO *pso)
{
    SO *psoRoot;
    void (*pfn)(SO *);

    _UpdateAloXfWorld(pso);
    psoRoot = STRUCT_OFFSET(pso, 0x50, SO *); // paloRoot
    pfn = (void (*)(SO *))STRUCT_OFFSET(STRUCT_OFFSET(psoRoot, 0x0, void *), 0xD8, void *);
    pfn(psoRoot);
    InvalidateSwXpForObject(pso->psw, pso, 7);
    InvalidateSwAaox(pso->psw);
}

INCLUDE_ASM("asm/nonmatchings/P2/so", FIgnoreSoIntersection__FP2SOT0);

INCLUDE_ASM("asm/nonmatchings/P2/so", UpdateSoImpacts__FP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/so", UProjectVector__FP6VECTORN20);

INCLUDE_ASM("asm/nonmatchings/P2/so", AdjustSoXpLocal__FP2SOP2XPi);

JUNK_WORD(0xF8C10000);

INCLUDE_ASM("asm/nonmatchings/P2/so", CalculateSoAngularEffectWorld__FP2SOP6VECTORT1);

INCLUDE_ASM("asm/nonmatchings/P2/so", AccelSoTowardPosSpring__FP2SOP6VECTORP3CLQT1T2f);

INCLUDE_ASM("asm/nonmatchings/P2/so", AccelSoTowardMatSpring__FP2SOP7MATRIX3P3CLQP6VECTORT2f);

INCLUDE_ASM("asm/nonmatchings/P2/so", PresetSoAccel__FP2SOf);

INCLUDE_ASM("asm/nonmatchings/P2/so", RenderSoSelf__FP2SOP2CMP2RO);

void UpdateSo(SO *pso, float dt)
{
    UpdateAlo(pso, dt);
}

void SetSoMass(SO *pso, float mass)
{
    float oldMass = STRUCT_OFFSET(pso, 0x368, float); // pso->mass
    float massRatio = mass / oldMass;

    // Redundant multiplication needed for match ¯\_(ツ)_/¯
    float newMass = oldMass * massRatio;

    STRUCT_OFFSET(pso, 0x368, float) = newMass; // Should be pso->mass = mass
    // Technically newMass != mass due to floating point precision errors

    AdjustSoMomint(pso, massRatio);
}

INCLUDE_ASM("asm/nonmatchings/P2/so", AdjustSoMomint__FP2SOf);

INCLUDE_ASM("asm/nonmatchings/P2/so", DiscardSoXps__FP2SO);

void UpdateSoPosWorldPrev(SO *pso)
{
    // posWorldPrev (0x370) = xf.posWorld (0x140)
    STRUCT_OFFSET(pso, 0x370, qword) = STRUCT_OFFSET(pso, 0x140, qword);
}

INCLUDE_ASM("asm/nonmatchings/P2/so", TranslateSoToPos__FP2SOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/so", RotateSoToMat__FP2SOP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/so", TranslateSoToPosSafe__FP2SOP6VECTORT1);

JUNK_ADDIU(40);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoVelocityVec__FP2SOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoAngularVelocityVec__FP2SOP6VECTOR);

JUNK_ADDIU(20);

INCLUDE_ASM("asm/nonmatchings/P2/so", AddSoAcceleration__FP2SOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/so", AddSoAngularAcceleration__FP2SOP6VECTOR);

void SetSoConstraints(SO *pso, CT ctForce, VECTOR *pnormalForce, CT ctTorque, VECTOR *pnormalTorque)
{
    SO *psoRoot;
    uint64_t fWasLocked;

    STRUCT_OFFSET(pso, 0x450, CT) = ctForce; // constrForce.ct
    fWasLocked = (STRUCT_OFFSET(pso, 0x538, uint64_t) >> 54) & 1;
    if (pnormalForce != NULL)
    {
        STRUCT_OFFSET(pso, 0x440, VU_VECTOR) = *(VU_VECTOR *)pnormalForce;
    }
    STRUCT_OFFSET(pso, 0x470, CT) = ctTorque; // constrTorque.ct
    if (pnormalTorque != NULL)
    {
        STRUCT_OFFSET(pso, 0x460, VU_VECTOR) = *(VU_VECTOR *)pnormalTorque;
    }
    psoRoot = STRUCT_OFFSET(pso, 0x50, SO *);
    if (psoRoot != NULL)
    {
        int fLocked = 0;
        if (ctForce == CT_Locked)
        {
            fLocked = ctTorque == CT_Locked;
        }
        if (fWasLocked != fLocked)
        {
            RecalcSoLocked(psoRoot);
        }
    }
}

void SetSoParent(SO *pso, ALO *paloParent)
{
    VECTOR vecForce;
    VECTOR vecTorque;
    SO *psoRootOld;
    SO *psoRoot;

    if (pso->paloParent == paloParent)
    {
        return;
    }
    psoRootOld = STRUCT_OFFSET(pso, 0x50, SO *);
    // carry the constraint normals (world space) across the reparent
    ConvertAloVec(pso->paloParent, NULL, (VECTOR *)&STRUCT_OFFSET(pso, 0x440, VU_VECTOR), &vecForce);
    ConvertAloVec(pso->paloParent, NULL, (VECTOR *)&STRUCT_OFFSET(pso, 0x460, VU_VECTOR), &vecTorque);
    SetAloParent(pso, paloParent);
    ConvertAloVec(NULL, paloParent, &vecForce, (VECTOR *)&STRUCT_OFFSET(pso, 0x440, VU_VECTOR));
    ConvertAloVec(NULL, paloParent, &vecTorque, (VECTOR *)&STRUCT_OFFSET(pso, 0x460, VU_VECTOR));
    if (STRUCT_OFFSET(pso, 0x50, SO *) != NULL)
    {
        if (STRUCT_OFFSET(pso, 0x538, uint64_t) & ((uint64_t)0x8000 << 39)) // locked, bit 54
        {
            if (psoRootOld != NULL)
            {
                RecalcSoLocked(psoRootOld);
            }
        }
        psoRoot = STRUCT_OFFSET(pso, 0x50, SO *);
        if (STRUCT_OFFSET(psoRoot, 0x538, uint64_t) & ((uint64_t)0x8000 << 40)) // hierarchy locked, bit 55
        {
            RecalcSoLocked(psoRoot);
        }
        else
        {
            RecalcSoLocked(pso);
        }
    }
    RebuildSoPhysHook(pso);
}

INCLUDE_ASM("asm/nonmatchings/P2/so", ApplySoProxy__FP2SOP5PROXY);

JUNK_WORD(0x27BD0150);

INCLUDE_ASM("asm/nonmatchings/P2/so", AccelSoTowardMatSmooth__FP2SOfP7MATRIX3P3SMP);

JUNK_WORD(0x27BD01C0);

INCLUDE_ASM("asm/nonmatchings/P2/so", GetSoCpdefi__FP2SOfP6CPDEFI);

INCLUDE_ASM("asm/nonmatchings/P2/so", FIsSoTouching__FP2SOT0);

INCLUDE_ASM("asm/nonmatchings/P2/so", PsoFirstSoTouching__FP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/so", CloneSo__FP2SOT0);

INCLUDE_ASM("asm/nonmatchings/P2/so", ApplySoConstraintWorld__FP2SOP6CONSTRP6VECTORN22);

INCLUDE_ASM("asm/nonmatchings/P2/so", ApplyConstr__FP6CONSTRP6VECTORN21);

void ApplySoConstraintLocal(SO *pso, CONSTR *pconstr, VECTOR *pvecLocal, VECTOR *pvecConstr, VECTOR *pvecRemain)
{
    ApplyConstr(pconstr, pvecLocal, pvecConstr, pvecRemain);
}

void AddSoXa(SO *pso, XA *pxaAdd)
{
    STRUCT_OFFSET(pxaAdd, 0x8, XA *) = STRUCT_OFFSET(pso, 0x4B0, XA *); // pxaNext
    STRUCT_OFFSET(pso, 0x4B0, XA *) = pxaAdd;                           // pxaFirst
    ResolveAlo(pso);
}

void RemoveSoXa(SO *pso, XA *pxaRemove)
{
    XA **ppxa = &STRUCT_OFFSET(pso, 0x4B0, XA *); // &pxaFirst
    XA *pxa = STRUCT_OFFSET(pso, 0x4B0, XA *);
    if (pxa != NULL)
    {
        if (pxa == pxaRemove)
        {
            STRUCT_OFFSET(pso, 0x4B0, XA *) = STRUCT_OFFSET(pxaRemove, 0x8, XA *);
        }
        else
        {
            for (;;)
            {
                XA *pxaCur = *ppxa;
                XA *pxaNext = STRUCT_OFFSET(pxaCur, 0x8, XA *);
                ppxa = &STRUCT_OFFSET(pxaCur, 0x8, XA *);
                if (pxaNext == NULL)
                {
                    goto LDone;
                }
                if (pxaNext == pxaRemove)
                {
                    STRUCT_OFFSET(pxaCur, 0x8, XA *) = STRUCT_OFFSET(pxaRemove, 0x8, XA *);
                    break;
                }
            }
        }
        STRUCT_OFFSET(pxaRemove, 0x8, XA *) = NULL;
    }
LDone:
    ResolveAlo(pso);
}

INCLUDE_ASM("asm/nonmatchings/P2/so", AddSoWaterAcceleration__FP2SOP5WATERf);

void AddSoExternalAccelerations(SO *pso, XA *pxa, float dt)
{
    return;
}

INCLUDE_ASM("asm/nonmatchings/P2/so", LoadSoFromBrx__FP2SOP18CBinaryInputStream);

void SetSoSphere(SO *pso, float sRadius)
{
    uint64_t grfso = STRUCT_OFFSET(pso, 0x538, uint64_t);
    STRUCT_OFFSET(pso, 0x3CC, float) = sRadius;
    STRUCT_OFFSET(pso, 0x538, uint64_t) = grfso | 0x10000000000;
}

void SetSoNoInteract(SO *pso, int fNoInteract)
{
    SetSoConstraints(pso, CT_Locked, NULL, CT_Locked, NULL);
}

struct CNSTRE
{
    VECTOR *pnormal;
    CT ct;
};
extern CNSTRE D_002746E0[]; // s_acnstre: CNSTR -> (ct, normal) table

void ConstrFromCnstr(CNSTR cnstr, CT *pct, VECTOR *pnormal)
{
    *pct = D_002746E0[cnstr].ct;
    *(qword *)pnormal = *(qword *)D_002746E0[cnstr].pnormal;
}

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoCnstrForce__FP2SO5CNSTR);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoCnstrTorque__FP2SO5CNSTR);

void SetSoCameraStyle(SO *pso, CMK cmk)
{
    uint64_t grfso = STRUCT_OFFSET(pso, 0x538, uint64_t);
    grfso &= ~((uint64_t)0xF << 32); // cmk field, grfso bits 32..35
    grfso |= (uint64_t)(cmk & 0xF) << 32;
    STRUCT_OFFSET(pso, 0x538, uint64_t) = grfso;
}

void SetSoIgnoreLocked(SO *pso, int fIgnoreLocked)
{
    uint64_t grfso = STRUCT_OFFSET(pso, 0x538, uint64_t);
    grfso &= ~((uint64_t)1 << 47); // fIgnoreLocked, grfso bit 47
    grfso |= (uint64_t)(fIgnoreLocked & 1) << 47;
    STRUCT_OFFSET(pso, 0x538, uint64_t) = grfso;
}

void SetSoIceable(SO *pso, int fIceable)
{
    uint64_t grfso = STRUCT_OFFSET(pso, 0x538, uint64_t);
    grfso &= ~((uint64_t)1 << 48); // fIceable, grfso bit 48
    grfso |= (uint64_t)(fIceable & 1) << 48;
    STRUCT_OFFSET(pso, 0x538, uint64_t) = grfso;
}

void SetSoMtlk(SO *pso, MTLK mtlk)
{
    STRUCT_OFFSET(pso, 0x2c8, char) = mtlk;
}

void SetSoEdgeGrab(SO *pso, EGK egk)
{
    uint64_t grfso = STRUCT_OFFSET(pso, 0x538, uint64_t);
    grfso &= ~((uint64_t)0xF0 << 32); // egk field, grfso bits 36..39
    grfso |= (uint64_t)(egk & 0xF) << 36;
    STRUCT_OFFSET(pso, 0x538, uint64_t) = grfso;
}

void SendSoMessage(SO *pso, MSGID msgid, void *pv)
{
    XA *pxa;

    SendLoMessage(pso, msgid, pv);
    pxa = STRUCT_OFFSET(pso, 0x4B0, XA *); // pxaFirst
    while (pxa != NULL)
    {
        SO *psoTarget = STRUCT_OFFSET(pxa, 0x0, SO *);
        XA *pxaNext = STRUCT_OFFSET(pxa, 0x8, XA *);
        if (psoTarget != pso)
        {
            // virtual HandleMessage at vtable +0x44
            void (*pfn)(SO *, MSGID, void *) =
                (void (*)(SO *, MSGID, void *))STRUCT_OFFSET(STRUCT_OFFSET(psoTarget, 0x0, void *), 0x44, void *);
            if (pfn != NULL)
            {
                pfn(psoTarget, msgid, pv);
            }
        }
        pxa = pxaNext;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/so", PxpFindSoGround__FP2SOT0Pi);

void SetSoNoGravity(SO *pso, int fNoGravity)
{
    uint64_t grfso = STRUCT_OFFSET(pso, 0x538, uint64_t);
    grfso &= ~((uint64_t)1 << 51); // fNoGravity, grfso bit 51
    grfso |= (uint64_t)(fNoGravity & 1) << 51;
    STRUCT_OFFSET(pso, 0x538, uint64_t) = grfso;
}

void SetSoNoXpsAll(SO *pso, int fNoXps)
{
    uint64_t bit = (uint64_t)(fNoXps & 1) << 42; // fNoXpsAll, grfso bit 42
    uint64_t mask = ~((uint64_t)1 << 42);
    uint64_t grfso = STRUCT_OFFSET(pso, 0x538, uint64_t);
    grfso &= mask;
    grfso |= bit;
    STRUCT_OFFSET(pso, 0x538, uint64_t) = grfso;
    DiscardSoXps__FP2SO(pso, fNoXps != 0);
}

void SetSoNoXpsSelf(SO *pso, int fNoXps)
{
    uint64_t bit = (uint64_t)(fNoXps & 1) << 43; // fNoXpsSelf, grfso bit 43
    uint64_t grfso = STRUCT_OFFSET(pso, 0x538, uint64_t);
    grfso &= ~((uint64_t)1 << 43);
    grfso |= bit;
    STRUCT_OFFSET(pso, 0x538, uint64_t) = grfso;
    DiscardSoXps__FP2SO(pso, fNoXps ? 2 : 0);
}

void SetSoNoXpsCenter(SO *pso, int fNoXps)
{
    uint64_t bit = (uint64_t)(fNoXps & 1) << 44; // fNoXpsCenter, grfso bit 44
    uint64_t grfso = STRUCT_OFFSET(pso, 0x538, uint64_t);
    grfso &= ~((uint64_t)1 << 44);
    grfso |= bit;
    STRUCT_OFFSET(pso, 0x538, uint64_t) = grfso;
    DiscardSoXps__FP2SO(pso, fNoXps ? 3 : 0);
}

void RebuildSoPhysHook(SO *pso)
{
    SO *psoChild;
    VECTOR vecUnused; // dead local; needed for the original's 0x30 frame
    void *pvt = STRUCT_OFFSET(pso, 0x0, void *);

    // The object is its own phys hook if it overrides any of the phys
    // handler virtuals (vtable slots 0x114 / 0x100 / 0x104 / 0x108).
    if (STRUCT_OFFSET(pvt, 0x114, void *) != NULL || STRUCT_OFFSET(pvt, 0x100, void *) != NULL ||
        STRUCT_OFFSET(pvt, 0x104, void *) != NULL || STRUCT_OFFSET(pvt, 0x108, void *) != NULL)
    {
        STRUCT_OFFSET(pso, 0x4E4, SO *) = pso; // psoPhysHook
    }
    else
    {
        ALO *paloParent = STRUCT_OFFSET(pso, 0x18, ALO *);
        if (paloParent != NULL)
        {
            STRUCT_OFFSET(pso, 0x4E4, SO *) = STRUCT_OFFSET(paloParent, 0x4E4, SO *);
        }
        else
        {
            STRUCT_OFFSET(pso, 0x4E4, SO *) = NULL;
        }
    }
    for (psoChild = STRUCT_OFFSET(pso, 0x34, SO *); psoChild != NULL;
         psoChild = STRUCT_OFFSET(psoChild, 0x1C, SO *))
    {
        // class-flags word at vtable +0x8, bit 1 = derives from SO
        if (STRUCT_OFFSET(STRUCT_OFFSET(psoChild, 0x0, void *), 0x8, int) & 2)
        {
            RebuildSoPhysHook(psoChild);
        }
    }
}

SO *PsoFindSoPhysHook(SO *psoLeaf, int ib)
{
    SO *pso = psoLeaf;
    while (pso != NULL)
    {
        pso = STRUCT_OFFSET(pso, 0x4E4, SO *); // psoPhysHook
        if (pso == NULL)
        {
            break;
        }
        // hook handles phys if its virtual at vtable offset ib is non-null
        if (STRUCT_OFFSET(STRUCT_OFFSET(pso, 0x0, void *), ib, void *) != NULL)
        {
            return pso;
        }
        pso = STRUCT_OFFSET(pso, 0x18, SO *); // paloParent
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/P2/so", RecalcSoLocked__FP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/so", FGetSoContactList__FP2SOPv);

INCLUDE_ASM("asm/nonmatchings/P2/so", GetSoContacts__FP2SOPiPPP2SO);

int FSoInStsoList(STSO *pstsoFirst, SO *pso)
{
    while (pstsoFirst != NULL)
    {
        if (STRUCT_OFFSET(pstsoFirst, 0x0, SO *) == pso) // pso held by this STSO
        {
            return 1;
        }
        pstsoFirst = pstsoFirst->pstsoNext;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/so", GenerateSoSpliceTouchingEvents__FP2SO);

int FInflictSoZap(SO *pso, XP *pxp, ZPR *pzpr)
{
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/so", EnsureSoLvo__FP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/so", ProjectSoLvo__FP2SOf);

INCLUDE_ASM("asm/nonmatchings/P2/so", ProjectSoTransform__FP2SOfi);

INCLUDE_ASM("asm/nonmatchings/P2/so", ApplySoImpulse__FP2SOP6VECTORT1f);

INCLUDE_ASM("asm/nonmatchings/P2/so", CalculateSoTrajectoryApex__FP2SOP6VECTORfT1);

int FAbsorbSoWkr(SO *pso, WKR *pwkr)
{
    if (pwkr->grfic & 0x8)
    {
        ApplySoImpulse(pso, &STRUCT_OFFSET(pwkr, 0x20, VECTOR), &STRUCT_OFFSET(pwkr, 0x30, VECTOR), pwkr->sftMax);
    }
    return pwkr->grfic != 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/so", CloneSoPhys__FP2SOT0i);

INCLUDE_ASM("asm/nonmatchings/P2/so", FUN_001bc4d8);

INCLUDE_ASM("asm/nonmatchings/P2/so", FUN_001bc670);

extern "C" void FUN_001bc710(SO *pso, int f)
{
    uint64_t grfso = STRUCT_OFFSET(pso, 0x538, uint64_t);
    grfso &= ~((uint64_t)1 << 52);
    grfso |= (uint64_t)(f & 1) << 52;
    STRUCT_OFFSET(pso, 0x538, uint64_t) = grfso;
}

extern "C" void FUN_001bc748(SO *pso, int *pn)
{
    *pn = (int)(STRUCT_OFFSET(pso, 0x538, uint64_t) >> 52) & 1; // grfso bit 52 (qword view)
}
