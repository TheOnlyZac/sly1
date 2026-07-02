#include <sky.h>
#include <alo.h>
#include <cm.h>

INCLUDE_ASM("asm/nonmatchings/P2/sky", PostSkyLoad__FP3SKY);

void UpdateSky(SKY *psky, float dt)
{
    VU_VECTOR vec;
    void (*pfn)(SKY *, VU_VECTOR *);

    UpdateAlo((ALO *)psky, dt);

    vec = STRUCT_OFFSET(g_pcm, 0x40, VU_VECTOR);
    if (STRUCT_OFFSET(psky, 0x2D0, int) == 0)
    {
        STRUCT_OFFSET(&vec, 0x8, float) = STRUCT_OFFSET(psky, 0x148, float);
    }

    pfn = (void (*)(SKY *, VU_VECTOR *))STRUCT_OFFSET(STRUCT_OFFSET(psky, 0x0, char *), 0x84, void *);
    pfn(psky, &vec);
}
