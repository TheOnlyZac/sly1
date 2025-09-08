#include <pipe.h>

INCLUDE_ASM(const s32, "P2/pipe", StartupPipe__Fv);

INCLUDE_ASM(const s32, "P2/pipe", ResetPipeList__Fv);

INCLUDE_ASM(const s32, "P2/pipe", InitPipe__FP4PIPE);

INCLUDE_ASM(const s32, "P2/pipe", OnPipeAdd__FP4PIPE);

INCLUDE_ASM(const s32, "P2/pipe", OnPipeRemove__FP4PIPE);

INCLUDE_ASM(const s32, "P2/pipe", PostPipeLoad);

INCLUDE_ASM(const s32, "P2/pipe", ClonePipe__FP4PIPET0);
