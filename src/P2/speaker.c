#include <speaker.h>
#include <sm.h>
#include <find.h>

INCLUDE_ASM("asm/nonmatchings/P2/speaker", InitSpeaker__FP7SPEAKER);

INCLUDE_ASM("asm/nonmatchings/P2/speaker", PostSpeakerLoad__FP7SPEAKER);

void SetSpeakerSmIdle(SPEAKER *pspeaker, OID oid)
{
    if (STRUCT_OFFSET(pspeaker, 0x334, SMA *) != NULL)
    {
        RetractSma(STRUCT_OFFSET(pspeaker, 0x334, SMA *));
        STRUCT_OFFSET(pspeaker, 0x334, SMA *) = NULL;
    }

    SM *psm = (SM *) PloFindSwObject(pspeaker->psw, 0x101, oid, pspeaker);
    STRUCT_OFFSET(pspeaker, 0x330, SM *) = psm;

    if (psm != NULL)
    {
        STRUCT_OFFSET(pspeaker, 0x334, SMA *) = PsmaApplySm(psm, pspeaker, (OID)-1, 1);
    }

    STRUCT_OFFSET(pspeaker, 0x32c, OID) = oid;
}
