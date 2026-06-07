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

void LoadHndFromBrx(HND *phnd, CBinaryInputStream *pbis)
{
    LoadXfmFromBrx(phnd, pbis);
}

JUNK_NOP();
JUNK_ADDIU(A0);
JUNK_ADDIU(E0);
