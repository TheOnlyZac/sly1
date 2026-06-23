#include <steprail.h>
#include <alo.h>
#include <so.h>

INCLUDE_ASM("asm/nonmatchings/P2/steprail", func_001D31D0__FP2LOi);

extern "C" void post_load_steprail(ALO *palo)
{
    extern SNIP D_00274F90;
    PostAloLoad(palo);
    SnipAloObjects(palo, 1, &D_00274F90);
    void **ppvtable = (void **)STRUCT_OFFSET(palo, 0x0, void*);
    void (*pfn)(ALO *) = (void (*)(ALO *))STRUCT_OFFSET(ppvtable, 0x1c, void*);
    pfn(palo);
}

INCLUDE_ASM("asm/nonmatchings/P2/steprail", func_001D32D8__FiP2JTl);

INCLUDE_ASM("asm/nonmatchings/P2/steprail", update_steprail);

extern "C" void preset_steprail_accel(SO *pso, float dt)
{
    MATRIX3 mat;
    extern VECTOR D_00248D30;

    PresetSoAccel(pso, dt);

    if (STRUCT_OFFSET(pso, 0x18, int) == 0) // pso->paloParent
    {
        TiltMatUpright((MATRIX3 *)((uint8_t *)pso + 0xD0), NULL, &mat);
        AccelSoTowardMatSpring(
            pso,
            &mat,
            STRUCT_OFFSET(pso, 0x214, CLQ *),
            &D_00248D30,
            STRUCT_OFFSET(pso, 0x218, CLQ *),
            dt);
    }
}

void FUN_001d34e0(uint8_t *param_1)
{
    FUN_001bc4d8(param_1, param_1 + 0x554);
}

int FUN_001d3500(SO *pso, WKR *pwkr)
{
    int fAbsorbed = FAbsorbSoWkr(pso, pwkr);
    if (fAbsorbed != 0 && (pwkr->grfic & 0x20))
    {
        LO *plo = pwkr->ploSource;
        int g;
        if (STRUCT_OFFSET(STRUCT_OFFSET(plo, 0x0, uint8_t *), 0x8, int) & 1)
        {
            g = STRUCT_OFFSET(plo, 0x50, int);
        }
        else
        {
            g = STRUCT_OFFSET(STRUCT_OFFSET(plo, 0x18, uint8_t *), 0x50, int);
        }
        func_001D32D8((int)pso, (JT *)pwkr->ploSource, g == (int)(long)g_pjt);
        FreeSwXpList(STRUCT_OFFSET(pso, 0x14, SW *), STRUCT_OFFSET(pso, 0x554, XP *));
        STRUCT_OFFSET(pso, 0x554, XP *) = 0;
    }
    return fAbsorbed;
}

INCLUDE_ASM("asm/nonmatchings/P2/steprail", FUN_001d35a8);

INCLUDE_ASM("asm/nonmatchings/P2/steprail", update_steprail_message);
