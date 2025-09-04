#include <blip.h>

extern QW *g_aqwBlipeGifsNormal;
extern QW *g_aqwBlipeGifsClampedAdd;

INCLUDE_ASM(const s32, "P2/blip", BuildBlipAqwGifs__FiPP2QW);

void StartupBlips()
{
    BuildBlipAqwGifs(1, &g_aqwBlipeGifsNormal);
    BuildBlipAqwGifs(2, &g_aqwBlipeGifsClampedAdd);
}

INCLUDE_ASM(const s32, "P2/blip", PblipNew__FP5BLIPG);

INCLUDE_ASM(const s32, "P2/blip", RemoveBlip__FP4BLIP);

INCLUDE_ASM(const s32, "P2/blip", PblipgNew__FP2SW);

INCLUDE_ASM(const s32, "P2/blip", InitBlipg__FP5BLIPG);

INCLUDE_ASM(const s32, "P2/blip", OnBlipgAdd__FP5BLIPG);

INCLUDE_ASM(const s32, "P2/blip", OnBlipgRemove__FP5BLIPG);

INCLUDE_ASM(const s32, "P2/blip", SetBlipgShader__FP5BLIPG3OID);

INCLUDE_ASM(const s32, "P2/blip", PropagateBlipgShader__FP5BLIPG);

INCLUDE_ASM(const s32, "P2/blip", SetBlipgEmitb__FP5BLIPGP5EMITB);

INCLUDE_ASM(const s32, "P2/blip", UpdateBlipg__FP5BLIPGf);

INCLUDE_ASM(const s32, "P2/blip", SubscribeBlipgObject__FP5BLIPGP2LO);

INCLUDE_ASM(const s32, "P2/blip", CblipeProjectBlipTransformAccel__FP7MATRIX4G8VU_FLOATP5BLIPPP5BLIPVP5BLIPXi6BLIPOKP6VECTORT7);

INCLUDE_ASM(const s32, "P2/blip", ProjectBlipgTransformAccel__FP5BLIPGf);

INCLUDE_ASM(const s32, "P2/blip", ProjectBlipgTransform__FP5BLIPGfi);

INCLUDE_ASM(const s32, "P2/blip", RenderBlipgSelf__FP5BLIPGP2CMP2RO);

INCLUDE_ASM(const s32, "P2/blip", DrawBlipg__FP3RPL);

INCLUDE_ASM(const s32, "P2/blip", PropagateBlipgShaders__Fi);
