#include <sort.h>

void SwapEntries(void *afoo, int cb, int i1, int i2)
{
    int *p1 = (int *)(i1 * cb + (int)afoo);
    int *p2 = (int *)(i2 * cb + (int)afoo);

    while (cb > 0)
    {
        int temp = *p1;
        *p1 = *p2;
        *p2 = temp;

        p1++;
        p2++;
        cb -= sizeof(int);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sort", HeapSort__FPviiPFPvPv_i);
