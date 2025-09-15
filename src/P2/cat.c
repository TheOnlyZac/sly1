#include <cat.h>
#include <cd.h>

extern CDS g_cds;

void StartupCatalog()
{
    g_cds = CDS_Ready;
}

int FUN_001407A0(uint *pui)
{
    return pui[1];
}
