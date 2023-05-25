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

enum class CID : int
{
    CID_Nil = -1,
    CID_BASIC = 0,
    CID_LO = 1,
    CID_ALO = 2,
    CID_SO = 3,
    CID_MS = 4,
    CID_PO = 5,
    CID_STEP = 6,
    CID_JT = 7,
    CID_STEPGUARD = 8,
    CID_SMARTGUARD = 9,
    CID_GOMER = 10,
    CID_UBG = 11,
    CID_MBG = 12,
    CID_BHG = 13,
    CID_MURRAY = 14,
    CID_PUFFC = 15,
    CID_CRFOD = 16,
    CID_CRFODB = 17,
    CID_CRFODK = 18,
    CID_TANK = 19,
    CID_JP = 20,
    CID_HG = 21,
    CID_MECHA = 22,
    CID_ROV = 23,
    CID_TURRET = 24,
    CID_VAULT = 25,
    CID_PUFFER = 26,
    CID_MGV = 27,
    CID_SUV = 28,
    CID_CYCLE = 29,
    CID_LGN = 30,
    CID_JACK = 31,
    CID_RIPG = 32,
    CID_WATER = 33,
    CID_BRK = 34,
    CID_BREAK = 35,
    CID_ALBRK = 36,
    CID_CAN = 37,
    CID_DARTGUN = 38,
    CID_SWP = 39,
    CID_FRAGILE = 40,
    CID_ZAPBREAK = 41,
    CID_BRKP = 42,
    CID_BUTTON = 43,
    CID_VOLBTN = 44,
    CID_JLOVOL = 45,
    CID_SQUISH = 46,
    CID_BONE = 47,
    CID_SPRIZE = 48,
    CID_SCPRIZE = 49,
    CID_LIFETKN = 50,
    CID_CLUE = 51,
    CID_ALARM = 52,
    CID_SENSOR = 53,
    CID_LASEN = 54,
    CID_CAMSEN = 55,
    CID_PRSEN = 56,
    CID_BARRIER = 57,
    CID_IKH = 58,
    CID_TZP = 59,
    CID_VOLZP = 60,
    CID_CNVO = 61,
    CID_HBSK = 62,
    CID_BOMB = 63,
    CID_MISSILE = 64,
    CID_ACCMISS = 65,
    CID_TARMISS = 66,
    CID_SPLMISS = 67,
    CID_GROUNDMISS = 68,
    CID_FLY = 69,
    CID_RAT = 70,
    CID_ROH = 71,
    CID_ROC = 72,
    CID_ROST = 73,
    CID_ROP = 74,
    CID_DART = 75,
    CID_UBV = 76,
    CID_UBP = 77,
    CID_DSP = 78,
    CID_JLO = 79,
    CID_PUFFT = 80,
    CID_MRKV = 81,
    CID_LGNB = 82,
    CID_BLIPG = 83,
    CID_CAMERA = 84,
    CID_LBONE = 85,
    CID_EMITTER = 86,
    CID_LIGHT = 87,
    CID_SCH = 88,
    CID_LIKH = 89,
    CID_CHKPNT = 90,
    CID_PROXY = 91,
    CID_SKY = 92,
    CID_DPRIZE = 93,
    CID_CHARM = 94,
    CID_COIN = 95,
    CID_KEY = 96,
    CID_GOLD = 97,
    CID_LOCK = 98,
    CID_LOCKG = 99,
    CID_TAIL = 100,
    CID_ROB = 101,
    CID_FLASH = 102,
    CID_DYSH = 103,
    CID_SCENTMAP = 104,
    CID_WAYPOINT = 105,
    CID_TN = 106,
    CID_JLOC = 107,
    CID_DIALOG = 108,
    CID_SPEAKER = 109,
    CID_ROPE = 110,
    CID_WM = 111,
    CID_PUFFB = 112,
    CID_CRBRAIN = 113,
    CID_MGC = 114,
    CID_JACKB = 115,
    CID_JACKN = 116,
    CID_JACKF = 117,
    CID_SW = 118,
    CID_CM = 119,
    CID_SHAPE = 120,
    CID_HSHAPE = 121,
    CID_PIPE = 122,
    CID_RAIL = 123,
    CID_LANDING = 124,
    CID_XFM = 125,
    CID_WARP = 126,
    CID_TARGET = 127,
    CID_HND = 128,
    CID_EXPL = 129,
    CID_EXPLG = 130,
    CID_EXPLO = 131,
    CID_EXPLS = 132,
    CID_VOL = 133,
    CID_RATHOLE = 134,
    CID_PUFFV = 135,
    CID_EXIT = 136,
    CID_PNT = 137,
    CID_PNTSV = 138,
    CID_PNTS = 139,
    CID_PNTVEC = 140,
    CID_HPNT = 141,
    CID_JMT = 142,
    CID_SPIRE = 143,
    CID_SCAN = 144,
    CID_ASEG = 145,
    CID_ASEGBL = 146,
    CID_MAP = 147,
    CID__VISZONE = 148,
    CID_VISMAP = 149,
    CID_FRZG = 150,
    CID_SM = 151,
    CID_SGG = 152,
    CID_PATHZONE = 153,
    CID_RCHM = 154,
    CID_RWM = 155,
    CID_WR = 156,
    CID_KEYHOLE = 157,
    CID_JSG = 158,
    CID_ASEGA = 159,
    CID_SMA = 160,
    CID__FCST = 161,
    CID_Max = 162
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
void SetupGame(char* pchzWorld, int grftrans);
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
