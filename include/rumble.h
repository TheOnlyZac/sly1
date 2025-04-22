/**
 * @file rumble.h
 *
 * @brief Joypad rumble.
 */
#ifndef RUMBLE_H
#define RUMBLE_H

#include "common.h"

/**
 * @todo This needs to go in rumble.c once it exists.
 */
// void InitRumble(RUMBLE *prumble, int nPort, int nSlot)
// {
//     if (prumble->rums == RUMS_Dead)
//     {
//         SetRumbleRums(prumble, RUMS_Idle);
//         prumble->nSlot = nSlot;
//     }
//     else
//     {
//         SetRumbleRums(prumble, RUMS_Stop);
//         prumble->nSlot = nSlot;
//     }
//     prumble->nPort = nPort;
// }

struct JOY; // Forward declaration

/**
 * @brief Rumble state
 */
enum RUMS
{
    RUMS_Dead = 0,
    RUMS_Idle = 1,
    RUMS_Rumble = 2,
    RUMS_Stop = 3,
    RUMS_Kill = 4,
    RUMS_Max = 5
};

/**
 * @brief Rumble kind
 */
enum RUMK
{
    RUMK_Nil = -1,
    RUMK_SteadyBuzz = 0,
    RUMK_LowThrob = 1,
    RUMK_MediumThrob = 2,
    RUMK_HardThrob = 3,
    RUMK_Blunt = 4,
    RUMK_Electric = 5,
    RUMK_Fire = 6,
    RUMK_Water = 7,
    RUMK_Crush = 8,
    RUMK_Break = 9,
    RUMK_Bomb = 10,
    RUMK_Max = 11
};

/**
 * @brief Rumble intensity
 */
struct RUMINS
{
    int fHighSpeedMotor;
    byte bLowSpeedMotor;
    byte unk1;
    byte unk2;
    float dt;
};

/**
 * @brief Rumble pattern
 */
struct RUMPAT
{
    int crumins;
    RUMINS arumins[32];
};

/**
 * @brief Rumble
 *
 * Combines the rumble state, rumble pattern, and rumble intensity along with the
 * port and slot of the controller.
 */
struct RUMBLE
{
    int nPort;
    int nSlot;
    RUMS rums;
    RUMPAT *prumpat;
    int irumins;
    float dtRumble;
    float dtRumins;
};

void InitRumble(RUMBLE *prumble, int nPort, int nSlot);
void TriggerRumbleRumk(RUMBLE *prumble, RUMK rumk, float dt);
void SetRumbleRums(RUMBLE *prumble, RUMS rums);

#endif // RUMBLE_H
