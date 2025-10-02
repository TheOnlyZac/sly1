#include <hnd.h>

extern float D_0024A7DC;

void InitHnd(HND *phnd)
{
    InitTarget(phnd);

    float val = D_0024A7DC;
    STRUCT_OFFSET(phnd, 0x88, int) = 1; // phnd->grftak
    STRUCT_OFFSET(phnd, 0xa8, int) = 8; // Likely phnd->sfxidRelease
    STRUCT_OFFSET(phnd, 0xac, int) = 9; // Likely phnd->sfxidGrab
    STRUCT_OFFSET(phnd, 0xb4, float) = val;
}

/**
 * @todo Objdiff reports a 100% match, but checksum check still fails.
 */
INCLUDE_ASM("asm/nonmatchings/P2/hnd", LoadHndFromBrx__FP3HNDP18CBinaryInputStream);
#ifdef SKIP_ASM
void LoadHndFromBrx(HND *phnd, CBinaryInputStream *pbis)
{
    LoadXfmFromBrx(phnd, pbis);
}
#endif // SKIP_ASM

JUNK_ADDIU(A0);
JUNK_ADDIU(E0);
