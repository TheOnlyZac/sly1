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

    int grfzon = 0;
    while (pvismap->cgrfzon > grfzon)
    {
        pvismap->agrfzonOneHop[grfzon++] = pbis->U32Read();
    }

    LoadOptionsFromBrx(pvismap, pbis);
}

INCLUDE_ASM("asm/nonmatchings/P2/vis", GrfzonOneHop__FP6VISMAPP4VBSP);

INCLUDE_ASM("asm/nonmatchings/P2/vis", ClipVbspSphereOneHop__FP6VISMAPP4VBSPG9VU_VECTORfPi);

INCLUDE_ASM("asm/nonmatchings/P2/vis", ClipVismapSphereOneHop__FP6VISMAPP6VECTORfPi);

INCLUDE_ASM("asm/nonmatchings/P2/vis", ClipVismapPointNoHop__FP6VISMAPP6VECTORPi);
