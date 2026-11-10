#include <asega.h>
#include <sw.h>
#include <actseg.h>
#include <find.h>
#include <sound.h>
#include <dialog.h>
#include <xform.h>
#include <so.h>
#include <wipe.h>
#include <screen.h>
#include <sm.h>
#include <jsg.h>
#include <jt.h>
#include <mpeg.h>
#include <joy.h>
#include <ui.h>
#include <pnt.h>
#include <game.h>
#include <act.h>
#include <alo.h>
#include <rumble.h>

extern VTBASIC g_vtasega;

ASEGA *PasegaNew(SW *psw)
{
    ASEGA *pasega = (ASEGA *)PvAllocSlotheapClearImpl(&psw->slotheapAsega);
    pasega->pvtbasic = &g_vtasega;
    InitDl(&pasega->dlActseg, 0x20);
    pasega->punk60 = pasega->unk64;
    return pasega;
}

void SetAsegaHandsOff(ASEGA *pasega, int fHandsOff)
{
    if (fHandsOff == pasega->fHandsOff)
        return;

    if (fHandsOff)
    {
        IncrementSwHandsOff(g_psw);
    }
    else
    {
        DecrementSwHandsOff(g_psw);
    }

    pasega->fHandsOff = fHandsOff;
}

INCLUDE_ASM("asm/nonmatchings/P2/asega", UpdateAsegaIeaCur__FP5ASEGA);

ACTSEG *PactsegFindAsega(ASEGA *pasega, OID oid)
{
    VECTOR vec; // unused, but needed to match the original stack frame
    for (ACTSEG *pactseg = (ACTSEG *)pasega->dlActseg.head; pactseg != 0; pactseg = (ACTSEG *)pactseg->dleAsega.next)
    {
        if (FMatchesLoName(pactseg->palo, oid))
        {
            return pactseg;
        }
    }
    return 0;
}

JUNK_NOP();
JUNK_ADDIU(10);

#include <actseg.h>

// Functions and data used here that have no header yet.
struct CREDIT
{
    void **pvtcredit;
};
void ContinueMusic();
void PauseMusic();
void DisableCamera(CAMERA *pcamera);
void StopTimer(TIMER *ptimer);
extern "C" void PreloadVag1(int);
extern "C" void FUN_001ddb58(SW *psw);
extern "C" void FUN_001ddbb8(SW *psw);
int FPauseForVag();
void StopVag();
int FContinuousSound(SFXID sfxid);
void SetJtPuppet(JT *pjt, ASEGA *pasega);
void PlaceCredit(CREDIT *pcredit, float x, float y, int i);
void VacateCredit(CREDIT *pcredit);
void SetCreditLine(CREDIT *pcredit, int iLine, char *pchz, float u);
extern CREDIT D_00272E08;
extern TIMER g_unkblot9;

/** Unaligned int access. Reproduces the swl/swr store the original code does (the real cause is unknown). */
struct __attribute__((packed)) UNALIGNED_INT
{
    int n;
};

struct VTCHN
{
    void (*pfnEval)(CHN *, ALO *, float, float, int, void *, void *);
};

/** Sound event description, pointed to by the event's first argument. */
struct SNDEV
{
    short csfx;
    short asfxid[6];
    short iLast;
    short oid;
    short unk12;
    int sFull;
    int sStart;
    float frq;
    float uDoppler;
    float uVolAtSource;
};

/** Message sent by event 39 (name is a guess). */
struct ASEGMSG13
{
    ASEGA *pasega;
    float t;
    int n;
};

/** Message sent by event 41 (name is a guess). */
struct ASEGMSG15
{
    ASEGA *pasega;
    LO *plo;
    float t;
};

/** Event description for starting another aseg. */
struct ASEGEV
{
    OID oidAseg;
    OID oidRoot;
    float t;
    float svt;
};

/** Event description for a transform projection. */
struct PROJEV
{
    OID oidAlo;
    OID oidTarget;
    OID oidUp;
    float g;
};

/** Message handed to the ALO's pfnProjectAloTransform. */
struct PROJMSG
{
    int grf;
    void *pv4;
    int unk8[6];
    VECTOR pos;
    float g30;
    int unk34;
    void *pv38;
};

