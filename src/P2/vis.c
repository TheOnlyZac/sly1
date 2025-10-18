#include <vis.h>
#include <sw.h>
#include <brx.h>
#include <memory.h>

void InitVismap(VISMAP *pvismap)
{
    InitLo(pvismap);
    pvismap->psw->pvismap = pvismap;
}

void LoadVismapFromBrx(VISMAP *pvismap, CBinaryInputStream *pbis)
{
    pbis->ReadVbsp(&pvismap->cvbsp, &pvismap->avbsp);

    pvismap->cgrfzon = pbis->U16Read();
    pvismap->agrfzonOneHop = (GRFZON *)PvAllocSwImpl(pvismap->cgrfzon * sizeof(GRFZON));

    for (int i = 0; i < pvismap->cgrfzon; i++)
    {
        pvismap->agrfzonOneHop[i] = pbis->U32Read();
    }

    LoadOptionsFromBrx(pvismap, pbis);
}

GRFZON GrfzonOneHop(VISMAP *pvismap, VBSP *pvbsp)
{
    int bits = (int)((uint)pvbsp & 0x7fffffff);
    if (bits == 0)
        return 0;

    int acc = -1;
    for (int i = 0; i < pvismap->cgrfzon; i++)
    {
        int shifted = bits >> i;
        if ((shifted & 1) != 0)
        {
            acc &= pvismap->agrfzonOneHop[i];
        }
    }

    return acc | (uint)bits;
}

INCLUDE_ASM("asm/nonmatchings/P2/vis", ClipVbspSphereOneHop__FP6VISMAPP4VBSPG9VU_VECTORfPi);

/**
 * @brief 89.47% match. Single load instruction mismatch. VU_VECTOR implemented wrong?
 * https://decomp.me/scratch/5lzfX
 */
INCLUDE_ASM("asm/nonmatchings/P2/vis", ClipVismapSphereOneHop__FP6VISMAPP6VECTORfPi);
#ifdef SKIP_ASM
void ClipVismapSphereOneHop(VISMAP *pvismap, VECTOR *ppos, float sRadius, GRFZON *pgrfzon)
{
    if (pvismap && pvismap->avbsp)
    {
        VU_VECTOR vuvector = *(VU_VECTOR *)ppos;
        *pgrfzon = 0;
        ClipVbspSphereOneHop(pvismap, pvismap->avbsp, vuvector, sRadius, pgrfzon);
        return;
    }

    *pgrfzon = 0xfffffff;
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/vis", ClipVismapPointNoHop__FP6VISMAPP6VECTORPi);
