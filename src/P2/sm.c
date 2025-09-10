#include <sm.h>

INCLUDE_ASM("asm/nonmatchings/P2/sm", LoadSmFromBrx__FP2SMP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/sm", PostSmLoad__FP2SM);

INCLUDE_ASM("asm/nonmatchings/P2/sm", PostSmLoadCallback__FP2SM5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/sm", PsmaApplySm__FP2SMP3ALO3OIDi);

INCLUDE_ASM("asm/nonmatchings/P2/sm", PsmaFindSm__FP2SMP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/sm", IsmsFindSmOptional__FP2SM3OID);

INCLUDE_ASM("asm/nonmatchings/P2/sm", IsmsFindSmRequired__FP2SM3OID);

INCLUDE_ASM("asm/nonmatchings/P2/sm", OidFromSmIsms__FP2SMi);

INCLUDE_ASM("asm/nonmatchings/P2/sm", RetractSma__FP3SMA);

INCLUDE_ASM("asm/nonmatchings/P2/sm", SetSmaGoal__FP3SMA3OID);

INCLUDE_ASM("asm/nonmatchings/P2/sm", GetSmaGoal__FP3SMAP3OID);

INCLUDE_ASM("asm/nonmatchings/P2/sm", GetSmaCur__FP3SMAP3OID);

INCLUDE_ASM("asm/nonmatchings/P2/sm", GetSmaNext__FP3SMAP3OID);

INCLUDE_ASM("asm/nonmatchings/P2/sm", SetSmaSvt__FP3SMAf);

INCLUDE_ASM("asm/nonmatchings/P2/sm", SeekSma__FP3SMA3OID);

INCLUDE_ASM("asm/nonmatchings/P2/sm", ChooseSmaTransition__FP3SMA);

INCLUDE_ASM("asm/nonmatchings/P2/sm", EndSmaTransition__FP3SMA);

INCLUDE_ASM("asm/nonmatchings/P2/sm", HandleSmaMessage__FP3SMA5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/sm", SkipSma__FP3SMAf);

INCLUDE_ASM("asm/nonmatchings/P2/sm", SendSmaMessage__FP3SMA5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/sm", FUN_001b6df8);

INCLUDE_ASM("asm/nonmatchings/P2/sm", NotifySmaSpliceOnEnterState__FP3SMAii);
