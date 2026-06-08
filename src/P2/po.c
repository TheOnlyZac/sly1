#include <po.h>
#include <jt.h>
#include <zap.h>
#include <cm.h>
#include <rip.h>
#include <aseg.h>

extern int g_ippoCur;
extern PO *g_appo[];

void InitPo(PO *ppo)
{
    InitSo(ppo);

    STRUCT_OFFSET(ppo, 0x598, PO *) = ppo;
    STRUCT_OFFSET(ppo, 0x580, int) = 1;

    SetPoPlayable(ppo, 1);
}

void ClonePo(PO *ppo, PO *ppoBase)
{
    CloneSo(ppo, ppoBase);
    if (STRUCT_OFFSET(ppo, 0x550, int) == 0) // ppo->fPlayable
    {
        STRUCT_OFFSET(ppo, 0x550, int) = 1; // ppo->fPlayable
        SetPoPlayable(ppo, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/po", HandlePoMessage__FP2PO5MSGIDPv);

void OnPoActive(PO *ppo, int fActive, PO *ppoOther)
{
    if (fActive)
    {
        STRUCT_OFFSET(ppo, 0x560, VU_VECTOR) = STRUCT_OFFSET(ppo, 0x140, VU_VECTOR);
        SetCmPolicy(g_pcm, CPP_Default, &STRUCT_OFFSET(g_pcm, 0x520, CPLCY), (SO *)ppo, 0);
    }
    else
    {
        int i;

        for (i = 1; i < 7; i++)
        {
            RevokeCmPolicy(g_pcm, 5, (CPP)i, 0, (SO *)ppo, 0);
        }
    }
}

extern SMP D_00269BC0;

void GetPoCpdefi(PO *ppo, float dt, CPDEFI *pcpdefi)
{
    GetSoCpdefi((SO *)ppo, dt, pcpdefi);

    if (STRUCT_OFFSET(ppo, 0x554, int) != 0)
    {
        STRUCT_OFFSET(pcpdefi, 0x10, VU_VECTOR) = STRUCT_OFFSET(ppo, 0x560, VU_VECTOR);
    }
    else
    {
        if (g_pcm->field41_0x224 == 0)
        {
            pcpdefi->posBase.z = GSmooth(STRUCT_OFFSET(ppo, 0x568, float),
                                         STRUCT_OFFSET(ppo, 0x148, float),
                                         dt, &D_00269BC0, NULL);
        }
        STRUCT_OFFSET(ppo, 0x560, VU_VECTOR) = STRUCT_OFFSET(pcpdefi, 0x10, VU_VECTOR);
    }
}

int FIsPoSoundBase(PO *ppo)
{
    return 1;
}

void MakePoActive(PO *ppo)
{
    if (ppo != PpoCur())
    {
        SwitchToPo(ppo);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/po", FInvulnerablePo__FP2PO3ZPK);

int FTakePoDamage(PO *ppo, ZPR *pzpr)
{
    return 0;
}

JTHS JthsCurrentPo(PO *ppo)
{
    return JTHS_Normal;
}

void FUN_00192498(PO *ppo, int *pi)
{
    void *pvt = STRUCT_OFFSET(ppo, 0x0, void *);
    int (*pfn)(PO *) = (int (*)(PO *))STRUCT_OFFSET(pvt, 0x144, void *);
    *pi = pfn(ppo);
}

void CollectPoPrize(PO *ppo, PCK pck, ALO *palo)
{
    switch (pck)
    {
    case PCK_Key:
        if (STRUCT_OFFSET(ppo, 0x5F0, ASEG *) != 0)
        {
            RIP *prip = PripNewRipg(RIPT_Match, NULL);
            STRUCT_OFFSET(ppo, 0x5AC, RIP *) = prip;
            STRUCT_OFFSET(ppo, 0x5D0, int) = 1;
            if (prip != NULL)
            {
                void (*pfnInit)(RIP *, float, VECTOR *, int) =
                    (void (*)(RIP *, float, VECTOR *, int))STRUCT_OFFSET(STRUCT_OFFSET(prip, 0x0, void *), 0x0, void *);
                pfnInit(prip, 1.0f, (VECTOR *)((uint8_t *)palo + 0x140), 0);
                SubscribeRipObject(prip, (LO *)ppo);
                STRUCT_OFFSET(prip, 0x1C, float) = TFindAsegLabel(STRUCT_OFFSET(ppo, 0x5F0, ASEG *), (OID)0x13F);
                STRUCT_OFFSET(prip, 0x20, int) = STRUCT_OFFSET(ppo, 0x59C, int);
                STRUCT_OFFSET(prip, 0xC0, qword) = STRUCT_OFFSET(STRUCT_OFFSET(palo, 0x14, uint8_t *), 0x1EE0, qword);
                STRUCT_OFFSET(prip, 0x134, ALO *) = palo;
            }
            {
                void (*pfnPrize)(PO *, int) =
                    (void (*)(PO *, int))STRUCT_OFFSET(STRUCT_OFFSET(ppo, 0x0, void *), 0x14C, void *);
                pfnPrize(ppo, 1);
            }
        }
        break;
    case PCK_Gold:
        {
            void (*pfnPrize)(PO *, int) =
                (void (*)(PO *, int))STRUCT_OFFSET(STRUCT_OFFSET(ppo, 0x0, void *), 0x14C, void *);
            pfnPrize(ppo, 2);
        }
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/po", FUN_001925C0);

PO *PpoCur()
{
    if (g_ippoCur < 0)
    {
        return NULL;
    }

	return g_appo[g_ippoCur];
}

INCLUDE_ASM("asm/nonmatchings/P2/po", PpoStart__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/po", _IppoFindPo__FP2PO);

INCLUDE_ASM("asm/nonmatchings/P2/po", AddPoToList__FP2PO);

INCLUDE_ASM("asm/nonmatchings/P2/po", RemovePoFromList__FP2PO);

void OnPoAdd(PO *ppo)
{
    OnSoAdd(ppo);
    AddPoToList(ppo);
}

void OnPoRemove(PO *ppo)
{
    OnSoRemove(ppo);
    RemovePoFromList(ppo);
}

INCLUDE_ASM("asm/nonmatchings/P2/po", SwitchToIppo__Fi);

JUNK_ADDIU(10);

void SetPoPlayable(PO *ppo, int fPlayable)
{
    if (STRUCT_OFFSET(ppo, 0x550, int) == fPlayable)
        return;

    STRUCT_OFFSET(ppo, 0x550, int) = fPlayable;
    if (fPlayable)
    {
        AddPoToList(ppo);
    }
    else
    {
        RemovePoFromList(ppo);
    }
}

void SwitchToPo(PO *ppo)
{
    SwitchToIppo(_IppoFindPo(ppo));
}

INCLUDE_ASM("asm/nonmatchings/P2/po", PpziCur__Fv);

void GetPoDiapi(PO *ppo, DIALOG *pdialog, DIAPI *pdiapi)
{
    pdiapi->fPlayable = 1;
    pdiapi->fCallable = 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/po", PlayPoDialog__FP2POP6DIALOG);

INCLUDE_ASM("asm/nonmatchings/P2/po", FUN_00192a70);

INCLUDE_ASM("asm/nonmatchings/P2/po", UpdatePo__FP2POf);

INCLUDE_ASM("asm/nonmatchings/P2/po", UsePoCharm__FP2PO);

INCLUDE_ASM("asm/nonmatchings/P2/po", FUN_00192dd0);

PO *FUN_001930B0(PO *ppo)
{
    return ppo;
}

INCLUDE_ASM("asm/nonmatchings/P2/po", po__static_initialization_and_destruction_04);

INCLUDE_ASM("asm/nonmatchings/P2/po", _GLOBAL_$I$InitPo__FP2PO);
