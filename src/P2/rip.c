#include <rip.h>
#include <clock.h>
#include <alo.h>
#include <cid.h>
#include <wr.h>
#include <bsp.h>
#include <bez.h>

RIPG *PripgNew(SW *psw, RIPGT ripgt)
{
    if (ripgt == RIPGT_Default && STRUCT_OFFSET(psw, 0x1B3C, RIPG *) != NULL)
    {
        return STRUCT_OFFSET(psw, 0x1B3C, RIPG *);
    }

    RIPG *pripg = STRUCT_OFFSET(psw, 0x1B38, RIPG *);
    if (pripg != NULL)
    {
        STRUCT_OFFSET(psw, 0x1B38, RIPG *) = STRUCT_OFFSET(pripg, 0x564, RIPG *);
        STRUCT_OFFSET(pripg, 0x550, RIPGT) = ripgt;
        (*(void (**)(RIPG *))((uint8_t *)STRUCT_OFFSET(pripg, 0x0, void *) + 0x18))(pripg);
        if (ripgt == RIPGT_Default)
        {
            STRUCT_OFFSET(psw, 0x1B3C, RIPG *) = pripg;
        }
    }
    return pripg;
}

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

void ForceRipFade(RIP *prip, float dtFade)
{
    float dtRemain = STRUCT_OFFSET(prip, 0x1c, float) - (g_clock.t - STRUCT_OFFSET(prip, 0x18, float));
    if (dtFade < dtRemain)
    {
        float ratio = dtRemain / STRUCT_OFFSET(prip, 0x1c, float);
        float v = dtFade / ratio;
        STRUCT_OFFSET(prip, 0x1c, float) = v;
        STRUCT_OFFSET(prip, 0x18, float) = g_clock.t - (1.0f - ratio) * v;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", FBounceRip__FP3RIPP2SOP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ProjectRipTransform__FP3RIPf);

void UpdateRip(RIP *prip, float dt)
{
    if (STRUCT_OFFSET(prip, 0x1c, float) < g_clock.t - STRUCT_OFFSET(prip, 0x18, float))
    {
        RemoveRip(prip);
        return;
    }

    RIPG *pripg = prip->pripg;
    if (STRUCT_OFFSET(pripg, 0x550, int) == 1)
        return;

    if (STRUCT_OFFSET(prip, 0x24, ALO *) == NULL)
        return;
    if (STRUCT_OFFSET(STRUCT_OFFSET(prip, 0x24, ALO *), 0x3f8, BSP *) == NULL)
        return;

    int fInBsp = 0;
    if (FIsLoInWorld((LO *)STRUCT_OFFSET(prip, 0x24, ALO *)))
    {
        if (PbspPointInBspQuick(&STRUCT_OFFSET(prip, 0x80, VECTOR), STRUCT_OFFSET(STRUCT_OFFSET(prip, 0x24, ALO *), 0x3f8, BSP *)))
            fInBsp = 1;
    }

    (*(void (**)(RIP *, int))((uint8_t *)STRUCT_OFFSET(prip, 0x0, void *) + 0x18))(prip, fInBsp);
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", FRenderRipPosMat__FP3RIPP2CMP6VECTORP7MATRIX3);

void RenderRip(RIP *prip, CM *pcm)
{
    VECTOR pos;
    MATRIX3 mat;
    VECTOR *ppos;
    MATRIX3 *pmat;
    WR *pwr;

    pwr = STRUCT_OFFSET(prip, 0x114, WR *);
    if (pwr != NULL)
    {
        WarpWrTransform(pwr, 50.0f,
            &STRUCT_OFFSET(prip, 0x80, VECTOR),
            &STRUCT_OFFSET(prip, 0x50, MATRIX3),
            &pos, &mat, NULL);
        ppos = &pos;
        pmat = &mat;
    }
    else
    {
        ppos = &STRUCT_OFFSET(prip, 0x80, VECTOR);
        pmat = &STRUCT_OFFSET(prip, 0x50, MATRIX3);
    }

    if (!FRenderRipPosMat(prip, pcm, ppos, pmat))
    {
        RemoveRip(prip);
    }
}

void SubscribeRipObject(RIP *prip, LO *ploTarget)
{
    SubscribeSwPpmqStruct(g_psw, &STRUCT_OFFSET(prip, 0x118, MQ *), ploTarget->pvtlo->pfnHandleLoMessage, ploTarget);
}

void SubscribeRipStruct(RIP *prip, PFNMQ pfnmq, void *pvContext)
{
    SubscribeSwPpmqStruct(g_psw, &STRUCT_OFFSET(prip, 0x118, MQ *), pfnmq, pvContext);
}

void UnsubscribeRipStruct(RIP *prip, PFNMQ pfnmq, void *pvContext)
{
    UnsubscribeSwPpmqStruct(g_psw, &STRUCT_OFFSET(prip, 0x118, MQ *), pfnmq, pvContext);
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitDroplet__FP7DROPLETP6VECTORfP2SO);

void TouchDroplet(DROPLET *pdroplet, int fTouching)
{
    LSG alsg[16];

    if (fTouching)
    {
        *(VU_VECTOR *)alsg = STRUCT_OFFSET(pdroplet, 0x80, VU_VECTOR);

        BSP *pbsp = STRUCT_OFFSET(STRUCT_OFFSET(pdroplet, 0x24, ALO *), 0x3f8, BSP *);
        if (pbsp)
        {
            ClsgClipEdgeToBsp(
                pbsp,
                (VECTOR *)((uint8_t *)pdroplet + 0x90),
                (VECTOR *)((uint8_t *)pdroplet + 0x80),
                NULL, 0x10, alsg);
        }

        RIP *prip = PripNewRipg(RIPT_Ripple, NULL);
        if (prip != NULL)
        {
            (*(void (**)(RIP *, VECTOR *, float, SO *))(STRUCT_OFFSET(prip, 0x0, void *)))(
                prip, (VECTOR *)alsg, 40.0f, NULL);
            STRUCT_OFFSET(prip, 0x1c, float) = 0.75f;
            STRUCT_OFFSET(prip, 0x34, float) = 30.0f;

            void *p278 = STRUCT_OFFSET(STRUCT_OFFSET(pdroplet, 0x24, ALO *), 0x278, void *);
            if (p278 != NULL)
            {
                STRUCT_OFFSET(prip, 0x114, int) = STRUCT_OFFSET(p278, 0xc, int);
            }
        }

        RemoveRip((RIP *)pdroplet);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitBublet__FP6BUBLETP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ProjectBubletTransform__FP6BUBLETf);

void TouchBublet(BUBLET *pbublet, int fTouching)
{
    TouchDroplet((DROPLET *)pbublet, fTouching == 0);
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitRipple__FP6RIPPLEP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitPuff__FP4PUFFP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitDablet__FP6DABLETP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitFlake__FP5FLAKEP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", UpdateFlake__FP5FLAKEf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderFlake__FP5FLAKEP2CM);

void TouchFlake(FLAKE *pflake, int fTouching)
{
    if (fTouching)
    {
        RemoveRip(pflake);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitSpark__FP5SPARKP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderSpark__FP5SPARKP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitBurst__FP5BURSTP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitTrail__FP5TRAILP6VECTORfP2SO);

void OnTrailRemove(TRAIL *ptrail)
{
    SetTrailTrls(ptrail, (TRLS)0, 0);
}

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

void UpdateSmack(SMACK *psmack, float dt)
{
    if (STRUCT_OFFSET(psmack, 0x1c, float) < g_clock.t - STRUCT_OFFSET(psmack, 0x18, float))
    {
        RemoveRip(psmack);
        (*(void (**)(int))((uint8_t *)STRUCT_OFFSET(psmack, 0x130, void *) + 0x60))(STRUCT_OFFSET(psmack, 0x134, int));
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitOrbit__FP5ORBITP6VECTORfP2SO);

JUNK_ADDIU(80);

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

int SgnCmpHp(const void *pv0, const void *pv1)
{
    if (STRUCT_OFFSET(pv0, 0x20, float) < STRUCT_OFFSET(pv1, 0x20, float))
        return -1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", ChpBuildConvexHullScreen__FP6VECTORiP2HP);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ChpBuildConvexHullXY__FP7MATRIX4iP2HP);

void PostFlyingEmit(FLYING *pflying, EMITB *pemitb)
{
    STRUCT_OFFSET(pflying, 0x120, int) = STRUCT_OFFSET(pemitb, 0x1DC, int);
    STRUCT_OFFSET(pflying, 0x124, int) = STRUCT_OFFSET(pemitb, 0x1F0, int);
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderFlying__FP6FLYINGP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", CreateStuck__FP3RIPP3ALOP2SOP6VECTORT3PP5STUCK);

INCLUDE_ASM("asm/nonmatchings/P2/rip", FBounceFlying__FP6FLYINGP2SOP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/rip", UpdateStuck__FP5STUCKf);

void RenderStuck(STUCK *pstuck, CM *pcm)
{
    VECTOR pos;
    MATRIX3 mat;

    ConvertAloPos(STRUCT_OFFSET(pstuck, 0x120, ALO *), NULL, &STRUCT_OFFSET(pstuck, 0x80, VECTOR), &pos);
    ConvertAloMat(STRUCT_OFFSET(pstuck, 0x120, ALO *), NULL, &STRUCT_OFFSET(pstuck, 0x50, MATRIX3), &mat);
    FRenderRipPosMat((RIP *)pstuck, pcm, &pos, &mat);
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", PostLeafEmit__FP4LEAFP5EMITB);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ProjectLeafTransform__FP4LEAFf);

int FBounceLeaf(LEAF *pleaf, SO *psoOther, VECTOR *ppos, VECTOR *pnormal)
{

    if (FIsBasicDerivedFrom(STRUCT_OFFSET(psoOther, 0x50, BASIC *), CID_MISSILE))
        return 0;
    if (FIsBasicDerivedFrom(STRUCT_OFFSET(psoOther, 0x50, BASIC *), CID_STEP))
        return 0;

    STUCK *pstuck;
    CreateStuck((RIP *)pleaf, STRUCT_OFFSET(pleaf, 0x20, ALO *), psoOther, ppos, pnormal, &pstuck);
    if (pstuck != NULL)
    {
        ConvertAloMat(NULL, psoOther, &STRUCT_OFFSET(pstuck, 0x50, MATRIX3), &STRUCT_OFFSET(pstuck, 0x50, MATRIX3));
    }
    RemoveRip((RIP *)pleaf);
    return 1;
}

int FFilterFlameObjects(void *pv, SO *pso)
{
    if (STRUCT_OFFSET(pso, 0x538, unsigned long long) & ((unsigned long long)0x8000 << 28))
    {
        return 0;
    }
    return pso != STRUCT_OFFSET(pv, 0x7C, SO *);
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", PostFlameEmit__FP5FLAMEP5EMITB);

void PostBulletEmit(BULLET *pbullet, EMITB *pemitb)
{
    ConvertAloPos(STRUCT_OFFSET(pemitb, 0x7c, ALO *), NULL, &STRUCT_OFFSET(pemitb, 0x20, VECTOR), &STRUCT_OFFSET(pbullet, 0x80, VECTOR));
    STRUCT_OFFSET(pbullet, 0xb0, int) = 0;
    STRUCT_OFFSET(pbullet, 0x110, int) = 0;
    STRUCT_OFFSET(pbullet, 0x120, int) = STRUCT_OFFSET(pemitb, 0x1f4, int);
    STRUCT_OFFSET(pbullet, 0x124, int) = STRUCT_OFFSET(pemitb, 0x1f0, int);
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderBullet__FP6BULLETP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", FBounceBullet__FP6BULLETP2SOP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/rip", PostShrapnelEmit__FP8SHRAPNELP5EMITB);

int FBounceShrapnel(SHRAPNEL *pshrapnel, SO *psoOther, VECTOR *ppos, VECTOR *pnormal)
{
    if (FIsBasicDerivedFrom(STRUCT_OFFSET(psoOther, 0x50, BASIC *), CID_STEP))
        return 0;
    return FBounceRip((RIP *)pshrapnel, psoOther, ppos, pnormal);
}

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

JUNK_ADDIU(10);
JUNK_WORD(0x7C450000);
JUNK_WORD(0x48220800);
