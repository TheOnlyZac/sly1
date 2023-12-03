/**
 * @file vec.cpp
 *
 * @brief Defines functions for vector math.
*/
#include <vec.h>
#include <math.h>

// todo: cleanup and fix params

void CalculateVectorPanTilt(VECTOR* pvec, float* ppan, float* ptilt)
{
    float val;

    if (*ppan != 0.0)
    {
        val = atan2f(pvec->y, pvec->x);
        //fVar1 = FUN_001ea408(fVar1);
        *ppan = val;
    }
    if (*ptilt != 0.0)
    {
        val = atan2f(pvec->z, sqrt(pvec->x * pvec->x + pvec->y * pvec->y));
        //val = FUN_001ea408(val); // todo implement function
        *ptilt = val;
    }
    return;
}

void ConvertDeulToW(VECTOR* param_1, VECTOR* param_2, VECTOR* param_3)
{
    float local_50;
    float local_4c;
    float local_48;
    float local_44;

    //CalculateSinCos(param_1->y, &local_50, (float*)((uint32_t)&local_50 | 4));
    //CalculateSinCos(param_1->z, (float*)((uint32_t)&local_50 | 8), (float*)((uint32_t)&local_50 | 0xc));
    param_3->x = local_4c * local_44 * param_2->x - local_48 * param_2->y;
    param_3->y = local_4c * local_48 * param_2->x + local_44 * param_2->y;
    param_3->z = -local_50 * param_2->x + param_2->z;
    return;
}

bool FCalculateMuzzleVelocity(VECTOR* param_1, VECTOR* param_2, VECTOR* param_3, VECTOR* param_4, SO* param_5)
{
    float fVar1;
    bool bVar2;
    float fVar3;
    float fVar4;
    VECTOR* pVVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    float in_f12;
    float fVar11;

    if (param_4 == (VECTOR*)0x0)
    {
        //pVVar5 = (VECTOR*)&g_psw[1].field_0x72;
    }
    else
    {
        pVVar5 = param_4 + 0x35;
    }
    fVar10 = pVVar5->z;
    fVar3 = param_2->x - param_1->x;
    fVar4 = param_2->y - param_1->y;
    fVar11 = param_2->z - param_1->z;
    //if (ABS(fVar10) < 1.0)
    {
        //fVar10 = SQRT(fVar3 * fVar3 + fVar4 * fVar4 + fVar11 * fVar11 * 1.0) + 0.0;
        if (fVar10 < 0.0001) {
            //fVar3 = (float)_DAT_00248d30;
            //fVar4 = (float)((ulong)_DAT_00248d30 >> 0x20);
            //fVar11 = DAT_00248d38;
            //fVar10 = DAT_00248d3c;
        }
        else
        {
            fVar10 = 1.0 / fVar10;
            fVar3 = fVar3 * fVar10;
            fVar4 = fVar4 * fVar10;
            fVar11 = fVar11 * fVar10;
            fVar10 = (param_2->gUnused - param_1->gUnused) * fVar10;
        }
        bVar2 = true;
        param_3->x = fVar3 * in_f12;
        param_3->y = fVar4 * in_f12;
        param_3->z = fVar11 * in_f12;
        param_3->gUnused = fVar10 * in_f12;
    }
    //else
    {
        fVar11 = (float)((int)fVar11 * (uint32_t)(0.0 < fVar11));
        //fVar1 = SQRT(fVar3 * fVar3 + fVar4 * fVar4 + 0.0) + 0.0;
        fVar7 = fVar10 * fVar11 + in_f12 * in_f12;
        fVar9 = fVar10 * fVar10 * 0.25;
        fVar8 = -fVar7 * -fVar7 - fVar9 * (fVar1 * fVar1 + fVar11 * fVar11) * 4.0;
        if (0.0 <= fVar8)
        {
            //fVar8 = SQRT(fVar8);
            fVar6 = (fVar7 - fVar8) / (fVar9 + fVar9);
            fVar8 = (fVar7 + fVar8) / (fVar9 + fVar9);
            if ((0.0 < fVar6) || (fVar6 = fVar8, 0.0 < fVar8))
            {
                //fVar6 = SQRT(fVar6);
                param_3->x = fVar3 * (1.0 / fVar1) * (fVar1 / fVar6);
                param_3->y = fVar4 * (1.0 / fVar1) * (fVar1 / fVar6);
                param_3->z = (fVar11 - fVar10 * fVar6 * 0.5 * fVar6) / fVar6;
                return true;
            }
        }
        bVar2 = false;
    }
    return bVar2;
}

