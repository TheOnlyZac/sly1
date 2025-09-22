#include <rip.h>

INCLUDE_ASM("asm/nonmatchings/P2/rip", PripgNew__FP2SW5RIPGT);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitRipg__FP4RIPG);

void SetRipgEmitb(RIPG *pripg, EMITB *pemitb)
{
    // pripg->sExpand & pemib->emitp.emitrip.sExpand
    STRUCT_OFFSET(pripg, 0x554, float) = STRUCT_OFFSET(pemitb, 0x1e8, float);
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", OnRipgRemove__FP4RIPG);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ProjectRipgTransform__FP4RIPGfi);

void UpdateRipgBounds(RIPG *pripg)
{
    return;
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", FUN_0019e420);

INCLUDE_ASM("asm/nonmatchings/P2/rip", BounceRipgRips__FP4RIPG);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderRipgSelf__FP4RIPGP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", PvtripFromRipt__F4RIPT);

INCLUDE_ASM("asm/nonmatchings/P2/rip", PripNewRipg__F4RIPTP4RIPG);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitRip__FP3RIPP6VECTORfP2SO);

void RemoveRip(RIP *prip)
{
	RemoveDlEntry(&STRUCT_OFFSET(prip->pripg, 0x558, DL), prip);
    ReleaseRip(prip);
}

void AddRipRef(RIP *prip)
{
    prip->cref++;
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", ReleaseRip__FP3RIP);

void TouchRip(RIP *prip, int fTouching)
{
    if (fTouching)
    {
        RemoveRip(prip);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", ForceRipFade__FP3RIPf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", FBounceRip__FP3RIPP2SOP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ProjectRipTransform__FP3RIPf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", UpdateRip__FP3RIPf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", FRenderRipPosMat__FP3RIPP2CMP6VECTORP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderRip__FP3RIPP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", SubscribeRipObject__FP3RIPP2LO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", SubscribeRipStruct__FP3RIPPFPv5MSGIDPv_vPv);

INCLUDE_ASM("asm/nonmatchings/P2/rip", UnsubscribeRipStruct__FP3RIPPFPv5MSGIDPv_vPv);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitDroplet__FP7DROPLETP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", TouchDroplet__FP7DROPLETi);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitBublet__FP6BUBLETP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ProjectBubletTransform__FP6BUBLETf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", TouchBublet__FP6BUBLETi);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitRipple__FP6RIPPLEP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitPuff__FP4PUFFP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitDablet__FP6DABLETP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitFlake__FP5FLAKEP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", UpdateFlake__FP5FLAKEf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderFlake__FP5FLAKEP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", TouchFlake__FP5FLAKEi);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitSpark__FP5SPARKP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderSpark__FP5SPARKP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitBurst__FP5BURSTP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitTrail__FP5TRAILP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", OnTrailRemove__FP5TRAIL);

INCLUDE_ASM("asm/nonmatchings/P2/rip", SetTrailTrls__FP5TRAIL4TRLSPv);

INCLUDE_ASM("asm/nonmatchings/P2/rip", DetachTrail__FP5TRAIL);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ProjectTrailTransform__FP5TRAILf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderTrail__FP5TRAILP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", HandleTrailMessage__FP5TRAIL5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitFireball__FP8FIREBALLP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", UpdateFireball__FP8FIREBALLf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitSmokecloud__FP10SMOKECLOUDP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitSmoketrail__FP10SMOKETRAILP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitDebris__FP6DEBRISP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitSmack__FP5SMACKP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ProjectSmackTransform__FP5SMACKf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderSmack__FP5SMACKP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", UpdateSmack__FP5SMACKf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitOrbit__FP5ORBITP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", junk_001A1028);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ProjectOrbitTransform__FP5ORBITf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", UpdateOrbit__FP5ORBITf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderOrbit__FP5ORBITP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitRay__FP3RAYP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitRose__FP4ROSEP6VECTORfP2SO);

void ProjectRoseTransform(ROSE *prose, float dt)
{
    return;
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", UpdateRose__FP4ROSEf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderRose__FP4ROSEP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", SetRoseRoses__FP4ROSE5ROSES);

INCLUDE_ASM("asm/nonmatchings/P2/rip", SgnCmpHp__FPCvT0);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ChpBuildConvexHullScreen__FP6VECTORiP2HP);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ChpBuildConvexHullXY__FP7MATRIX4iP2HP);

INCLUDE_ASM("asm/nonmatchings/P2/rip", PostFlyingEmit__FP6FLYINGP5EMITB);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderFlying__FP6FLYINGP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", CreateStuck__FP3RIPP3ALOP2SOP6VECTORT3PP5STUCK);

INCLUDE_ASM("asm/nonmatchings/P2/rip", FBounceFlying__FP6FLYINGP2SOP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/rip", UpdateStuck__FP5STUCKf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderStuck__FP5STUCKP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", PostLeafEmit__FP4LEAFP5EMITB);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ProjectLeafTransform__FP4LEAFf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", FBounceLeaf__FP4LEAFP2SOP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/rip", FFilterFlameObjects__FPvP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", PostFlameEmit__FP5FLAMEP5EMITB);

INCLUDE_ASM("asm/nonmatchings/P2/rip", PostBulletEmit__FP6BULLETP5EMITB);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderBullet__FP6BULLETP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", FBounceBullet__FP6BULLETP2SOP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/rip", PostShrapnelEmit__FP8SHRAPNELP5EMITB);

INCLUDE_ASM("asm/nonmatchings/P2/rip", FBounceShrapnel__FP8SHRAPNELP2SOP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderShrapnel__FP8SHRAPNELP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitGlint__FP5GLINTP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderGlint__FP5GLINTP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitMatch__FP5MATCHP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", LaunchMatch__FP5MATCH);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ProjectMatchTransform__FP5MATCHf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", UpdateMatch__FP5MATCHf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderMatch__FP5MATCHP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", PostRemitEmit__FP5REMITP5EMITB);

INCLUDE_ASM("asm/nonmatchings/P2/rip", UpdateRemit__FP5REMITf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", junk_001A3AC8);
