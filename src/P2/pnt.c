#include <pnt.h>
#include <brx.h>

void LoadPntFromBrx(PNT *ppnt, CBinaryInputStream *pbis)
{
    pbis->ReadVector(&ppnt->posLocal);
    LoadOptionsFromBrx(ppnt, pbis);
}

void GetPntPos(PNT *ppnt, VECTOR *ppos)
{
    ConvertAloPos(ppnt->paloParent, (ALO *)nullptr, &ppnt->posLocal, ppos);
}

void SetPntParent(PNT *ppnt, ALO *paloParent)
{
    ConvertAloPos(ppnt->paloParent, paloParent, &ppnt->posLocal, &ppnt->posLocal);
    SetLoParent(ppnt, paloParent);
}

void ApplyPntProxy(PNT *ppnt, PROXY *pproxyApply)
{
    ConvertAloPos((ALO *)pproxyApply, (ALO *)nullptr, &ppnt->posLocal, &ppnt->posLocal);
}

/**
 * @todo Rename function and figure out what does it actually do.
 */
void FUN_00192150(PNT *ppnt, CBinaryInputStream *pbis)
{
    LoadPntFromBrx(ppnt, pbis);
    pbis->ReadStringSw(&STRUCT_OFFSET(ppnt, 0x50, char *));
}

/**
 * @todo Rename function and figure out what does it actually do.
 */
void FUN_00192190(PNT *ppnt)
{
    STRUCT_OFFSET(ppnt, 0x54, float) = 0.5f;
    STRUCT_OFFSET(ppnt, 0x58, float) = 0.5f;
}
