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
#ifdef SKIP_ASM
void MatchCnvoScrollerToBeltSpeed(CNVO *pcnvo)
{
    int c = STRUCT_OFFSET(pcnvo, 0x27c, int);
    if (c <= 0)
        return;

    void **arr = &STRUCT_OFFSET(pcnvo, 0x280, void *);
    int i = 0;
    do
    {
        void *pelem = arr[i];
        if (STRUCT_OFFSET(pelem, 0x8, int) == 6)
        {
            STRUCT_OFFSET(pelem, 0x2c, float) =
                -(STRUCT_OFFSET(pcnvo, 0x550, float) * STRUCT_OFFSET(pcnvo, 0x554, float));
            STRUCT_OFFSET(pelem, 0x30, float) =
                -(STRUCT_OFFSET(pcnvo, 0x550, float) * STRUCT_OFFSET(pcnvo, 0x558, float));
            return;
        }
        i = i + 1;
    } while (i < STRUCT_OFFSET(pcnvo, 0x27c, int));
}
#endif // SKIP_ASM
