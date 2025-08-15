#include <po.h>

/**
 * @todo 100% matched but not integrated
 * https://decomp.me/scratch/Ktol3
 */
INCLUDE_ASM(const s32, "P2/po", InitPo__FP2PO);
#ifdef SKIP_ASM
// todo
#endif

INCLUDE_ASM(const s32, "P2/po", ClonePo__FP2POT0);

INCLUDE_ASM(const s32, "P2/po", HandlePoMessage__FP2PO5MSGIDPv);

INCLUDE_ASM(const s32, "P2/po", OnPoActive__FP2POiT0);

INCLUDE_ASM(const s32, "P2/po", GetPoCpdefi__FP2POfP6CPDEFI);
INCLUDE_ASM(const s32, "P2/po", func_00192410);

void MakePoActive(PO *ppo)
{
    if (ppo != PpoCur())
    {
        SwitchToPo(ppo);
    }
}

INCLUDE_ASM(const s32, "P2/po", FUN_00192450);
INCLUDE_ASM(const s32, "P2/po", func_00192488);
INCLUDE_ASM(const s32, "P2/po", func_00192490);

INCLUDE_ASM(const s32, "P2/po", FUN_00192498);

INCLUDE_ASM(const s32, "P2/po", CollectPoPrize__FP2PO3PCKP3ALO);
INCLUDE_ASM(const s32, "P2/po", func_001925C0);

INCLUDE_ASM(const s32, "P2/po", PpoCur__Fv);

INCLUDE_ASM(const s32, "P2/po", PpoStart__Fv);

INCLUDE_ASM(const s32, "P2/po", _IppoFindPo__FP2PO);

INCLUDE_ASM(const s32, "P2/po", AddPoToList__FP2PO);

INCLUDE_ASM(const s32, "P2/po", RemovePoFromList__FP2PO);

void OnPoAdd(PO *ppo)
{
    FUN_001B7A98(ppo);
    AddPoToList(ppo);
}

void OnPoRemove(PO *ppo)
{
    FUN_001B7B78(ppo);
    RemovePoFromList(ppo);
}

INCLUDE_ASM(const s32, "P2/po", SwitchToIppo__Fi);
INCLUDE_ASM(const s32, "P2/po", func_00192988);

/**
 * @todo Fix ppo fields once PO struct is complete.
 */
void SetPoPlayable(PO *ppo, int playable)
{
    if (*(int *)((uint8_t *)ppo + 0x550) != playable)
    {
        *(int *)((uint8_t *)ppo + 0x550) = playable;
        if (playable != 0)
        {
            AddPoToList(ppo);
        }
        else
        {
            RemovePoFromList(ppo);
        }
    }
}

void SwitchToPo(PO *ppo)
{
    SwitchToIppo(_IppoFindPo(ppo));
}

INCLUDE_ASM(const s32, "P2/po", PpziCur__Fv);
INCLUDE_ASM(const s32, "P2/po", func_00192A28);

INCLUDE_ASM(const s32, "P2/po", PlayPoDialog__FP2POP6DIALOG);

INCLUDE_ASM(const s32, "P2/po", FUN_00192a70);

INCLUDE_ASM(const s32, "P2/po", UpdatePo__FP2POf);

INCLUDE_ASM(const s32, "P2/po", UsePoCharm__FP2PO);

INCLUDE_ASM(const s32, "P2/po", FUN_00192dd0);
INCLUDE_ASM(const s32, "P2/po", func_001930B0);

INCLUDE_ASM(const s32, "P2/po", po__static_initialization_and_destruction_04);

INCLUDE_ASM(const s32, "P2/po", _GLOBAL_$I$InitPo__FP2PO);