uint32_t FCalculateMuzzleVelocityAngle(VECTOR* param_1, VECTOR* param_2, VECTOR* param_3, VECTOR* param_4, SO* param_5)
{
    uint32_t uVar1 = FCalculateMuzzleVelocity(param_1, param_2, param_3, param_4, param_5);
    return uVar1;
}

void FindClosestPointBetweenLines(VECTOR* pA, VECTOR* pB, VECTOR* pC, VECTOR* pD, float* unk_float1, float* unk_float2, VECTOR* presult)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float zresult;
    float fVar10;
    float fVar11;
    float xresult;
    float yresult;
    float fVar14;
    float fVar15;
    float gresult;

    fVar10 = pA->gUnused;
    fVar11 = pC->gUnused;
    fVar1 = pC->x - pA->x;
    fVar2 = pC->y - pA->y;
    fVar3 = pC->z - pA->z;
    gresult = pB->x - pA->x;
    zresult = pB->y - pA->y;
    fVar4 = pB->z - pA->z;
    fVar5 = pD->x - pC->x;
    fVar6 = pD->y - pC->y;
    fVar7 = pD->z - pC->z;
    xresult = zresult * fVar7 - fVar6 * fVar4;
    yresult = fVar4 * fVar5 - fVar7 * gresult;
    fVar14 = gresult * fVar6 - fVar5 * zresult;
    fVar15 = 0.0;
    fVar8 = xresult * xresult + yresult * yresult + fVar14 * fVar14 * 1.0;
    if (fVar8 < 0.0001)
    {
        *unk_float1 = 0.0;
        unk_float1[1] = 0.0;
        xresult = fVar1;
        yresult = fVar2;
        fVar14 = fVar3;
        fVar15 = fVar11 - fVar10;
    }
    else
    {
        *unk_float1 = ((fVar2 * fVar7 - fVar6 * fVar3) * xresult + (fVar3 * fVar5 - fVar7 * fVar1) * yresult
            + (fVar1 * fVar6 - fVar5 * fVar2) * fVar14 * 1.0) / fVar8;
        unk_float1[1] = ((fVar2 * fVar4 - zresult * fVar3) * xresult +
            (fVar3 * gresult - fVar4 * fVar1) * yresult +
            (fVar1 * zresult - gresult * fVar2) * fVar14 * 1.0) / fVar8;
        if (fVar1 * xresult + fVar2 * yresult + fVar3 * fVar14 * 1.0 < 0.0)
        {
            xresult = xresult * -1.0;
            yresult = yresult * -1.0;
            fVar14 = fVar14 * -1.0;
            fVar15 = -0.0;
        }
    }
    //fVar16 = SQRT(fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14 * 1.0) + 0.0;
    if (gresult < 0.0001)
    {
        //fVar12 = (float)_DAT_00248d20;
        //fVar13 = (float)((ulong)_DAT_00248d20 >> 0x20);
        //fVar9 = DAT_00248d28;
        //fVar16 = DAT_00248d2c;
    }
    else
    {
        gresult = 1.0 / gresult;
        xresult = xresult * gresult;
        yresult = yresult * gresult;
        zresult = fVar14 * gresult;
        gresult = fVar15 * gresult;
    }
    *unk_float2 = xresult * fVar1 + yresult * fVar2 + zresult * fVar3 * 1.0;
    presult->x = xresult;
    presult->y = yresult;
    presult->z = zresult;
    presult->gUnused = gresult;
    return;
}

