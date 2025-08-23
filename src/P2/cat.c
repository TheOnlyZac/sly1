#include <cat.h>
#include "cd.h"

extern CDS g_cds;

void StartupCatalog()
{
    g_cds = CDS_Ready;
}

INCLUDE_ASM(const s32, "P2/cat", FUN_001407A0);
