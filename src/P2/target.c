#include <target.h>

DL g_dlTarget = {0};
int g_fShowTargets = 0; // NOTE: Seemingly only used in prototype but not in retail.

void StartupTarget()
{
    InitDl(&g_dlTarget, offsetof(TARGET, dleTarget));
}

void ResetTargetList()
{
    ClearDl(&g_dlTarget);
}

void InitTarget(TARGET *ptarget)
{
    InitXfm(ptarget);
    ptarget->grftak = 0x1e;
    ptarget->sRadiusTarget = 25.0f;
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
    DLE dleTarget = ptarget->dleTarget;
    CloneLo(ptarget, ptargetBase);
    ptarget->dleTarget = dleTarget;
}
