#include "steppower.h"
#include <game.h>
#include <jt.h>
#include <screen.h>
#include <clock.h>
#include <steprail.h>

void SetFsp(FSP fsp) {
    // Cleanup current powerup
    switch (g_fsp) {
        case FSP_Ball:
            // If cur powerup is roll, reset JT's body state
            if (g_pjt != nullptr && g_pjt->unk2220 == 13) {
                SetJtJts(g_pjt, JTS_Stand, JTBS_Nil);
            }
            break;
        case FSP_Mine:
            // If cur powerup is mine, fade out the mine
            if (g_pjt != nullptr) {
                LO *ploMine = g_pjt->ploMine_1518;
                if ((ploMine != nullptr) && (FIsLoInWorld(ploMine))) {
                    FadeAloOut((ALO *)g_pjt->ploMine_1518, 0.5f);
                }
            }
            break;
        default:
            break;
    }

    if (g_pjt != nullptr) {
        g_rtClockPowerUp = 1.0f;
        if ((g_pjt->unk2750 != 0) && FIsLoInWorld((JT*)g_pjt->unk2750)) {
            func_001D32D8(g_pjt->unk2750, g_pjt, 1);
        }

        func_001D31D0(g_pjt, 0);
        if (g_pjt != nullptr && g_pjt == PpoCur()) {
            g_fsp = fsp;
        }
    }

    // If fsp is unchanged or invalid, return
    int fspLast = g_pgsCur->fspLast;
    if (fsp == fspLast || fsp >= (uint)FSP_Max) {
        return;
    }

    // Show note
    SetBlotDtVisible((NOTE*)&g_note.unk278, (g_pjt != nullptr) && (g_pjt == PpoCur()) ? 3.0 : 8.0);
    SetBlotFontScale(0.6, (NOTE*)&g_note.unk278);
    ((NOTE*)&g_note.unk278)->pvtnote->pfnSetNoteAchzDraw((NOTE*)&g_note.unk278, s_mpfspachz[fsp]);
    ((NOTE*)&g_note.unk278)->pvtnote->pfnShowBlot((NOTE*)&g_note.unk278);

    // Update last fsp in game state
    g_pgsCur->fspLast = fsp;
}

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
