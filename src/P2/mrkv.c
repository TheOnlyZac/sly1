#include <mrkv.h>

void InitMrkv(MRKV *pmrkv)
{
    InitSo(pmrkv);
    STRUCT_OFFSET(pmrkv, 0x538, ulong) = STRUCT_OFFSET(pmrkv, 0x538, ulong) | 0x80000000000;
    SetSoConstraints(pmrkv, CT_Locked, (VECTOR *)nullptr, CT_Locked, (VECTOR *)nullptr);
}
