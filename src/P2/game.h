#pragma once

/* Object ID
 There are a lot more that are unknown. */
enum class OID : int
{
	OID_Unknown = 0x0,
	OID__MERGED_STATICS = 0x1,
	OID__VISIBILITY_MAP = 0x2,
	OID__WORLD = 0x3,
	OID__CAMERA = 0x4,
	OID_jt = 0x5,
	OID_bentley = 0x6,
	OID_murray = 0x7,
	// ...
	OID_rat = 0x269
	// ...
};

/* World IDs
 Some of these values are directly from the may proto, 
 the rest are extrapolated based on the order of levels in the game. */
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

void SetCcoin(int nParam);
int CcharmMost();
bool FCharmAvailable();
void SetCcharm(int nParam);
