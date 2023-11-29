#include <game.h>
#include <joy.h>
#include <gs.h>
#include <cstring>

/* Resets the save data values to their defaults */
void InitGameState(GS* pgs)
{
	memset(pgs, 0, sizeof(GS));
	pgs->gameworldCur = GAMEWORLD::Intro;
	pgs->grfvault = 0;
	pgs->gsv = 0x12;
	pgs->cbThis = sizeof(GS);
	pgs->worldlevelCur = WORLDLEVEL::Level2;
	pgs->clife = 5;
	pgs->nPowerupLast = -1;
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

/* Clears the level save struct */
void ClearLs(LS* pls)
{
	memset(pls, 0, sizeof(LS));
}

void SetupGame(char* pchzWorld, int grftrans)
{

}

void RetryGame(void)
{
	GS* gsCur = g_pgsCur;

	g_pgsCur->clife = 5; // set lives to 5
	gsCur->ccharm = 0; // set charms to 0

	/* todo: implement function and CHKMGR struct
	ResetChkmgrCheckpoints(&g_chkmgr); */
}

/* Sets the number of charms on the save file */
void SetCcharm(int nParam)
{
	g_pgsCur->ccharm = nParam;
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

/* Sets the number of coins on the save file */
void SetCcoin(int nParam)
{
	g_pgsCur->ccoin = nParam;
}

/* Clears the GAME struct */
void OnGameLoad(GAME* pgame)
{
	memset(pgame, 0, sizeof(GAME));
}

/* Returns the max number of charms the player can have */
int CcharmMost()
{
	/* This was more complicated in the may proto because there was 
	a powerup which enables you to have more than two charms */
	return 2;
}