void FindClosestPointBetweenLineSegments(VECTOR* param_1, VECTOR* param_2, VECTOR* param_3, VECTOR* param_4, VECTOR* param_5, float* param_6, VECTOR* param_7)
{
    float fVar1;
    float fVar2;
    uint64_t uVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar8;

    FindClosestPointBetweenLines(param_1, param_2, param_3, param_4, (float*)param_5, param_6, param_7);
    fVar5 = param_5->x;
    if (0.0 <= fVar5) {
        if (1.0 < fVar5) {
            fVar5 = 1.0;
        }
        fVar6 = param_5->y;
    }
    else {
        fVar6 = param_5->y;
        fVar5 = 0.0;
    }
    param_5->x = fVar5;
    fVar5 = 0.0;
    if ((0.0 <= fVar6) && (fVar5 = fVar6, 1.0 < fVar6)) {
        fVar5 = 1.0;
    }
    fVar4 = -param_5->x;
    param_5->y = fVar5;
    fVar7 = param_5->x - 1.0;
    fVar8 = 1.0 - fVar5;
    fVar6 = param_1->x * fVar7 + param_2->x * fVar4 + param_3->x * fVar8 + param_4->x * fVar5;
    fVar1 = param_1->y * fVar7 + param_2->y * fVar4 + param_3->y * fVar8 + param_4->y * fVar5;
    fVar2 = param_1->z * fVar7 + param_2->z * fVar4 + param_3->z * fVar8 + param_4->z * fVar5;
    fVar5 = param_1->gUnused * fVar7 + param_2->gUnused * fVar4 + param_3->gUnused * fVar8 +
        param_4->gUnused * fVar5;
    //fVar4 = SQRT(fVar6 * fVar6 + fVar1 * fVar1 + fVar2 * fVar2 * 1.0) + 0.0;
    param_7->x = fVar6;
    param_7->y = fVar1;
    param_7->z = fVar2;
    param_7->gUnused = fVar5;
    //fVar8 = DAT_00248d0c;
     //fVar7 = DAT_00248d08;
    //uVar3 = _DAT_00248d00;
    if (fVar4 < 0.0001) {
        //param_7->x = (float)_DAT_00248d00;
        param_7->y = (float)((uint64_t)uVar3 >> 0x20);
        param_7->z = fVar7;
        param_7->gUnused = fVar8;
    }
    else {
        fVar7 = 1.0 / fVar4;
        param_7->x = fVar6 * fVar7;
        param_7->y = fVar1 * fVar7;
        param_7->z = fVar2 * fVar7;
        param_7->gUnused = fVar5 * fVar7;
    }
    *param_6 = fVar4;
    return;
}

void GetNormalVector(VECTOR* pvec, VECTOR* presult)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float local_10;
    float local_c;
    float local_8;

    fVar1 = pvec->x;
    local_10 = pvec->y;
    fVar2 = pvec->z;
    //if (ABS(fVar1) <= ABS(local_10))
    {
        //if (ABS(fVar1) <= ABS(fVar2))
        {
            local_8 = -local_10;
            local_10 = 0.0;
            local_c = fVar2;
            goto LAB_001ed8b8;
        }
    }
    //else
    {
        local_8 = -fVar1;
        //if (ABS(local_10) <= ABS(fVar2))
        {
            local_c = 0.0;
            local_10 = fVar2;
            goto LAB_001ed8b8;
        }
    }
    local_8 = 0.0;
    local_c = -fVar1;
LAB_001ed8b8:
    fVar1 = pvec->y * local_8 - local_c * pvec->z;
    fVar2 = pvec->z * local_10 - local_8 * fVar1;
    fVar3 = pvec->x * local_c - local_10 * fVar2;
    //fVar4 = 1.0 / (SQRT(fVar1 * fVar1 + fVar2 * fVar2 + fVar3 * fVar3 * 1.0) + 0.0);
    presult->x = fVar1 * fVar4;
    presult->y = fVar2 * fVar4;
    presult->z = fVar3 * fVar4;
    presult->gUnused = fVar4 * 0.0;
    return;
}

