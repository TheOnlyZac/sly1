/**
 * @file asega.h
 */
#ifndef ASEGA_H
#define ASEGA_H

#include "common.h"
#include <basic.h>
#include <aseg.h>
#include <dl.h>
#include <sw.h>

// Forward.
struct ACTSEG;
struct CHN;
struct EA;

/**
 * @class ANIMATION_SEGMENT_APPLICATION
 * @brief Unknown.
 */
struct ASEGA : public BASIC
{
    /* 0x08 */ ASEG *paseg;
    /* 0x0c */ LO *plo;
    /* 0x10 */ STRUCT_PADDING(1);
    /* 0x14 */ float tLocal;
    /* 0x18 */ float svtLocal;
    /* 0x1c */ float svtMaster;
    /* 0x20 */ int ieaCur;
    /* 0x24 */ char fHandsOff;
    /* 0x25 */ undefined1 unk1;
    /* 0x26 */ undefined1 unk2;
    /* 0x27 */ undefined1 unk3;
    /* 0x28 */ ACTSEG *pactsegError;
    /* 0x2c */ STRUCT_PADDING(6);
    /* 0x44 */ DL dlActseg;
    /* 0x50 */ STRUCT_PADDING(4);
    /* 0x60 */ uint32_t *punk60; // points at unk64
    /* 0x64 */ uint32_t unk64[32];
    /* 0xe4 */ MQ *pmqFirst;
    // ...
};

/**
 * @brief Allocates and initializes a new animation segment application.
 *
 * @param psw The world to allocate the segment in.
 * @return The new, zeroed and initialized animation segment application.
 */
ASEGA *PasegaNew(SW *psw);

void SetAsegaHandsOff(ASEGA *pasega, int fHandsOff);

void UpdateAsegaIeaCur(ASEGA *pasega);

/**
 * @brief Finds the action segment of an animation segment whose object matches an ID.
 *
 * @param pasega The animation segment application to search.
 * @param oid The object ID to look for.
 * @return The first matching action segment, or null if none match.
 */
ACTSEG *PactsegFindAsega(ASEGA *pasega, OID oid);

void HandleAsegaEvent(ASEGA *pasega, EA *pea, int *pfRetracted);

void HandleAsegaEventsFF(ASEGA *pasega, ASEG *paseg, int *pfRetract);

void HandleAsegaEvents(ASEGA *pasega, ASEG *paseg, int *pfRetracted);

void RemoveAsega(ASEGA *pasega);

void RetractAsega(ASEGA *pasega);

float UFromEaErrorFunc(EA *pea, float s);

int FWrapAsegaTime(ASEGA *pasega, float *ptLocal, float *psvtLocal);

void UpdateAsega(ASEGA *pasega, float dt);

void SeekAsega(ASEGA *pasega, SEEK seek, float dtLocal, float svtLocal);

/**
 * @brief Snaps every action segment of an animation segment.
 *
 * @param pasega The animation segment application to snap.
 * @param fForce Passed through to each action segment.
 */
void SnapAsega(ASEGA *pasega, int fForce);

/**
 * @brief Adapts every action segment of an animation segment.
 *
 * @param pasega The animation segment application to adapt.
 */
void AdaptAsega(ASEGA *pasega);

void FindChnClosestPointLocal(CHN *pchn, ALO *palo, VECTOR *ppos, float tAsegMax, float sIgnore, float t, float *ptClosest, VECTOR *pposClosest, VECTOR *pvClosest);

/**
 * @brief Sets the playback speed of an animation segment.
 *
 * @param pasega The animation segment application to update.
 * @param svt The requested speed.
 * @note The meaning of "svt" is a guess from its name and usage.
 */
void SetAsegaSpeed(ASEGA *pasega, float svt);

/**
 * @brief Sets the master speed of an animation segment.
 *
 * @details Re-applies the current speed so it reflects the new master speed.
 *
 * @param pasega The animation segment application to update.
 * @param svtMaster The new master speed.
 */
void SetAsegaMasterSpeed(ASEGA *pasega, float svtMaster);

/**
 * @brief Sets the priority of every action segment of an animation segment.
 *
 * @param pasega The animation segment application to update.
 * @param nPriority The new priority value.
 */
void SetAsegaPriority(ASEGA *pasega, int nPriority);

/**
 * @brief Retracts the action segment of an animation segment that matches an ID.
 *
 * @param pasega The animation segment application to search.
 * @param oid The object ID of the action segment to retract.
 * @param grfra Passed through to the action's retract function.
 * @note The real name of this function is unknown.
 */
void FUN_0012e928(ASEGA *pasega, OID oid, int grfra);

/**
 * @brief Sends a message to an animation segment's target object and subscribers.
 *
 * @details Forwards to the target object, then calls each subscriber. The next
 * entry is read before each callback, so a callback may unlink itself.
 *
 * @param pasega The animation segment application sending the message.
 * @param msgid The message ID.
 * @param pv Message data passed to the object and each callback.
 */
void SendAsegaMessage(ASEGA *pasega, MSGID msgid, void *pv);

/**
 * @brief Subscribes a callback to messages sent by an animation segment.
 *
 * @param pasega The animation segment application to subscribe to.
 * @param pfnmq The callback to invoke for messages.
 * @param pvContext Context pointer passed to the callback.
 */
void SubscribeAsegaStruct(ASEGA *pasega, PFNMQ pfnmq, void *pvContext);

/**
 * @brief Subscribes an object's message handler to messages sent by an animation segment.
 *
 * @param pasega The animation segment application to subscribe to.
 * @param ploTarget The object whose message handler to register.
 */
void SubscribeAsegaObject(ASEGA *pasega, LO *ploTarget);

#endif // ASEGA_H
