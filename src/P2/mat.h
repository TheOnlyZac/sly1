/**
 * @file mat.h
 *
 * @brief Defines 4x4 and 3x3 matrix types.
*/
#pragma once

typedef struct MATRIX4 GRFDP;

/**
 * @brief 4x4 Matrix
*/
struct MATRIX4
{
	float mat[4][4];
};

/**
 * @brief 3x3 Matrix
*/
struct MATRIX3
{
	float mat[3][3];
};
