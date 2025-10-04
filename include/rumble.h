/**
 * @file rumble.h
 *
 * @brief Joypad rumble.
 */
#ifndef RUMBLE_H
#define RUMBLE_H

#include "common.h"

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
    byte fHighSpeedMotor;
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
    /* 0x00 */ STRUCT_PADDING(1); // TODO: Add vtable.
    /* 0x04 */ int nPort;
    /* 0x08 */ int nSlot;
    /* 0x0c */ RUMS rums;
    RUMPAT *prumpat;
    int irumins;
    float dtRumble;
    float dtRumins;
};

void InitRumble(RUMBLE *prumble, int nPort, int nSlot);

void TriggerRumbleRumk(RUMBLE *prumble, RUMK rumk, float dt);

void SetRumbleRums(RUMBLE *prumble, RUMS rums);

void StopRumbleActuators(RUMBLE *prumble);

#endif // RUMBLE_H
