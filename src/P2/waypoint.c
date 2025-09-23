#include <waypoint.h>
#include <button.h>
#include <memory.h>
#include <sw.h>

extern SNIP s_asnipPostWaypointLoad;
extern VTWPSG g_vtwpsg;

void InitWaypoint(WAYPOINT *pwaypoint)
{
    InitAlo(pwaypoint);
    STRUCT_OFFSET(pwaypoint, 0x2d0, int) = -1; // pwaypoint->oidSync
    STRUCT_OFFSET(pwaypoint, 0x2e0, int) = -1; // pwaypoint->wps
}

void PostWaypointLoad(WAYPOINT *pwaypoint)
{
    PostAloLoad(pwaypoint);
    SnipAloObjects(pwaypoint, 1, &s_asnipPostWaypointLoad);
    SetWaypointWps(pwaypoint, WPS_Passive);
    pwaypoint->pvtlo->pfnRemoveLo(pwaypoint);
}

void SetWaypointRsmg(WAYPOINT *pwaypoint, int fOnTrigger, OID oidRoot, OID oidSm, OID oidGoal)
{
    // pwaypoint->arsmgSet & pwaypoint->crsmgSet
    FAddRsmg(&STRUCT_OFFSET(pwaypoint, 0x2e8, RSMG), 4, &STRUCT_OFFSET(pwaypoint, 0x2e4, int), fOnTrigger, oidRoot, oidSm, oidGoal);
}

void UpdateWaypoint(WAYPOINT *pwaypoint, float dt)
{
    return;
}

INCLUDE_ASM("asm/nonmatchings/P2/waypoint", SetWaypointWps__FP8WAYPOINT3WPS);

void HandleWaypointMessage(WAYPOINT *pwaypoint, MSGID msgid, void *pv)
{
    HandleAloMessage(pwaypoint, msgid, pv);

    // pwaypoint->paseg
    if (msgid == MSGID_asega_limit && STRUCT_OFFSET(pv, 0x08, ASEG *) == STRUCT_OFFSET(pwaypoint, 0x2dc, ASEG *))
    {
        SetWaypointWps(pwaypoint, WPS_Passive);
    }
}

WPSG *PwpsgNew()
{
    WPSG *pwpsg = (WPSG *)PvAllocSwClearImpl(sizeof(WPSG));
    pwpsg->pvtwpsg = &g_vtwpsg;
    return pwpsg;
}

void AddWpsgWaypoint(WPSG *pwpsg, WAYPOINT *pwaypoint)
{
    if (pwpsg->cpwaypoint < 8)
    {
        pwpsg->apwaypoint[pwpsg->cpwaypoint++] = pwaypoint;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/waypoint", RemoveWpsgWaypoint__FP4WPSGP8WAYPOINT);

INCLUDE_ASM("asm/nonmatchings/P2/waypoint", UpdateWpsgCallback__FP4WPSG5MSGIDPv);

void EnsureWpsgCallback(WPSG *pwpsg)
{
    if (!pwpsg->fCallback)
    {
        pwpsg->fCallback = 1;
        PostSwCallback(g_psw, UpdateWpsgCallback, pwpsg, MSGID_Nil, nullptr);
    }
}

JUNK_ADDIU(40);
