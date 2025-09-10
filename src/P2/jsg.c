#include <jsg.h>
#include <sw.h>
#include <clock.h>
#include <memory.h>
#include <sce/memset.h>

extern JSGE s_jsge;

void InitJsg(JSG *pjsg)
{
    InitLo(pjsg);
    pjsg->ajsge = (JSGE *)PvAllocSwImpl(0xa00);
    pjsg->unk3 = 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/jsg", GetJsgLocation__FP3JSGP2LOP6VECTORPf);

INCLUDE_ASM("asm/nonmatchings/P2/jsg", SetJsgFocus__FP3JSGP2LO);

INCLUDE_ASM("asm/nonmatchings/P2/jsg", SetJsgTn__FP3JSGP2TN);

INCLUDE_ASM("asm/nonmatchings/P2/jsg", NextJsgJsge__FP3JSG);

INCLUDE_ASM("asm/nonmatchings/P2/jsg", FIsJsgJsgeComplete__FP3JSGP4JSGE);

INCLUDE_ASM("asm/nonmatchings/P2/jsg", UpdateJsgJsge__FP3JSG);

INCLUDE_ASM("asm/nonmatchings/P2/jsg", ReadJsgJoystick__FP3JSGP3JOY);

int FIsJsgActive(JSG *pjsg)
{
    UpdateJsgJsge(pjsg);

    int fActive = 0;
    if (pjsg->cjsge > 0)
    {
        fActive = pjsg->ijsgeCur < pjsg->cjsge;
    }

    return fActive;
}

void ClearJsg(JSG *pjsg)
{
    if (pjsg->pjt)
    {
        RetractJsg(pjsg);
    }

    pjsg->ijsgeCur = 0;
    pjsg->cjsge = 0;
}

void ApplyJsg(JSG *pjsg, JT *pjt)
{
    STRUCT_OFFSET(pjt, 0x2740, JSG *) = pjsg; // pjt->pjsgCur
    pjsg->pjt = pjt;
    pjsg->ijsgeCur = -1;

    HandleLoSpliceEvent(pjsg, 0x17, 0, (void **)nullptr);

    if (pjsg->unk3)
    {
        AddGrfusr(4);
        IncrementSwHandsOff(pjsg->psw);
    }
}

void RetractJsg(JSG *pjsg)
{
    if (pjsg->pjt)
    {
        SetJsgTn(pjsg, (TN *)nullptr);
        SetJsgFocus(pjsg, (LO *)nullptr);

        if (pjsg->pasegaCur)
        {
            RetractAsega(pjsg->pasegaCur);
            pjsg->pasegaCur = 0;
        }

        SetClockRate(1.0f);
        pjsg->ijsgeCur = pjsg->cjsge;
        pjsg->ploContext = (LO *)nullptr;
        pjsg->pjsgeJoy = (JSGE *)nullptr;
        STRUCT_OFFSET(pjsg->pjt, 0x2740, JSG *) = (JSG *)nullptr; // pjsg->pjt->pjsgCur
        pjsg->pjt = (JT *)nullptr;

        HandleLoSpliceEvent(pjsg, 0x19, 0, 0);

        if (pjsg->unk3)
        {
            RemoveGrfusr(4);
            DecrementSwHandsOff(pjsg->psw);
        }
    }
}

/**
 * @todo Objdiff reports a 100% match, but compiler seemingly
 * adds extra instructions?
 */
INCLUDE_ASM("asm/nonmatchings/P2/jsg", PjsgeAllocJsg__FP3JSG5JSGEK3OIDi);
#ifdef SKIP_ASM
JSGE *PjsgeAllocJsg(JSG *pjsg, JSGEK jsgek, OID oid, int fAsync)
{
    JSGE *pjsge;
    int cjsge = pjsg->cjsge;

    if (cjsge < 0x80)
    {
        pjsg->cjsge = cjsge + 1;
        pjsge = &pjsg->ajsge[cjsge];
        memset(pjsge, 0, sizeof(JSGE));

        pjsge->jsgek = jsgek;
        pjsge->oid = oid;
        pjsge->fAsync = fAsync;
    }
    else
    {
        pjsge = &s_jsge;
    }

    return pjsge;
}
#endif // SKIP_ASM

void AddJsgContext(JSG *pjsg, OID oid)
{
    PjsgeAllocJsg(pjsg, JSGEK_Context, oid, 1);
}

void AddJsgCut(JSG *pjsg, OID oid)
{
    PjsgeAllocJsg(pjsg, JSGEK_Cut, oid, 1);
}

void AddJsgFocus(JSG *pjsg, OID oid)
{
    PjsgeAllocJsg(pjsg, JSGEK_Focus, oid, 1);
}

void AddJsgLabel(JSG *pjsg, OID oid)
{
    JSGE *pjsge = PjsgeAllocJsg(pjsg, JSGEK_Label, OID_Nil, 1);
    pjsge->label.oid = oid;
}

void AddJsgTunnel(JSG *pjsg, OID oid)
{
    PjsgeAllocJsg(pjsg, JSGEK_Tunnel, oid, 1);
}

void AddJsgPause(JSG *pjsg, OID oid, float dtPause)
{
    JSGE *pjsge = PjsgeAllocJsg(pjsg, JSGEK_Pause, oid, 0);
    pjsge->pause.dtPause = dtPause;
}

void AddJsgAseg(JSG *pjsg, OID oid, int fAsync)
{
    PjsgeAllocJsg(pjsg, JSGEK_Aseg, oid, fAsync);
}

void AddJsgJump(JSG *pjsg, OID oid, JSGJK jsgjk, JSGLK jsglk, int fAsync)
{
    JSGE *pjsge = PjsgeAllocJsg(pjsg, JSGEK_Jump, oid, fAsync);
    pjsge->jump.jsgjk = jsgjk;
    pjsge->jump.jsglk = jsglk;
}

void AddJsgRun(JSG *pjsg, OID oid, float uRun, int fAsync)
{
    JSGE *pjsge = PjsgeAllocJsg(pjsg, JSGEK_Run, oid, fAsync);
    pjsge->run.uRun = uRun;
}

void AddJsgClimb(JSG *pjsg, OID oid, float uClimb, int fAsync)
{
    JSGE *pjsge = PjsgeAllocJsg(pjsg, JSGEK_Climb, oid, fAsync);
    pjsge->climb.uClimb = uClimb;
}

void AddJsgAttack(JSG *pjsg, OID oid, FTAK ftak, int fAsync)
{
    JSGE *pjsge = PjsgeAllocJsg(pjsg, JSGEK_Attack, oid, fAsync);
    pjsge->attack.ftak = ftak;
}

void AddJsgClock(JSG *pjsg, float rdt)
{
    JSGE *pjsge = PjsgeAllocJsg(pjsg, JSGEK_Clock, OID_Nil, 1);
    pjsge->clock.rdt = rdt;
}

void AddJsgUnknown(JSG *pjsg)
{
    PjsgeAllocJsg(pjsg, JSGEK_Unknown, OID_Nil, 0);
}
