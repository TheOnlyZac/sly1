/**
 * @file waypoint.h
 */
#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "common.h"
#include <alo.h>
#include <oid.h>
#include <mq.h>
#include <rs.h>

// Forward.
struct SGG;
struct WPSG;

/**
 * @brief Waypoint state.
 */
enum WPS
{
    WPS_Nil = -1,
    WPS_Passive = 0,
    WPS_Sync = 1,
    WPS_Active = 2,
    WPS_Max = 3
};

/**
 * @class WAY_POINT
 * @brief Waypoint.
 */
struct WAYPOINT : public ALO
{
    /* 0x2d0 */ WPS wps;
    /* 0x2d4 */ float tWps;
    float dtPause;
    /* 0x2dc */ ASEG *paseg;
    /* 0x2e0 */ OID oidSync;
    /* 0x2e4 */ int crsmgSet;
    /* 0x2e8 */ RSMG arsmgSet[4];
    WPSG *pwpsg;
};

/**
 * @brief Stepguard waypoint?
 */
struct WPSG
{
    /* 0x00 */ VTWPSG *pvtwpsg;
    /* 0x04 */ int cpwaypoint;
    /* 0x08 */ WAYPOINT *apwaypoint[8];
    /* 0x28 */ int fCallback;
    /* 0x2c */ SGG *psgg;
};

/**
 * @brief Message waypoint?
 */
struct MSGWPT
{
    /* 0x00 */ WAYPOINT *pwaypoint;
    /* 0x04 */ WPS wpsFrom;
    /* 0x08 */ WPS wpsTo;
};

void InitWaypoint(WAYPOINT *pwaypoint);

void PostWaypointLoad(WAYPOINT *pwaypoint);

void SetWaypointRsmg(WAYPOINT *pwaypoint, int fOnTrigger, OID oidRoot, OID oidSm, OID oidGoal);

void UpdateWaypoint(WAYPOINT *pwaypoint, float dt);

void SetWaypointWps(WAYPOINT *pwaypoint, WPS wps);

void HandleWaypointMessage(WAYPOINT *pwaypoint, MSGID msgid, void *pv);

WPSG *PwpsgNew();

void AddWpsgWaypoint(WPSG *pwpsg, WAYPOINT *pwaypoint);

void RemoveWpsgWaypoint(WPSG *pwpsg, WAYPOINT *pwaypoint);

void UpdateWpsgCallback(WPSG *pwpsg, MSGID msgid, void *pv);

void EnsureWpsgCallback(WPSG *pwpsg);

#endif // WAYPOINT_H
