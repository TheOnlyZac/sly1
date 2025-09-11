#include <waypoint.h>

void InitWaypoint(WAYPOINT *pwaypoint)
{
    InitAlo__FP3ALO(pwaypoint);
    STRUCT_OFFSET(pwaypoint, 0x2d0, int) = -1; // pwaypoint->oidSync
    STRUCT_OFFSET(pwaypoint, 0x2e0, int) = -1; // pwaypoint->wps
}

INCLUDE_ASM("asm/nonmatchings/P2/waypoint", PostWaypointLoad__FP8WAYPOINT);

INCLUDE_ASM("asm/nonmatchings/P2/waypoint", SetWaypointRsmg__FP8WAYPOINTi3OIDN22);

void UpdateWaypoint(WAYPOINT *pwaypoint, float dt)
{
    return;
}

INCLUDE_ASM("asm/nonmatchings/P2/waypoint", SetWaypointWps__FP8WAYPOINT3WPS);

INCLUDE_ASM("asm/nonmatchings/P2/waypoint", HandleWaypointMessage__FP8WAYPOINT5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/waypoint", PwpsgNew__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/waypoint", AddWpsgWaypoint__FP4WPSGP8WAYPOINT);

INCLUDE_ASM("asm/nonmatchings/P2/waypoint", RemoveWpsgWaypoint__FP4WPSGP8WAYPOINT);

INCLUDE_ASM("asm/nonmatchings/P2/waypoint", UpdateWpsgCallback__FP4WPSG5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/waypoint", EnsureWpsgCallback__FP4WPSG);

INCLUDE_ASM("asm/nonmatchings/P2/waypoint", junk_001EFCE0);
