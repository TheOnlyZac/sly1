#include <prompt.h>
#include <find.h>
#include <wipe.h>
#include <sw.h>
#include <rog.h>
#include <xform.h>
#include <text.h>

// TODO: Change to static when possible.
extern char *s_mprespkachz[13];

// TODO: Move elsewhere?
extern BLOT g_unkblot12;

char *AchzFromRespk(RESPK respk)
{
	return s_mprespkachz[respk];
}

INCLUDE_ASM("asm/nonmatchings/P2/prompt", FUN_001935b0);

/**
 * @todo Rename and figure out what does this actually do.
 */
int FUN_00193660()
{
	LO *plo = PloFindSwObject(g_psw, 5, (OID)0x42c, NULL);
	return plo ? STRUCT_OFFSET(plo, 0x48, int) : 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/prompt", SetPromptPrk__FP6PROMPT3PRK);

INCLUDE_ASM("asm/nonmatchings/P2/prompt", PostPromptLoad__FP6PROMPT);

INCLUDE_ASM("asm/nonmatchings/P2/prompt", FUN_00193ee8);

/**
 * @todo This could be a part of another function?
 * At the end is an unconditional branching to a label after the next function.
 */
INCLUDE_ASM("asm/nonmatchings/P2/prompt", FUN_00193f88__Fv);
#ifdef SKIP_ASM
void FUN_00193f88()
{
	BLOT *pblot = &g_unkblot12;
	SetBlotDtVisible(pblot, 0.0f);
	SetBlotFontScale(pblot, 0.60000002f);
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/prompt", FUN_00193fb8);

INCLUDE_ASM("asm/nonmatchings/P2/prompt", OnPromptActive__FP6PROMPTi);

extern "C" {
void FUN_00194278(PROMPT *pprompt, int fButton, WIPEK wipek)
{
    int idLevel;

    SetPrompt(pprompt, (PRP)0, (PRK)-1);

    idLevel = (STRUCT_OFFSET(g_pgsCur, 0x19d8, int) << 8) | STRUCT_OFFSET(g_pgsCur, 0x19dc, int);

    if (idLevel == 0x106)
    {
        if (fButton)
        {
            TRANS trans;
            trans.fSet = 1;
            trans.pchzWorld = (LevelTableStruct *)((char *)&g_transition + 0x14);
            trans.oidWarp = (OID)-1;
            trans.oidWarpContet = (OID)-1;
            trans.grftrans = 0;
            ActivateWipe(&g_wipe, &trans, wipek);
        }
        else
        {
            LO *plo = PloFindSwObjectByClass(g_psw, 5, (CID)0x5F, NULL);
            SetRobRobs((ROB *)plo, (ROBS)6);
        }
    }
    else
    {
        if (fButton)
        {
            TRANS trans;
            trans.fSet = 1;
            trans.pchzWorld = (LevelTableStruct *)((char *)&g_transition + 0x14);
            trans.oidWarp = (OID)-1;
            trans.oidWarpContet = (OID)-1;
            trans.grftrans = 0x10;
            ActivateWipe(&g_wipe, &trans, wipek);
        }
        else
        {
            TriggerDefaultExit(0, wipek);
        }
    }
}
}

INCLUDE_ASM("asm/nonmatchings/P2/prompt", FUN_00194398__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/prompt", UpdatePromptActive__FP6PROMPTP3JOY);

INCLUDE_ASM("asm/nonmatchings/P2/prompt", SetPrompt__FP6PROMPT3PRP3PRK);

INCLUDE_ASM("asm/nonmatchings/P2/prompt", SetPromptBlots__FP6PROMPT5BLOTS);

INCLUDE_ASM("asm/nonmatchings/P2/prompt", FUN_00194f00);

INCLUDE_ASM("asm/nonmatchings/P2/prompt", FUN_00194f38);

INCLUDE_ASM("asm/nonmatchings/P2/prompt", DrawPrompt__FP6PROMPT);

INCLUDE_ASM("asm/nonmatchings/P2/prompt", FUN_00195928);

INCLUDE_ASM("asm/nonmatchings/P2/prompt", ExecutePrompt__FP6PROMPT);

INCLUDE_ASM("asm/nonmatchings/P2/prompt", CancelPrompt__FP6PROMPT);

INCLUDE_ASM("asm/nonmatchings/P2/prompt", prompt__static_initialization_and_destruction_0);

JUNK_WORD(0xe48c0000);
JUNK_WORD(0xe48c0008);

INCLUDE_ASM("asm/nonmatchings/P2/prompt", _GLOBAL_$I$AchzFromRespk__F5RESPK);
