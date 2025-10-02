#include <cnvo.h>
#include <bbmark.h>

void InitCnvo(CNVO *pcnvo)
{
    InitSo(pcnvo);
    STRUCT_OFFSET(pcnvo, 0x550, float) = 100.0f; // pcnvo->svBelt
}

void LoadCnvoFromBrx(CNVO *pcnvo, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(pcnvo, pbis);
    STRUCT_OFFSET(pcnvo, 0x554, float) = pbis->F32Read(); // pcnvo->svuAvg
    STRUCT_OFFSET(pcnvo, 0x558, float) = pbis->F32Read(); // pcnvo->svvAvg
}

void PostCnvoLoad(CNVO *pcnvo)
{
    PostAloLoad(pcnvo);
    MatchCnvoScrollerToBeltSpeed(pcnvo);
}

INCLUDE_ASM("asm/nonmatchings/P2/cnvo", AdjustCnvoXpVelocity__FP4CNVOP2XPi);

void SetCnvoBeltSpeed(CNVO *pcnvo, float svBelt)
{
    if (svBelt == STRUCT_OFFSET(pcnvo, 0x550, float)) // pcnvo->svBelt
        return;

    STRUCT_OFFSET(pcnvo, 0x550, float) = svBelt; // pcnvo->svBelt
    InvalidateSwXpForObject(pcnvo->psw, pcnvo, 7);
    MatchCnvoScrollerToBeltSpeed(pcnvo);
    ResolveAlo(pcnvo);
}

INCLUDE_ASM("asm/nonmatchings/P2/cnvo", MatchCnvoScrollerToBeltSpeed__FP4CNVO);
