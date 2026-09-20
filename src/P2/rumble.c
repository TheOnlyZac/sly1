#include <rumble.h>
#include <clock.h>
#include <gs.h>
#include <sdk/ee/libpad.h>

/**
 * @brief List of rumble patterns for each RUMK.
 */
static RUMPAT s_mprumkrumpat[RUMK_Max] =
{
    // RUMK_SteadyBuzz
    {
        1,
        {
            {0x01, 0x00, 0x00, 0x00, 0.05f},
        },
    },
    // RUMK_LowThrob
    {
        2,
        {
            {0x00, 0x96, 0x00, 0x00, 0.05f},
            {0x00, 0x00, 0x00, 0x00, 0.05f},
        },
    },
    // RUMK_MediumThrob
    {
        2,
        {
            {0x00, 0xd2, 0x00, 0x00, 0.05f},
            {0x00, 0x00, 0x00, 0x00, 0.10f},
        },
    },
    // RUMK_HardThrob
    {
        2,
        {
            {0x00, 0xff, 0x00, 0x00, 0.10f},
            {0x00, 0x00, 0x00, 0x00, 0.10f},

        },
    },
    // RUMK_Blunt
    {
        7,
        {
            {0x00, 0xd2, 0x00, 0x00, 0.10f},
            {0x00, 0xbe, 0x00, 0x00, 0.01f},
            {0x00, 0xaa, 0x00, 0x00, 0.01f},
            {0x00, 0x96, 0x00, 0x00, 0.01f},
            {0x00, 0x82, 0x00, 0x00, 0.01f},
            {0x00, 0x6e, 0x00, 0x00, 0.01f},
            {0x00, 0x00, 0x00, 0x00, 0.25f},
        },
    },
    // RUMK_Electric
    {
        2,
        {
            {0x01, 0xff, 0x00, 0x00, 0.10f},
            {0x01, 0x00, 0x00, 0x00, 0.05f},
        },
    },
    // RUMK_Fire
    {
        2,
        {
            {0x00, 0xaa, 0x00, 0x00, 0.05f},
            {0x00, 0x00, 0x00, 0x00, 0.10f},
        },
    },
    // RUMK_Water
    {
        2,
        {
            {0x00, 0xaa, 0x00, 0x00, 0.05f},
            {0x00, 0x00, 0x00, 0x00, 0.10f},
        },
    },
    // RUMK_Crush
    {
        2,
        {
            {0x00, 0xaa, 0x00, 0x00, 0.05f},
            {0x00, 0x00, 0x00, 0x00, 0.10f},
        },
    },
    // RUMK_Break
    {
        3,
        {
            {0x00, 0xa0, 0x00, 0x00, 0.15f},
            {0x00, 0x00, 0x00, 0x00, 0.10f},
            {0x00, 0x5a, 0x00, 0x00, 0.05f},
        },
    },
    // RUMK_Bomb
    {
        5,
        {
            {0x00, 0xff, 0x00, 0x00, 0.20f},
            {0x00, 0x00, 0x00, 0x00, 0.08f},
            {0x00, 0xc8, 0x00, 0x00, 0.13f},
            {0x00, 0x00, 0x00, 0x00, 0.06f},
            {0x00, 0x96, 0x00, 0x00, 0.11f},
        },
    },
};

/**
 * @todo Rename.
 */
int g_rumbleUnk = 0;

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

void UpdateRumble(RUMBLE *prumble)
{
    byte abShockDirect[6];
    float dtReal = g_clock.dtReal;

    switch(prumble->rums)
    {
        case RUMS_Rumble:
        {
            // Continue the active rumble pattern.
            if (g_clock.fEnabled && prumble->dtRumble > 0.0f)
            {
                prumble->dtRumins -= dtReal;

                // Advance to the next pattern entry when the current element has expired.
                if (prumble->dtRumins <= 0.0f)
                {
                    if (++prumble->irumins >= prumble->prumpat->crumins)
                    {
                        prumble->irumins = 0;
                    }

                    // NOTE: Unfortunately we need to have the repeated expressions for a full match.
                    abShockDirect[0] = prumble->prumpat->arumins[prumble->irumins].fHighSpeedMotor;
                    abShockDirect[1] = prumble->prumpat->arumins[prumble->irumins].bLowSpeedMotor;
                    scePadSetActDirect(prumble->nPort, prumble->nSlot, abShockDirect);
                    prumble->dtRumins = prumble->prumpat->arumins[prumble->irumins].dt;
                }

                prumble->dtRumble -= dtReal;
            }
            else
            {
                SetRumbleRums(prumble, RUMS_Stop);
            }
            break;
        }
        case RUMS_Stop:
        case RUMS_Kill:
        {
            // Keep the actuators stopped until the remaining rumble interval has expired.
            if (prumble->dtRumins > 0.0f)
            {
                StopRumbleActuators(prumble);
                prumble->dtRumins -= dtReal;
            }
            else
            {
                SetRumbleRums(prumble, (prumble->rums == RUMS_Stop) ? RUMS_Idle : RUMS_Dead);
            }
            break;
        }
        default:
        {
            return;
        }
    }
}

void TriggerRumbleRumk(RUMBLE *prumble, RUMK rumk, float dt)
{
    TriggerRumbleRumpat(prumble, &s_mprumkrumpat[rumk], dt);
}

void TriggerRumbleRumpat(RUMBLE *prumble, RUMPAT *prumpat, float dt)
{
    if (prumble->rums != RUMS_Dead && prumpat->crumins > 0 && RumbleUnknown3(g_pgsCur) != 0)
    {
        prumble->dtRumble = dt;
        prumble->prumpat = prumpat;
        prumble->irumins = 0;
        prumble->dtRumins = prumpat->arumins[0].dt;
        prumble->rums = RUMS_Nil;
        SetRumbleRums(prumble, RUMS_Rumble);
    }
}

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

    byte abShockDirect[6];
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
    byte abShockDirect[6];
    abShockDirect[0] = '\0';
    abShockDirect[1] = '\0';
    scePadSetActDirect(prumble->nPort, prumble->nSlot, abShockDirect);
}

/**
 * @todo Rename and figure out what does this do.
 */
void RumbleUnknown1()
{
    if (g_rumbleUnk == 0)
    {
        g_rumbleUnk = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rumble", RumbleUnknown2__FP2GS);

INCLUDE_ASM("asm/nonmatchings/P2/rumble", RumbleUnknown3__FP2GS);

INCLUDE_ASM("asm/nonmatchings/P2/rumble", RumbleUnknown4__FP2GS);
