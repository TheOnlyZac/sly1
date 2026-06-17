#include <credit.h>
#include <clock.h>
#include <screen.h>

struct CREDIT;

INCLUDE_ASM("asm/nonmatchings/P2/credit", InitCredit__FP6CREDIT5BLOTK);

void PostCreditLoad(CREDIT *pcredit)
{
    int i;
    BLOT *pblot;

    PostBlotLoad((BLOT *)pcredit);

    pblot = (BLOT *)((char *)pcredit + 0x264);
    for (i = 0; i < 4; i++)
    {
        pblot->pvtblot->pfnPostBlotLoad(pblot);
        pblot->pte = 0;
        STRUCT_OFFSET(pblot->pfont, 0x44, float) = 0.8f;
        STRUCT_OFFSET(pblot->pfont, 0x48, float) = 0.8f;
        SetBlotDtAppear(pblot, 1.0f);
        SetBlotDtDisappear(pblot, 1.0f);
        SetBlotDtVisible(pblot, 0.0f);
        pblot = (BLOT *)((char *)pblot + 0x260);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/credit", SetCreditClock__FP6CREDITPf);

INCLUDE_ASM("asm/nonmatchings/P2/credit", UpdateCredit__FP6CREDIT);

void DrawCredit(CREDIT *pcredit)
{
    extern int D_00275BEC;

    if (D_00275BEC == 1)
    {
        int i = 0;
        float s = STRUCT_OFFSET(pcredit, 0x220, float);

        if (STRUCT_OFFSET(pcredit, 0x260, int) > 0)
        {
            char *pe = (char *)pcredit + 0x264;
            do
            {
                float sSave = STRUCT_OFFSET(pe, 0x23C, float);

                STRUCT_OFFSET(pe, 0x220, float) = s;
                STRUCT_OFFSET(pe, 0x21C, float) = STRUCT_OFFSET(pcredit, 0x21C, float);
                STRUCT_OFFSET(pe, 0x23C, float) = sSave * g_rtClock;

                (*(void (**)(void *))(STRUCT_OFFSET(pe, 0x0, char *) + 0x24))(pe);
                i++;

                STRUCT_OFFSET(pe, 0x23C, float) = sSave;
                s = s + STRUCT_OFFSET(pe, 0x238, float);
                pe += 0x260;
            } while (i < STRUCT_OFFSET(pcredit, 0x260, int));
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/credit", PlaceCredit__FP6CREDITffi);

struct CREDIT;

void VacateCredit(CREDIT *pcredit)
{
    (*(void (**)(CREDIT *, int))((char *)*(void **)pcredit + 0x40))(pcredit, 0);
}

INCLUDE_ASM("asm/nonmatchings/P2/credit", SetCreditLine__FP6CREDITiPcf);
