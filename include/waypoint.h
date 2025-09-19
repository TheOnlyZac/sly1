/**
 * @file waypoint.h
 */
#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "common.h"
#include <alo.h>
#include <oid.h>
#include <mq.h>

// Forward.
struct SGG;

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
    undefined1 unknown[2];
    WPS wps;
    float tWps;
    float dtPause;
    // ...
};

/**
 * @brief Stepguard waypoint?
 */
struct WPSG
{
    /* 0x00 */ VTWPSG *pvtwpsg;
    /* 0x04 */ uint cpwaypoint;
    /* 0x08 */ WAYPOINT *apwaypoint[8];
    /* 0x28 */ int fCallback;
    /* 0x2c */ SGG *psgg;
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
