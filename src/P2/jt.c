#include <jt.h>
#include <alo.h>
#include <po.h>
#include <steppower.h>
#include <game.h>
#include <so.h>
#include <cm.h>
#include <ui.h>
#include <dialog.h>
#include <clock.h>
#include <stepcane.h>
#include <emitter.h>

extern BLOT g_binoc;
void FUN_001d4c98(JT *pjt);
extern "C" void FUN_001c4618(STEP *pstep, float f, int a, int b, int c, int *pd);

INCLUDE_ASM("asm/nonmatchings/P2/jt", InitJt__FP2JT);

extern SNIP D_00262E40[];

void LoadJtFromBrx(JT *pjt, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(pjt, pbis);
    SnipAloObjects(pjt, 0x97, D_00262E40);
    InferExpl(&STRUCT_OFFSET(pjt, 0x2428, EXPL *), pjt);
    STRUCT_OFFSET(pjt, 0x2284, float) = -1.0f;
    STRUCT_OFFSET(pjt, 0x21c8, float) = -1.0f;
    g_pjt = pjt;
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", PostJtLoad__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", PresetJtAccelBase);

INCLUDE_ASM("asm/nonmatchings/P2/jt", PresetJtAccel__FP2JTf);

INCLUDE_ASM("asm/nonmatchings/P2/jt", AdjustJtNewXp__FP2JTP2XPi);

extern float D_002637BC;
extern float D_002637C0;

void AdjustJtDz(JT *pjt, GRFADJ grfadj, DZ *pdz, int ixpd, float dt)
{
    if (pjt->jts == JTS_Sidestep)
    {
        if (grfadj & 0x10)
        {
            float g;
            if (grfadj & 1)
            {
                g = -STRUCT_OFFSET(pjt, 0x368, float) * STRUCT_OFFSET(pjt, 0x358, float) * g_clock.dt * D_002637BC;
            }
            else
            {
                g = -STRUCT_OFFSET(pjt, 0x368, float) * STRUCT_OFFSET(pjt, 0x358, float) * D_002637C0;
            }
            if (g < STRUCT_OFFSET(pdz, 0x30, float))
            {
                STRUCT_OFFSET(pdz, 0x30, float) = g;
            }
        }
    }
    else
    {
        AdjustStepDzBase(pjt, grfadj, pdz, ixpd);
    }
}

