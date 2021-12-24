#include <wipe.h>

// First parameter is ptr to enc level file info second paramter unk third is warp type
void WipeToWorldWarp(LevelTableStruct* pchzWorld, OID oidWarp, WIPEK wipek)
{
	trans.fSet = 1;
	trans.grftrans = (GRFTRANS)0;
	trans.pchzWorld = pchzWorld;
	trans.oidWarp = (OID)oidWarp;
	ActivateWipe(&g_pwipe, &trans, wipek);
	return;
}

void ActivateWipe(WIPE* pwipe, TRANS* ptrans, WIPEK wipek)
{
	uint32_t unk_0;
	GRFTRANS grftrans;
	LevelTableStruct* load_data;
	bool condition;

	if (pwipe->wipes != WIPES_Idle)
	{
		return;
	}

	load_data = ptrans->pchzWorld;

	if (load_data == 0)
	{
		grftrans = ptrans->grftrans;
	}

	else
	{
		if (load_data == (LevelTableStruct*)g_transition.m_achzWorldCur)
		{
			condition = true;
		}

		else
		{
			unk_0 = load_data->search_val ^ load_data->search_cipher;

			if (unk_0 == 0)
			{
				condition = false;
				grftrans = (GRFTRANS)0xfffffffffffffff7;
			}

			else
			{
				condition = true;
			}
		}
	}
	ptrans->grftrans = grftrans;
	pwipe->trans.grftrans = ptrans->grftrans;
	WIPES wipes = WIPES_WipingOut;

	if (&g_psw == nullptr)
	{
		wipes = WIPES_Black;
	}

	SetWipeWipes(pwipe, wipes);
}

void SetWipeWipes(WIPE* pwipe, WIPES wipes)
{
	WORLDLEVEL worldlevel;
	WORLDLEVEL unk_0;

	if (pwipe->wipes == wipes)
	{
		return;
	}

	if (pwipe->wipes == WIPES_Black && (&g_wmc != 0))
	{
		//SetWmWm(g_wmc, 0);
	}

	if (wipes == WIPES_WipingOut)
	{
		if (pwipe->wipek == WIPEK::WorldMap)
		{
			//worldlevel = FFindLevel(pwipe->trans.pchzWorld);
			if (&g_wmc == 0 || worldlevel == WORLDLEVEL::Approach)
			{
				pwipe->wipek = WIPEK::Fade;
			}
			else
			{
				unk_0 = WORLDLEVEL::Max;
				if (&worldlevel != 0)
				{
					unk_0 = worldlevel;
				}

				//ShowWm(g_wmc, unk_0, 3);
				//FUN_001ddb58(g_psw);
			}
		}

		else
		{
			if (pwipe->wipek == WIPEK::Frozen)
			{
				wipes = WIPES_Black;
				if (pwipe->trans.fSet != 0)
				{
					g_transition.Set((char*)pwipe->trans.pchzWorld, pwipe->trans.oidWarp, pwipe->trans.trans_mod_flags, pwipe->trans.grftrans);
				}

				pwipe->trans.fSet = 0;
				pwipe->uBlack = 1.0;
				pwipe->transButton.fSet = 0;

				if (wipes != WIPES_WipingIn)
				{
					pwipe->wipes = wipes;
					//pwipe->tWipes = g_clock.tReal;
					return;
				}

				if (pwipe->wipek != WIPEK::WorldMap)
				{
					if (pwipe->wipek != WIPEK::Frozen)
					{
						pwipe->wipes = WIPES_WipingIn;
						//pwipe->tWipes = g_clock.tReal;
						return;
					}

					wipes = WIPES_Idle;
					//FadeFramesToBlack(0.25);
					WIPES unk_1 = pwipe->wipes;
					//pwipe->tWipes = g_clock.tReal;
					return;
				}

				if (&g_wmc != 0)
				{
					//SetWmWms(g_wmc, WMS_Disappearing);
					pwipe->wipes = WIPES_WipingOut;
					//pwipe->tWipes = g_clock.tReal;
					return;
				}
				pwipe->wipek = WIPEK::Frozen;
			}
		}
	}
}