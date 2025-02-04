#include <basic.h>

int FIsBasicDerivedFrom(BASIC *pbasic, CID cid) {
    VTBASIC *vt = pbasic->pvtbasic;
    while (vt != 0) {
        if (vt->cid == cid) return 1;
        vt = vt->pvtSuper;
    }

    return 0;
}

INCLUDE_ASM(const s32, "P2/basic", EnsureBasicSidebag__FP5BASIC);

INCLUDE_ASM(const s32, "P2/basic", func_00130158);
