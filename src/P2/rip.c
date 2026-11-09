#include <rip.h>
#include <wr.h>
#include <bsp.h>

typedef void (*PFNRIP)(RIP *);
typedef void (*PFNINITRIP)(RIP *, VECTOR *, float, SO *);

extern qword D_0026B710;
extern qword D_0026B720;
extern qword D_0026B5B0;
extern qword D_0026B5C0;

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

void ReleaseRip(RIP *prip)
{
    if (--prip->cref == 0)
    {
        PFNRIP pfn = STRUCT_OFFSET(STRUCT_OFFSET(prip, 0, char *), 8, PFNRIP);
        if (pfn)
            pfn(prip);
        MQ *pmqFirst = STRUCT_OFFSET(prip, 0x118, MQ *);
        if (pmqFirst)
        {
            STRUCT_OFFSET(prip, 0x118, MQ *) = 0;
            for (MQ *pmq = pmqFirst; pmq != 0; pmq = pmq->pmqNext)
            {
                pmq->pfnmq(pmq->pvContext, MSGID_rip_removed, prip);
            }
            FreeSwMqList(g_psw, pmqFirst);
        }
        FreeSlotheapPv(&STRUCT_OFFSET(prip->pripg->psw, 0x1b2c, SLOTHEAP), prip);
    }
}

void TouchRip(RIP *prip, int fTouching)
{
    if (fTouching)
    {
        RemoveRip(prip);
    }
}

