/**
 * @note Should be merged with mat.c.
 */
#include <mat.h>

void AddMatrix4Matrix4(MATRIX4 *pmatLeft, MATRIX4 *pmatRight, MATRIX4 *pmatDst)
{
    for(int i = 0; i < 16; i++)
    {
        pmatDst->mat[0][i] = pmatLeft->mat[0][i] + pmatRight->mat[0][i];
    }
}

INCLUDE_ASM(const s32, "P2/mat_AddMatrix4Matrix4", junk_00188848);
