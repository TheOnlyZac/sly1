#include <spire.h>
#include <sw.h>

/**
 * @todo Rename.
 */
extern float DAT_0024d3b4;

void InitSpire(SPIRE *pspire)
{
    InitLo(pspire);
    STRUCT_OFFSET(pspire, 0x58, float) = DAT_0024d3b4;
}

void OnSpireAdd(SPIRE *pspire)
{
    OnLoAdd(pspire);
    AppendDlEntry(&pspire->psw->dlSpire, pspire);
}

void OnSpireRemove(SPIRE *pspire)
{
    OnLoRemove(pspire);
    RemoveDlEntry(&pspire->psw->dlSpire, pspire);
}

void CloneSpire(SPIRE *pspire, SPIRE *pspireBase)
{
    // pspire->dleSpire
    DLE dleSpire = STRUCT_OFFSET(pspire, 0x50, DLE); 
    CloneLo(pspire, pspireBase);
    STRUCT_OFFSET(pspire, 0x50, DLE) = dleSpire;
}
