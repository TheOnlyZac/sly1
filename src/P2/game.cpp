#include <game.h>
#include <joy.h>
#include <gs.h>
#include <cstring>

void InitGameState(GS* pgs)
{
	memset(pgs, 0, sizeof(GS));
	pgs->gameworldCur = GAMEWORLD_Intro;
	pgs->grfvault = 0;
	pgs->gsv = 0x12;
	pgs->cbThis = sizeof(GS);
	pgs->worldlevelCur = WORLDLEVEL_Level2;
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

void ClearLs(LS* pls)
{
	memset(pls, 0, sizeof(LS));
}

void RetryGame(void)
{
	GS* gsCur = g_pgsCur;

	g_pgsCur->clife = 5; // set lives to 5
	gsCur->ccharm = 0; // set charms to 0

	/* todo: implement function and CHKMGR struct
	ResetChkmgrCheckpoints(&g_chkmgr); */
}

void SetCcharm(int nParam)
{
	g_pgsCur->ccharm = nParam;
}

void SetClife(int nParam)
{
	g_pgsCur->clife = nParam;
}

void SetCcoin(int nParam)
{
	g_pgsCur->ccoin = nParam;
}

bool FCharmAvailable()
{
	if ((g_pgsCur->ccharm > 0) || ((g_grfcht & (int)(FCHT_InfiniteCharms)) != (int)FCHT_None))
	{
		return true;
	}
	return false;

}

void OnGameLoad(GAME* pgame)
{
	memset(pgame, 0, sizeof(GAME));
}

int CcharmMost()
{
	return 2;
}
