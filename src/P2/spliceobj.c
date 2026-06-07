#include <spliceobj.h>

INCLUDE_ASM("asm/nonmatchings/P2/spliceobj", PeopidFind__FP5BASICi);

INCLUDE_ASM("asm/nonmatchings/P2/spliceobj", RefGetObjectList__FP5BASIC4OTYPPFPv_v);

INCLUDE_ASM("asm/nonmatchings/P2/spliceobj", RefGetPeopid__FP5BASICP5EOPID);

INCLUDE_ASM("asm/nonmatchings/P2/spliceobj", FAppendSpliceListElement__FPvT0);

INCLUDE_ASM("asm/nonmatchings/P2/spliceobj", FSpliceListElementExists__FPvT0);

INCLUDE_ASM("asm/nonmatchings/P2/spliceobj", RefSetPvsFromSplice__FiP4CRefP4OTYPPPv);

INCLUDE_ASM("asm/nonmatchings/P2/spliceobj", RefSetArgListFromPvs__FiP4OTYPPPv);

INCLUDE_ASM("asm/nonmatchings/P2/spliceobj", RefSetPeopid__FP5BASICP5EOPIDP4CRef);

CRef RefGetOption(BASIC *pbasic, int optid)
{
    if (optid < 0x495)
    {
        EOPID *peopid = PeopidFind(pbasic, optid);
        return RefGetPeopid(pbasic, peopid);
    }
    else
    {
        CRef ref;
        pbasic->psidebag->FFindBinding(optid, &ref);
        return ref;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/spliceobj", RefSetOption__FP5BASICiP4CRef);

INCLUDE_ASM("asm/nonmatchings/P2/spliceobj", RefAddOption__FP5BASICiP4CRef);

INCLUDE_ASM("asm/nonmatchings/P2/spliceobj", RefEnsureOption__FP5BASICiP4CRef);

INCLUDE_ASM("asm/nonmatchings/P2/spliceobj", RefSetArgsFromSplice__FiP4CRefP4OTYPe);
