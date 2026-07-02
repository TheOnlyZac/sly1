#include <steppipe.h>

INCLUDE_ASM("asm/nonmatchings/P2/steppipe", PostJtLoadPipe__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/steppipe", GetJtPipeGoalMat__FP2JTP4PIPEfP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/steppipe", PresetJtAccelPipe__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/steppipe", UpdateJtActivePipe__FP2JTP3JOY);

INCLUDE_ASM("asm/nonmatchings/P2/steppipe", UpdateJtInternalXpsPipe__FP2JT);

void SetJtJtpdk(JT *pjt, JTPDK jtpdk)
{
    JTPDK jtpdkCur = STRUCT_OFFSET(pjt, 0x2718, JTPDK);
    if (jtpdkCur != jtpdk)
    {
        if (jtpdkCur == JTPDK_Nil)
        {
            IncrementSwHandsOff(pjt->psw);
            FUN_001ddb58(pjt->psw);
        }
        STRUCT_OFFSET(pjt, 0x2718, JTPDK) = jtpdk;
        if (jtpdk == JTPDK_Nil)
        {
            DecrementSwHandsOff(pjt->psw);
            FUN_001ddbb8(pjt->psw);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/steppipe", PlaceJtOnPipe__FP2JTP4PIPE);