/**
 * @brief Handles one event of an animation segment.
 *
 * @details Events (EA) are the timed triggers stored in an animation segment: sounds and music,
 * showing and hiding objects, wipes, camera and Sly control changes, messages to other objects, and so on.
 * Called by HandleAsegaEvents for each event the playback head crosses. EA::eak picks what happens,
 * see EAK. Most cases look up a target object by OID, with the animation's object (or the segment itself)
 * as the search context, then act on it.
 *
 * Paired events (show/hide, enable/disable, hands off/on, ack begin/end, puppet on/off, act pos/rot)
 * are inverted when the segment plays backward over the segment's own event list.
 * That is what fReverse tracks: svtLocal is negative and the event is in the segment's own array.
 *
 * A few events steer playback itself: they seek (tLocal, speed), hold at a time (Hold, PauseForVag)
 * or retract the whole animation (Retract), and report that through pfRetracted so the caller stops
 * handling events.
 *
 * @param pasega The animation segment application that owns the event.
 * @param pea The event to handle.
 * @param pfRetracted Set to 1 when the event pauses or retracts the animation, so the caller stops.
 *
 * @note All the event and payload field names here are guesses from what the code does.
 */
void HandleAsegaEvent(ASEGA *pasega, EA *pea, int *pfRetracted)
{
    ASEG *paseg = pasega->paseg;
    SW *psw = paseg->psw;
    int fReverse = 0;
    if (pasega->svtLocal < 0.0f)
    {
        fReverse = pea >= paseg->aea && pea < paseg->aea + paseg->cea;
    }
    switch (pea->eak)
    {
    case EAK_PauseForVag:
    {
        if (!FPauseForVag())
            return;
        float t = pea->tLocal;
        float tMax = paseg->tMax;
        if (t < 0.0f)
            t = 0.0f;
        else if (tMax < t)
            t = tMax;
        pasega->tLocal = t;
        pasega->ieaCur--;
        *pfRetracted = 1;
        break;
    }
    case EAK_PreloadVag:
        PreloadVag1(pea->n8);
        break;
    case EAK_StopVag:
        StopVag();
        break;
    case EAK_Sound:
    {
        // pea->pv8 is re-read each time on purpose, this is what matches.
        int i;
        if (((SNDEV *)pea->pv8)->csfx < 2)
        {
            i = 0;
        }
        else
        {
            // Pick a random sound that is not the one played last.
            int r = NRandInRange(0, ((SNDEV *)pea->pv8)->csfx - 2);
            i = (((SNDEV *)pea->pv8)->iLast + r + 1) % ((SNDEV *)pea->pv8)->csfx;
            ((SNDEV *)pea->pv8)->iLast = i;
        }
        SFXID sfxid = (SFXID)((SNDEV *)pea->pv8)->asfxid[i];
        if (sfxid == -1)
            return;
        int fContinuous = FContinuousSound(sfxid);
        if (pasega->pamb != 0 && fContinuous)
            return;
        LO *plo;
        if (((SNDEV *)pea->pv8)->oid != -1)
        {
            LO *ploCtx = pasega->plo ? pasega->plo : pasega->paseg;
            plo = PloFindSwObject(psw, 0x104, (OID)((SNDEV *)pea->pv8)->oid, ploCtx);
        }
        else
        {
            plo = pasega->plo;
        }
        if (plo != 0)
        {
            StartSound(sfxid, fContinuous ? &pasega->pamb : 0, (ALO *)plo, 0, (float)((SNDEV *)pea->pv8)->sStart,
                       (float)((SNDEV *)pea->pv8)->sFull, ((SNDEV *)pea->pv8)->uVolAtSource, ((SNDEV *)pea->pv8)->frq,
                       ((SNDEV *)pea->pv8)->uDoppler, 0, 0);
            if (fContinuous && pasega->pamb != 0)
            {
                plo->pvtlo->pfnSendLoMessage(plo, (MSGID)8, pasega->pamb);
            }
        }
        else
        {
            StartSound(sfxid, fContinuous ? &pasega->pamb : 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
        break;
    }
    case EAK_StopSound:
        if (pasega->pamb != 0)
            StopSound(pasega->pamb, 0);
        break;
    case EAK_ContinueMusic:
        ContinueMusic();
        break;
    case EAK_PauseMusic:
        PauseMusic();
        break;
    case EAK_Hold:
    {
        float t = pea->tLocal;
        float tMax = paseg->tMax;
        if (t < 0.0f)
            t = 0.0f;
        else if (tMax < t)
            t = tMax;
        pasega->tLocal = t;
        pasega->svtLocal = 0.0f;
        break;
    }
    case EAK_SetTimeSpeed:
    case EAK_SetTimeSpeedAlt:
        pasega->tLocal = pea->g8;
        SetAsegaSpeed(pasega, pea->gC);
        UpdateAsegaIeaCur(pasega);
        AdaptAsega(pasega);
        break;
    case EAK_SetSpeed:
        SetAsegaSpeed(pasega, pea->g8);
        break;
    case EAK_Dialog:
    {
        LO *plo = PloFindSwObject(psw, 0x104, pea->oid8, pasega->plo ? pasega->plo : paseg);
        if (plo != 0)
            TriggerDialog((DIALOG *)plo);
        break;
    }
    case EAK_Retract:
        RetractAsega(pasega);
        *pfRetracted = 1;
        break;
    case EAK_ShowObject:
    case EAK_HideObject:
    {
        int fIn = (pea->eak == EAK_ShowObject);
        fIn ^= fReverse;
        LO *plo = PloFindSwObject(psw, 0x104, pea->oid8, pasega->plo ? pasega->plo : paseg);
        if (plo == 0)
            return;
        if (pea->gC != 0.0f)
        {
            if (fIn)
                FadeAloIn((ALO *)plo, pea->gC);
            else
                FadeAloOut((ALO *)plo, pea->gC);
        }
        else
        {
            if (fIn)
                plo->pvtlo->pfnAddLo(plo);
            else
                plo->pvtlo->pfnRemoveLo(plo);
        }
        break;
    }
    case EAK_SoConstraints:
    {
        LO *plo = PloFindSwObject(psw, 0x104, pea->oid8, pasega->plo ? pasega->plo : pasega->paseg);
        if (plo == 0)
            return;
        CT ctForce = pea->shC.s0 < 0 ? STRUCT_OFFSET(plo, 0x450, CT) : (CT)pea->shC.s0;
        CT ctTorque = pea->shC.s2 < 0 ? STRUCT_OFFSET(plo, 0x470, CT) : (CT)pea->shC.s2;
        SetSoConstraints((SO *)plo, ctForce, 0, ctTorque, 0);
        break;
    }
    case EAK_EnableCamera:
    case EAK_DisableCamera:
    {
        int fOn = pea->eak == EAK_EnableCamera;
        if (fReverse)
            fOn = !fOn;
        LO *plo = PloFindSwObject(psw, 4, pea->oid8, pasega->paseg);
        if (plo == 0)
            return;
        if (fOn)
            EnableCamera((CAMERA *)plo);
        else
            DisableCamera((CAMERA *)plo);
        break;
    }
    case EAK_HandsOff:
    case EAK_HandsOn:
    {
        int fHandsOff = (pea->eak == EAK_HandsOff);
        fHandsOff ^= fReverse;
        SetAsegaHandsOff(pasega, fHandsOff);
        break;
    }
    case EAK_PuppetOn:
    case EAK_PuppetOff:
    {
        int fPuppet = (pea->eak == EAK_PuppetOn);
        fPuppet ^= fReverse;
        // The declared second parameter is an ASEGA* but the original code passes the flag.
        SetJtPuppet(g_pjt, (ASEGA *)fPuppet);
        if (!fPuppet)
            return;
        if (pea->nC != 0)
            SnapAsega(pasega, 1);
        break;
    }
    case EAK_ActAckBegin:
    case EAK_ActAckEnd:
    {
        ACTSEG *pactseg = PactsegFindAsega(pasega, pea->oid8);
        if (pactseg == 0)
            break;
        if ((pea->eak != EAK_ActAckBegin) != (fReverse == 0))
        {
            // Matching quirk: the original does not share one register for both 5s.
            int c = 5;
            STRUCT_OFFSET(pactseg, 0x11, char) = c;
            STRUCT_OFFSET(pactseg, 0x10, char) = 5;
        }
        else
        {
            CalculateActDefaultAck(pactseg);
        }
        break;
    }
    case EAK_ErrorBeginA:
    case EAK_ErrorEndA:
    case EAK_ErrorBeginB:
    case EAK_ErrorEndB:
    {
        // Tracks the act segment used for error correction (see UFromEaErrorFunc) while either
        // of two overlapping begin/end windows is open. The meaning is a guess.
        OID oid;
        if (pea->eak == EAK_ErrorBeginA || pea->eak == EAK_ErrorBeginB)
            oid = *(OID *)pea->pv8;
        else
            oid = pea->oid8;
        ACTSEG *pactseg = PactsegFindAsega(pasega, oid);
        if (pactseg == 0)
            break;
        switch (pea->eak)
        {
        case EAK_ErrorBeginA:
            pasega->pactsegError = pactseg;
            pasega->peaErrorA = pea;
            break;
        case EAK_ErrorEndA:
            pasega->peaErrorA = 0;
            if (pasega->peaErrorB == 0)
                pasega->pactsegError = 0;
            break;
        case EAK_ErrorBeginB:
            pasega->pactsegError = pactseg;
            pasega->peaErrorB = pea;
            break;
        case EAK_ErrorEndB:
            pasega->peaErrorB = 0;
            if (pasega->peaErrorA == 0)
                pasega->pactsegError = 0;
            break;
        }
        break;
    }
    case EAK_ActivateWipe:
        ActivateWipe(&g_wipe, (TRANS *)pea->pvC, (WIPEK)pea->sh8.s0);
        break;
    case EAK_SetWipeButtonTrans:
        SetWipeButtonTrans(&g_wipe, (TRANS *)pea->pvC, (WIPEK)pea->sh8.s0);
        break;
    case EAK_DefaultExit:
    {
        if (g_pjt != 0 && STRUCT_OFFSET(g_pjt, 0x2220, int) == 9 && STRUCT_OFFSET(g_pjt, 0x2228, int) == 0x1C
            && (void *)g_plsCur == (void *)g_pwsCur)
            return;
        TriggerDefaultExit(pea->n8, (WIPEK)pea->nC);
        break;
    }
    case EAK_StartTimer:
        SetTimer(&g_unkblot9, pea->g8);
        StartTimer(&g_unkblot9);
        break;
    case EAK_StopTimer:
        StopTimer(&g_unkblot9);
        break;
    case EAK_ApplyAseg:
    {
        LO *plo = PloFindSwNearest(psw, ((ASEGEV *)pea->pv8)->oidAseg, paseg->paloParent);
        ALO *paloRoot;
        if (((ASEGEV *)pea->pv8)->oidRoot != -1)
            paloRoot = (ALO *)PloFindSwNearest(paseg->psw, ((ASEGEV *)pea->pv8)->oidRoot, paseg->paloParent);
        else
            paloRoot = 0;
        if (plo != 0)
            ApplyAseg((ASEG *)plo, paloRoot, ((ASEGEV *)pea->pv8)->t, ((ASEGEV *)pea->pv8)->svt, 0, 0);
        break;
    }
    case EAK_PosOn:
    case EAK_PosOff:
    case EAK_RotOn:
    case EAK_RotOff:
    {
        ACTSEG *pactseg = PactsegFindAsega(pasega, pea->oid8);
        int fCall = 0;
        if (pactseg != 0)
        {
            ACHN *pachn = &paseg->pachn[pactseg->iachn];
            switch (pea->eak)
            {
            case EAK_PosOn:
                if (pachn->punkPos != 0)
                {
                    uchar c = STRUCT_OFFSET(pactseg, 0x12, uchar);
                    STRUCT_OFFSET(pactseg, 0x12, uchar) = 2;
                    fCall = (uchar)(c + 1) < 2;
                }
                break;
            case EAK_PosOff:
                if (pachn->punkPos != 0)
                {
                    char c = STRUCT_OFFSET(pactseg, 0x12, char);
                    STRUCT_OFFSET(pactseg, 0x12, char) = -1;
                    fCall = c != -1;
                }
                break;
            case EAK_RotOn:
                if (pachn->punkRot != 0)
                {
                    uchar c = STRUCT_OFFSET(pactseg, 0x13, uchar);
                    STRUCT_OFFSET(pactseg, 0x13, uchar) = 2;
                    fCall = (uchar)(c + 1) < 2;
                }
                break;
            case EAK_RotOff:
                if (pachn->punkRot != 0)
                {
                    char c = STRUCT_OFFSET(pactseg, 0x13, char);
                    STRUCT_OFFSET(pactseg, 0x13, char) = -1;
                    fCall = c != -1;
                }
                break;
            }
        }
        if (!fCall)
            break;
        pactseg->palo->pvtalo->pfnRecacheAloActList(pactseg->palo);
        break;
    }
    case EAK_EvalPos:
    case EAK_EvalRot:
    {
        ACTSEG *pactseg = PactsegFindAsega(pasega, pea->oid8);
        if (pactseg == 0)
            break;
        ACHN *pachn = &paseg->pachn[pactseg->iachn];
        ALO *palo = pactseg->palo;
        if (pea->eak == EAK_EvalPos)
        {
            VECTOR pos;
            VECTOR v;
            CHN *pchn = pachn->pchnPos;
            (*(VTCHN **)pchn)->pfnEval(pchn, palo, pea->tLocal, pasega->svtLocal, 0, &pos, &v);
            palo->pvtalo->pfnTranslateAloToPos(palo, &pos);
            palo->pvtalo->pfnSetAloVelocityVec(palo, &v);
        }
        else
        {
            VECTOR w;
            MATRIX3 mat;
            CHN *pchn = pachn->pchnRot;
            (*(VTCHN **)pchn)->pfnEval(pchn, palo, pea->tLocal, pasega->svtLocal, 0, &mat, &w);
            palo->pvtalo->pfnRotateAloToMat(palo, &mat);
            palo->pvtalo->pfnSetAloAngularVelocityVec(palo, &w);
        }
        break;
    }
    case EAK_JoyRumble:
        TriggerJoyRumbleRumk(&g_joy, (RUMK)pea->sh8.s2, (float)pea->sh8.s0 * (1.0f / 60.0f));
        break;
    case EAK_SendLoMessage:
    {
        LO *plo;
        if (pea->oid8 == -1)
            plo = pasega->plo;
        else
            plo = PloFindSwNearest(psw, pea->oid8, pasega->plo);
        if (plo == 0)
            break;
        void *apv[2];
        apv[1] = pea->pvC;
        apv[0] = pasega;
        plo->pvtlo->pfnSendLoMessage(plo, (MSGID)0x12, apv);
        break;
    }
    case EAK_SendAsegaMessage13:
    {
        ASEGMSG13 msg;
        msg.t = pea->tLocal;
        msg.n = pea->n8;
        msg.pasega = pasega;
        SendAsegaMessage(pasega, (MSGID)0x13, &msg);
        break;
    }
    case EAK_SpliceEvent:
    {
        void *apv[2];
        apv[0] = &pasega;
        apv[1] = &pea->n8;
        HandleLoSpliceEvent(pasega->paseg, 0xA, 2, apv);
        break;
    }
    case EAK_SendAsegaMessage15:
    {
        if (pasega->plo == 0)
            break;
        LO *plo = PloFindSwObject(psw, 0x104, pea->oid8, pasega->plo);
        if (plo == 0)
            break;
        ASEGMSG15 msg;
        msg.plo = plo;
        msg.t = pea->tLocal;
        msg.pasega = pasega;
        SendAsegaMessage(pasega, (MSGID)0x15, &msg);
        break;
    }
    case EAK_PoseCombo:
    {
        LO *plo = PloFindSwObject(psw, 0x104, pea->oid8, pasega->plo);
        if (plo == 0)
            return;
        SetAloPoseCombo((ALO *)plo, pea->oidC);
        break;
    }
    case EAK_ApplySm:
    {
        LO *ploCtx = pasega->plo ? pasega->plo : pasega->paseg;
        LO *plo1 = PloFindSwObject(psw, 0x104, (OID)pea->sh8.s0, ploCtx);
        if (plo1 == 0)
            break;
        LO *plo2 = PloFindSwObject(psw, 0x104, (OID)pea->sh8.s2, ploCtx);
        SMA *psma = PsmaFindSm((SM *)plo1, (ALO *)plo2);
        if (psma == 0)
            psma = PsmaApplySm((SM *)plo1, (ALO *)plo2, (OID)pea->shC.s0, 1);
        SetSmaGoal(psma, (OID)pea->shC.s0);
        break;
    }
    case EAK_RetractSm:
    {
        LO *ploCtx = pasega->plo;
        SMA *psma = 0;
        if (ploCtx == 0)
            ploCtx = pasega->paseg;
        LO *plo1 = PloFindSwNearest(psw, pea->oid8, ploCtx);
        if (plo1 != 0)
        {
            LO *plo2 = PloFindSwNearest(psw, pea->oidC, ploCtx);
            psma = PsmaFindSm((SM *)plo1, (ALO *)plo2);
        }
        if (psma != 0)
            RetractSma(psma);
        break;
    }
    case EAK_ProjectAlo:
    {
        // Builds a message (target object or position, optional up object, optional scale) and
        // hands it to the ALO's pfnProjectAloTransform. The meaning is a guess.
        PROJEV *pprojev = (PROJEV *)pea->pv8;
        LO *ploCtx = pasega->plo ? pasega->plo : paseg;
        LO *plo = PloFindSwObject(psw, 0x104, pprojev->oidAlo, ploCtx);
        if (plo == 0)
            break;
        PROJMSG msg;
        msg.grf = 0;
        if (pprojev->oidTarget != -1)
        {
            LO *ploT = PloFindSwObject(psw, 4, pprojev->oidTarget, ploCtx);
            if (ploT != 0)
            {
                if (FIsBasicDerivedFrom(ploT, CID_ALO))
                {
                    msg.pv4 = ploT;
                    msg.grf |= 1;
                }
                // 0x7E and 0x73 do not line up with the CID enum. Guesses: a point and a transform.
                else if (FIsBasicDerivedFrom(ploT, (CID)0x7E))
                {
                    msg.grf |= 4;
                    GetPntPos((PNT *)ploT, &msg.pos);
                }
                else if (FIsBasicDerivedFrom(ploT, (CID)0x73))
                {
                    msg.grf |= 4;
                    GetXfmPos((XFM *)ploT, &msg.pos);
                }
            }
        }
        if (msg.grf == 0)
        {
            if (plo->paloParent != 0 && FIsLoInWorld(plo->paloParent))
            {
                msg.grf |= 1;
                msg.pv4 = plo->paloParent;
            }
            else
            {
                msg.grf |= 4;
                GetXfmPos((XFM *)plo, &msg.pos);
            }
        }
        if (pprojev->oidUp != -1)
        {
            LO *ploUp = PloFindSwObject(psw, 4, pprojev->oidUp, ploCtx);
            if (ploUp != 0)
            {
                msg.pv38 = ploUp;
                msg.grf |= 0x20;
            }
        }
        if (pprojev->g != 1.0f)
        {
            msg.grf |= 0x18;
            msg.g30 = pprojev->g;
        }
        ((ALO *)plo)->pvtalo->pfnProjectAloTransform((ALO *)plo, &msg);
        break;
    }
    case EAK_Unk49:
        FUN_001ddb58(psw);
        break;
    case EAK_Unk50:
        FUN_001ddbb8(psw);
        break;
    case EAK_Mpeg:
        g_mpeg.FUN_0018f0e8(pea->pv8);
        break;
    case EAK_PlaceCredit:
        // Virtual call, slot at vtable offset 0x44 (guess: sets the credit's owner time).
        ((void (*)(CREDIT *, float *))D_00272E08.pvtcredit[0x44 / 4])(&D_00272E08, &pasega->tLocal);
        PlaceCredit(&D_00272E08, (float)pea->sh8.s0, (float)pea->sh8.s2, pea->shC.s0);
        break;
    case EAK_VacateCredit:
        ((void (*)(CREDIT *, float *))D_00272E08.pvtcredit[0x44 / 4])(&D_00272E08, 0);
        VacateCredit(&D_00272E08);
        break;
    case EAK_SetCreditLine:
        SetCreditLine(&D_00272E08, pea->sh8.s0, (char *)pea->pvC, (float)pea->sh8.s2 * (1.0f / 256.0f));
        break;
    case EAK_UiMode0:
    {
        UI *pui = &g_ui;
        ((UNALIGNED_INT *)&pui->unk6)->n = 0;
        SetUiUis(pui, (UIS)0);
        break;
    }
    case EAK_UiMode1:
        g_ui.unk6 = 1;
        SetUiUis(&g_ui, (UIS)1);
        break;
    case EAK_Darken:
        SetSwDarken(psw, pea->g8);
        break;
    case EAK_DarkenSmooth:
        SetSwDarkenSmooth(psw, pea->g8);
        break;
    case EAK_Jsg:
    {
        LO *plo = PloFindSwObject(psw, 0x104, pea->oid8, pasega->plo ? pasega->plo : paseg);
        if (plo != 0)
            ApplyJsg((JSG *)plo, g_pjt);
        break;
    }
    }
}
ALIGN_SECTION(rodata, 4);

INCLUDE_ASM("asm/nonmatchings/P2/asega", HandleAsegaEventsFF__FP5ASEGAP4ASEGPi);

INCLUDE_ASM("asm/nonmatchings/P2/asega", HandleAsegaEvents__FP5ASEGAP4ASEGPi);

void RemoveAsega(ASEGA *pasega)
{
    RemoveDlEntry(&g_psw->dlAsegaPending, pasega);
    FreeSlotheapPv(&g_psw->slotheapAsega, pasega);
}

INCLUDE_ASM("asm/nonmatchings/P2/asega", RetractAsega__FP5ASEGA);

void FUN_0012e928(ASEGA *pasega, OID oid, int grfra)
{
    ACTSEG *pactseg = PactsegFindAsega(pasega, oid);
    if (pactseg != 0)
    {
        pactseg->pvtact->pfnRetractAct(pactseg, grfra);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/asega", UFromEaErrorFunc__FP2EAf);

INCLUDE_ASM("asm/nonmatchings/P2/asega", FWrapAsegaTime__FP5ASEGAPfT1);

INCLUDE_ASM("asm/nonmatchings/P2/asega", UpdateAsega__FP5ASEGAf);

INCLUDE_ASM("asm/nonmatchings/P2/asega", SeekAsega__FP5ASEGA4SEEKff);

void SnapAsega(ASEGA *pasega, int fForce)
{
    VECTOR vec; // unused, but needed to match the original stack frame
    for (ACTSEG *pactseg = (ACTSEG *)pasega->dlActseg.head; pactseg != 0; pactseg = (ACTSEG *)pactseg->dleAsega.next)
    {
        SnapAct(pactseg, fForce);
    }
}

void AdaptAsega(ASEGA *pasega)
{
    VECTOR vec; // unused, but needed to match the original stack frame
    for (ACTSEG *pactseg = (ACTSEG *)pasega->dlActseg.head; pactseg != 0; pactseg = (ACTSEG *)pactseg->dleAsega.next)
    {
        AdaptAct(pactseg);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/asega", FindChnClosestPointLocal__FP3CHNP3ALOP6VECTORfffPfT2T2);

void SetAsegaSpeed(ASEGA *pasega, float svt)
{
    float svtScaled = svt * pasega->svtMaster;
    pasega->svtLocal = svtScaled * pasega->paseg->svtMasterSuck;
}

void SetAsegaMasterSpeed(ASEGA *pasega, float svtMaster)
{
    float svtScale = pasega->svtMaster * pasega->paseg->svtMasterSuck;
    float svt = pasega->svtLocal;
    if (svtScale != 0.0f)
    {
        svt = svt / svtScale;
    }
    pasega->svtMaster = svtMaster;
    SetAsegaSpeed(pasega, svt);
}

void SetAsegaPriority(ASEGA *pasega, int nPriority)
{
    VECTOR vec; // unused, but needed to match the original 64-byte stack frame
    for (ACTSEG *pactseg = (ACTSEG *)pasega->dlActseg.head; pactseg != 0; pactseg = (ACTSEG *)pactseg->dleAsega.next)
    {
        pactseg->nPriority = nPriority;
        ResortAloActList(pactseg->palo);
    }
}

void SendAsegaMessage(ASEGA *pasega, MSGID msgid, void *pv)
{
    LO *plo = pasega->plo;
    if (plo != 0)
    {
        plo->pvtlo->pfnSendLoMessage(plo, msgid, pv);
    }
    MQ *pmq = pasega->pmqFirst;
    while (pmq != 0)
    {
        MQ *pmqNext = pmq->pmqNext;
        pmq->pfnmq(pmq->pvContext, msgid, pv);
        pmq = pmqNext;
    }
}

void SubscribeAsegaStruct(ASEGA *pasega, PFNMQ pfnmq, void *pvContext)
{
    SubscribeSwPpmqStruct(pasega->paseg->psw, &pasega->pmqFirst, pfnmq, pvContext);
}

void SubscribeAsegaObject(ASEGA *pasega, LO *ploTarget)
{
    SubscribeSwPpmqStruct(pasega->paseg->psw, &pasega->pmqFirst, (PFNMQ)ploTarget->pvtlo->pfnHandleLoMessage, ploTarget);
}
