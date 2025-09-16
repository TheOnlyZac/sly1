#include <gomer.h>
#include <stepguard.h>
#include <find.h>
#include <memory.h>
#include <waypoint.h>

#define PI 3.1415927f

void InitGomer(GOMER *pgomer)
{
    InitStepguard(pgomer);
    STRUCT_OFFSET(pgomer, 0xC20, float) = 1000.0f;
    STRUCT_OFFSET(pgomer, 0xC24, float) = 1500.0f;
    STRUCT_OFFSET(pgomer, 0xC28, float) = PI / 4.0f;
    STRUCT_OFFSET(pgomer, 0xC2C, float) = PI;
    STRUCT_OFFSET(pgomer, 0xC10, float) = 2000.0f;
    STRUCT_OFFSET(pgomer, 0xC30, OID) = OID_Nil;
    STRUCT_OFFSET(pgomer, 0xC14, float) = 300.0f;
    STRUCT_OFFSET(pgomer, 0xC18, OID) = OID_Nil;
    STRUCT_OFFSET(pgomer, 0x73C, float) = 300.0f;
    STRUCT_OFFSET(pgomer, 0x738, int) = 0;
    STRUCT_OFFSET(pgomer, 0x74C, float) = PI / 3.0f;
}

INCLUDE_ASM("asm/nonmatchings/P2/gomer", PostGomerLoad__FP5GOMER);
#ifdef SKIP_ASM
extern int func_0012D1B0(int worldLevel, GOMER *pgomer, int *outCount, void ***outArray);

/**
 * @todo 99.74% matched.
 *
 * The call to func_0012D1B0 is problematic.
 */
void PostGomerLoad(GOMER *pgomer)
{
    PostStepguardLoad(pgomer);

    // If CID at offset 0xC18 is not NIL, find nearest SW and store to 0xC1C.
    if (STRUCT_OFFSET(pgomer, 0xC18, OID) != OID_Nil)
    {
        STRUCT_OFFSET(pgomer, 0xC1C, LO *) = PloFindSwNearest(
            pgomer->psw,
            STRUCT_OFFSET(pgomer, 0xC18, OID),
            pgomer);
    }

    // If CID at offset 0xC30 is not NIL, find nearest SW and store to 0xC34.
    if (STRUCT_OFFSET(pgomer, 0xC30, OID) != OID_Nil)
    {
        STRUCT_OFFSET(pgomer, 0xC34, LO *) = PloFindSwNearest(
            pgomer->psw,
            STRUCT_OFFSET(pgomer, 0xC30, OID),
            pgomer);
    }

    /* if world/level pointer at 0x750 is zero, skip waypoint building */
    if (!STRUCT_OFFSET(pgomer, 0x750, int))
    {
        return;
    }

    InitStackImpl();

    /* Call helper to populate an array and count. func_0012D1B0 writes the
       count and array pointer into memory we provide addresses for. */
    void **arr;
    int count;
    func_0012D1B0(STRUCT_OFFSET(pgomer, 0x750, int), pgomer, &count, &arr);

    for (int i = 0; i < count; i++)
    {
        void *elem = arr[i];
        if (!STRUCT_OFFSET(elem, 0x328, WPSG *))
        {
            WPSG *newwpsg = PwpsgNew();
            STRUCT_OFFSET(elem, 0x328, WPSG *) = newwpsg;
            AddWpsgWaypoint(newwpsg, (WAYPOINT *)elem);
        }
    }

    FreeStackImpl();
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/gomer", FUN_00167ef0);

INCLUDE_ASM("asm/nonmatchings/P2/gomer", FDetectGomer__FP5GOMER);
