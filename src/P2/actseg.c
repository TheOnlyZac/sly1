#include <actseg.h>
#include <asega.h>

void RetractActseg(ACTSEG *pactseg, GRFRA grfra)
{
    ASEGA *pasega = pactseg->pasega;
    RemoveDlEntry(&pasega->dlActseg, pactseg);

    if (pasega->pactsegError == pactseg)
    {
        pasega->pactsegError = (ACTSEG *)nullptr;
    }

    RetractAct(pactseg, grfra);
}

void CloneActseg(ACTSEG *pactseg, ACTSEG *pactsegBase)
{
    ASEGA *pasega = pactseg->pasega;
    DLE dleAsega = pactseg->dleAsega;

    CloneAct(pactseg, pactsegBase);

    pactseg->dleAsega = dleAsega;
    pactseg->pasega = pasega;
}

INCLUDE_ASM("asm/nonmatchings/P2/actseg", GetActsegPositionGoal__FP6ACTSEGfP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/actseg", GetActsegRotationGoal__FP6ACTSEGfP7MATRIX3P6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/actseg", GetActsegTwistGoal__FP6ACTSEGPfT1);

INCLUDE_ASM("asm/nonmatchings/P2/actseg", GetActsegScale__FP6ACTSEGP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/actseg", GGetActsegPoseGoal__FP6ACTSEGi);
