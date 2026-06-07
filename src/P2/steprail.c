#include <steprail.h>

extern "C" void FUN_001bc4d8(uint8_t *param_1, uint8_t *param_2);

INCLUDE_ASM("asm/nonmatchings/P2/steprail", func_001D31D0__FP2LOi);

INCLUDE_ASM("asm/nonmatchings/P2/steprail", post_load_steprail);

INCLUDE_ASM("asm/nonmatchings/P2/steprail", func_001D32D8__FiP2JTl);

INCLUDE_ASM("asm/nonmatchings/P2/steprail", update_steprail);

INCLUDE_ASM("asm/nonmatchings/P2/steprail", preset_steprail_accel);

void FUN_001d34e0(uint8_t *param_1)
{
    FUN_001bc4d8(param_1, param_1 + 0x554);
}

INCLUDE_ASM("asm/nonmatchings/P2/steprail", FUN_001d3500);

INCLUDE_ASM("asm/nonmatchings/P2/steprail", FUN_001d35a8);

INCLUDE_ASM("asm/nonmatchings/P2/steprail", update_steprail_message);
