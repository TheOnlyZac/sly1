#include <joy.h>

INCLUDE_ASM(const s32, "P2/joy", StartupJoy__Fv);

INCLUDE_ASM(const s32, "P2/joy", AddGrfusr__Fi);

INCLUDE_ASM(const s32, "P2/joy", RemoveGrfusr__Fi);

INCLUDE_ASM(const s32, "P2/joy", UpdateGrfjoytFromGrfusr__Fv);

INCLUDE_ASM(const s32, "P2/joy", InitJoy__FP3JOYii);

INCLUDE_ASM(const s32, "P2/joy", UpdateJoy__FP3JOY);

INCLUDE_ASM(const s32, "P2/joy", SetJoyJoys__FP3JOY4JOYS4JOYK);

INCLUDE_ASM(const s32, "P2/joy", GetJoyXYDeflection__FP3JOYUcUcPfN23PUcT6PiP2LM);

INCLUDE_ASM(const s32, "P2/joy", FReadJoy__FP3JOY);

INCLUDE_ASM(const s32, "P2/joy", SetJoyBtnHandled__FP3JOYUs);

INCLUDE_ASM(const s32, "P2/joy", rumble_related);
INCLUDE_ASM(const s32, "P2/joy", func_0016EC80);

INCLUDE_ASM(const s32, "P2/joy", StartJoySelection__FP3JOY);

INCLUDE_ASM(const s32, "P2/joy", DxSelectionJoy__FP3JOY);

INCLUDE_ASM(const s32, "P2/joy", DySelectionJoy__FP3JOY);

INCLUDE_ASM(const s32, "P2/joy", UBtnpJoy__FP3JOY4BTNP);

INCLUDE_ASM(const s32, "P2/joy", AddCode__FP4CODE);
INCLUDE_ASM(const s32, "P2/joy", func_0016F1F0);

INCLUDE_ASM(const s32, "P2/joy", _ResetCodes__Fv);

INCLUDE_ASM(const s32, "P2/joy", _MatchCodes__FP3JOYUs);

INCLUDE_ASM(const s32, "P2/joy", UpdateCodes__Fv);

INCLUDE_ASM(const s32, "P2/joy", remove_all_fchts);

INCLUDE_ASM(const s32, "P2/joy", AddFcht__Fi);
INCLUDE_ASM(const s32, "P2/joy", func_0016F470);

INCLUDE_ASM(const s32, "P2/joy", Chetkido__Fv);

INCLUDE_ASM(const s32, "P2/joy", StartupCodes__Fv);
