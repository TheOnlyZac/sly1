#include <rumble.h>
#include <clock.h>
#include <sdk/ee/libpad.h>

/**
 * @brief Rename.
 */
extern int DAT_0026c3dc;

void InitRumble(RUMBLE *prumble, int nPort, int nSlot)
{
    if (prumble->rums == RUMS_Dead)
    {
        SetRumbleRums(prumble, RUMS_Idle);
    }
    else
    {
        SetRumbleRums(prumble, RUMS_Stop);
    }

    prumble->nPort = nPort;
    prumble->nSlot = nSlot;
}

INCLUDE_ASM("asm/nonmatchings/P2/rumble", UpdateRumble__FP6RUMBLE);

INCLUDE_ASM("asm/nonmatchings/P2/rumble", TriggerRumbleRumk__FP6RUMBLE4RUMKf);

INCLUDE_ASM("asm/nonmatchings/P2/rumble", TriggerRumbleRumpat__FP6RUMBLEP6RUMPATf);

/**
 * @brief 100% match. Rodata issue.
 * https://decomp.me/scratch/tFbRA
 */
INCLUDE_ASM("asm/nonmatchings/P2/rumble", SetRumbleRums__FP6RUMBLE4RUMS);
#ifdef SKIP_ASM
void SetRumbleRums(RUMBLE *prumble, RUMS rums)
{
    if (rums == prumble->rums)
        return;

    unsigned char abShockDirect[6];
    switch(rums)
    {
        case RUMS_Dead:
        case RUMS_Idle:
        {
            break;
        }
        case RUMS_Rumble:
        {
            abShockDirect[0] = prumble->prumpat->arumins[0].fHighSpeedMotor;
            abShockDirect[1] = prumble->prumpat->arumins[0].bLowSpeedMotor;
            scePadSetActDirect(prumble->nPort, prumble->nSlot, abShockDirect);
            prumble->rums = rums;
            break;
        }
        case RUMS_Stop:
        case RUMS_Kill:
        {
            StopRumbleActuators(prumble);
            prumble->dtRumins = g_clock.dtReal * 4.0f;
        }
        default:
        {
            prumble->rums = rums;
            break;
        }
    }
}
#endif // SKIP_ASM

void StopRumbleActuators(RUMBLE *prumble)
{
    unsigned char abShockDirect[6];
    abShockDirect[0] = '\0';
    abShockDirect[1] = '\0';
    scePadSetActDirect(prumble->nPort, prumble->nSlot, abShockDirect);
}

/**
 * @todo Rename and figure out what does this do.
 */
void FUN_001A7E70()
{
    if (DAT_0026c3dc == 0)
    {
        DAT_0026c3dc = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rumble", FUN_001A7E90);

INCLUDE_ASM("asm/nonmatchings/P2/rumble", FUN_001A7EE8);

INCLUDE_ASM("asm/nonmatchings/P2/rumble", FUN_001A7F50);
