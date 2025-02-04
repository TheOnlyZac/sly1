#include <basic.h>
#include <splice/gc.h>
#include <splice/sidebag.h>

extern CGc g_gc;

int FIsBasicDerivedFrom(BASIC *pbasic, CID cid) {
    VTBASIC *vt = pbasic->pvtbasic;
    while (vt != 0) {
        if (vt->cid == cid) return 1;
        vt = vt->pvtSuper;
    }

    return 0;
}

void EnsureBasicSidebag(BASIC *pbasic) {
    if (pbasic->psidebag == 0) {
        CSidebag *psidebag = PsidebagNew();
        pbasic->psidebag = psidebag;
        g_gc.AddRootSidebag(psidebag);
    }
    return;
}

INCLUDE_ASM(const s32, "P2/basic", func_00130158);
