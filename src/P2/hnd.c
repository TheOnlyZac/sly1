#include <hnd.h>

extern float D_0024A7DC;

void InitHnd(HND *phnd)
{
    InitTarget(phnd);
    phnd->grftak = 1;
    phnd->sfxidRelease = (SFXID)8; // Supposed to be SFXID_CaneHandleLock.
    phnd->sfxidGrab = (SFXID)9; // Supposed to be SFXID_CaneHandleUnlock.
    phnd->unk1 = D_0024A7DC;
}

void LoadHndFromBrx(HND *phnd, CBinaryInputStream *pbis)
{
    LoadXfmFromBrx(phnd, pbis);
}

JUNK_NOP();
JUNK_ADDIU(A0);
JUNK_ADDIU(E0);
