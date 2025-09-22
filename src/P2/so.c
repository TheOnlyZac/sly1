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

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoMass__FP2SOf);

INCLUDE_ASM("asm/nonmatchings/P2/so", AdjustSoMomint__FP2SOf);

INCLUDE_ASM("asm/nonmatchings/P2/so", DiscardSoXps__FP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/so", UpdateSoPosWorldPrev__FP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/so", TranslateSoToPos__FP2SOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/so", RotateSoToMat__FP2SOP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/so", TranslateSoToPosSafe__FP2SOP6VECTORT1);

JUNK_ADDIU(40);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoVelocityVec__FP2SOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoAngularVelocityVec__FP2SOP6VECTOR);

JUNK_ADDIU(20);

INCLUDE_ASM("asm/nonmatchings/P2/so", AddSoAcceleration__FP2SOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/so", AddSoAngularAcceleration__FP2SOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoConstraints__FP2SO2CTP6VECTORT1T2);

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

INCLUDE_ASM("asm/nonmatchings/P2/so", AddSoXa__FP2SOP2XA);

INCLUDE_ASM("asm/nonmatchings/P2/so", RemoveSoXa__FP2SOP2XA);

INCLUDE_ASM("asm/nonmatchings/P2/so", AddSoWaterAcceleration__FP2SOP5WATERf);

void AddSoExternalAccelerations(SO *pso, XA *pxa, float dt)
{
    return;
}

INCLUDE_ASM("asm/nonmatchings/P2/so", LoadSoFromBrx__FP2SOP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoSphere__FP2SOf);

void SetSoNoInteract(SO *pso, int fNoInteract)
{
    SetSoConstraints(pso, CT_Locked, (VECTOR *)nullptr, CT_Locked, (VECTOR *)nullptr);
}

INCLUDE_ASM("asm/nonmatchings/P2/so", ConstrFromCnstr__F5CNSTRP2CTP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoCnstrForce__FP2SO5CNSTR);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoCnstrTorque__FP2SO5CNSTR);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoCameraStyle__FP2SO3CMK);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoIgnoreLocked__FP2SOi);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoIceable__FP2SOi);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoMtlk__FP2SO4MTLK);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoEdgeGrab__FP2SO3EGK);

INCLUDE_ASM("asm/nonmatchings/P2/so", SendSoMessage__FP2SO5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/so", PxpFindSoGround__FP2SOT0Pi);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoNoGravity__FP2SOi);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoNoXpsAll__FP2SOi);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoNoXpsSelf__FP2SOi);

INCLUDE_ASM("asm/nonmatchings/P2/so", SetSoNoXpsCenter__FP2SOi);

INCLUDE_ASM("asm/nonmatchings/P2/so", RebuildSoPhysHook__FP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/so", PsoFindSoPhysHook__FP2SOi);

INCLUDE_ASM("asm/nonmatchings/P2/so", RecalcSoLocked__FP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/so", FGetSoContactList__FP2SOPv);

INCLUDE_ASM("asm/nonmatchings/P2/so", GetSoContacts__FP2SOPiPPP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/so", FSoInStsoList__FP4STSOP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/so", GenerateSoSpliceTouchingEvents__FP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/so", FInflictSoZap__FP2SOP2XPP3ZPR);

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
