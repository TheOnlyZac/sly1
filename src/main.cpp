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
//#include <transition.h>
//#include <mpeg.h>

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void Test(); // temp

int main(int cphzArgs, char* aphzArgs[])
{
	// __main(); // from libgcc2
	g_chpzArgs = cphzArgs;
	g_aphzArgs = aphzArgs;

	//Startup(); 

	while (true)
	{
		// todo: implement all these methods

		// Check if g_mpeg has an mpeg queued to be player
		/*if ((g_mpeg.oid_1 != OID::Unknown) && (g_wipe[1] != 0))
		{
			//FlushFrames(1);
			//g_mpeg::DoExecute();
		}*/
		
		// Check if g_transition has a pending transition
		/*if (g_transition.m_fPending != 0)
		{
			//FlushFrames(1);
			//g_transition::DoExecute();
		}*/

		// Check AGAIN if g_mpeg has an mpeg queued (in case two were queued back-to-back)
		/*if ((g_mpeg.oid_1 != OID::Unknown) && (g_wipe[1] != 0))
		{
			//FlushFrames(1);
			//g_mpeg::DoExecute();
		}*/

		// Call update functions
		UpdateJoy(&g_joy);
		//UpdateCodes();
		//UpdateSave(&g_save);
		//UpdateUi(g_ui);
		//UpdateGameState(g_clock.dt);

		// Render and draw current frame
		if (g_psw != NULL)
		{
			// Prepare to render frame
			SetupCm(g_pcm);
			OpenFrame();
			MarkClockTick(&g_clock);

			// call some function at g_ps2->0x54(?)
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

		// Temp: Print the current frame number
		printf("%d\r", g_cframe);

		// Increment the global frame counter
		g_cframe += 1;
	}
}

void Startup()
{
	// todo
	// ...
}