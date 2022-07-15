#pragma once
#include <iostream>
#include <so.h>
#include <util.h>

typedef unsigned char byte;
typedef int GRFPVA;

struct VECTOR
{
    float x;
    float y;
    float z;
    float gUnused;
};

struct BSPC
{
    int cbsp;
    int cbspFull;
    struct BSP* absp;
};

enum CT
{
    CT_Tangent = 1,
    CT_Free = 0,
    CT_Project = 2,
    CT_Locked = 3
};

struct CONSTR
{
    struct VECTOR normal;
    CT ct;
};

struct CLQ
{
    float g0;
    float g1;
    float g2;
    float gUnused;
    float u4ag[1];
};

void CalculateVectorPanTilt(VECTOR* param_1, float* param_2, float* param_3);
void ConvertDeulToW(VECTOR* param_1, VECTOR* param_2, VECTOR* param_3);
bool FCalculateMuzzleVelocity(VECTOR* param_1, VECTOR* param_2, VECTOR* param_3, VECTOR* param_4, SO* param_5);
uint32_t FCalculateMuzzleVelocityAngle(VECTOR* param_1, VECTOR* param_2, float param_3, VECTOR* param_4, SO* param_5);
void FindClosestPointBetweenLines(VECTOR* param_1, VECTOR* param_2, VECTOR* param_3, VECTOR* param_4, float* param_5, float* param_6, VECTOR* param_7);
void FindClosestPointBetweenLineSegments(VECTOR* param_1, VECTOR* param_2, VECTOR* param_3, VECTOR* param_4, VECTOR param_5, float* param_6, VECTOR* param_7);
void GetNormalVector(VECTOR* param_1, VECTOR* param_2);
void GetNormalVectors(VECTOR* param_1, VECTOR* param_2, VECTOR* param_3, VECTOR* param_4);
void LimitVectorLength(VECTOR* param_1, float param_2, VECTOR* param_3);
long RadBetweenVectors(VECTOR* param_1, VECTOR* param_2, VECTOR* param_3);
void SetVectorCylind(float param_1, float param_2, float param_3, VECTOR* param_4);
void SetVectorSphere(float param_1, float param_2, float param_3, VECTOR* param_4);
float SProjectVector(VECTOR* param_1, VECTOR* param_2);
