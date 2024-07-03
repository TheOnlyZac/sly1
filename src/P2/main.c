#include "common.h"
#include <game.h>

//extern g_chpzArgs;
//extern g_aphzArgs;

INCLUDE_ASM(const s32, "P2/main", main);
/*int main(int cphzArgs, char* aphzArgs[])
{
	__main(); // from libgcc2

	g_chpzArgs = cphzArgs;
	g_aphzArgs = aphzArgs;

	Startup();

	while (true)
	{
		// Check if g_mpeg has an mpeg queued to be played
		if ((g_mpeg.oid_1 != OID_Unknown) && (g_wipe.wipes != WIPES_Idle))
		{
			////FlushFrames(1);
			g_mpeg.ExecuteOids();
		}

		// Check if g_transition has a pending transition
		if (g_transition.m_fPending != 0)
		{
			////FlushFrames(1);
			g_transition.Execute();
		}

		// Check AGAIN if g_mpeg has an mpeg queued (in case two were queued back-to-back)
		if ((g_mpeg.oid_2 != OID_Unknown) && (g_wipe.wipes != WIPES_Idle))
		{
			////FlushFrames(1);
			g_mpeg.ExecuteOids();
		}

		// Call update functions
		UpdateJoy(&g_joy);
		UpdateCodes();
		////UpdateSave(&g_save);
		UpdateUi(&g_ui);
		UpdateGameState(g_clock.dt);

		// Render and draw current frame
		if (g_psw != NULL)
		{
			// Prepare to render frame
			SetupCm(g_pcm);
			OpenFrame();
			MarkClockTick(&g_clock);

			// This ends up calling UpdateSw down the line
			void* pv = g_psw + 0x54;
			if (pv != NULL)
			{
				////(*pv)(g_clock.dt);
			}

			// Render frame
			RenderSw(g_psw, g_pcm);
			RenderUi();

			// Draw frame
			DrawSw(g_psw, g_pcm);
			DrawUi();

			CloseFrame();
		}

		// Increment the global frame counter
		g_cframe += 1;
	}
}*/

INCLUDE_ASM(const s32, "P2/main", StartupVU0__Fv);

INCLUDE_ASM(const s32, "P2/main", StartupVU1__Fv);

INCLUDE_ASM(const s32, "P2/main", Startup__Fv);
