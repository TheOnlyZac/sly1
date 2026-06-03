#include <mrkv.h>

void InitMrkv(MRKV *pmrkv)
{
    InitSo(pmrkv);
    STRUCT_OFFSET(pmrkv, 0x538, ulong) |= 0x80000000000; // pmrkv->bspcCamera.absp
    SetSoConstraints(pmrkv, CT_Locked, NULL, CT_Locked, NULL);
}
