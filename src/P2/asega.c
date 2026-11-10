#include <asega.h>
#include <sw.h>
#include <actseg.h>

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

INCLUDE_ASM("asm/nonmatchings/P2/asega", HandleAsegaEvent__FP5ASEGAP2EAPi);

#ifdef SKIP_ASM
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
#include <actseg.h>
#include <rumble.h>

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
void TriggerJoyRumble(JOY *pjoy, RUMK rumk, float dt);
void PlaceCredit(CREDIT *pcredit, float x, float y, int i);
void VacateCredit(CREDIT *pcredit);
void SetCreditLine(CREDIT *pcredit, int iLine, char *pchz, float u);
extern CREDIT D_00272E08;
extern TIMER g_unkblot9;

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
 * @todo Work in progress, not matching yet.
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
    case 42:
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
    case 44:
        PreloadVag1(pea->n8);
        break;
    case 43:
        StopVag();
        break;
    case 0:
    {
        int i;
        if (((SNDEV *)pea->pv8)->csfx < 2) i = 0; else
        {
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
    case 1:
        if (pasega->pamb != 0)
            StopSound(pasega->pamb, 0);
        break;
    case 2:
        ContinueMusic();
        break;
    case 3:
        PauseMusic();
        break;
    case 11:
    {
        float t = pea->tLocal;
        float tMax = paseg->tMax;
        float tMin = 0.0f;
        float tc;
        if (t < tMin) tc = tMin; else {tc = t; if (tMax < t) tc = tMax;}
        pasega->tLocal = tc;
        pasega->svtLocal = 0.0f;
        break;
    }
    case 4:
    case 7:
        pasega->tLocal = pea->g8;
        SetAsegaSpeed(pasega, pea->gC);
        UpdateAsegaIeaCur(pasega);
        AdaptAsega(pasega);
        break;
    case 5:
        SetAsegaSpeed(pasega, pea->g8);
        break;
    case 6:
    {
        LO *plo = PloFindSwObject(psw, 0x104, pea->oid8, pasega->plo ? pasega->plo : paseg);
        if (plo != 0)
            TriggerDialog((DIALOG *)plo);
        break;
    }
    case 8:
        RetractAsega(pasega);
        *pfRetracted = 1;
        break;
    case 9:
    case 10:
    {
        int fIn = (pea->eak == 9);
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
    case 16:
    {
        LO *plo = PloFindSwObject(psw, 0x104, pea->oid8, pasega->plo ? pasega->plo : pasega->paseg);
        if (plo == 0)
            return;
        CT ctForce = (CT)pea->shC.s0;
        if (ctForce < 0)
            ctForce = STRUCT_OFFSET(plo, 0x450, CT);
        CT ctTorque = (CT)pea->shC.s2;
        if (ctTorque < 0)
            ctTorque = STRUCT_OFFSET(plo, 0x470, CT);
        SetSoConstraints((SO *)plo, ctForce, 0, ctTorque, 0);
        break;
    }
    case 12:
    case 13:
    {
        int fOn = pea->eak == 12;
        if (fReverse) fOn = !fOn;
        LO *plo = PloFindSwObject(psw, 4, pea->oid8, pasega->paseg);
        if (plo == 0)
            return;
        if (fOn)
            EnableCamera((CAMERA *)plo);
        else
            DisableCamera((CAMERA *)plo);
        break;
    }
    case 14:
    case 15:
        {
            int f = (pea->eak == 14);
            f ^= fReverse;
            SetAsegaHandsOff(pasega, f);
        }
        break;
    case 19:
    case 20:
    {
        int fPuppet = (pea->eak == 19);
        fPuppet ^= fReverse;
        SetJtPuppet(g_pjt, (ASEGA *)fPuppet);
        if (!fPuppet)
            return;
        if (pea->nC != 0)
            SnapAsega(pasega, 1);
        break;
    }
    case 17:
    case 18:
    {
        ACTSEG *pactseg = PactsegFindAsega(pasega, pea->oid8);
        if (pactseg == 0)
            break;
        if ((pea->eak != 17) != (fReverse == 0))
        {
            STRUCT_OFFSET(pactseg, 0x11, char) = 5;
            STRUCT_OFFSET(pactseg, 0x10, char) = 5;
        }
        else
        {
            CalculateActDefaultAck(pactseg);
        }
        break;
    }
    case 21:
    case 22:
    case 23:
    case 24:
    {
        OID oid;
        if (pea->eak == 21 || pea->eak == 23)
            oid = *(OID *)pea->pv8;
        else
            oid = pea->oid8;
        ACTSEG *pactseg = PactsegFindAsega(pasega, oid);
        if (pactseg == 0)
            break;
        switch (pea->eak)
        {
        case 21:
            pasega->peaErrorA = pea;
            pasega->pactsegError = pactseg;
            break;
        case 22:
            pasega->peaErrorA = 0;
            if (pasega->peaErrorB == 0)
                pasega->pactsegError = 0;
            break;
        case 23:
            pasega->peaErrorB = pea;
            pasega->pactsegError = pactseg;
            break;
        case 24:
            pasega->peaErrorB = 0;
            if (pasega->peaErrorA == 0)
                pasega->pactsegError = 0;
            break;
        }
        break;
    }
    case 25:
        ActivateWipe(&g_wipe, (TRANS *)pea->pvC, (WIPEK)pea->sh8.s0);
        break;
    case 26:
        SetWipeButtonTrans(&g_wipe, (TRANS *)pea->pvC, (WIPEK)pea->sh8.s0);
        break;
    case 27:
    {
        if (g_pjt != 0 && STRUCT_OFFSET(g_pjt, 0x2220, int) == 9 && STRUCT_OFFSET(g_pjt, 0x2228, int) == 0x1C
            && (void *)g_plsCur == (void *)g_pwsCur)
            return;
        TriggerDefaultExit(pea->n8, (WIPEK)pea->nC);
        break;
    }
    case 33:
        SetTimer(&g_unkblot9, pea->g8);
        StartTimer(&g_unkblot9);
        break;
    case 34:
        StopTimer(&g_unkblot9);
        break;
    case 28:
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
    case 29:
    case 30:
    case 31:
    case 32:
    {
        ACTSEG *pactseg = PactsegFindAsega(pasega, pea->oid8);
        int fCall = 0;
        if (pactseg != 0)
        {
            ACHN *pachn = &paseg->pachn[pactseg->iachn];
            switch (pea->eak)
            {
            case 29:
                if (pachn->punkPos != 0)
                {
                    uchar c = STRUCT_OFFSET(pactseg, 0x12, uchar);
                    STRUCT_OFFSET(pactseg, 0x12, uchar) = 2;
                    fCall = (uchar)(c + 1) < 2;
                }
                break;
            case 30:
                if (pachn->punkPos != 0)
                {
                    char c = STRUCT_OFFSET(pactseg, 0x12, char);
                    STRUCT_OFFSET(pactseg, 0x12, char) = -1;
                    fCall = c != -1;
                }
                break;
            case 31:
                if (pachn->punkRot != 0)
                {
                    uchar c = STRUCT_OFFSET(pactseg, 0x13, uchar);
                    STRUCT_OFFSET(pactseg, 0x13, uchar) = 2;
                    fCall = (uchar)(c + 1) < 2;
                }
                break;
            case 32:
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
    case 35:
    case 36:
    {
        ACTSEG *pactseg = PactsegFindAsega(pasega, pea->oid8);
        if (pactseg == 0)
            break;
        ACHN *pachn = &paseg->pachn[pactseg->iachn];
        ALO *palo = pactseg->palo;
        if (pea->eak == 35)
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
    case 37:
        TriggerJoyRumble(&g_joy, (RUMK)pea->sh8.s2, (float)pea->sh8.s0 * (1.0f / 60.0f));
        break;
    case 38:
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
    case 39:
    {
        ASEGMSG13 msg;
        msg.n = pea->n8;
        msg.t = pea->tLocal;
        msg.pasega = pasega;
        SendAsegaMessage(pasega, (MSGID)0x13, &msg);
        break;
    }
    case 40:
    {
        void *apv[2];
        apv[0] = &pasega;
        apv[1] = &pea->n8;
        HandleLoSpliceEvent(pasega->paseg, 0xA, 2, apv);
        break;
    }
    case 41:
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
    case 45:
    {
        LO *plo = PloFindSwObject(psw, 0x104, pea->oid8, pasega->plo);
        if (plo == 0)
            return;
        SetAloPoseCombo((ALO *)plo, pea->oidC);
        break;
    }
    case 46:
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
    case 47:
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
    case 48:
    {
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
    case 49:
        FUN_001ddb58(psw);
        break;
    case 50:
        FUN_001ddbb8(psw);
        break;
    case 51:
        g_mpeg.FUN_0018f0e8(pea->pv8);
        break;
    case 52:
        ((void (*)(CREDIT *, float *))D_00272E08.pvtcredit[0x44 / 4])(&D_00272E08, &pasega->tLocal);
        PlaceCredit(&D_00272E08, (float)pea->sh8.s0, (float)pea->sh8.s2, pea->shC.s0);
        break;
    case 53:
        ((void (*)(CREDIT *, float *))D_00272E08.pvtcredit[0x44 / 4])(&D_00272E08, 0);
        VacateCredit(&D_00272E08);
        break;
    case 54:
        SetCreditLine(&D_00272E08, pea->sh8.s0, (char *)pea->pvC, (float)pea->sh8.s2 * (1.0f / 256.0f));
        break;
    case 55:
        g_ui.unk6 = 0;
        SetUiUis(&g_ui, (UIS)0);
        break;
    case 56:
        g_ui.unk6 = 1;
        SetUiUis(&g_ui, (UIS)1);
        break;
    case 57:
        SetSwDarken(psw, pea->g8);
        break;
    case 58:
        SetSwDarkenSmooth(psw, pea->g8);
        break;
    case 59:
    {
        LO *plo = PloFindSwObject(psw, 0x104, pea->oid8, pasega->plo ? pasega->plo : paseg);
        if (plo != 0)
            ApplyJsg((JSG *)plo, g_pjt);
        break;
    }
    }
}
#endif

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
