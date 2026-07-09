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

extern VU_VECTOR g_normalX;
extern float D_0024B650; // FLT_MAX

void InitPipe(PIPE *ppipe)
{
    InitLo(ppipe);
    ppipe->normal = g_normalX;
    ppipe->unk_0x58 = -1;
    ppipe->unk_0x54 = 9;
    ppipe->unk_0x50 = 8;
    ppipe->unk_0x5c = D_0024B650;
    ppipe->oid = OID_Nil;
}

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
