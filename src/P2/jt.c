#include <jt.h>
#include <game.h>
#include <step.h>
#include <lo.h>
#include <cplcy.h>
#include <stepcane.h>
#include <emitter.h>

INCLUDE_ASM("asm/nonmatchings/P2/jt", InitJt__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", LoadJtFromBrx__FP2JTP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/jt", PostJtLoad__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", PresetJtAccelBase);

INCLUDE_ASM("asm/nonmatchings/P2/jt", PresetJtAccel__FP2JTf);

INCLUDE_ASM("asm/nonmatchings/P2/jt", AdjustJtNewXp__FP2JTP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/jt", AdjustJtDz__FP2JTiP2DZif);

extern "C" void FUN_001d4c98(JT *pjt);

extern "C" void HandleJtGrfjtsc(JT *pjt)
{
    int grfjtsc = STRUCT_OFFSET(pjt, 0x2254, int);
    if (grfjtsc == 0)
        return;

    if (grfjtsc & 0x8)
    {
        STRUCT_OFFSET(pjt, 0x2254, int) = grfjtsc & ~0x8;
        STRUCT_OFFSET(pjt, 0x224C, int) = STRUCT_OFFSET(pjt, 0x2264, int);
    }

    if (STRUCT_OFFSET(pjt, 0x2254, int) & 0x1)
        SetJtJts(pjt, STRUCT_OFFSET(pjt, 0x2258, JTS), STRUCT_OFFSET(pjt, 0x225C, JTBS));

    if (STRUCT_OFFSET(pjt, 0x2254, int) & 0x2)
        SetJtJtcs(pjt, STRUCT_OFFSET(pjt, 0x2260, JTCS));

    if (STRUCT_OFFSET(pjt, 0x2254, int) & 0x10)
        FUN_001d4c98(pjt);
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtInternalXps__FP2JT);

int FCheckJtXpBase(JT *pjt, XP *pxp, int ixpd)
{
	extern float D_00274AD0[];

	if (pjt->jts != JTS_Max)
	{
		return FCheckStepXpBase(pjt, pxp, ixpd);
	}

	if (STRUCT_OFFSET(pxp, 0x88, float) * D_00274AD0[ixpd] < 0.7f)
	{
		return 0;
	}

	{
		int n = STRUCT_OFFSET(pxp, 0x9C, int);
		if (n >= 7)
			return 0;
		if (n < 4)
			return 0;
		return ixpd == 0;
	}
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", AdjustJtXpVelocity__FP2JTP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/jt", HandleJtMessage__FP2JT5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/jt", FTurnJtToTarget__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtBalance__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", RebuildJtXmg__FP2JTP3ALOfT1P6ACTADJP3XMG);

INCLUDE_ASM("asm/nonmatchings/P2/jt", FMatchJtXmg__FP2JTP3XMGP6ACTADJ);

struct XMG;

int FTurnJtToTarget(JT *pjt);
void RebuildJtXmg(JT *pjt, ALO *palo, float s, ALO *palo2, ACTADJ *pactadj, XMG *pxmg);
int FMatchJtXmg(JT *pjt, XMG *pxmg, ACTADJ *pactadj);

void UpdateJtStand(JT *pjt)
{
    if (FTurnJtToTarget(pjt) == 0)
    {
        if (STRUCT_OFFSET(pjt, 0x690, int) != 0)
        {
            VECTOR w;
            float g;

            CalculateAloMovement(STRUCT_OFFSET(pjt, 0x6C0, ALO *), NULL,
                                 (VECTOR *)((char *)pjt + 0x6A0), NULL, &w, NULL, NULL);
            g = GLimitAbs(w.z, 10.0f);
            w.z = g;
            STRUCT_OFFSET(pjt, 0x638, float) += g * g_clock.dt;
        }
    }

    if (STRUCT_OFFSET(pjt, 0x250C, ACTADJ *) != NULL)
    {
        RebuildJtXmg(pjt, STRUCT_OFFSET(pjt, 0x628, ALO *), 5.0f, STRUCT_OFFSET(pjt, 0x620, ALO *),
                     STRUCT_OFFSET(pjt, 0x250C, ACTADJ *), (XMG *)((char *)pjt + 0x1190));
        RebuildJtXmg(pjt, STRUCT_OFFSET(pjt, 0x62C, ALO *), 5.0f, STRUCT_OFFSET(pjt, 0x624, ALO *),
                     STRUCT_OFFSET(pjt, 0x2510, ACTADJ *), (XMG *)((char *)pjt + 0x1290));

        if (FMatchJtXmg(pjt, (XMG *)((char *)pjt + 0x1190), STRUCT_OFFSET(pjt, 0x250C, ACTADJ *)))
        {
            if (FMatchJtXmg(pjt, (XMG *)((char *)pjt + 0x1290), STRUCT_OFFSET(pjt, 0x2510, ACTADJ *)))
                return;
        }

        if (STRUCT_OFFSET(pjt, 0x118C, int) != 0)
            return;

        if (STRUCT_OFFSET(pjt, 0x1188, SM *) != NULL)
        {
            if (IsmsFindSmOptional(STRUCT_OFFSET(pjt, 0x1188, SM *), (OID)0x148) >= 0)
                SeekSma(STRUCT_OFFSET(pjt, 0x2234, SMA *), (OID)0x148);
            STRUCT_OFFSET(pjt, 0x118C, int) = 1;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", ThrowJt__FP2JTP6VECTORff);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UnhookJt__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", CalculateJtToolSpin__FP2JTfP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/jt", RenderJtAll__FP2JTP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/jt", FUN_00172530);

INCLUDE_ASM("asm/nonmatchings/P2/jt", FUN_001725e0);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtTool__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", FUN_00172898);

void UpdateJtPosWorldPrev(JT *pjt)
{
    UpdateSoPosWorldPrev(pjt);
    STRUCT_OFFSET(pjt, 0x21CC, int) = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", FUN_00172b08);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtBounds__FP2JT);

SO *PsoGetJtEffect(JT *pjt, int *pn)
{
    SO *pso;

    pso = STRUCT_OFFSET(pjt, 0x25D8, SO *);
    if (pso != NULL)
    {
        if (FIsLoInWorld(pso))
        {
            *pn = 0;
            return STRUCT_OFFSET(pjt, 0x25D8, SO *);
        }
    }

    pso = STRUCT_OFFSET(pjt, 0x25E0, SO *);
    if (pso != NULL)
    {
        if (FIsLoInWorld(pso))
        {
            *pn = 1;
            return STRUCT_OFFSET(pjt, 0x25E0, SO *);
        }
    }

    pso = STRUCT_OFFSET(pjt, 0x25DC, SO *);
    if (pso != NULL)
    {
        if (FIsLoInWorld(pso))
        {
            *pn = 2;
            return STRUCT_OFFSET(pjt, 0x25DC, SO *);
        }
    }

    pso = STRUCT_OFFSET(pjt, 0x25E4, SO *);
    if (pso != NULL)
    {
        if (FIsLoInWorld(pso))
        {
            *pn = 2;
            return STRUCT_OFFSET(pjt, 0x25E4, SO *);
        }
    }

    pso = STRUCT_OFFSET(pjt, 0x25E8, SO *);
    if (pso != NULL)
    {
        if (FIsLoInWorld(pso))
        {
            *pn = 1;
            return STRUCT_OFFSET(pjt, 0x25E8, SO *);
        }
    }

    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", AddJtCustomXps__FP2JTP2SOiP3BSPT3PP2XP);

int CtTorqueJt(JT *pjt)
{
    if (pjt->jts == 3 || pjt->jts == 0xD)
        return 0;
    return 3;
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", FUN_00172ee0);

INCLUDE_ASM("asm/nonmatchings/P2/jt", GetJtCpdefiFlatten__FP2JTP6CPDEFI);

INCLUDE_ASM("asm/nonmatchings/P2/jt", FUN_00173708);

INCLUDE_ASM("asm/nonmatchings/P2/jt", FUN_00173750);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtActive__FP2JTP3JOYf);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJt__FP2JTf);

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtDrive__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jt", ChooseJtPhys__FP2JT);

void EnableJtActadj(JT *pjt, int grf)
{
    int a0;
    int a2;

    if (STRUCT_OFFSET(pjt, 0x2500, void *) != NULL)
    {
        a0 = grf & 0x1;
        STRUCT_OFFSET(STRUCT_OFFSET(pjt, 0x2500, char *), 0x10, char) = a0 ? 9 : -1;
        STRUCT_OFFSET(STRUCT_OFFSET(pjt, 0x2504, char *), 0x10, char) = a0 ? 9 : -1;
        STRUCT_OFFSET(STRUCT_OFFSET(pjt, 0x2508, char *), 0x10, char) = a0 ? 9 : -1;
        a2 = grf & 0x2;
        STRUCT_OFFSET(STRUCT_OFFSET(pjt, 0x250C, char *), 0x10, char) = a2 ? 9 : -1;
        STRUCT_OFFSET(STRUCT_OFFSET(pjt, 0x2510, char *), 0x10, char) = a2 ? 9 : -1;

        (*(*(void (***)(void *))STRUCT_OFFSET(pjt, 0x24F8, void *))[0x2F])(STRUCT_OFFSET(pjt, 0x24F8, void *));
        (*(*(void (***)(void *))STRUCT_OFFSET(pjt, 0x618, void *))[0x2F])(STRUCT_OFFSET(pjt, 0x618, void *));
        (*(*(void (***)(void *))STRUCT_OFFSET(pjt, 0x61C, void *))[0x2F])(STRUCT_OFFSET(pjt, 0x61C, void *));
        (*(*(void (***)(void *))STRUCT_OFFSET(pjt, 0x610, void *))[0x2F])(STRUCT_OFFSET(pjt, 0x610, void *));
        (*(*(void (***)(void *))STRUCT_OFFSET(pjt, 0x614, void *))[0x2F])(STRUCT_OFFSET(pjt, 0x614, void *));
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", SetJtJts__FP2JT3JTS4JTBS);

void ProfileJt(JT *pjt, int fProfile)
{
    return;
}

void SetJtPuppet(JT *pjt, ASEGA *paseg)
{
    SetJtJts(pjt, paseg ? JTS_Peek : JTS_Stand, JTBS_Nil);
}

void FUN_00177828(JT *pjt, int n)
{
    STRUCT_OFFSET(pjt, 0x2bd8, int) = n;
    STRUCT_OFFSET(pjt, 0x4b8, int) = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", PaloAbsorbWkr__FP3WKRiPP3ALO);

int NCmpWkr(WKR *pwkr1, WKR *pwkr2)
{
    return STRUCT_OFFSET(pwkr1, 0x14, float) > STRUCT_OFFSET(pwkr2, 0x14, float) ? 1 : -1;
}

INCLUDE_ASM("asm/nonmatchings/P2/jt", UpdateJtEffect__FP2JT);

int FIsJtSoundBase(JT *pjt)
{
    if (pjt->jts == JTS_Ball && pjt->jtbs == JTBS_Zap_Electric)
        return 0;

    return !FActiveCplcy(&STRUCT_OFFSET(g_pcm, 0x454, CPLCY));
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

INCLUDE_ASM("asm/nonmatchings/P2/jt", PlayJtDialog__FP2JTP6DIALOG);
