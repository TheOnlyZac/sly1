#include <actseg.h>
#include <asega.h>

void RetractActseg(ACTSEG *pactseg, GRFRA grfra)
{
    ASEGA *pasega = pactseg->pasega;
    RemoveDlEntry(&pasega->dlActseg, pactseg);

    if (pasega->pactsegError == pactseg)
    {
        pasega->pactsegError = NULL;
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

float GGetActsegPoseGoal(ACTSEG *pactseg, int ipose)
{
    float gGoal;
    ASEGA *pasega = pactseg->pasega;
    int iapose = STRUCT_OFFSET(pactseg, 0x28, int);
    void *p8 = STRUCT_OFFSET(pasega, 0x8, void *);
    uint8_t *pbase = STRUCT_OFFSET(p8, 0x3C, uint8_t *) + iapose * 0x1C;
    void **parr = STRUCT_OFFSET(pbase, 0x18, void **);
    void *papx = parr[ipose];

    (*(void (**)(void *, ALO *, int, float *, int, float, float))(*(void ***)papx))(
        papx, pactseg->palo, 0, &gGoal, 0,
        STRUCT_OFFSET(pasega, 0x14, float),
        STRUCT_OFFSET(pasega, 0x18, float));

    return gGoal;
}
