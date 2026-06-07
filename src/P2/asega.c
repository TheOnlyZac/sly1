#include <asega.h>
#include <sw.h>

extern char D_002197B8[];

ASEGA *PasegaNew(SW *psw)
{
    ASEGA *pasega = (ASEGA *)PvAllocSlotheapClearImpl(&psw->slotheapAsega);
    STRUCT_OFFSET(pasega, 0x0, void *) = D_002197B8;
    InitDl(&pasega->dlActseg, 0x20);
    STRUCT_OFFSET(pasega, 0x60, void *) = (char *)pasega + 0x64;
    return pasega;
}

void SetAsegaHandsOff(ASEGA *pasega, int fHandsOff)
{
    if (fHandsOff == pasega->fHandsOff)
        return;

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

void SetAsegaSpeed(ASEGA *pasega, float speed)
{
    STRUCT_OFFSET(pasega, 0x18, float) =
        speed * STRUCT_OFFSET(pasega, 0x1C, float) *
        STRUCT_OFFSET(STRUCT_OFFSET(pasega, 0x8, void *), 0x98, float);
}

void SetAsegaMasterSpeed(ASEGA *pasega, float gSpeed)
{
    float denom = STRUCT_OFFSET(pasega, 0x1C, float) *
                  STRUCT_OFFSET(STRUCT_OFFSET(pasega, 0x8, void *), 0x98, float);
    float speed = STRUCT_OFFSET(pasega, 0x18, float);
    if (denom != 0.0f)
        speed = speed / denom;
    STRUCT_OFFSET(pasega, 0x1C, float) = gSpeed;
    SetAsegaSpeed(pasega, speed);
}

INCLUDE_ASM("asm/nonmatchings/P2/asega", SetAsegaPriority__FP5ASEGAi);

INCLUDE_ASM("asm/nonmatchings/P2/asega", SendAsegaMessage__FP5ASEGA5MSGIDPv);

void SubscribeAsegaStruct(ASEGA *pasega, PFNMQ pfnmq, void *pvContext)
{
    SubscribeSwPpmqStruct(STRUCT_OFFSET(STRUCT_OFFSET(pasega, 0x8, void *), 0x14, SW *),
                          &STRUCT_OFFSET(pasega, 0xE4, MQ *),
                          pfnmq, pvContext);
}

void SubscribeAsegaObject(ASEGA *pasega, LO *plo)
{
    SubscribeSwPpmqStruct(STRUCT_OFFSET(STRUCT_OFFSET(pasega, 0x8, void *), 0x14, SW *),
                          &STRUCT_OFFSET(pasega, 0xE4, MQ *),
                          STRUCT_OFFSET(plo->pvtlo, 0x44, PFNMQ),
                          plo);
}
