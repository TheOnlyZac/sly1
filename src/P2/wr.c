#include <wr.h>

void InitWr(WR *pwr)
{
    InitLo(pwr);
    pwr->tLastUpdate = -1.0f;
    pwr->imatHalf = -1;
    pwr->iwreCur = -1;
}

INCLUDE_ASM("asm/nonmatchings/P2/wr", ApplyWrGlob__FP2WRP3ALOP4GLOB);

INCLUDE_ASM("asm/nonmatchings/P2/wr", UpdateWrStateVectors__FP2WR);

INCLUDE_ASM("asm/nonmatchings/P2/wr", WarpWrTransform__FP2WRfP6VECTORP7MATRIX3T2T3T2);

INCLUDE_ASM("asm/nonmatchings/P2/wr", GetWrBounds__FP2WRP6VECTOR);

float UNoise(int n)
{
    int x = (n << 13) ^ n;
    int y = x * x * 0x3d73 + 0xc0ae5;
    int z = x * y + 0x5208dd0d;
    x = z & 0x7fffffff;
    return (float)x / 2147483648.0f;
}

INCLUDE_ASM("asm/nonmatchings/P2/wr", UNoise__Ffff);

float UBias(float u, float v)
{
    return u / ((1.0f / v - 2.0f) * (1.0f - u) + 1.0f);
}

INCLUDE_ASM("asm/nonmatchings/P2/wr", GFromOnz__FP3ONZ);

INCLUDE_ASM("asm/nonmatchings/P2/wr", UpdateWrMatrixes__FP2WR);

INCLUDE_ASM("asm/nonmatchings/P2/wr", AddWrCircleWarp__FP2WR);

INCLUDE_ASM("asm/nonmatchings/P2/wr", AddWrBendWarp__FP2WR);

WRE *PwreGetWrCur(WR *pwr, ENSK ensk, WREK wrek)
{
    if (pwr->cwre == 0)
    {
        return (WRE *)0x00;
    }
    if (ensk == ENSK_Set)
    {
        pwr->fValuesChanged = 1;
    }
    
    return &pwr->awre[pwr->iwreCur];
}

WRE *PwreGetWrCircle(WR *pwr, ENSK ensk)
{
    return PwreGetWrCur(pwr, ensk, WREK_Circle);
}

WRE *PwreGetWrBend(WR *pwr, ENSK ensk)
{
    return PwreGetWrCur(pwr, ensk, WREK_Bend);
}

void SetWrWavelength(WR *pwr, float sWavelength)
{
    WRE *pwre = PwreGetWrCircle(pwr, ENSK_Set);
    if (sWavelength == 0.0f)
    {
        STRUCT_OFFSET(pwre, 0x64, float) = 0.0f;
    }
    else
    {
        STRUCT_OFFSET(pwre, 0x64, float) = 1.0f / sWavelength;
    }
}

void GetWrWavelength(WR *pwr, float *psWavelength)
{
    WRE *pwre = PwreGetWrCircle(pwr, ENSK_Set);
    if (STRUCT_OFFSET(pwre, 0x64, float) == 0.0f)
    {
        *psWavelength = 0.0f;
    }
    else
    {
        *psWavelength = 1.0f / STRUCT_OFFSET(pwre, 0x64, float);
    }
}

void AddOnzOnze(ONZ *ponz, float uAmpl, float gFreq, float gPhase, float uRandom)
{
    uint conze = ponz->conze;
    if (conze < 4)
    {
        ONZE *ponze = ponz->aonze + conze;
        ponz->conze++;

        ponze->uAmpl = uAmpl;
        ponze->gFreq = gFreq;
        ponze->gPhase = gPhase;
        ponze->uRandom = uRandom;
    }
}

void AddWrBendNoise(WR *pwr, float uAmpl, float gFreq, float gPhase, float uRandom)
{
    WRE *pwre = PwreGetWrBend(pwr, ENSK_Set);
    AddOnzOnze(&STRUCT_OFFSET(pwre, 0x30, ONZ), uAmpl, gFreq, gPhase, uRandom);
}

void AddWrSwivelNoise(WR *pwr, float uAmpl, float gFreq, float gPhase, float uRandom)
{
    WRE *pwre = PwreGetWrBend(pwr, ENSK_Set);
    AddOnzOnze(&STRUCT_OFFSET(pwre, 0x80, ONZ), uAmpl, gFreq, gPhase, uRandom);
}
