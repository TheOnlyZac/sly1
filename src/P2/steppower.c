#include "steppower.h"
#include <game.h>

INCLUDE_ASM(const s32, "P2/steppower", SetFsp__F3FSP);

INCLUDE_ASM(const s32, "P2/steppower", UpdateJtActivePowerUp__FP2JTP3JOY);

int IRotatePowerUp(JOY *pjoy, int iCur, int iMax, int *mpigrfvault)
{
    // If L2 or R2 not pressed, powerup is unchanged.
    if ((pjoy->grfbtnPressed & (PAD_L2 | PAD_R2)) == _NOT_PRESSED)
    {
        return iCur;
    }

    // Default to next powerup (assume R2 pressed).
    int direction = 1;
    if ((pjoy->grfbtnPressed & PAD_L2) != _NOT_PRESSED)
    {
        // L2 pressed, previous powerup.
        direction = -1;
    }

    SetJoyBtnHandled(pjoy, (ushort)(PAD_L2 | PAD_R2));

    uint grfValue;
    int iNew = iCur;
    int attemptsLeft = iMax;
    do
    {
        attemptsLeft--;
        iNew += direction;
        if (attemptsLeft < 0)
        {
            return iCur;
        }
        if (iNew < 0)
        {
            iNew = iMax - 1;
        }
        else if (iMax <= iNew)
        {
            iNew = 0;
        }
        grfValue = grfvault_something();
    } while ((grfValue & mpigrfvault[iNew]) == 0);

    // Return the new powerup index.
    return iNew;
}
