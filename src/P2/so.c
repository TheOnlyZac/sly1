#include <so.h>

INCLUDE_ASM("asm/nonmatchings/P2/so", InitSo__FP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/so", OnSoAdd__FP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/so", OnSoRemove__FP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/so", EnableSoPhys__FP2SOi);

INCLUDE_ASM("asm/nonmatchings/P2/so", DisplaceSo__FP2SOi);

INCLUDE_ASM("asm/nonmatchings/P2/so", ImpactSo__FP2SOi);

INCLUDE_ASM("asm/nonmatchings/P2/so", PivotSo__FP2SOi);

INCLUDE_ASM("asm/nonmatchings/P2/so", ExtendSoBounds__FP2SOP6VECTORf);

INCLUDE_ASM("asm/nonmatchings/P2/so", UpdateSoBounds__FP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/so", UpdateGeomWorld__FP4GEOMT0G9VU_VECTORP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/so", UpdateSoXfWorldHierarchy__FP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/so", UpdateSoXfWorld__FP2SO);

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

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoParent__FP2SOP3ALO);

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

INCLUDE_ASM("asm/nonmatchings/P2/so", ConstrFromCnstr__F5CNSTRP2CTP6VECTOR);

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

INCLUDE_ASM("asm/nonmatchings/P2/so", RebuildSoPhysHook__FP2SO);

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

INCLUDE_ASM("asm/nonmatchings/P2/so", FSoInStsoList__FP4STSOP2SO);

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

INCLUDE_ASM("asm/nonmatchings/P2/so", FAbsorbSoWkr__FP2SOP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/so", CloneSoPhys__FP2SOT0i);

INCLUDE_ASM("asm/nonmatchings/P2/so", FUN_001bc4d8);

INCLUDE_ASM("asm/nonmatchings/P2/so", FUN_001bc670);

INCLUDE_ASM("asm/nonmatchings/P2/so", FUN_001bc710);

INCLUDE_ASM("asm/nonmatchings/P2/so", FUN_001bc748);
