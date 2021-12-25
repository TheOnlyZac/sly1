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

void DrawWipe(WIPE* pwipe)
{
	int alpha;
	float uBlack;
	WIPEK wipek;
	if (&g_psw != nullptr && &g_pwipe != nullptr)
	{
		wipek = pwipe->wipek;
		if (wipek == WIPEK::Keyhole && &g_pkeyhole != nullptr)
		{
			//DrawKeyhole(g_pkeyhole, pwipe->uBlack);
			return;
		}

		else
		{
			uBlack = pwipe->uBlack;

			if (1 < (int)wipek && wipek != WIPEK::Fade)
			{
				return;
			}
		}

		uBlack = uBlack * 255.0;
		if (uBlack < 2.0)
		{
			alpha = uBlack;
		}

		else
		{
			if (uBlack < 0)
			{
				alpha = 0x7fffffff;
			}
			else
			{
				alpha = -0x80000000;
			}
		}

		//FillScreenRect(0, 0, 0, alpha, 0.0, 0.0, 640.0, 492.8, &g_gifs);
	}
}

void UpdateWipe(WIPE* param_1, JOY* param_2)
{
	WIPEK unk_0;
	GRFTRANS grftrans;
	WIPES wipes;
	float uBlack;
	float unk_3;

	wipes = param_1->wipes;
	//unk_2 = g_clock.tReal - param_1->tWipes;

	if (wipes == WIPES_WipingOut)
	{
		if(param_1->wipek != WIPEK::WorldMap)
		unk_3 = 0.5;
		if (param_1->wipek == WIPEK::Keyhole)
		{
			unk_3 = 1.5;
		}

		if (unk_3 < uBlack)
		{
			grftrans = param_1->trans.grftrans;
			wipes = WIPES_Black;
		}

		else
		{
			uBlack = uBlack / unk_3;
			if (uBlack < 0.0)
			{
				uBlack = 0.0;
			}
			else
			{
				if (1.0 < uBlack)
				{
					uBlack = 1.0;
				}
			}

			grftrans = param_1->trans.grftrans;
			param_1->uBlack = uBlack;
		}

		//DrawPrelit();
	}

	else
	{
		if (wipes < WIPES_Black)
		{
			//grftrans = FCatchWipeButtonTrans(param_1, param_2, WIPES_WipingOut);
			if (wipes == WIPES_Idle && grftrans != 0)
			{
				return;
			}
		}

		else
		{
			if (wipes == WIPES_Black)
			{
				if (param_1->trans.fSet == 0)
				{
					if (g_transition.m_fPending == 0)
					{
						wipes = WIPES_WipingIn;
					}
				}
			}

			else
			{
				if ((wipes == WIPES_WipingIn) && (unk_0 == param_1->wipek) && unk_0 != WIPEK::WorldMap)
				{
					unk_3 = 0.25;
					if (unk_0 == WIPEK::Keyhole)
					{
						unk_3 = 1.0;
					}

					if (unk_3 < uBlack)
					{
						if (unk_0 == WIPEK::Frozen)
						{
							param_1->wipek = WIPEK::Fade;
							//uBlack = g_clock.tReal;
							param_1->uBlack = 1.0;
							param_1->tWipes = uBlack;
						}

						else
						{
							wipes = WIPES_Idle;
						}
					}

					else
					{
						param_1->uBlack = 1.0 - uBlack / unk_3;
					}
				}
			}
		}
	}

	SetWipeWipes(param_1, wipes);
	return;
}

void InitWipe(WIPE* param_1)
{
	param_1->wipes = WIPES_Idle;
	SetWipeWipes(param_1, WIPES_Idle);
	return;
}

void SetWipeButtonTrans(WIPE* param_1, TRANS* param_2, WIPEK param_3)
{
	param_1->transButton.grftrans = param_2->grftrans;
	param_1->wipekButton = param_3;
	return;
}

int FCatchWipeButtonTrans(WIPE* pwipe, JOY* pjoy, WIPES wipesNew)
{
	bool is_match;
	GRFTRANS grftrans;
	//bool is_match = FUN_001dda80(g_psw);

	if (is_match == false)
	{
		return 0;
	}

	if (pwipe->trans.fSet = 0)
	{
		return 0;
	}

	if (pjoy->grfbtnPressed & PAD_START == _NOT_PRESSED)
	{
		return 0;
	}

	pwipe->wipek = pwipe->wipekButton;

	if (pwipe->trans.pchzWorld != 0)
	{
		pwipe->trans.grftrans = (GRFTRANS)0xfffffff7;
	}

	SetWipeWipes(pwipe, wipesNew);
	return 1;
}