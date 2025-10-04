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

void InitTarget(TARGET *ptarget)
{
    InitXfm(ptarget);
    STRUCT_OFFSET(ptarget, 0x88, int) = 0x1e; // ptarget->grftak
    STRUCT_OFFSET(ptarget, 0x8c, float) = 25.0f; // ptarget->sRadiusTarget
}

void OnTargetAdd(TARGET *ptarget)
{
    OnLoAdd(ptarget);
    AppendDlEntry(&g_dlTarget, ptarget);
}

void OnTargetRemove(TARGET *ptarget)
{
    OnLoRemove(ptarget);
    RemoveDlEntry(&g_dlTarget, ptarget);
}

void CloneTarget(TARGET *ptarget, TARGET *ptargetBase)
{
    DLE dleTarget = STRUCT_OFFSET(ptarget, 0x80, DLE); // ptarget->dleTarget
    CloneLo(ptarget, ptargetBase);
    STRUCT_OFFSET(ptarget, 0x80, DLE) = dleTarget; // ptarget->dleTarget
}
