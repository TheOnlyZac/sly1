#include <waypoint.h>
#include <button.h>
#include <memory.h>
#include <sw.h>

extern SNIP s_asnipPostWaypointLoad;
extern VTWPSG g_vtwpsg;

void InitWaypoint(WAYPOINT *pwaypoint)
{
    InitAlo(pwaypoint);
    pwaypoint->wps = WPS_Nil;
    pwaypoint->oidSync = OID_Nil;
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
    FAddRsmg(pwaypoint->arsmgSet, 4, &pwaypoint->crsmgSet, fOnTrigger, oidRoot, oidSm, oidGoal);
}

void UpdateWaypoint(WAYPOINT *pwaypoint, float dt)
{
    return;
}

INCLUDE_ASM("asm/nonmatchings/P2/waypoint", SetWaypointWps__FP8WAYPOINT3WPS);
#ifdef SKIP_ASM
/**
 * @todo 98.60% match. Uses "bnez" instead of "beqz".
 */
void SetWaypointWps(WAYPOINT *pwaypoint, WPS wps)
{
    if (pwaypoint->wps == wps)
    {
        return;
    }

    if (wps == WPS_Passive)
    {
        if (pwaypoint->wps == WPS_Active)
        {
            TriggerRsmg(g_psw, pwaypoint->crsmgSet, pwaypoint->arsmgSet, pwaypoint, 1);
        }
    }
    else if (wps == WPS_Active)
    {
        TriggerRsmg(g_psw, pwaypoint->crsmgSet, pwaypoint->arsmgSet, pwaypoint, 0);
    }

    MSGWPT msgwpt;
    msgwpt.pwaypoint = pwaypoint;
    msgwpt.wpsFrom = pwaypoint->wps;
    msgwpt.wpsTo = wps;

    pwaypoint->wps = wps;
    pwaypoint->tWps = g_clock.t;

    pwaypoint->pvtlo->pfnSendLoMessage(pwaypoint, (MSGID)0x16, &msgwpt);
}
#endif // SKIP_ASM

void HandleWaypointMessage(WAYPOINT *pwaypoint, MSGID msgid, void *pv)
{
    HandleAloMessage(pwaypoint, msgid, pv);

    if (msgid == MSGID_asega_limit && STRUCT_OFFSET(pv, 0x08, ASEG *) == pwaypoint->paseg)
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
    if ((uint)pwpsg->cpwaypoint < 8)
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
        PostSwCallback(g_psw, UpdateWpsgCallback, pwpsg, MSGID_Nil, NULL);
    }
}

JUNK_ADDIU(40);
