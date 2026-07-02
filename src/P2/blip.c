#include <blip.h>
#include <sce/memset.h>

extern QW *g_aqwBlipeGifsNormal;
extern QW *g_aqwBlipeGifsClampedAdd;

INCLUDE_ASM("asm/nonmatchings/P2/blip", BuildBlipAqwGifs__FiPP2QW);

void StartupBlips()
{
    BuildBlipAqwGifs(1, &g_aqwBlipeGifsNormal);
    BuildBlipAqwGifs(2, &g_aqwBlipeGifsClampedAdd);
}

BLIP *PblipNew(BLIPG *pblipg)
{
    BLIP *pblip;
    void *pv;

    pblip = (BLIP *)PvAllocSlotheapUnsafe(
        (SLOTHEAP *)((uint8_t *)STRUCT_OFFSET(pblipg, 0x14, void *) + 0x1B40));
    if (pblip == NULL)
        return NULL;

    memset(pblip, 0, 0x10C0);

    if (STRUCT_OFFSET(pblipg, 0x320, int) == 2)
    {
        pv = PvAllocSlotheapUnsafe(
            (SLOTHEAP *)((uint8_t *)STRUCT_OFFSET(pblipg, 0x14, void *) + 0x1B4C));
        STRUCT_OFFSET(pblip, 0x1088, void *) = pv;
        if (pv == NULL)
        {
            FreeSlotheapPv(
                (SLOTHEAP *)((uint8_t *)STRUCT_OFFSET(pblipg, 0x14, void *) + 0x1B40),
                pblip);
            return NULL;
        }
        memset(pv, 0, 0x580);
        STRUCT_OFFSET(pblip, 0x108C, BLIPG *) = pblipg;
    }
    else
    {
        STRUCT_OFFSET(pblip, 0x108C, BLIPG *) = pblipg;
    }

    AppendDlEntry((DL *)((uint8_t *)pblipg + 0x624), pblip);
    return pblip;
}

INCLUDE_ASM("asm/nonmatchings/P2/blip", RemoveBlip__FP4BLIP);

INCLUDE_ASM("asm/nonmatchings/P2/blip", PblipgNew__FP2SW);

void InitBlipg(BLIPG *pblipg)
{
    uint64_t flags;

    AppendDlEntry((DL *)((uint8_t *)STRUCT_OFFSET(pblipg, 0x14, void *) + 0x1CC0), pblipg);
    InitAlo((ALO *)pblipg);
    InitDl((DL *)((uint8_t *)pblipg + 0x624), 0x1090);

    flags = STRUCT_OFFSET(pblipg, 0x2C8, uint64_t);
    flags &= 0xFFFFFFFFCFFFFFFFULL;
    flags |= 0x20000000;
    STRUCT_OFFSET(pblipg, 0x80, float) = 10000000000.0f;
    flags &= 0xFFFFFCFFFFFFFFFFULL;
    flags |= 0x10000000000ULL;
    STRUCT_OFFSET(pblipg, 0x2C8, uint64_t) = flags;
}

void OnBlipgAdd(BLIPG *pblipg)
{
    RemoveDlEntry((DL *)((uint8_t *)STRUCT_OFFSET(pblipg, 0x14, void *) + 0x1CC0), pblipg);
    AppendDlEntry((DL *)((uint8_t *)STRUCT_OFFSET(pblipg, 0x14, void *) + 0x1CB4), pblipg);
    OnAloAdd((ALO *)pblipg);
}

INCLUDE_ASM("asm/nonmatchings/P2/blip", OnBlipgRemove__FP5BLIPG);

INCLUDE_ASM("asm/nonmatchings/P2/blip", SetBlipgShader__FP5BLIPG3OID);

INCLUDE_ASM("asm/nonmatchings/P2/blip", PropagateBlipgShader__FP5BLIPG);

INCLUDE_ASM("asm/nonmatchings/P2/blip", SetBlipgEmitb__FP5BLIPGP5EMITB);

INCLUDE_ASM("asm/nonmatchings/P2/blip", UpdateBlipg__FP5BLIPGf);

INCLUDE_ASM("asm/nonmatchings/P2/blip", SubscribeBlipgObject__FP5BLIPGP2LO);

INCLUDE_ASM("asm/nonmatchings/P2/blip", CblipeProjectBlipTransformAccel__FP7MATRIX4G8VU_FLOATP5BLIPPP5BLIPVP5BLIPXi6BLIPOKP6VECTORT7);

INCLUDE_ASM("asm/nonmatchings/P2/blip", ProjectBlipgTransformAccel__FP5BLIPGf);

INCLUDE_ASM("asm/nonmatchings/P2/blip", ProjectBlipgTransform__FP5BLIPGfi);

INCLUDE_ASM("asm/nonmatchings/P2/blip", RenderBlipgSelf__FP5BLIPGP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/blip", DrawBlipg__FP3RPL);

INCLUDE_ASM("asm/nonmatchings/P2/blip", PropagateBlipgShaders__Fi);