extern "C" void HandleJtGrfjtsc(JT *pjt)
{
    int grf = STRUCT_OFFSET(pjt, 0x2254, int);
    if (grf != 0)
    {
        if (grf & 8)
        {
            STRUCT_OFFSET(pjt, 0x2254, int) = grf & ~8;
            STRUCT_OFFSET(pjt, 0x224c, int) = STRUCT_OFFSET(pjt, 0x2264, int);
        }
        if (STRUCT_OFFSET(pjt, 0x2254, uint) & 1)
        {
            SetJtJts(pjt, STRUCT_OFFSET(pjt, 0x2258, JTS), STRUCT_OFFSET(pjt, 0x225c, JTBS));
        }
        if (STRUCT_OFFSET(pjt, 0x2254, uint) & 2)
        {
            SetJtJtcs(pjt, STRUCT_OFFSET(pjt, 0x2260, JTCS));
        }
        if (STRUCT_OFFSET(pjt, 0x2254, uint) & 0x10)
        {
            FUN_001d4c98(pjt);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtInternalXps__FP2JT);

extern float D_00274AD0[];

int FCheckJtXpBase(JT *pjt, XP *pxp, int ixpd)
{
    if (pjt->jts != JTS_Max)
    {
        return FCheckStepXpBase(pjt, pxp, ixpd);
    }
    if (STRUCT_OFFSET(pxp, 0x88, float) * D_00274AD0[ixpd] < 0.7f)
    {
        return 0;
    }
    int n = STRUCT_OFFSET(pxp, 0x9c, int);
    if (n < 7)
    {
        if (n < 4)
        {
            return 0;
        }
        return ixpd == 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", AdjustJtXpVelocity__FP2JTP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/jt", HandleJtMessage__FP2JT5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/jt", FTurnJtToTarget__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtBalance__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", RebuildJtXmg__FP2JTP3ALOfT1P6ACTADJP3XMG);

INCLUDE_ASM("asm/nonmatchings/P2/jt", FMatchJtXmg__FP2JTP3XMGP6ACTADJ);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtStand__FP2JT);

void ThrowJt(JT *pjt, VECTOR *pposTarget, float radVert, float gSpin)
{
    VECTOR posLaunch;
    VECTOR vecMuzzle;

    STRUCT_OFFSET(&posLaunch, 0, qword) = STRUCT_OFFSET(pjt, 0x140, qword);
    posLaunch.z -= 75.0f;
    FCalculateMuzzleVelocity(&posLaunch, pposTarget, radVert, &vecMuzzle, pjt);
    ((void (*)(JT *, VECTOR *))STRUCT_OFFSET(pjt->pvtso, 0x90, void *))(pjt, &vecMuzzle);
    if (pjt->jts != JTS_Sidestep)
    {
        SetJtJts(pjt, JTS_Jump, JTBS_Jump_Thrown);
        STRUCT_OFFSET(pjt, 0x226c, float) *= gSpin;
        if (gSpin == 0.0f)
        {
            STRUCT_OFFSET(pjt, 0x2498, int) = 0;
        }
    }
}

void UnhookJt(JT *pjt)
{
    switch (pjt->jts)
    {
    case JTS_Zap:
    case JTS_Edge:
        STRUCT_OFFSET(pjt, 0x224c, int) = 1;
        SetJtJts(pjt, JTS_Jump, JTBS_Jump_Fall);
        break;
    case JTS_Pipe:
    {
        int n = STRUCT_OFFSET(pjt, 0x239c, int);
        if (n < 6)
        {
            if (n >= 4)
            {
                SetJtJts(pjt, JTS_Jump, JTBS_Jump_Fall);
            }
        }
        break;
    }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", CalculateJtToolSpin__FP2JTfP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/jt", RenderJtAll__FP2JTP2CMP2RO);

void FUN_00172530(JT *pjt)
{
    UpdateStepXfWorld(pjt);
    if (pjt->jts != JTS_Pipe || STRUCT_OFFSET(pjt, 0x239c, int) != 7)
    {
        int a = STRUCT_OFFSET(pjt, 0x610, int);
        if (a != 0 && STRUCT_OFFSET(pjt, 0x614, int) != 0)
        {
            FUN_001c4618(pjt, 6.0f, a, a, STRUCT_OFFSET(pjt, 0x620, int), &STRUCT_OFFSET(pjt, 0x1190, int));
            FUN_001c4618(pjt, 6.0f, STRUCT_OFFSET(pjt, 0x614, int), STRUCT_OFFSET(pjt, 0x614, int), STRUCT_OFFSET(pjt, 0x624, int), &STRUCT_OFFSET(pjt, 0x1290, int));
            return;
        }
    }
    STRUCT_OFFSET(pjt, 0x11e0, int) = 0;
    STRUCT_OFFSET(pjt, 0x12e0, int) = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", FUN_001725e0);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtTool__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", FUN_00172898);

void UpdateJtPosWorldPrev(JT *pjt)
{
    UpdateSoPosWorldPrev(pjt);
    STRUCT_OFFSET(pjt, 0x21cc, int) = 0;
}

void FUN_00172b08(JT *pjt)
{
    STRUCT_OFFSET(pjt, 0x21e0, qword) = STRUCT_OFFSET(STRUCT_OFFSET(pjt, 0x23d4, void *), 0x140, qword);
    STRUCT_OFFSET(pjt, 0x21cc, int) = 0;
    ProjectSoTransform(pjt, g_clock.dt, 0);
    if (STRUCT_OFFSET(pjt, 0x223c, int) == 0)
    {
        STRUCT_OFFSET(pjt, 0x21d0, qword) = STRUCT_OFFSET(pjt, 0x140, qword);
        STRUCT_OFFSET(pjt, 0x21f0, qword) = STRUCT_OFFSET(STRUCT_OFFSET(pjt, 0x23d4, void *), 0x140, qword);
        STRUCT_OFFSET(pjt, 0x21cc, int) = 3;
        pjt->pvtso->pfnUpdateSoBounds(pjt);
    }
    else
    {
        STRUCT_OFFSET(pjt, 0x21cc, int) = 0;
    }
}

void UpdateJtBounds(JT *pjt)
{
    int i;
    UpdateSoBounds(pjt);
    for (i = 0; i < STRUCT_OFFSET(pjt, 0x21cc, int); i++)
    {
        ExtendSoBounds(pjt, &STRUCT_OFFSET(pjt, 0x21d0 + i * 0x10, VECTOR), STRUCT_OFFSET(pjt, 0x2420, float));
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", PsoGetJtEffect__FP2JTPi);

INCLUDE_ASM("asm/nonmatchings/P2/jt", AddJtCustomXps__FP2JTP2SOiP3BSPT3PP2XP);

CT CtTorqueJt(JT *pjt)
{
    if (pjt->jts == JTS_Zap || pjt->jts == (JTS)13)
    {
        return CT_Free;
    }
    return CT_Locked;
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", FUN_00172ee0);

INCLUDE_ASM("asm/nonmatchings/P2/jt", GetJtCpdefiFlatten__FP2JTP6CPDEFI);

void FUN_00173708(JT *pjt, int fActive, PO *ppoOther)
{
    OnPoActive(pjt, fActive, ppoOther);
    SetFsp((FSP)(fActive ? g_pgsCur->fspLast : -1));
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", FUN_00173750);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtActive__FP2JTP3JOYf);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJt__FP2JTf);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtDrive__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", ChooseJtPhys__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", EnableJtActadj__FP2JTi);

INCLUDE_ASM("asm/nonmatchings/P2/jt", SetJtJts__FP2JT3JTS4JTBS);

void ProfileJt(JT *pjt, int fProfile)
{
    return;
}

void SetJtPuppet(JT *pjt, ASEGA *pasega)
{
    SetJtJts(pjt, pasega ? JTS_Peek : JTS_Stand, JTBS_Nil);
}

void FUN_00177828(JT *pjt, int n)
{
    STRUCT_OFFSET(pjt, 0x2bd8, int) = n;
    STRUCT_OFFSET(pjt, 0x4b8, int) = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", PaloAbsorbWkr__FP3WKRiPP3ALO);

int NCmpWkr(WKR *pwkr0, WKR *pwkr1)
{
    return pwkr0->gSort > pwkr1->gSort ? 1 : -1;
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtEffect__FP2JT);

int FIsJtSoundBase(JT *pjt)
{
    if (pjt->jts == JTS_Ball && pjt->jtbs == JTBS_Zap_Electric)
    {
        return 0;
    }
    return !FActiveCplcy(&g_pcm->cpman);
}

void CollectJtPrize(JT *pjt, PCK pck, ALO *paloOther)
{
    CollectPoPrize(pjt, pck, paloOther);
    switch (pck)
    {
    case PCK_Key:
        SetJtJts(pjt, JTS_Rush, JTBS_Rush_Attack);
        break;
    case PCK_Gold:
        SetJtJts(pjt, JTS_Rush, JTBS_Rush_Bounce);
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", GetJtDiapi__FP2JTP6DIALOGP5DIAPI);

void PlayJtDialog(JT *pjt, DIALOG *pdialog)
{
    if ((uint)(STRUCT_OFFSET(pdialog, 0x2d0, int) - 1) < 2)
    {
        BLOT *pbinoc = &g_binoc;
        STRUCT_OFFSET(pbinoc, 0x324, DIALOG *) = pdialog;
        PushUiActiveBlot(&g_ui, pbinoc);
    }
    else if (pjt->jts != JTS_Ball)
    {
        STRUCT_OFFSET(pjt, 0x225c, int) = 0x21;
        STRUCT_OFFSET(pjt, 0x2bd0, DIALOG *) = pdialog;
        STRUCT_OFFSET(pjt, 0x2258, int) = JTS_Ball;
        STRUCT_OFFSET(pjt, 0x2254, uint) |= 1;
    }
}
