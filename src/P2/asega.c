#include <asega.h>
#include <sw.h>

INCLUDE_ASM("asm/nonmatchings/P2/asega", PasegaNew__FP2SW);

void SetAsegaHandsOff(ASEGA *pasega, int fHandsOff)
{
    if (fHandsOff != pasega->fHandsOff)
    {
        if (fHandsOff)
        {
            IncrementSwHandsOff(g_psw);
        }
        else
        {
            DecrementSwHandsOff(g_psw);
        }
        
        pasega->fHandsOff = fHandsOff;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/asega", UpdateAsegaIeaCur__FP5ASEGA);

INCLUDE_ASM("asm/nonmatchings/P2/asega", PactsegFindAsega__FP5ASEGA3OID);

JUNK_ADDIU(10);

INCLUDE_ASM("asm/nonmatchings/P2/asega", HandleAsegaEvent__FP5ASEGAP2EAPi);

INCLUDE_ASM("asm/nonmatchings/P2/asega", HandleAsegaEventsFF__FP5ASEGAP4ASEGPi);

INCLUDE_ASM("asm/nonmatchings/P2/asega", HandleAsegaEvents__FP5ASEGAP4ASEGPi);

void RemoveAsega(ASEGA *pasega)
{
    RemoveDlEntry(&g_psw->dlAsegaPending, pasega);
    FreeSlotheapPv(&g_psw->slotheapAsega, pasega);
}

INCLUDE_ASM("asm/nonmatchings/P2/asega", RetractAsega__FP5ASEGA);

INCLUDE_ASM("asm/nonmatchings/P2/asega", FUN_0012e928);

INCLUDE_ASM("asm/nonmatchings/P2/asega", UFromEaErrorFunc__FP2EAf);

INCLUDE_ASM("asm/nonmatchings/P2/asega", FWrapAsegaTime__FP5ASEGAPfT1);

INCLUDE_ASM("asm/nonmatchings/P2/asega", UpdateAsega__FP5ASEGAf);

INCLUDE_ASM("asm/nonmatchings/P2/asega", SeekAsega__FP5ASEGA4SEEKff);

INCLUDE_ASM("asm/nonmatchings/P2/asega", SnapAsega__FP5ASEGAi);

INCLUDE_ASM("asm/nonmatchings/P2/asega", AdaptAsega__FP5ASEGA);

INCLUDE_ASM("asm/nonmatchings/P2/asega", FindChnClosestPointLocal__FP3CHNP3ALOP6VECTORfffPfT2T2);

INCLUDE_ASM("asm/nonmatchings/P2/asega", SetAsegaSpeed__FP5ASEGAf);

INCLUDE_ASM("asm/nonmatchings/P2/asega", SetAsegaMasterSpeed__FP5ASEGAf);

INCLUDE_ASM("asm/nonmatchings/P2/asega", SetAsegaPriority__FP5ASEGAi);

INCLUDE_ASM("asm/nonmatchings/P2/asega", SendAsegaMessage__FP5ASEGA5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/asega", SubscribeAsegaStruct__FP5ASEGAPFPv5MSGIDPv_vPv);

INCLUDE_ASM("asm/nonmatchings/P2/asega", SubscribeAsegaObject__FP5ASEGAP2LO);
