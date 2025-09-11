#include <pipe.h>
#include <dl.h>

extern DL g_dlPipe;

void StartupPipe()
{
    InitDl(&g_dlPipe, 0x38);
}

void ResetPipeList()
{
    ClearDl(&g_dlPipe);
}

INCLUDE_ASM("asm/nonmatchings/P2/pipe", InitPipe__FP4PIPE);

void OnPipeAdd(PIPE *ppipe)
{
    OnLoAdd(ppipe);
    AppendDlEntry(&g_dlPipe, ppipe);
}

void OnPipeRemove(PIPE *ppipe)
{
    OnLoRemove(ppipe);
    RemoveDlEntry(&g_dlPipe, ppipe);
}

INCLUDE_ASM("asm/nonmatchings/P2/pipe", PostPipeLoad);

INCLUDE_ASM("asm/nonmatchings/P2/pipe", ClonePipe__FP4PIPET0);
