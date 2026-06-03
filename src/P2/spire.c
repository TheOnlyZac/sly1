#include <spire.h>
#include <sw.h>

/**
 * @todo Rename.
 */
extern float DAT_0024d3b4; // FLT_MAX (3.40282346638529E38)

void InitSpire(SPIRE *pspire)
{
    InitLo(pspire);
    pspire->unk1 = DAT_0024d3b4;
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
    DLE dleSpire = pspire->dleSpire;
    CloneLo(pspire, pspireBase);
    pspire->dleSpire = dleSpire;
}
