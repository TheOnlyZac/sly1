#include <po.h>
#include <jt.h>
#include <zap.h>

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

INCLUDE_ASM("asm/nonmatchings/P2/po", OnPoActive__FP2POiT0);

INCLUDE_ASM("asm/nonmatchings/P2/po", GetPoCpdefi__FP2POfP6CPDEFI);

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

INCLUDE_ASM("asm/nonmatchings/P2/po", FUN_00192498);

INCLUDE_ASM("asm/nonmatchings/P2/po", CollectPoPrize__FP2PO3PCKP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/po", FUN_001925C0);

PO *PpoCur()
{
    if (g_ippoCur < 0)
    {
        return (PO *)nullptr;
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

INCLUDE_ASM("asm/nonmatchings/P2/po", FUN_001930B0);

INCLUDE_ASM("asm/nonmatchings/P2/po", po__static_initialization_and_destruction_04);

INCLUDE_ASM("asm/nonmatchings/P2/po", _GLOBAL_$I$InitPo__FP2PO);
