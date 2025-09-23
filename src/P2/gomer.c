#include <gomer.h>
#include <stepguard.h>
#include <find.h>
#include <memory.h>
#include <aseg.h>
#include <waypoint.h>
#include <basic.h>
#include <sw.h>
#include <chkpnt.h>

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

void PostGomerLoad(GOMER *pgomer)
{
    PostStepguardLoad(pgomer);

    // If OID at 0xC18 is not NIL, find nearest LO of OID at 0xc18, and save it to 0xC1C.
    if (STRUCT_OFFSET(pgomer, 0xC18, OID) != OID_Nil)
    {
        STRUCT_OFFSET(pgomer, 0xC1C, LO *) = PloFindSwNearest(
            pgomer->psw,
            STRUCT_OFFSET(pgomer, 0xC18, OID),
            pgomer);
    }

    // If OID at 0xC30 is not NIL, find nearest LO of OID at 0xc30, and save it to 0xC34.
    if (STRUCT_OFFSET(pgomer, 0xC30, OID) != OID_Nil)
    {
        STRUCT_OFFSET(pgomer, 0xC34, LO *) = PloFindSwNearest(
            pgomer->psw,
            STRUCT_OFFSET(pgomer, 0xC30, OID),
            pgomer);
    }

    // If aseg pointer at 0x750 is null, skip waypoint collection.
    if (!STRUCT_OFFSET(pgomer, 0x750, ASEG *))
    {
        return;
    }

    InitStackImpl();

    // Collect aseg waypoints.
    WAYPOINT **apwaypoint;
    int cpwaypoint;
    GetAsegWaypoints(STRUCT_OFFSET(pgomer, 0x750, ASEG *), pgomer, &cpwaypoint, &apwaypoint);

    for (int i = 0; i < cpwaypoint; i++)
    {
        WAYPOINT *waypoint = apwaypoint[i];
        if (!STRUCT_OFFSET(waypoint, 0x328, WPSG *))
        {
            WPSG *newwpsg = PwpsgNew();
            STRUCT_OFFSET(waypoint, 0x328, WPSG *) = newwpsg;
            AddWpsgWaypoint(newwpsg, (WAYPOINT *)waypoint);
        }
    }

    FreeStackImpl();
}

INCLUDE_ASM("asm/nonmatchings/P2/gomer", FUN_00167ef0);

INCLUDE_ASM("asm/nonmatchings/P2/gomer", FDetectGomer__FP5GOMER);
#ifdef SKIP_ASM
extern float func_001C7A60(GOMER *pgomer);
extern int func_001CB3D0(GOMER *pgomer);

/**
 * @todo 52.12% matched.
 */
