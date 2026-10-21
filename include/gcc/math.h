/**
 * @file math.h
 *
 * @brief Library math functions.
 */
#ifndef MATH_H
#define MATH_H

extern "C"
{
    float atanf(float x);
    float cosf(float x);
    float sinf(float x);
    float tanf(float x);
    float acosf(float x);
    float asinf(float x);
    float atan2f(float x, float y);
    float fmodf(float x, float y);
    float sqrtf(float x);
}

#endif // MATH_H
