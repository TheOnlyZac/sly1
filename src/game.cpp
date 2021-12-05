#include <game.h>
#include <joy.h>
#include <gs.h>

#include <cstring>

/* Clears the GAME struct */
void OnGameLoad(GAME* pgame)
{
	memset(pgame, 0, sizeof(GAME));
}

/* Resets the save data values to their defaults */
void InitGameState(GS* pgs)

{
	std::memset(pgs, 0, sizeof(GS));
	pgs->gameworldCur = GAMEWORLD::Intro;
	pgs->unlocked_thief_moves = 0;
	pgs->gsv = 0x12;
	pgs->cbThis = sizeof(GS);
	pgs->worldlevelCur = WORLDLEVEL::Level2;
	pgs->clife = 5;
	pgs->last_thief_move = -1;
	/* todo: implement function (name is wrong)
	reset_settings(pgs); */
}

void UpdateGameState(float dt)

{
	LS* lsCur = g_plsCur;
	WS* wsCur = g_pwsCur;

	g_pgsCur->dt = g_pgsCur->dt + dt; // inc global playtime
	wsCur->dt = wsCur->dt + dt; // inc world playtime
	lsCur->dt = lsCur->dt + dt; // inc level playtime
}

/* Sets the number of coins on the save file */
void SetCcoin(int nParam)
{
	g_pgsCur->ccoin = nParam;
}

/* Returns the max number of charms the player can have */
int CcharmMost()
{
	/* This was more complicated in the may proto because there was 
	a powerup which enables you to have more than two charms */
	return 2;
}

/* Returns true if Sly has a charm or infinite charms cheat is enabled */
bool FCharmAvailable()
{
	if ((g_pgsCur->ccharm > 0) || ((g_grfcht & (int)(FCHT::InfiniteCharms)) != (int)FCHT::None))
	{
		return true;
	}
	return false;
}

/* Sets the number of charms on the save file */
void SetCcharm(int nParam)
{
	g_pgsCur->ccharm = nParam;
}