void ForceRipFade(RIP *prip, float dtFade)
{
    float tStart = STRUCT_OFFSET(prip, 0x18, float);
    float life = STRUCT_OFFSET(prip, 0x1c, float);
    float left = life - (g_clock.t - tStart);
    if (dtFade < left)
    {
        float r = left / life;
        float nl = dtFade / r;
        STRUCT_OFFSET(prip, 0x1c, float) = nl;
        STRUCT_OFFSET(prip, 0x18, float) = g_clock.t - (1.0f - r) * nl;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", FBounceRip__FP3RIPP2SOP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ProjectRipTransform__FP3RIPf);

void UpdateRip(RIP *prip, float dt)
{
    if (STRUCT_OFFSET(prip, 0x1c, float) < g_clock.t - STRUCT_OFFSET(prip, 0x18, float))
    {
        RemoveRip(prip);
    }
    else if (STRUCT_OFFSET(prip->pripg, 0x550, int) != 1)
    {
        SO *pso = STRUCT_OFFSET(prip, 0x24, SO *);
        if (pso != 0 && STRUCT_OFFSET(pso, 0x3f8, BSP *) != 0)
        {
            int fInBsp = 0;
            if (FIsLoInWorld(pso))
            {
                if (PbspPointInBspQuick(&STRUCT_OFFSET(prip, 0x80, VECTOR), STRUCT_OFFSET(STRUCT_OFFSET(prip, 0x24, SO *), 0x3f8, BSP *)))
                    fInBsp = 1;
            }
            typedef void (*PFNUP)(RIP *, int);
            STRUCT_OFFSET(STRUCT_OFFSET(prip, 0, char *), 0x18, PFNUP)(prip, fInBsp);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", FRenderRipPosMat__FP3RIPP2CMP6VECTORP7MATRIX3);

void RenderRip(RIP *prip, CM *pcm)
{
    VECTOR pos;
    MATRIX3 mat;
    VECTOR *ppos;
    MATRIX3 *pmat;
    if (STRUCT_OFFSET(prip, 0x114, WR *))
    {
        WarpWrTransform(STRUCT_OFFSET(prip, 0x114, WR *), 50.0f, &STRUCT_OFFSET(prip, 0x80, VECTOR), &STRUCT_OFFSET(prip, 0x50, MATRIX3), &pos, &mat, 0);
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

void InitDroplet(DROPLET *pdroplet, VECTOR *ppos, float gScale, SO *psoTouch)
{
    InitRip(pdroplet, ppos, gScale, psoTouch);
    float g = 5.0f;
    SW *psw = g_psw;
    STRUCT_OFFSET(pdroplet, 0x1c, float) = g;
    STRUCT_OFFSET(pdroplet, 0x20, int) = STRUCT_OFFSET(psw, 0x1cec, int);
    STRUCT_OFFSET(pdroplet, 0xc0, qword) = STRUCT_OFFSET(psw, 0x1ee0, qword);
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", TouchDroplet__FP7DROPLETi);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitBublet__FP6BUBLETP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ProjectBubletTransform__FP6BUBLETf);

void TouchBublet(BUBLET *pbublet, int fTouching)
{
    TouchDroplet((DROPLET *)pbublet, !fTouching);
}

void InitRipple(RIPPLE *pripple, VECTOR *ppos, float gScale, SO *psoTouch)
{
    InitRip(pripple, ppos, gScale, psoTouch);
    float lim = 200.0f;
    SW *psw = g_psw;
    float g = (gScale < lim) ? gScale : lim;
    float h = g * 0.6f;
    int v = STRUCT_OFFSET(psw, 0x1cf0, int);
    STRUCT_OFFSET(pripple, 0x30, float) = g;
    STRUCT_OFFSET(pripple, 0x20, int) = v;
    STRUCT_OFFSET(pripple, 0x34, float) = h;
}

void InitPuff(PUFF *ppuff, VECTOR *ppos, float gScale, SO *psoTouch)
{
    InitRip(ppuff, ppos, gScale, psoTouch);
    float g = 3.0f;
    SW *psw = g_psw;
    float h = 0.6f;
    STRUCT_OFFSET(ppuff, 0x1c, float) = g;
    STRUCT_OFFSET(ppuff, 0x20, int) = STRUCT_OFFSET(psw, 0x1cf4, int);
    STRUCT_OFFSET(ppuff, 0x34, float) = h;
}

void InitDablet(DABLET *pdablet, VECTOR *ppos, float gScale, SO *psoTouch)
{
    InitRip(pdablet, ppos, gScale, psoTouch);
    float g = 2.0f;
    SW *psw = g_psw;
    float h = -1.0f;
    STRUCT_OFFSET(pdablet, 0x1c, float) = g;
    STRUCT_OFFSET(pdablet, 0xc0, qword) = STRUCT_OFFSET(psw, 0x1ee0, qword);
    STRUCT_OFFSET(pdablet, 0x38, float) = h;
}

void InitFlake(FLAKE *pflake, VECTOR *ppos, float gScale, SO *psoTouch)
{
    InitRip(pflake, ppos, gScale, psoTouch);
    int v = STRUCT_OFFSET(g_psw, 0x1d00, int);
    STRUCT_OFFSET(pflake, 0x1c, float) = 0.5f;
    STRUCT_OFFSET(pflake, 0x20, int) = v;
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", UpdateFlake__FP5FLAKEf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderFlake__FP5FLAKEP2CM);

void TouchFlake(FLAKE *pflake, int fTouching)
{
    if (fTouching)
    {
        RemoveRip(pflake);
    }
}

void InitSpark(SPARK *pspark, VECTOR *ppos, float gScale, SO *psoTouch)
{
    InitRip(pspark, ppos, gScale, psoTouch);
    float g = 0.25f;
    SW *psw = g_psw;
    float h = 0.05f;
    STRUCT_OFFSET(pspark, 0x1c, float) = g;
    STRUCT_OFFSET(pspark, 0x20, int) = STRUCT_OFFSET(psw, 0x1cf8, int);
    STRUCT_OFFSET(pspark, 0x40, qword) = *(qword *)&g_clqOne;
    STRUCT_OFFSET(pspark, 0x120, float) = h;
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderSpark__FP5SPARKP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitBurst__FP5BURSTP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitTrail__FP5TRAILP6VECTORfP2SO);

void OnTrailRemove(TRAIL *ptrail)
{
    SetTrailTrls(ptrail, TRLS_None, 0);
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", SetTrailTrls__FP5TRAIL4TRLSPv);

INCLUDE_ASM("asm/nonmatchings/P2/rip", DetachTrail__FP5TRAIL);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ProjectTrailTransform__FP5TRAILf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderTrail__FP5TRAILP2CM);

void HandleTrailMessage(TRAIL *ptrail, MSGID msgid, void *pv)
{
    switch (msgid)
    {
    case MSGID_removed:
    case MSGID_water_entered:
    case MSGID_rip_removed:
        SetTrailTrls(ptrail, TRLS_None, 0);
        break;
    case MSGID_translated:
        SetTrailTrls(ptrail, TRLS_None, (char *)pv + 0x10);
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitFireball__FP8FIREBALLP6VECTORfP2SO);

void UpdateFireball(FIREBALL *pfireball, float dt)
{
    UpdateRip(pfireball, dt);
    float dtAge = g_clock.t - STRUCT_OFFSET(pfireball, 0x18, float) - 0.15f;
    if (dtAge >= 0.0f && dtAge < dt)
    {
        float gScale = -STRUCT_OFFSET(pfireball, 0x38, float);
        RIP *prip = PripNewRipg((RIPT)12, 0);
        if (prip)
        {
            STRUCT_OFFSET(STRUCT_OFFSET(prip, 0, char *), 0, PFNINITRIP)(prip, &STRUCT_OFFSET(pfireball, 0x80, VECTOR), gScale, 0);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitSmokecloud__FP10SMOKECLOUDP6VECTORfP2SO);
// @todo 40% matched (store/load scheduling differs)
#ifdef SKIP_ASM
void InitSmokecloud(SMOKECLOUD *psmokecloud, VECTOR *ppos, float gScale, SO *psoTouch)
{
    InitRip(psmokecloud, ppos, gScale, psoTouch);
    STRUCT_OFFSET(psmokecloud, 0x1c, float) = 3.0f;
    STRUCT_OFFSET(psmokecloud, 0x20, int) = STRUCT_OFFSET(g_psw, 0x1d0c, int);
    STRUCT_OFFSET(psmokecloud, 0x34, float) = STRUCT_OFFSET(psmokecloud, 0x30, float) * 0.25f;
    STRUCT_OFFSET(psmokecloud, 0x40, qword) = D_0026B5B0;
    STRUCT_OFFSET(psmokecloud, 0xb0, float) = -1.0f;
    STRUCT_OFFSET(psmokecloud, 0xc0, qword) = D_0026B5C0;
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitSmoketrail__FP10SMOKETRAILP6VECTORfP2SO);

void InitDebris(DEBRIS *pdebris, VECTOR *ppos, float gScale, SO *psoTouch)
{
    InitRip(pdebris, ppos, gScale, psoTouch);
    SW *psw = g_psw;
    int v = STRUCT_OFFSET(psw, 0x1cec, int);
    STRUCT_OFFSET(pdebris, 0x1c, float) = 0.5f;
    STRUCT_OFFSET(pdebris, 0x20, int) = v;
    STRUCT_OFFSET(pdebris, 0xc0, qword) = STRUCT_OFFSET(psw, 0x1ee0, qword);
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", InitSmack__FP5SMACKP6VECTORfP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ProjectSmackTransform__FP5SMACKf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderSmack__FP5SMACKP2CM);

void UpdateSmack(SMACK *psmack, float dt)
{
    if (STRUCT_OFFSET(psmack, 0x1c, float) < g_clock.t - STRUCT_OFFSET(psmack, 0x18, float))
    {
        RemoveRip(psmack);
        void *pv = STRUCT_OFFSET(psmack, 0x134, void *);
        ((void (*)(void *))STRUCT_OFFSET(STRUCT_OFFSET(psmack, 0x130, char *), 0x60, int))(pv);
    }
}

void InitOrbit(ORBIT *porbit, VECTOR *ppos, float gScale, SO *psoTouch)
{
    InitRip(porbit, ppos, gScale, psoTouch);
    qword q = *(qword *)&g_clqOne;
    STRUCT_OFFSET(porbit, 0x1c, float) = 2.0f;
    STRUCT_OFFSET(porbit, 0x40, qword) = q;
}

JUNK_ADDIU(80);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ProjectOrbitTransform__FP5ORBITf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", UpdateOrbit__FP5ORBITf);

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderOrbit__FP5ORBITP2CM);

void InitRay(RAY *pray, VECTOR *ppos, float gScale, SO *psoTouch)
{
    InitSpark(pray, ppos, gScale, psoTouch);
    SW *psw = g_psw;
    int v = STRUCT_OFFSET(psw, 0x1d28, int);
    STRUCT_OFFSET(pray, 0x120, float) = 0.15f;
    STRUCT_OFFSET(pray, 0x20, int) = v;
}

void InitRose(ROSE *prose, VECTOR *ppos, float gScale, SO *psoTouch)
{
    InitRip(prose, ppos, gScale, psoTouch);
    int n = -1;
    SW *psw = g_psw;
    int v = STRUCT_OFFSET(psw, 0x1d28, int);
    STRUCT_OFFSET(prose, 0x120, int) = n;
    STRUCT_OFFSET(prose, 0x20, int) = v;
    STRUCT_OFFSET(prose, 0x128, int) = n;
}

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
    STRUCT_OFFSET(pflying, 0x120, int) = STRUCT_OFFSET(pemitb, 0x1dc, int);
    STRUCT_OFFSET(pflying, 0x124, int) = STRUCT_OFFSET(pemitb, 0x1f0, int);
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderFlying__FP6FLYINGP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", CreateStuck__FP3RIPP3ALOP2SOP6VECTORT3PP5STUCK);

INCLUDE_ASM("asm/nonmatchings/P2/rip", FBounceFlying__FP6FLYINGP2SOP6VECTORT2);

void UpdateStuck(STUCK *pstuck, float dt)
{
    UpdateRip(pstuck, dt);
    if (STRUCT_OFFSET(pstuck, 0x120, LO *) != 0 && !FIsLoInWorld(STRUCT_OFFSET(pstuck, 0x120, LO *)))
    {
        RemoveRip(pstuck);
    }
}

void RenderStuck(STUCK *pstuck, CM *pcm)
{
    VECTOR pos;
    MATRIX3 mat;
    ConvertAloPos(STRUCT_OFFSET(pstuck, 0x120, ALO *), 0, &STRUCT_OFFSET(pstuck, 0x80, VECTOR), &pos);
    ConvertAloMat(STRUCT_OFFSET(pstuck, 0x120, ALO *), 0, &STRUCT_OFFSET(pstuck, 0x50, MATRIX3), &mat);
    FRenderRipPosMat(pstuck, pcm, &pos, &mat);
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
    CreateStuck(pleaf, STRUCT_OFFSET(pleaf, 0x20, ALO *), psoOther, ppos, pnormal, &pstuck);
    if (pstuck)
    {
        MATRIX3 *pmat = &STRUCT_OFFSET(pstuck, 0x50, MATRIX3);
        ConvertAloMat(0, (ALO *)psoOther, pmat, pmat);
    }
    RemoveRip(pleaf);
    return 1;
}

int FFilterFlameObjects(void *pv, SO *pso)
{
    if (STRUCT_OFFSET(pso, 0x538, ulong) & 0x80000000000)
        return 0;
    return pso != STRUCT_OFFSET(pv, 0x7c, SO *);
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", PostFlameEmit__FP5FLAMEP5EMITB);

void PostBulletEmit(BULLET *pbullet, EMITB *pemitb)
{
    ConvertAloPos(STRUCT_OFFSET(pemitb, 0x7c, ALO *), 0, &STRUCT_OFFSET(pemitb, 0x20, VECTOR), &STRUCT_OFFSET(pbullet, 0x80, VECTOR));
    STRUCT_OFFSET(pbullet, 0xb0, int) = 0;
    STRUCT_OFFSET(pbullet, 0x110, int) = 0;
    STRUCT_OFFSET(pbullet, 0x120, int) = STRUCT_OFFSET(pemitb, 0x1f4, int);
    STRUCT_OFFSET(pbullet, 0x124, int) = STRUCT_OFFSET(pemitb, 0x1f0, int);
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderBullet__FP6BULLETP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/rip", FBounceBullet__FP6BULLETP2SOP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/rip", PostShrapnelEmit__FP8SHRAPNELP5EMITB);

int FBounceShrapnel(SHRAPNEL *pshrapnel, SO *pso, VECTOR *pposCenter, VECTOR *pnormal)
{
    if (FIsBasicDerivedFrom(STRUCT_OFFSET(pso, 0x50, BASIC *), CID_STEP))
        return 0;
    return FBounceRip(pshrapnel, pso, pposCenter, pnormal);
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderShrapnel__FP8SHRAPNELP2CM);

void InitGlint(GLINT *pglint, VECTOR *ppos, float gScale, SO *psoTouch)
{
    InitRip(pglint, ppos, gScale, psoTouch);
    float g = 0.5f;
    SW *psw = g_psw;
    STRUCT_OFFSET(pglint, 0x1c, float) = g;
    STRUCT_OFFSET(pglint, 0x20, int) = STRUCT_OFFSET(psw, 0x1d30, int);
    STRUCT_OFFSET(pglint, 0x40, qword) = D_0026B710;
    STRUCT_OFFSET(pglint, 0x30, qword) = D_0026B720;
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", RenderGlint__FP5GLINTP2CM);

void InitMatch(MATCH *pmatch, VECTOR *ppos, float gScale, SO *psoTouch)
{
    InitRip(pmatch, ppos, gScale, psoTouch);
    STRUCT_OFFSET(pmatch, 0x40, qword) = *(qword *)&g_clqOne;
    STRUCT_OFFSET(pmatch, 0x30, float) = gScale;
    STRUCT_OFFSET(pmatch, 0x34, float) = 1.0f - gScale;
    STRUCT_OFFSET(pmatch, 0x38, int) = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/rip", LaunchMatch__FP5MATCH);

INCLUDE_ASM("asm/nonmatchings/P2/rip", ProjectMatchTransform__FP5MATCHf);

void UpdateMatch(MATCH *pmatch, float dt)
{
    if (STRUCT_OFFSET(pmatch, 0x18, float) <= g_clock.t && STRUCT_OFFSET(pmatch, 0x134, int) != 0)
    {
        LaunchMatch(pmatch);
    }
    if (STRUCT_OFFSET(pmatch, 0x1c, float) < g_clock.t - STRUCT_OFFSET(pmatch, 0x18, float))
    {
        void *pv = STRUCT_OFFSET(pmatch, 0x20, void *);
        ((void (*)(void *))STRUCT_OFFSET(STRUCT_OFFSET(pv, 0, char *), 0x18, int))(pv);
        RemoveRip(pmatch);
    }
}

void RenderMatch(MATCH *pmatch, CM *pcm)
{
    if (g_clock.t < STRUCT_OFFSET(pmatch, 0x18, float))
        return;
    RenderRip(pmatch, pcm);
}

void PostRemitEmit(REMIT *premit, EMITB *pemitb)
{
    STRUCT_OFFSET(premit, 0x120, LO *) = PloFindSwObject(g_psw, (GRFFSO)0x104, STRUCT_OFFSET(pemitb, 0x1f0, OID), STRUCT_OFFSET(pemitb, 0x7c, LO *));
    STRUCT_OFFSET(premit, 0x124, float) = STRUCT_OFFSET(pemitb, 0x1f4, float);
}

void UpdateRemit(REMIT *premit, float dt)
{
    UpdateRip(premit, dt);
    if (STRUCT_OFFSET(premit, 0x120, int) != 0)
    {
        float t = STRUCT_OFFSET(premit, 0x128, float) + dt * STRUCT_OFFSET(premit, 0x124, float);
        STRUCT_OFFSET(premit, 0x128, float) = t;
        if (t >= 1.0f)
        {
            do
            {
                struct
                {
                    int msgid;
                    int apad[7];
                    qword pos;
                    int apad2[8];
                } msg;
                msg.msgid = 4;
                msg.pos = STRUCT_OFFSET(premit, 0x80, qword);
                typedef void (*PFNH)(void *, void *);
                STRUCT_OFFSET(STRUCT_OFFSET(STRUCT_OFFSET(premit, 0x120, char *), 0, char *), 0x7c, PFNH)(STRUCT_OFFSET(premit, 0x120, void *), &msg);
                STRUCT_OFFSET(premit, 0x128, float) -= 1.0f;
            } while (STRUCT_OFFSET(premit, 0x128, float) >= 1.0f);
        }
    }
}

JUNK_ADDIU(10);
JUNK_WORD(0x7C450000);
JUNK_WORD(0x48220800);
