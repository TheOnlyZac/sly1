#include "steppower.h"
#include <game.h>
#include <jt.h>
#include <screen.h>
#include <clock.h>
#include <steprail.h>

// GRFVAULT s_mpfspgrfvault[7];
extern BLOT g_binoc;   // todo: find where this belongs.
extern int D_00270458; // temp
// SMP SMP_00274f78; // initialized with { 2.0f, 0.0f, 0.1f }

void SetFsp(FSP fsp)
{
    // Cleanup current powerup
    switch (g_fsp)
    {
    case FSP_Ball:
        // If cur powerup is roll, reset JT's body state
        if (g_pjt != nullptr && g_pjt->jts == (JTS)13)
        {
            SetJtJts(g_pjt, JTS_Stand, JTBS_Nil);
        }
        break;
    case FSP_Mine:
        // If cur powerup is mine, fade out the mine
        if (g_pjt != nullptr)
        {
            ALO *palo = g_pjt->paloMine_0x1518;
            if ((palo != nullptr) && (FIsLoInWorld((LO *)g_pjt->paloMine_0x1518)))
            {
                FadeAloOut(g_pjt->paloMine_0x1518, 0.5f);
            }
        }
        break;
    default:
        break;
    }

    if (g_pjt != nullptr)
    {
        g_rtClockPowerUp = 1.0f;
        if ((g_pjt->unk_0x2750 != 0) && FIsLoInWorld((JT *)g_pjt->unk_0x2750))
        {
            func_001D32D8(g_pjt->unk_0x2750, g_pjt, 1);
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

    // Show note
    SetBlotDtVisible((NOTE *)&g_note.unk278, (g_pjt != nullptr) && (g_pjt == PpoCur()) ? 3.0 : 8.0);
    SetBlotFontScale(0.6, (NOTE *)&g_note.unk278);
    ((NOTE *)&g_note.unk278)->pvtnote->pfnSetNoteAchzDraw((NOTE *)&g_note.unk278, s_mpfspachz[fsp]);
    ((NOTE *)&g_note.unk278)->pvtnote->pfnShowBlot((NOTE *)&g_note.unk278);

    // Update last fsp in game state
    g_pgsCur->fspLast = fsp;
}

INCLUDE_ASM(const s32, "P2/steppower", UpdateJtActivePowerUp__FP2JTP3JOY);
// #ifdef SKIP_ASM
/**
 * @todo 46.12% match.
 */
/*
void UpdateJtActivePowerUp(JT *pjt, JOY *pjoy)
{
    if (g_fsp > FSP_Nil)
    {
        // Some powerup is active, so get the grfvault.
        GRFVAULT grfvault = GetGrfvault_unknown();
        if (s_mpfspgrfvault[(uint)g_fsp] & (uint)grfvault == 0)
        {
            // Disable powerup if grfvault didn't match a valid powerup.
            SetFsp(FSP_Nil);
            g_pgsCur->fspLast = FSP_Nil;
        }
    }

    // Check whether jt is in a state where rotating powerups is allowed.
    bool fcanRotate;
    uint jtsval;
    switch (g_fsp)
    {
    case FSP_Dive:
        // Only rotate if JT is rushing or ledge grabbing.
        if (g_pjt == nullptr
            || g_pjt->jts != JTS_Rush
            || !g_pjt->jts == JTS_Jump && g_pjt->jtbs == (JTBS)0x8)
        {
            fcanRotate = true;
        }
        else
        {
            fcanRotate = false;
        }
        break;
    case FSP_Ball:
        // Only rotate if JT is not rolling.
        if (g_pjt != nullptr
            && !(g_pjt->jts == JTS_Ball && g_pjt->jtbs == (JTBS)0xd))
            {
                fcanRotate = true;
            }
            else
            {
                fcanRotate = false;
            }
        break;
    case FSP_SlowDownClock:
    case FSP_SpeedUpClock:
        // Only rotate when clock rate is close enough to 1.0.
        fcanRotate = FFloatsNear(g_rtClockPowerUp, 1.0, 0.0001);
        break;
    case FSP_Mine:
        // Only rotate if Xor of current jts with 0x10 != 0.
        jtsval = g_pjt->jts ^ 0x10;
        fcanRotate = (uint)(jtsval != 0);
        break;
    case FSP_Decoy:
        // Only rotate if Xor of current jts with 0xe != 0.
        jtsval = g_pjt->jts ^ 0xE;
        fcanRotate = (uint)(jtsval != 0);
        break;
    case FSP_Stun:
        // Only rotate if ???
        fcanRotate = 0;
        if (g_pjt->jts != (JTS)0xF)
        {
            fcanRotate = STRUCT_OFFSET(g_pjt, 0x275c, uint) == 0;
        }
        break;
    case FSP_Nil:
        // Always rotate is no powerup is selected.
        fcanRotate = 1;
        break;
    default:
        break;
    }

    // Disallow rotating if JT status is Zap or binoc is showing.
    if (g_pjt != nullptr && g_pjt->jts == JTS_Zap)
        fcanRotate = false;

    if (g_binoc.blots != BLOTS_Hidden)
        fcanRotate = false;

    // Rotate the selected powerup flags if allowed to and L2/R2 pressed.
    if (fcanRotate && JOY_BUTTON_PRESSED(pjoy, PAD_L2|PAD_R2))
    {
        FSP newFsp = (FSP)IRotatePowerUp(pjoy, (int)g_fsp, (int)FSP_Max, s_mpfspgrfvault);
        g_pgsCur->fspLast = FSP_Nil;
        SetFsp(newFsp);
    }

    // Powerup activation logic (how the sausage is actually made).
    switch (g_fsp)
    {
    case FSP_Ball:
        if (pjt->jts > JTS_Nil && pjt->jts < (JTS)3
            && JOY_BUTTON_PRESSED(pjoy, PAD_TRIANGLE))
        {
            SetJoyBtnHandled(pjoy, PAD_TRIANGLE);

            // Two different animations based on 0x690 offset(?).
            if (STRUCT_OFFSET(g_pjt, 0x690, float) = 0.0f)
            {
                SetJtJts(pjt, (JTS)13, (JTBS)0x36);
            }
            else
            {
                SetJtJts(pjt, (JTS)13, (JTBS)0x37);
            }
        }
        break;
    case FSP_SlowDownClock:
        if (g_grfusr & (FUSR_Menu|FUSR_HandsOff) == 0)
        {
            if (D_00270458 == 3)
            {
                // LAB_001d2ef0:
                STRUCT_OFFSET(pjt, 0x2744, float) = 0.0f;
            }
            else if (pjt->jts == (JTS)2)
            {
                if (JOY_BUTTON_PRESSED(pjoy, PAD_TRIANGLE))
                {
                    SetJoyBtnHandled(pjoy, PAD_TRIANGLE);
                    // goto lab_001d2ee8;
                }
            }
            else if (pjoy->grfbtn & 0x10 == 0)
            {
                STRUCT_OFFSET(pjt, 0x2744, int) = 0;
            }
            else
            {
                GRFVAULT grfvault = GetGrfvault_unknown();
                if ((grfvault & 0x1000) == 0)
                {
                    // goto LAB_001d2ef0;
                    // LAB_001d2ee8:
                    STRUCT_OFFSET(pjt, 0x2744, int) = 1;
                }
            }
        }
        else
        {
            STRUCT_OFFSET(pjt, 0x2744, int) = 0;
        }

        if (STRUCT_OFFSET(pjt, 0x2744, int) == 0)
        {
            g_rtClockPowerUp = 1.0f;
        }
        else
        {
            g_rtClockPowerUp = RT_JtSlowDownClock;
        }
        break;
    case FSP_Mine:
        if (pjt->jts < (JTS)2
            && JOY_BUTTON_PRESSED(pjoy, PAD_TRIANGLE)
            && STRUCT_OFFSET(pjt, 0x1518, LO *) != nullptr)
        {
            SetJoyBtnHandled(pjoy, PAD_TRIANGLE);
            LO *ploMine = STRUCT_OFFSET(pjt, 0x1518, LO *);
            if (FIsLoInWorld(ploMine))
            {
                // Compute vector from JT pos to mine
                VECTOR posMine = ploMine->pos;
                VECTOR posJt = pjt->pos;
                VECTOR3 dir = RadNormalize(posMine - posJt);
                float angle = atan2f(dir.y, dir.x);
                STRUCT_OFFSET(pjt, 0x01010, float) = angle;
                // FUN_001c5d58(pjt) // Spawns the mine?
                SetJtJts(pjt, (JTS)0x10, (JTBS)0x3a);
            }
            else
            {
                SetJtJts(pjt, (JTS)0x10, (JTBS)0x39);
            }
        }
        break;
    case FSP_SpeedUpClock:
        if (D_00270458 == 3)
        {
            STRUCT_OFFSET(pjt, 0x2748, float) = 0.0f;
        }
        else if (pjoy->grfbtn & 0x10 == 0)
        {
            STRUCT_OFFSET(pjt, 0x2748, float) = GSmooth(STRUCT_OFFSET(pjt, 0x2748, float), 0.0f, g_clock.dtReal, &SMP_00274f78, 0);
        }
        break;
    case FSP_Decoy:
        if (pjt->jts < (JTS)2
            && JOY_BUTTON_PRESSED(pjoy, PAD_TRIANGLE)
            && STRUCT_OFFSET(pjt, 0x2750, float) != 0.0f)
        {
             SetJoyBtnHandled(pjoy, PAD_TRIANGLE);
             SetJtJts(pjt, (JTS)0xE, JTBS_Nil);
        }
        break;
    case FSP_Stun:
        int stunVar;
        if (pjt->jts < (JTS)2)
        {
            if (JOY_BUTTON_PRESSED(pjoy, PAD_TRIANGLE))
            {
                SetJoyBtnHandled(pjoy, PAD_TRIANGLE);
                SetJtJts(pjt, (JTS)0xf, JTBS_Nil);
            }
            stunVar = STRUCT_OFFSET(pjt, 0x275c, int);
        }
        else
        {
            stunVar = STRUCT_OFFSET(pjt, 0x275c, int);
        }

        if (stunVar && (3.0 < g_clock.t - STRUCT_OFFSET(pjt, 0x2758, float)))
        {
            // FUN_002d31d0(pjt, 0);
        }
        break;
    default:
        break;
    }
}
    */
// #endif

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
