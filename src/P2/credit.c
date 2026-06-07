#include <credit.h>

INCLUDE_ASM("asm/nonmatchings/P2/credit", InitCredit__FP6CREDIT5BLOTK);

INCLUDE_ASM("asm/nonmatchings/P2/credit", PostCreditLoad__FP6CREDIT);

INCLUDE_ASM("asm/nonmatchings/P2/credit", SetCreditClock__FP6CREDITPf);

INCLUDE_ASM("asm/nonmatchings/P2/credit", UpdateCredit__FP6CREDIT);

INCLUDE_ASM("asm/nonmatchings/P2/credit", DrawCredit__FP6CREDIT);

INCLUDE_ASM("asm/nonmatchings/P2/credit", PlaceCredit__FP6CREDITffi);

struct CREDIT;

void VacateCredit(CREDIT *pcredit)
{
    (*(void (**)(CREDIT *, int))((char *)*(void **)pcredit + 0x40))(pcredit, 0);
}

INCLUDE_ASM("asm/nonmatchings/P2/credit", SetCreditLine__FP6CREDITiPcf);
