#include <wipe.h>
#include <keyhole.h>
#include <render.h>
#include <gifs.h>
#include <sw.h>

extern GIFS g_gifs;
extern KEYHOLE *g_pkeyhole;

void InitWipe(WIPE *pwipe)
{
    pwipe->wipes = WIPES_Nil;
    SetWipeWipes(pwipe, WIPES_Idle);
}

INCLUDE_ASM("asm/nonmatchings/P2/wipe", UpdateWipe__FP4WIPEP3JOY);

/**
 * @todo 94.58% match. The order of the checks might be wrong.
 */
INCLUDE_ASM("asm/nonmatchings/P2/wipe", DrawWipe__FP4WIPE);
#ifdef SKIP_ASM
void DrawWipe(WIPE *pwipe)
{
    if (!g_psw || !g_pwipe)
    {
        return;
    }

    WIPEK wipek = pwipe->wipek;
    if (wipek != WIPEK_Keyhole)
    {
        if (wipek > WIPEK_Keyhole || wipek == WIPEK_Fade)
        {
            return;
        }
    }
    if (g_pkeyhole)
    {
        DrawKeyhole(g_pkeyhole, pwipe->uBlack);
        return;
    }

    FillScreenRect(0, 0, 0, (int)(pwipe->uBlack * 255.0f), 0.0f, 0.0f, 640.0f, 492.80002f, &g_gifs);
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/wipe", ActivateWipe__FP4WIPEP5TRANS5WIPEK);

void SetWipeButtonTrans(WIPE *pwipe, TRANS *ptrans, WIPEK wipek)
{
    STRUCT_OFFSET(pwipe, 0x28, TRANS) = *ptrans;
    STRUCT_OFFSET(pwipe, 0x3c, WIPEK) = wipek;
}

INCLUDE_ASM("asm/nonmatchings/P2/wipe", FCatchWipeButtonTrans__FP4WIPEP3JOY5WIPES);

JUNK_WORD(0x00A0102D);

INCLUDE_ASM("asm/nonmatchings/P2/wipe", SetWipeWipes__FP4WIPE5WIPES);

void WipeToWorldWarp(const void *pchzWorld, OID oidWarp, WIPEK wipek)
{
    TRANS trans;
    trans.fSet = 1;
    trans.grftrans = 0;
    trans.pchzWorld = (LevelTableStruct *)pchzWorld;
    trans.oidWarp = oidWarp;
    ActivateWipe(&g_wipe, &trans, wipek);
}
