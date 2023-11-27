#include <wipe.h>
#include <clock.h>
#include <wm.h>

WIPE* g_pwipe = &g_wipe;

// First parameter is ptr to enc level file info second paramter unk third is warp type
void WipeToWorldWarp(LevelTableStruct* pchzWorld, OID oidWarp, WIPEK wipek)
{
    trans.fSet = 1;
    trans.grftrans = (GRFTRANS)0;
    trans.pchzWorld = pchzWorld;
    trans.oidWarp = (OID)oidWarp;
    ActivateWipe(g_pwipe, &trans, wipek);
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

    if (g_psw == nullptr)
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
        SetWmWms(&g_wmc, 0); // this was SetWmWm but I changed it to SetWmWms, I think it was a typo -Zac
    }

    if (wipes == WIPES_WipingOut)
    {
        if (pwipe->wipek == WIPEK_WorldMap)
        {
            //worldlevel = FFindLevel(pwipe->trans.pchzWorld); // todo implement func
            if (&g_wmc == 0 || worldlevel == WORLDLEVEL_Approach)
            {
                pwipe->wipek = WIPEK_Fade;
            }
            else
            {
                unk_0 = WORLDLEVEL_Max;
                if (&worldlevel != 0)
                {
                    unk_0 = worldlevel;
                }

                //ShowWm(g_wmc, unk_0, 3); // todo implement function
                //FUN_001ddb58(g_psw);
            }
        }

        else
        {
            if (pwipe->wipek == WIPEK_Frozen)
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
                    pwipe->tWipes = g_clock.tReal;
                    return;
                }

                if (pwipe->wipek != WIPEK_WorldMap)
                {
                    if (pwipe->wipek != WIPEK_Frozen)
                    {
                        pwipe->wipes = WIPES_WipingIn;
                        pwipe->tWipes = g_clock.tReal;
                        return;
                    }

                    wipes = WIPES_Idle;
                    //FadeFramesToBlack(0.25); //todo implement function
                    WIPES unk_1 = pwipe->wipes;
                    pwipe->tWipes = g_clock.tReal;
                    return;
                }

                if (&g_wmc != 0)
                {
                    //SetWmWms(g_wmc, WMS_Disappearing); //todo g_wmc
                    pwipe->wipes = WIPES_WipingOut;
                    pwipe->tWipes = g_clock.tReal;
                    return;
                }
                pwipe->wipek = WIPEK_Frozen;
            }
        }
    }
}

void DrawWipe(WIPE* pwipe)
{
    float alpha;
    float uBlack;
    WIPEK wipek;
    if (g_psw != nullptr && g_pwipe != nullptr)
    {
        wipek = pwipe->wipek;
        if (wipek == WIPEK_Keyhole && g_pkeyhole != nullptr)
        {
            //DrawKeyhole(g_pkeyhole, pwipe->uBlack);
            return;
        }

        else
        {
            uBlack = pwipe->uBlack;

            if (1 < (int)wipek && wipek != WIPEK_Fade)
            {
                return;
            }
        }

        uBlack = uBlack * 255.0f;
        if (uBlack < 2.0f)
        {
            alpha = uBlack;
        }

        else
        {
            if (uBlack < 0.0f)
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

void UpdateWipe(WIPE* pwipe, JOY* pjoy)
{
    WIPEK unk_0;
    GRFTRANS grftrans;
    WIPES wipes;
    float uBlack;
    float unk_3;

    wipes = pwipe->wipes;

    // g_clock is implemented but unk_2 is not used in this function so
    // I'm not sure why this line is here. It is supposed to be unk_3? -Zac
    //unk_2 = g_clock.tReal - pwipe->tWipes;

    if (wipes == WIPES_WipingOut)
    {
        if (pwipe->wipek != WIPEK_WorldMap)
            unk_3 = 0.5;
        if (pwipe->wipek == WIPEK_Keyhole)
        {
            unk_3 = 1.5;
        }

        if (unk_3 < uBlack)
        {
            grftrans = pwipe->trans.grftrans;
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

            grftrans = pwipe->trans.grftrans;
            pwipe->uBlack = uBlack;
        }

        //DrawPrelit();
    }

    else
    {
        if (wipes < WIPES_Black)
        {
            grftrans = (GRFTRANS)FCatchWipeButtonTrans(pwipe, pjoy, WIPES_WipingOut);
            if (wipes == WIPES_Idle && grftrans != 0)
            {
                return;
            }
        }

        else
        {
            if (wipes == WIPES_Black && pwipe->trans.fSet == 0 && g_transition.m_fPending == 0)
            {
                wipes = WIPES_WipingIn;
            }

            else
            {
                if ((wipes == WIPES_WipingIn) && (unk_0 == pwipe->wipek) && unk_0 != WIPEK_WorldMap)
                {
                    unk_3 = 0.25;
                    if (unk_0 == WIPEK_Keyhole)
                    {
                        unk_3 = 1.0;
                    }

                    if (unk_3 < uBlack)
                    {
                        if (unk_0 == WIPEK_Frozen)
                        {
                            pwipe->wipek = WIPEK_Fade;
                            //uBlack = g_clock.tReal;
                            pwipe->uBlack = 1.0;
                            pwipe->tWipes = uBlack;
                        }

                        else
                        {
                            wipes = WIPES_Idle;
                        }
                    }

                    else
                    {
                        pwipe->uBlack = 1.0f - uBlack / unk_3;
                    }
                }
            }
        }
    }

    SetWipeWipes(pwipe, wipes);
}

void InitWipe(WIPE* pwipe)
{
    pwipe->wipes = WIPES_Idle;
    SetWipeWipes(pwipe, WIPES_Idle);
}

void SetWipeButtonTrans(WIPE* pwipe, TRANS* ptrans, WIPEK wipek)
{
    pwipe->transButton.grftrans = ptrans->grftrans;
    pwipe->wipekButton = wipek;
}

int FCatchWipeButtonTrans(WIPE* pwipe, JOY* pjoy, WIPES wipesNew)
{
    bool is_match = false;
    GRFTRANS grftrans;
    //bool is_match = FUN_001dda80(g_psw);

    if (!is_match || pwipe->trans.fSet == 0 || (pjoy->grfbtnPressed & PAD_START) == NOT_PRESSED)
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
