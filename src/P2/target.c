#include <target.h>

extern DL g_dlTarget;

void StartupTarget()
{
    InitDl(&g_dlTarget, 0x80);
}

void ResetTargetList()
{
    ClearDl(&g_dlTarget);
}

INCLUDE_ASM(const s32, "P2/target", InitTarget__FP6TARGET);

INCLUDE_ASM(const s32, "P2/target", OnTargetAdd__FP6TARGET);

INCLUDE_ASM(const s32, "P2/target", OnTargetRemove__FP6TARGET);

INCLUDE_ASM(const s32, "P2/target", CloneTarget__FP6TARGETT0);
