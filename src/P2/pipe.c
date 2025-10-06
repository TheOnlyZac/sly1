#include <pipe.h>
#include <find.h>
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

void PostPipeLoad(PIPE *ppipe)
{
    PostLoLoad(ppipe);
    if (ppipe->oid != OID_Nil)
    {
        // TODO: Check whether this is LO or something that inherits from it.
        ppipe->plo = PloFindSwObject(ppipe->psw, 4, ppipe->oid, ppipe);
    }
}

void ClonePipe(PIPE *ppipe, PIPE *ppipeBase)
{
    DLE dlePipe = ppipe->dlePipe;
    CloneLo(ppipe, ppipeBase);
    ppipe->dlePipe = dlePipe;
}
