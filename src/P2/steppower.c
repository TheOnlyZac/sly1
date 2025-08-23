#include "steppower.h"
#include <game.h>
#include <jt.h>
#include <screen.h>
#include <clock.h>
#include <steprail.h>

extern uint D_00274F38; // todo: find where this belongs.
extern uint D_002701F8; // todo: find where this belongs.

void SetFsp(FSP fsp)
{
    // Cleanup the current powerup before we set the one
    switch (g_fsp)
    {
    case FSP_Ball:
        // If cur powerup is roll, reset JT's body state
        if (g_pjt != nullptr && g_pjt->unk2220 == 13)
        {
            SetJtJts(g_pjt, JTS_Stand, JTBS_Nil);
        }
        break;
    case FSP_Mine:
        // If cur powerup is mine, fade out the mine
        if (g_pjt != nullptr)
        {
            LO *ploMine = g_pjt->ploMine_1518;
            if ((ploMine != nullptr) && (FIsLoInWorld(ploMine)))
            {
                FadeAloOut((ALO *)g_pjt->ploMine_1518, 0.5f);
            }
        }
        break;
    default:
        break;
    }

    if (g_pjt != nullptr)
    {
        g_rtClockPowerUp = 1.0f;
        if ((g_pjt->unk2750 != 0) && FIsLoInWorld((JT *)g_pjt->unk2750))
        {
            func_001D32D8(g_pjt->unk2750, g_pjt, 1);
        }

        func_001D31D0(g_pjt, 0);
        if (g_pjt != nullptr && g_pjt == PpoCur())
        {
            g_fsp = fsp;
        }
    }

    // If fsp is unchanged or invalid, return
    int fspLast = g_pgsCur->fspLast;
    if (fsp == fspLast || fsp >= (uint)FSP_Max)
    {
        return;
    }

    // Show note in lower-left corner indicating the new powerup
    SetBlotDtVisible((NOTE *)&g_note.unk278, (g_pjt != nullptr) && (g_pjt == PpoCur()) ? 3.0 : 8.0);
    SetBlotFontScale(0.6, (NOTE *)&g_note.unk278);
    ((NOTE *)&g_note.unk278)->pvtnote->pfnSetNoteAchzDraw((NOTE *)&g_note.unk278, s_mpfspachz[fsp]);
    ((NOTE *)&g_note.unk278)->pvtnote->pfnShowBlot((NOTE *)&g_note.unk278);

    // Update last fsp record in game state
    g_pgsCur->fspLast = fsp;
}

INCLUDE_ASM(const s32, "P2/steppower", UpdateJtActivePowerUp__FP2JTP3JOY);
#ifdef SKIP_ASM
/**
 * @todo 2.01% match.
 */
void UpdateJtActivePowerUp(JT *pjt, JOY *pjoy)
{
    uint unk1;
    FSP fsp;
    GRFVAULT grfvault;

    grfvault = GetGrfvault_unknown();

    // FFloatsNear(float, float, float);
    // g_rtClockPowerUp
    // D_002701F8
    // IRotatePowerUp(pjoy, int, int, int*);
    // SetFsp(FSP);
    // GSmooth(float, float, float, SMP*, float*);
    // RT_JtSpeedUpClock
    // g_rtClockPowerUp
    // g_grfusr
    // SetJoyBtnHandled(JOY*, ushort);
    // GetGrfvault_unknown();
    // RT_JtSlowDownClock
    // g_rtClockPowerUp
    // SetJoyBtnHandled(JOY*, ushort);
    // SetJtJts(JT*, JTS, JTBS);
    // SetJtJts(JT*, JTS, JTBS);
    // SetJoyBtnHandled(JOY*, ushort);
    // SetJtJts(JT*, JTS, JTBS);
    // SetJoyBtnHandled(JOY*, ushort);
    // SetJtJts(JT*, JTS, JTBS);
    // g_clock+0x4
    // func_001D31D0
    // SetJoyBtnHandled(JOY*, ushort);
    // FIsLoInWorld(LO*)
    // atan2f
    // func_001C5D58();
    // SetJtJts(JT*, JTS, JTBS);
    // SetJtJts(JT*, JTS, JTBS);


    switch (fsp)
    {
    case FSP_Dive:
    case FSP_Ball:
    case FSP_SlowDownClock:
    case FSP_Mine:
    case FSP_SpeedUpClock:
    case FSP_Decoy:
    case FSP_Stun:
    default:
        break;
    }
}
#endif

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
        grfValue = GetGrfvault_unknown();
    } while ((grfValue & mpigrfvault[iNew]) == 0);

    // Return the new powerup index.
    return iNew;
}
