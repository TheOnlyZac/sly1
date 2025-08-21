#include <rumble.h>

INCLUDE_ASM(const s32, "P2/rumble", InitRumble__FP6RUMBLEii);
#ifdef SKIP_ASM
/**
 * @todo 20.35% matching.
 */
void InitRumble(RUMBLE *prumble, int nPort, int nSlot)
{
    if (prumble->rums == RUMS_Dead)
    {
        SetRumbleRums(prumble, RUMS_Idle);
        prumble->nSlot = nSlot;
    }
    else
    {
        SetRumbleRums(prumble, RUMS_Stop);
        prumble->nSlot = nSlot;
    }
    prumble->nPort = nPort;
}
#endif

INCLUDE_ASM(const s32, "P2/rumble", func_001A7B88);

INCLUDE_ASM(const s32, "P2/rumble", TriggerRumbleRumk__FP6RUMBLE4RUMKf);

INCLUDE_ASM(const s32, "P2/rumble", func_001A7D18);

INCLUDE_ASM(const s32, "P2/rumble", SetRumbleRums__FP6RUMBLE4RUMS);

INCLUDE_ASM(const s32, "P2/rumble", func_001A7E40);

INCLUDE_ASM(const s32, "P2/rumble", func_001A7E70);

INCLUDE_ASM(const s32, "P2/rumble", func_001A7E90);

INCLUDE_ASM(const s32, "P2/rumble", func_001A7EE8);

INCLUDE_ASM(const s32, "P2/rumble", func_001A7F50);