int FDetectGomer(GOMER *pgomer)
{
    if (!pgomer->psw)
    {
        return 0;
    }

    GOMERS gomers = STRUCT_OFFSET(pgomer, 0x724, GOMERS);
    if (gomers == (GOMERS)0x10 || gomers == (GOMERS)0x08)
    {
        return 0;
    }

    // Call func at pvtgomer->0x198 to get pbasic.
    VT *pvtgomer = STRUCT_OFFSET(pgomer, 0x0, VT *);
    void *fp = STRUCT_OFFSET(pvtgomer, 0x198, void *);
    void *(*fn)(GOMER *) = (void *(*)(GOMER *))fp;
    void *pbasic = fn(pgomer);

    // If C40 flag set, or basic is null, clear latch and return 0.
    if (!STRUCT_OFFSET(pgomer, 0xC40, int) || !pbasic)
    {
        STRUCT_OFFSET(pgomer, 0xC38, int) = 0;
        return 0;
    }

    if (pbasic && FIsBasicDerivedFrom((BASIC *)pbasic, (CID)5)) // CID_PO?
    {
        // If basic derived from CID 5, call method at pvt???->0x144 and check for return == 2.
        VTBASIC *pvtbasic = STRUCT_OFFSET(pbasic, 0x0, VTBASIC *);
        void *fp2 = STRUCT_OFFSET(pvtbasic, 0x144, void *);
        int (*getState)(void *) = (int (*)(void *))fp2;
        if (getState(pbasic) == 2)
        {
            STRUCT_OFFSET(pgomer, 0xC38, int) = 0;
            return 0;
        }
    }

    // If exclude volume at 0xC1C exists, and point NOT inside it, clear C38 and return 0.
    if (STRUCT_OFFSET(pgomer, 0xC1C, void *))
    {
        VOL *vol = STRUCT_OFFSET(pgomer, 0xC1C, VOL *);
        int inside = FCheckVolPoint(vol, &STRUCT_OFFSET(pbasic, 0x140, VECTOR));
        if (!inside)
        {
            STRUCT_OFFSET(pgomer, 0xC38, int) = 0;
            return 0;
        }
    }
    else
    {
        // Vertical threshold then 2D XY distance check against C10 using pbasic@0x140 vs pgomer@0x190.
        float vert_diff;
        float vth;
        float dx;
        float dy;
        float dist;
        float *tpos;
        float *gpos2;
        vert_diff = STRUCT_OFFSET(pbasic, 0x148, float) - STRUCT_OFFSET(pgomer, 0x198, float);
        if (vert_diff < 0.0f)
        {
            vert_diff = -vert_diff;
        }
        vth = STRUCT_OFFSET(pgomer, 0xC14, float);
        if (vert_diff > vth)
        {
            STRUCT_OFFSET(pgomer, 0xC38, int) = 0;
            return 0;
        }

        tpos = &STRUCT_OFFSET(pbasic, 0x140, float);
        gpos2 = &STRUCT_OFFSET(pgomer, 0x190, float);
        dx = tpos[0] - gpos2[0];
        dy = tpos[1] - gpos2[1];
        /* sqrtf prototype (avoid including headers) */
        {
            extern float sqrtf(float);
            dist = sqrtf(dx * dx + dy * dy);
        }
        if (dist > STRUCT_OFFSET(pgomer, 0xC10, float))
        {
            STRUCT_OFFSET(pgomer, 0xC38, int) = 0;
            return 0;
        }
    }

    /* Second-phase: if already latched (C38!=0), return 1 */
    if (STRUCT_OFFSET(pgomer, 0xC38, int))
    {
        return 1;
    }

    /* If include volume at 0xC34 exists and point inside, skip straight to final checks */
    if (STRUCT_OFFSET(pgomer, 0xC34, void *))
    {
        int inside2 = FCheckVolPoint(STRUCT_OFFSET(pgomer, 0xC34, VOL *), &STRUCT_OFFSET(pbasic, 0x140, VECTOR));
        if (inside2)
        {
            if (func_001CB3D0(pgomer))
            {
                return 0;
            }

            STRUCT_OFFSET(pgomer, 0xC38, int) = 1;
            return 1;
        }
    }

    /* Range gating using positions at 0x140 for both */
    float *gpos;
    float *tpos2;
    float dx2;
    float dy2;
    float dist2;
    float outer;

    gpos = &STRUCT_OFFSET(pgomer, 0x140, float);
    tpos2 = &STRUCT_OFFSET(pbasic, 0x140, float);
    dx2 = gpos[0] - tpos2[0];
    dy2 = gpos[1] - tpos2[1];
    {
        extern float sqrtf(float);
        dist2 = sqrtf(dx2 * dx2 + dy2 * dy2);
    }

    outer = STRUCT_OFFSET(pgomer, 0xC24, float);
    if (!(dist2 < outer))
    {
        return 0;
    }

    float inner;
    float angle_min;
    float angle_max;
    float f20;
    float a;

    inner = STRUCT_OFFSET(pgomer, 0xC20, float);
    if (dist2 < inner)
    {
        f20 = STRUCT_OFFSET(pgomer, 0xC2C, float);
    }
    else
    {
        float one;
        float num;
        float den;
        float t;

        one = 1.0f;
        angle_max = STRUCT_OFFSET(pgomer, 0xC2C, float);
        angle_min = STRUCT_OFFSET(pgomer, 0xC28, float);
        num = dist2 - inner;
        den = outer - inner;
        if (den != 0.0f)
        {
            t = num / den;
        }
        else
        {
            t = 0.0f;
        }
        f20 = t * angle_min + (one - t) * angle_max;
    }

    a = func_001C7A60(pgomer);
    if (a < 0.0f)
    {
        a = -a;
    }
    if (a <= f20)
    {
        return 0;
    }

    if (func_001CB3D0(pgomer))
    {
        return 0;
    }

    STRUCT_OFFSET(pgomer, 0xC38, int) = 1;
    return STRUCT_OFFSET(pgomer, 0xC38, int);
}
#endif
