#pragma once

#include <gs.h>

/* Object IDs
 There are a lot more that are unknown. */
enum class OID : int
{
	Unknown = 0x0,
	_MERGED_STATICS = 0x1,
	_VISIBILITY_MAP = 0x2,
	_WORLD = 0x3,
	_CAMERA = 0x4,
	jt = 0x5,
	bentley = 0x6,
	murray = 0x7,
	// ...
	rat = 0x269
	// ...
};

/* World IDs
 Some of these values are directly from the may proto, 
 the rest I extrapolated based on the order of levels in the game -Zac */
enum class WID : int
{
	// Intro
	stock_objects = 0x0,
	splash = 0x1,
	attract = 0x2,
	jb_intro = 0x3,

	// Underwater
	uw_exterior_approach = 0x4,
	uw_exterior_boat = 0x5,
	uw_bonus_security = 0x6,
	uw_bonus_drivewheels_final = 0x7,
	uw_bonus_library = 0x8,
	uw_t3_final = 0x9,
	uw_rip_off = 0xa,
	uw_c2_final = 0xb,
	uw_boss_blimp = 0xc,

	// Mesa
	ms_approach = 0xd,
	ms_casino = 0xe,
	ms_exterior = 0xf,
	ms_inspector = 0x10,
	ms_rooftop = 0x11,
	ms_vertigo = 0x12,
	ms_sniper = 0x13,
	ms_suv = 0x14,
	ms_boss_battle = 0x15,

	// Voodoo
	v_approach = 0x16,
	v_gomerville = 0x17,
	v_swamp_monster = 0x18,
	v_hub = 0x19,
	v_skinterior = 0x1a,
	v_murray = 0x1b,
	v_chicken = 0x1c,
	v_puffer = 0x1d,
	v_boss = 0x1e,

	// Snow
	s_approach = 0x1f,
	s_barrel = 0x20,
	s_hub = 0x21,
	s_inspector = 0x22,
	s_security = 0x23,
	s_sniper = 0x24,
	s_suv = 0x25,
	s_tank = 0x26,
	s_boss = 0x27,

	// Clockwerk
	cw_suv = 0x28,
	cw_turret = 0x29,
	cw_security = 0x2a,
	cw_bentley = 0x2b,
	cw_reverse_sniper = 0x2c,
	cw_outclimb = 0x2d,
	cw_finish = 0x2e,
	
	Max = 0x2f
};

struct GAME {
	int cAlarmsTriggered;
	int fTimedChallenge;
	float dtChallenge;
	int cgoldLatest;
};


//void StartupGame();

//char* PchzFromLevel(GAMEWORLD gameworld, WORLDLEVEL worldlevel);
//char* PchzFriendlyFromLevel(GAMEWORLD gameworld, WORLDLEVEL worldlevel);
//char* PchzFriendlyFromWorld(char* pchzWorld);

//int FFindLevel(char* pchzWorld, GAMEWORLD* pgameworld, WORLDLEVEL* pworldlevel);

void InitGameState(GS* pgs);
//void SetupGame(char* pchzWorld, GRFTRANS grftrans)
void UpdateGameState(float dt);

//GRFLS GrflsFromWid(WID wid)
void ClearLs(LS* pls);

//void UnloadGame();
void RetryGame();
//void StartGame();

void SetCcharm(int nParam);
bool FCharmAvailable();
//void SetClife(int nParam);
void SetCcoin(int nParam);

//int* PfLookupDialog(LS* pls, OID oidDialog);
//char* AchzFromGameworld(GAMEWORLD gameworld);
//int CwlpGetWlps(int cwlpMax, WLP* awlp);

void OnGameLoad(GAME* pgame);
//void OnGameWorldTransition(GAME* pgame);
//void OnGameAlarmTriggered(GAME* pgame);
//void OnGameAlarmDisabled(GAME* pgame);
//void OnGameEnterUis(GAME* pgame, UIS uis);

//void StartGameTimedChallenge(GAME* pgame, GOLDCOLLECTED* pgoldCollected)
//void EndGameTimedChallenge(GAME* pgame, int* pfNewBestTime);
//void OnGameTimedChallengeTimerNotify(TIMER* ptimer, TIMERNOTK timernotk);
//void StartGameTimedChallengeTimer(GAME* pgame, float dt);
//void ResetGameTimedChallenge(GAME* pgame);
//void PrepareGameGoldForTimedChallenge(GAME* pgame);
//void GetBlueprintInfo(GRFVAULT* pgrfvault, int* pipdialog);

int CcharmMost();
