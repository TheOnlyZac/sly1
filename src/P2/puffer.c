#include <puffer.h>
#include <po.h>

INCLUDE_ASM("asm/nonmatchings/P2/puffer", InitPuffer__FP6PUFFER);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", LoadPufferFromBrx__FP6PUFFERP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", PostPufferLoad__FP6PUFFER);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", PresetPufferAccel__FP6PUFFERf);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", FFilterPuffer__FP6PUFFERP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", UpdatePuffer__FP6PUFFERf);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", PpufftChoosePuffer__FP6PUFFER);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", FUN_001973d8);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", FUN_00197458);

void OnPufferActive(PUFFER *ppuffer, int fActive, PO *ppoOther)
{
    OnPoActive(ppuffer, fActive, ppoOther);
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", UpdatePufferActive__FP6PUFFERP3JOYf);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", FUN_00197788);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", FUN_00197848);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", FUN_00197a08);

extern float D_0026A83C;
extern float D_0026A840;

extern "C" void FUN_00197a68(void *pv, void *p)
{
    float dx = D_0026A83C;
    float dy = D_0026A840;
    STRUCT_OFFSET(p, 0x98, float) = dx;
    STRUCT_OFFSET(p, 0x94, float) = dy;
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", AddPufferWaterAcceleration__FP6PUFFERP5WATERf);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", HandlePufferMessage__FP6PUFFER5MSGIDPv);

void PostPuffcLoad(PUFFC *ppuffc)
{
    PostStepguardLoad((STEPGUARD *)ppuffc);
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", PresetPuffcAccel__FP5PUFFCf);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", FUN_001982a0);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", UpdatePuffcGoal__FP5PUFFCi);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", OnPuffcExitingSgs__FP5PUFFC3SGS);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", OnPuffcEnteringSgs__FP5PUFFC3SGSP4ASEG);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", UpdatePuffcSgs__FP5PUFFC);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", HandlePuffcMessage__FP5PUFFC5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", UpdatePuffc__FP5PUFFCf);

int FCanPuffcAttack(PUFFC *ppuffc)
{
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", FUN_00198860);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", PostPuffbLoad__FP5PUFFB);
