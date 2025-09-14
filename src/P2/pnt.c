#include <pnt.h>
#include <brx.h>

void LoadPntFromBrx(PNT *ppnt, CBinaryInputStream *pbis)
{
    pbis->ReadVector(&STRUCT_OFFSET(ppnt, 0x40, VECTOR)); // ppnt->posLocal
    LoadOptionsFromBrx(ppnt, pbis);
}

void GetPntPos(PNT *ppnt, VECTOR *ppos)
{
    ConvertAloPos(ppnt->paloParent, (ALO *)nullptr, &STRUCT_OFFSET(ppnt, 0x40, VECTOR), ppos); // ppnt->posLocal
}

INCLUDE_ASM("asm/nonmatchings/P2/pnt", SetPntParent__FP3PNTP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/pnt", ApplyPntProxy__FP3PNTP5PROXY);

INCLUDE_ASM("asm/nonmatchings/P2/pnt", FUN_00192150);

INCLUDE_ASM("asm/nonmatchings/P2/pnt", FUN_00192190);
