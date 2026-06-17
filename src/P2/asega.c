#include <asega.h>
#include <sw.h>
#include <aseg.h>

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

void UpdateAsegaIeaCur(ASEGA *pasega)
{
    void *paseg = STRUCT_OFFSET(pasega, 0x8, void *);
    int c = STRUCT_OFFSET(paseg, 0x5C, int);
    if (c == 0)
        return;

    if (0.0f <= STRUCT_OFFSET(pasega, 0x18, float))
    {
        int i = c - 1;
        i = 0;
        if (c > 0)
        {
            char *p = STRUCT_OFFSET(paseg, 0x60, char *);
            float t = STRUCT_OFFSET(pasega, 0x14, float);
            if (!(t <= *(float *)p))
            {
                int cmax = c;
                i = i + 1;
                while (i < cmax)
                {
                    p += 0x10;
                    if (t <= *(float *)p)
                        break;
                    i = i + 1;
                }
            }
        }
        STRUCT_OFFSET(pasega, 0x20, int) = i;
    }
    else
    {
        int i = c - 1;
        if (i >= 0)
        {
            char *p = STRUCT_OFFSET(paseg, 0x60, char *) + (i << 4);
            float t = STRUCT_OFFSET(pasega, 0x14, float);
            while (1)
            {
                if (*(float *)p <= t)
                    break;
                i = i - 1;
                if (i < 0)
                    break;
                p -= 0x10;
            }
        }
        STRUCT_OFFSET(pasega, 0x20, int) = i + 1;
    }
}

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

void SendAsegaMessage(ASEGA *pasega, MSGID msgid, void *pv)
{
    LO *plo = STRUCT_OFFSET(pasega, 0xC, LO *);
    if (plo)
    {
        plo->pvtlo->pfnSendLoMessage(plo, msgid, pv);
    }

    MQ *pmq = STRUCT_OFFSET(pasega, 0xE4, MQ *);

    while (pmq)
    {
        PFNMQ pfnmq = pmq->pfnmq;
        void *pmqContext = pmq->pvContext;

        pmq = pmq->pmqNext;

        pfnmq(pmqContext, msgid, pv);
    }
}

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