void GetNormalVectors(VECTOR* param_1, VECTOR* param_2, VECTOR* param_3, VECTOR* param_4)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar8;

    fVar2 = param_1->x;
    fVar3 = param_1->y;
    fVar4 = param_1->z;
    fVar5 = param_3->y * fVar4 - fVar3 * param_3->z;
    fVar6 = param_3->z * fVar2 - fVar4 * param_3->x;
    fVar7 = param_3->x * fVar3 - fVar2 * param_3->y;
    if (fVar5 * fVar5 + fVar6 * fVar6 + fVar7 * fVar7 * 1.0 < 0.0001)
    {
        fVar5 = param_4->y * fVar4 - fVar3 * param_4->z;
        fVar6 = param_4->z * fVar2 - fVar4 * param_4->x;
        fVar7 = param_4->x * fVar3 - fVar2 * param_4->y;
    }
    fVar1 = fVar3 * fVar7 - fVar6 * fVar4;
    fVar4 = fVar4 * fVar5 - fVar7 * fVar2;
    fVar2 = fVar2 * fVar6 - fVar5 * fVar3;
    //fVar3 = 1.0 / (SQRT(fVar5 * fVar5 + fVar6 * fVar6 + fVar7 * fVar7 * 1.0) + 0.0);
    //fVar8 = 1.0 / (SQRT(fVar1 * fVar1 + fVar4 * fVar4 + fVar2 * fVar2 * 1.0) + 0.0);
    param_2->x = fVar5 * fVar3;
    param_2->y = fVar6 * fVar3;
    param_2->z = fVar7 * fVar3;
    param_2->gUnused = fVar3 * 0.0;
    param_2[1].x = fVar1 * fVar8;
    param_2[1].y = fVar4 * fVar8;
    param_2[1].z = fVar2 * fVar8;
    param_2[1].gUnused = fVar8 * 0.0;
    return;
}

void LimitVectorLength(VECTOR* pvec, float glength, VECTOR* presult)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;

    fVar2 = pvec->x;
    fVar3 = pvec->y;
    fVar4 = pvec->z;
    fVar5 = pvec->gUnused;
    //fVar1 = SQRT(fVar2 * fVar2 + fVar3 * fVar3 + fVar4 * fVar4 * 1.0) + 0.0;
    if (glength < fVar1)
    {
        fVar1 = glength / fVar1;
        presult->x = fVar2 * fVar1;
        presult->y = fVar3 * fVar1;
        presult->z = fVar4 * fVar1;
        presult->gUnused = fVar5 * fVar1;
    }
    else
    {
        if (pvec != presult) {
            presult->x = fVar2;
            presult->y = fVar3;
            presult->z = fVar4;
            presult->gUnused = fVar5;
        }
    }
    return;
}

