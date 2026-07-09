#include <fader.h>
#include <sw.h>
#include <slotheap.h>
#include <dl.h>
#include <memory.h>

INCLUDE_ASM("asm/nonmatchings/P2/fader", UpdateFader__FP5FADERf);

FADER *PfaderNew(ALO *palo)
{
    FADER *pfader;

    pfader = (FADER *)PvAllocSlotheapClearImpl(&STRUCT_OFFSET(g_psw, 0x1C18, SLOTHEAP));
    STRUCT_OFFSET(pfader, 0x0, ALO *) = palo;

    if (STRUCT_OFFSET(palo, 0x294, int) != 0)
    {
        AppendDlEntry(&STRUCT_OFFSET(g_psw, 0x1C30, DL), pfader);
    }
    else
    {
        AppendDlEntry(&STRUCT_OFFSET(g_psw, 0x1C24, DL), pfader);
    }

    return pfader;
}

INCLUDE_ASM("asm/nonmatchings/P2/fader", RemoveFader__FP5FADER);
