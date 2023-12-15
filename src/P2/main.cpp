#include <main.h>
#include <gs.h>
#include <joy.h>
#include <clock.h>
#include <ui.h>
#include <game.h>
#include <update.h>
#include <sw.h>
#include <render.h>
#include <frm.h>
#include <transition.h>
#include <mpeg.h>
#include <wipe.h>
#include <phasemem.h>
#include <spliceutils.h>
#include <stdio.h>
#include <stdlib.h>

#define BUILD_TITLE "Sly Cooper"
#define BUILD_YEAR __DATE__[7], __DATE__[8], __DATE__[9], __DATE__[10]
#define COPYRIGHT "Sly 1 Decompilation Team"
#define BUILD_ID __DATE__[0], __DATE__[1], __DATE__[2], (__DATE__[4] == ' ' ? '0' : __DATE__[4]), __DATE__[5], __TIME__[0], __TIME__[1], __TIME__[3], __TIME__[4]
#define BRX_VERSION "000"

#ifndef __BUILD_USER
#define __BUILD_USER "nobody"
#endif

int main(int cphzArgs, char* aphzArgs[])
{
	// __main(); // from libgcc2
	g_chpzArgs = cphzArgs;
	g_aphzArgs = aphzArgs;

	Startup();

	while (true)
	{
		// todo: implement all these methods

		// Check if g_mpeg has an mpeg queued to be played
		if ((g_mpeg.oid_1 != OID_Unknown) && (g_wipe.wipes != WIPES_Idle))
		{
			//FlushFrames(1); // todo implement
			g_mpeg.ExecuteOids();
		}

		// Check if g_transition has a pending transition
		if (g_transition.m_fPending != 0)
		{
			//FlushFrames(1); // todo implement
			g_transition.Execute();
		}

		// Check AGAIN if g_mpeg has an mpeg queued (in case two were queued back-to-back)
		if ((g_mpeg.oid_2 != OID_Unknown) && (g_wipe.wipes != WIPES_Idle))
		{
			//FlushFrames(1); // todo implement
			g_mpeg.ExecuteOids();
		}

		// Call update functions
		UpdateJoy(&g_joy);
		UpdateCodes();
		//UpdateSave(&g_save);
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
				//(*pv)(g_clock.dt);
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
}

void Startup()
{
#ifdef __DEBUG
	printf("%s @ %c%c%c%c\n", BUILD_TITLE, BUILD_YEAR);
	printf("  %s\n", COPYRIGHT);
	printf("P2: %c%c%c%c%c.%c%c%c%c %s\n", BUILD_ID, __BUILD_USER);
	printf("Brx: %s\n"`, BRX_VERSION);
#endif
	SetPhase(PHASE_Startup);

	StartupSplice();

	// todo startup other game systems
	// ...

	ClearPhase(PHASE_Startup);
}
