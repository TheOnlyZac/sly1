#include <sprbuf.h>

INCLUDE_ASM("asm/nonmatchings/P2/sprbuf", LoadSprBuf__Fie);

INCLUDE_ASM("asm/nonmatchings/P2/sprbuf", SaveSprBuf__FPve);

JUNK_ADDIU(A0);

INCLUDE_ASM("asm/nonmatchings/P2/sprbuf", sprbuf__static_initialization_and_destruction_0);

INCLUDE_ASM("asm/nonmatchings/P2/sprbuf", _GLOBAL_$I$g_asprbuf);