long RadBetweenVectors(VECTOR* pvec1, VECTOR* pvec2, VECTOR* param_3)
{
    float fVar1;
    long gAngleRads;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    float fVar11;

    //fVar4 = DAT_00248d0c;
    //fVar5 = DAT_00248d08;
    //lVar2 = _DAT_00248d00;
    fVar9 = pvec1->x;
    fVar10 = pvec1->y;
    fVar11 = pvec1->z;
    fVar6 = pvec2->x;
    fVar7 = pvec2->y;
    fVar8 = pvec2->z;
    //fVar3 = SQRT(fVar9 * fVar9 + fVar10 * fVar10 + fVar11 * fVar11 * 1.0) + 0.0;
    //fVar1 = SQRT(fVar6 * fVar6 + fVar7 * fVar7 + fVar8 * fVar8 * 1.0) + 0.0;

    if ((fVar3 < 0.0001) || (fVar1 < 0.0001)) {
        //param_3->x = (float)_DAT_00248d00;
        //param_3->y = (float)((ulong)lVar2 >> 0x20);
        param_3->z = fVar5;
        param_3->gUnused = fVar4;
    }
    else {
        if (param_3 == (VECTOR*)0x0) {
            fVar4 = pvec1->x;
            fVar5 = pvec1->y;
            fVar6 = pvec1->z;
        }
        else {
            fVar4 = fVar10 * fVar8 - fVar7 * fVar11;
            fVar8 = fVar11 * fVar6 - fVar8 * fVar9;
            fVar6 = fVar9 * fVar7 - fVar6 * fVar10;
            param_3->x = fVar4;
            param_3->y = fVar8;
            param_3->z = fVar6;
            param_3->gUnused = 0.0;
            //fVar5 = SQRT(fVar4 * fVar4 + fVar8 * fVar8 + fVar6 * fVar6 * 1.0) + 0.0;
            if (1e-08 < fVar5) {
                fVar5 = 1.0 / fVar5;
                param_3->x = fVar4 * fVar5;
                param_3->y = fVar8 * fVar5;
                param_3->z = fVar6 * fVar5;
                param_3->gUnused = fVar5 * 0.0;
            }
            else {
                GetNormalVector(pvec1, param_3);
            }
            fVar4 = pvec1->x;
            fVar5 = pvec1->y;
            fVar6 = pvec1->z;
        }
        fVar5 = fVar5 * pvec2->y;
        fVar4 = fVar4 * pvec2->x + fVar5 + fVar6 * pvec2->z * 1.0;
        //lVar2 = CONCAT44(fVar5, fVar4);
        acosf(fVar4 / (fVar3 * fVar1));
    }
    return gAngleRads;
}

void SetVectorCylind(float param_1, float param_2, float param_3, VECTOR* param_4)
{
    float local_40;
    float local_3c;

    //CalculateSinCos(param_1, &local_40, (float*)((uint32_t)&local_40 | 4));
    param_4->z = param_3;
    param_4->x = local_3c * param_2;
    param_4->y = local_40 * param_2;
    return;
}

void SetVectorSphere(float param_1, float param_2, float param_3, VECTOR* param_4)
{
    float local_40;
    float local_3c;
    float local_38;
    float local_34;

    //CalculateSinCos(param_1, &local_40, (float*)((uint32_t)&local_40 | 4));
    //CalculateSinCos(param_2, (float*)((uint32_t)&local_40 | 8), (float*)((uint32_t)&local_40 | 0xc));
    param_4->z = local_38 * param_3;
    param_4->x = local_34 * local_3c * param_3;
    param_4->y = local_34 * local_40 * param_3;
    return;
}

float SProjectVector(VECTOR* pvec1, VECTOR* pvec2)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    VECTOR* in_a2_lo;
    VECTOR* pfVar6;
    uint32_t in_a2_hi;
    VECTOR* in_a3_lo;
    uint32_t in_a3_hi;
    float fVar6;
    float fVar7;
    float fVar8;
    float fVar9;

    fVar6 = pvec1->x;
    fVar7 = pvec1->y;
    fVar8 = pvec1->z;
    fVar9 = pvec1->gUnused;
    fVar1 = fVar6 * pvec2->x + fVar7 * pvec2->y + fVar8 * pvec2->z * 1.0;
    fVar2 = pvec2->x * fVar1;
    fVar3 = pvec2->y * fVar1;
    fVar4 = pvec2->z * fVar1;
    fVar5 = pvec2->gUnused * fVar1;

    //if (CONCAT44(in_a2_hi, in_a2_lo) != 0)
    {
        in_a2_lo->x = fVar2;
        in_a2_lo->y = fVar3;
        in_a2_lo->z = fVar4;
        in_a2_lo->gUnused = fVar5;
    }
    //if (CONCAT44(in_a3_hi, in_a3_lo) != 0)
    {
        in_a3_lo->x = fVar6 - fVar2;
        in_a3_lo->y = fVar7 - fVar3;
        in_a3_lo->z = fVar8 - fVar4;
        in_a3_lo->gUnused = fVar9 - fVar5;
    }
    return fVar1;
}
