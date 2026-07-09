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

void HeapSort(void *afoo, int iMac, int cb, PFNCMP pfncmp)
{
    int iLast, cHalf, iRoot, iChild;

    if (iMac < 2)
    {
        return;
    }
    iLast = iMac - 1;
    cHalf = iMac / 2;
    for (;;)
    {
        if (cHalf > 0)
        {
            // build phase: sift the next non-leaf down
            cHalf--;
        }
        else
        {
            // extract phase: move the max to the end, shrink the heap
            SwapEntries(afoo, cb, iLast, 0);
            if (iLast-- < 2)
            {
                return;
            }
        }
        iRoot = cHalf;
        iChild = iRoot * 2 + 1;
        while (iChild <= iLast)
        {
            if (iChild < iLast)
            {
                if (pfncmp((void *)(iChild * cb + (int)afoo), (void *)((iChild + 1) * cb + (int)afoo)) < 0)
                {
                    iChild = iChild + 1;
                }
            }
            if (pfncmp((void *)(iRoot * cb + (int)afoo), (void *)(iChild * cb + (int)afoo)) < 0)
            {
                SwapEntries(afoo, cb, iRoot, iChild);
                iRoot = iChild;
                iChild += iChild + 1;
            }
            else
            {
                break;
            }
        }
    }
}
