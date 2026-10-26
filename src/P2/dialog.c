#include <dialog.h>
#include <speaker.h>
#include <asega.h>
#include <aseg.h>
#include <mpeg.h>
#include <screen.h>
#include <wipe.h>
#include <sound.h>
#include <ui.h>
#include <memory.h>
#include <bis.h>
#include <clock.h>
#include <cm.h>
#include <cplcy.h>
#include <binoc.h>
#include <tv.h>
#include <find.h>
#include <sw.h>
#include <po.h>
#include <joy.h>
#include <jt.h>
#include <sce/memset.h>

struct CALL : public BLOT
{
    /* 0x260 */ DIALOG *pdialog;
};

extern CALL g_call;
extern int s_cpdialogCalling;
extern TV g_tvLeft;
extern TV g_tvRight;
extern GRFBTN s_mpdpkgrfbtn[];
extern char s_mpdpkchPause[];

void InitDialog(DIALOG *pdialog)
{
    InitAlo(pdialog);
    STRUCT_OFFSET(pdialog, 0x2c8, ulong) = STRUCT_OFFSET(pdialog, 0x2c8, ulong) | 0x100000000;
    pdialog->oidPntAnchor = OID_Nil;
    pdialog->oidDialog = OID_Nil;
}

void LoadDialogFromBrx(DIALOG *pdialog, CBinaryInputStream *pbis)
{
    LoadAloFromBrx(pdialog, pbis);
    LoadDialogEventsFromBrx(pdialog, pbis, &pdialog->cde, &pdialog->ade);
}

void LoadDialogEventsFromBrx(DIALOG *pdialog, CBinaryInputStream *pbis, int *pcde, DE **pade)
{
    int ide;
    *pcde = pbis->S8Read();
    *pade = (DE *)PvAllocSwClearImpl(*pcde * sizeof(DE));
    for (ide = 0; ide < *pcde; ide++)
    {
        DE *pde = &(*pade)[ide];
        pde->dek = (DEK)pbis->S8Read();
        switch (pde->dek)
        {
        case DEK_PreloadVag:
        case DEK_ShowMovie:
            pbis->Unknown2((void **)&pde->pchz);
            break;

        case DEK_SpeakerLeft:
        case DEK_SpeakerRight:
            pde->speaker.oid = (OID)pbis->S16Read();
            pde->speaker.oidReplace = (OID)pbis->S16Read();
            break;

        case DEK_Talk:
            pde->talk.uZoom = pbis->F32Read();
            pde->talk.dtPause = pbis->F32Read();
            pde->talk.fUser = pbis->U8Read();
            pde->talk.dpk = (DPK)pbis->U8Read();
            pde->talk.oidSpeaker = (OID)pbis->S16Read();
            pde->talk.oidLipsAseg = (OID)pbis->S16Read();
            pde->talk.oidFocus = (OID)pbis->S16Read();
            pde->talk.oidPntAnchor = (OID)pbis->S16Read();
            pbis->ReadStringSw(&pde->talk.pchzText);
            break;

        case DEK_CallSplice:
            pde->oidLabel = (OID)pbis->S16Read();
            break;

        case DEK_ShowLetterbox:
        case DEK_HideLetterbox:
        default:
            break;
        }
    }
}

void PostDialogLoad(DIALOG *pdialog)
{
    PostAloLoad(pdialog);
    if (pdialog->oidDialog == OID_Nil)
    {
        pdialog->oidDialog = pdialog->oid;
    }
    pdialog->pfPlayed = PfLookupDialog(g_plsCur, pdialog->oidDialog);
    if (pdialog->pfPlayed == NULL)
    {
        pdialog->pfPlayed = &pdialog->fPlayed;
    }
}

void SetDialogInstruct(DIALOG *pdialog)
{
    pdialog->dialogk = DIALOGK_Instruct;
}

void SetDialogConfront(DIALOG *pdialog)
{
    pdialog->dialogk = DIALOGK_Confront;
}

void GetDialogPlayed(DIALOG *pdialog, int *pfPlayed)
{
    *pfPlayed = *pdialog->pfPlayed;
}

void SetDialogPlayed(DIALOG *pdialog, int fPlayed)
{
    *pdialog->pfPlayed = fPlayed;
}

void SetDialogDialogs(DIALOG *pdialog, DIALOGS dialogs)
{
    if (dialogs == pdialog->dialogs)
    {
        return;
    }

    switch (pdialog->dialogs)
    {
    case DIALOGS_UnableToCall:
        if (g_call.pdialog == pdialog)
        {
            g_call.pdialog = NULL;
        }
        break;

    case DIALOGS_Triggered:
        if (pdialog->dialogk != DIALOGK_Instruct)
        {
            s_cpdialogCalling--;
        }
        break;

    case DIALOGS_Playing:
        *pdialog->pfPlayed = 1;
        StopVag();
        HandleLoSpliceEvent(pdialog, 0x15, 0, NULL);
        if (pdialog->dialogk == DIALOGK_Confront)
        {
            RevokeCmPolicy(g_pcm, 0xf, CPP_LookAround, &g_pcm->cplook, NULL, NULL);
            DecrementSwHandsOff(g_psw);
        }
        LookkPopCplook(&g_pcm->cplook);
        if ((pdialog->dp.grfdp & FDP_Lipsync) && pdialog->dp.pasegaLipsync != NULL)
        {
            RetractAsega(pdialog->dp.pasegaLipsync);
        }
        if (pdialog->dialogk == DIALOGK_Confront)
        {
            if (pdialog->fDuckAudio)
            {
                SetMvgkRvol(9, MVGK_Effects, 1.0f);
                SetMvgkRvol(9, MVGK_Music, 1.0f);
            }
        }
        break;

    case DIALOGS_Calling:
    {
        struct Unaligned
        {
            int x;
        } __attribute__((packed));

        BLOT *pbinoc = &g_binoc;
        STRUCT_OFFSET(pbinoc, 0x324, Unaligned).x = 0;
        open_close_binoc(pbinoc, BINOCS_None);
        break;
    }

    default:
        break;
    }

    switch (dialogs)
    {
    case DIALOGS_UnableToCall:
        if (g_call.pdialog != NULL)
        {
            SetDialogDialogs(g_call.pdialog, DIALOGS_Enabled);
        }
        g_call.pdialog = pdialog;
        break;

    case DIALOGS_Triggered:
        if (pdialog->dialogk != DIALOGK_Instruct)
        {
            s_cpdialogCalling++;
        }
        break;

    case DIALOGS_Playing:
        pdialog->ideCur = -1;
        pdialog->dp.grfdp = GRFDP_None;
        if (pdialog->dialogk == DIALOGK_Confront)
        {
            PushCplookLookk(&g_pcm->cplook, LOOKK_Confront);
            SetCmPolicy(g_pcm, CPP_LookAround, &g_pcm->cplook, NULL, NULL);
            IncrementSwHandsOff(g_psw);
            SetBinocLookat(&g_binoc, NULL);
            if (pdialog->fDuckAudio)
            {
                SetMvgkRvol(9, MVGK_Effects, 0.6f);
                SetMvgkRvol(9, MVGK_Music, 0.6f);
            }
        }
        else
        {
            PushCplookLookk(&g_pcm->cplook, LOOKK_Dialog);
            if (pdialog->dialogk == DIALOGK_Binoc)
            {
                if (pdialog->oidPntAnchor != OID_Nil)
                {
                    g_pcm->cplook.ppntAnchor = (PNT *)PloFindSwNearest(pdialog->psw, pdialog->oidPntAnchor, NULL);
                }
                else
                {
                    g_pcm->cplook.ppntAnchor = NULL;
                }
            }
        }
        break;

    case DIALOGS_Calling:
        SetTvSpeaker(&g_tvLeft, NULL);
        SetTvReplace(&g_tvLeft, NULL);
        SetTvSpeaker(&g_tvRight, NULL);
        SetTvReplace(&g_tvRight, NULL);
        break;

    default:
        break;
    }

    pdialog->dialogs = dialogs;
    pdialog->tDialogs = g_clock.t;
}

void UpdateDialog(DIALOG *pdialog, float dt)
{
    UpdateAlo(pdialog, dt);

    NOTE *pnote = &g_note;
    if (STRUCT_OFFSET(pnote, 0x260, int) >= 2 ||
        STRUCT_OFFSET(pnote, 0x26c, int) != 0 ||
        SetVagUnpaused() ||
        g_wipe.wipes == WIPES_WipingOut)
    {
        switch (pdialog->dialogs)
        {
        case DIALOGS_Triggered:
        case DIALOGS_UnableToCall:
        case DIALOGS_Pending:
            SetDialogDialogs(pdialog, DIALOGS_Enabled);
            return;

        default:
            break;
        }
    }

    DIAPI diapi;
    memset(&diapi, 0, sizeof(diapi));

    PO *ppo = PpoCur();

    if (FActiveCplcy(&STRUCT_OFFSET(g_pcm, 0x454, CPLCY)))
    {
        diapi.fPlayable = 0;
        diapi.fCallable = 0;
    }
    else
    {
        if (ppo != NULL)
        {
            ((void (*)(PO *, DIALOG *, DIAPI *))STRUCT_OFFSET(ppo->pvtbasic, 0x154, void *))(ppo, pdialog, &diapi);
        }
        else
        {
            diapi.fPlayable = 1;
        }
    }

    DIALOGS dialogsNext = pdialog->dialogs;

    switch (pdialog->dialogs)
    {
    case DIALOGS_Enabled:
        if (pdialog->fDefault)
        {
            if (g_wipe.wipes == WIPES_Idle && diapi.fPlayable)
            {
                pdialog->fDefault = 0;
                TriggerDialog(pdialog);
                dialogsNext = pdialog->dialogs;
            }
        }
        break;

    case DIALOGS_UnableToCall:
        if (!diapi.fCallable)
        {
            dialogsNext = DIALOGS_Pending;
            break;
        }
        if (g_clock.t - pdialog->tDialogs >= 5.0f)
        {
            dialogsNext = DIALOGS_Enabled;
        }
        break;

    case DIALOGS_Pending:
        if (diapi.fCallable)
        {
            dialogsNext = DIALOGS_UnableToCall;
            break;
        }
        if (g_clock.t - pdialog->tDialogs >= 5.0f)
        {
            dialogsNext = DIALOGS_Enabled;
        }
        break;

    case DIALOGS_Triggered:
        if (diapi.fPlayable)
        {
            if (g_pdialogPlaying == NULL)
            {
                FUN_00151860(pdialog, (BLOT *)ppo);
                dialogsNext = pdialog->dialogs;
                break;
            }

            if (g_pdialogPlaying != pdialog)
            {
                if (!g_pdialogPlaying->fCrucial && g_pdialogPlaying->dialogs == DIALOGS_Playing)
                {
                    FUN_001516c0(g_pdialogPlaying);
                }
            }
        }
        else
        {
            if (g_clock.t - pdialog->tDialogs >= 5.0f)
            {
                dialogsNext = DIALOGS_Enabled;
            }
        }
        break;

    case DIALOGS_Playing:
        if (pdialog->dialogk != DIALOGK_Confront)
        {
            if (pdialog->ideCur >= pdialog->cde || g_wipe.wipes == WIPES_WipingOut)
            {
                PopUiActiveBlot(&g_ui);
                dialogsNext = pdialog->dialogs;
            }
        }
        break;

    case DIALOGS_Calling:
        if (g_tvLeft.blots == BLOTS_Hidden && g_tvRight.blots == BLOTS_Hidden)
        {
            dialogsNext = DIALOGS_Enabled;
        }
        break;

    case DIALOGS_Disabled:
        break;
    }

    SetDialogDialogs(pdialog, dialogsNext);

    switch (pdialog->dialogs)
    {
    case DIALOGS_Playing:
        HandleDialogEvents(pdialog);
        break;

    case DIALOGS_Enabled:
    case DIALOGS_Triggered:
    case DIALOGS_Disabled:
    case DIALOGS_Calling:
    case DIALOGS_UnableToCall:
    case DIALOGS_Pending:
    default:
        break;
    }
}

void HandleDialogEvent(DIALOG *pdialog, DE *pde)
{
    switch (pde->dek)
    {
    case DEK_PreloadVag:
        PreloadVag1(pde->pchz);
        pdialog->dp.grfdp |= FDP_PreloadSound;
        break;

    case DEK_SpeakerLeft:
    case DEK_SpeakerRight:
    {
        SPEAKER *pspeaker;
        if (pde->speaker.oid != OID_Nil)
        {
            pspeaker = (SPEAKER *)PloFindSwObject(pdialog->psw, (GRFFSO)0x104, pde->speaker.oid, pdialog->paloRoot != NULL ? pdialog->paloRoot : (ALO *)pdialog);
        }
        else
        {
            pspeaker = NULL;
        }

        ALO *paloReplace;
        if (pde->speaker.oidReplace != OID_Nil)
        {
            paloReplace = (ALO *)PloFindSwObject(pdialog->psw, (GRFFSO)0x104, pde->speaker.oidReplace, pdialog->paloRoot != NULL ? pdialog->paloRoot : (ALO *)pdialog);
        }
        else
        {
            paloReplace = NULL;
        }

        if (pspeaker != NULL && pspeaker->psmaIdle != NULL)
        {
            SetSmaGoal(pspeaker->psmaIdle, (OID)0x34c);
        }

        switch (pde->dek)
        {
        case DEK_SpeakerLeft:
            SetTvSpeaker(&g_tvLeft, pspeaker);
            SetTvReplace(&g_tvLeft, paloReplace);
            pdialog->dp.pspeakerLeft = pspeaker;
            if (pspeaker != NULL)
            {
                pdialog->dp.grfdp |= FDP_SpeakerLeft;
            }
            break;

        case DEK_SpeakerRight:
            SetTvSpeaker(&g_tvRight, pspeaker);
            SetTvReplace(&g_tvRight, paloReplace);
            pdialog->dp.pspeakerRight = pspeaker;
            if (pspeaker != NULL)
            {
                pdialog->dp.grfdp |= FDP_SpeakerRight;
            }
            break;
        }
        break;
    }

    case DEK_Talk:
    {
        SPEAKER *pspeaker;
        if (pdialog->dp.pspeakerLeft != NULL && FMatchesLoName(pdialog->dp.pspeakerLeft, pde->talk.oidSpeaker))
        {
            pspeaker = pdialog->dp.pspeakerLeft;
            SetTvTvs(&g_tvLeft, TVS_Talk);
            SetTvTvs(&g_tvRight, TVS_Listen);
        }
        else if (pdialog->dp.pspeakerRight != NULL && FMatchesLoName(pdialog->dp.pspeakerRight, pde->talk.oidSpeaker))
        {
            pspeaker = pdialog->dp.pspeakerRight;
            SetTvTvs(&g_tvRight, TVS_Talk);
            SetTvTvs(&g_tvLeft, TVS_Listen);
        }
        else
        {
            pspeaker = NULL;
        }

        ASEG *paseg = NULL;
        if (pde->talk.oidLipsAseg != OID_Nil)
        {
            paseg = (ASEG *)PloFindSwObject(pdialog->psw, (GRFFSO)2, pde->talk.oidLipsAseg, pdialog);
            pdialog->dp.grfdp |= FDP_Lipsync;
        }
        else if (pspeaker != NULL)
        {
            paseg = (ASEG *)PloFindSwObject(pdialog->psw, (GRFFSO)1, (OID)0x54a, pspeaker);
        }

        if (paseg != NULL)
        {
            ApplyAseg(paseg, pspeaker, 0.0f, 1.0f, 1, &pdialog->dp.pasegaLipsync);
            SubscribeAsegaObject(pdialog->dp.pasegaLipsync, pdialog);
        }

        if (pde->talk.pchzText != NULL && pde->talk.pchzText[0] != '\0')
        {
            g_binoc.pvtbinoc->pfnSetBinocAchzDraw(&g_binoc, pde->talk.pchzText);
            if (pspeaker != NULL)
            {
                g_binoc.rgbaText = pspeaker->rgbaText;
            }
            else
            {
                *(int *)&g_binoc.rgbaText = 0x80808080;
            }

            float dt;
            if (pdialog->dp.pasegaLipsync != NULL && pde->talk.oidLipsAseg != OID_Nil)
            {
                dt = pdialog->dp.pasegaLipsync->paseg->tMax;
            }
            else
            {
                dt = pde->talk.dtPause;
            }

            if (0.0f < dt)
            {
                g_binoc.svch = (float)(strlen(pde->talk.pchzText) + 10) / dt;
            }
            else
            {
                g_binoc.svch = 15.0f;
            }
            pdialog->dp.grfdp |= FDP_Text;
        }

        if (0.0f <= pde->talk.uZoom)
        {
            SetBinocZoom(&g_binoc, pde->talk.uZoom + 1.0f);
            pdialog->dp.grfdp |= FDP_Zoom;
        }

        if (0.0f <= pde->talk.dtPause)
        {
            pdialog->dp.grfdp |= FDP_Time;
            pdialog->dp.tPauseMin = g_clock.t + pde->talk.dtPause;
        }

        if (pde->talk.oidFocus != OID_Nil)
        {
            ALO *paloFocus = (ALO *)PloFindSwObject(pdialog->psw, (GRFFSO)0x104, pde->talk.oidFocus, pdialog->paloRoot != NULL ? pdialog->paloRoot : (ALO *)pdialog);
            SetBinocLookat(&g_binoc, paloFocus);
        }

        if (pde->talk.oidPntAnchor != OID_Nil)
        {
            g_pcm->cplook.ppntAnchor = (PNT *)PloFindSwNearest(pdialog->psw, pde->talk.oidPntAnchor, NULL);
        }
        else if (pdialog->oidPntAnchor != OID_Nil)
        {
            g_pcm->cplook.ppntAnchor = (PNT *)PloFindSwNearest(pdialog->psw, pdialog->oidPntAnchor, NULL);
        }
        else
        {
            g_pcm->cplook.ppntAnchor = NULL;
        }

        if (pde->talk.fUser != 0)
        {
            pdialog->dp.grfdp |= FDP_User;
            pdialog->dp.dpk = pde->talk.dpk;
        }
        pdialog->dp.grfdp |= FDP_Sound;
        break;
    }

    case DEK_CallSplice:
    {
        void *pvArg = &pde->oidLabel;
        HandleLoSpliceEvent(pdialog, 0x10, 1, &pvArg);
        break;
    }

    case DEK_ShowLetterbox:
        FUN_001ddb58(pdialog->psw);
        break;

    case DEK_HideLetterbox:
        FUN_001ddbb8(pdialog->psw);
        break;

    case DEK_ShowMovie:
        g_mpeg.FUN_0018f0e8(pde->pchz);
        break;

    default:
        break;
    }
}

void HandleDialogMessage(DIALOG *pdialog, MSGID msgid, void *pv)
{
    HandleAloMessage(pdialog, msgid, pv);
    if (msgid == MSGID_asega_retracted && (ASEGA *)pv == pdialog->dp.pasegaLipsync)
    {
        pdialog->dp.pasegaLipsync = NULL;
    }
}

int FPauseDialog(DIALOG *pdialog)
{
    GRFDP grfdp = pdialog->dp.grfdp;

    if (grfdp & FDP_SpeakerLeft)
    {
        DE *pdeNext = (pdialog->ideCur < pdialog->cde - 1) ? &pdialog->ade[pdialog->ideCur + 1] : NULL;
        if (pdeNext != NULL && pdeNext->dek == DEK_SpeakerRight)
        {
            if (grfdp == FDP_SpeakerLeft)
            {
                return 0;
            }
        }
        if (g_tvLeft.pspeaker == pdialog->dp.pspeakerLeft && g_tvLeft.tvgs == TVGS_Open)
        {
            grfdp &= ~FDP_SpeakerLeft;
        }
    }

    if (grfdp & FDP_SpeakerRight)
    {
        DE *pdeNext = (pdialog->ideCur < pdialog->cde - 1) ? &pdialog->ade[pdialog->ideCur + 1] : NULL;
        if (pdeNext != NULL && pdeNext->dek == DEK_SpeakerLeft)
        {
            if (grfdp == FDP_SpeakerRight)
            {
                return 0;
            }
        }
        if (g_tvRight.pspeaker == pdialog->dp.pspeakerRight && g_tvRight.tvgs == TVGS_Open)
        {
            grfdp &= ~FDP_SpeakerRight;
        }
    }

    if (grfdp & FDP_PreloadSound)
    {
        if (!FPauseForVag())
        {
            grfdp &= ~FDP_PreloadSound;
        }
    }

    if (grfdp & FDP_Sound)
    {
        if (!FVagPlaying())
        {
            grfdp &= ~FDP_Sound;
        }
    }

    if (grfdp & FDP_Lipsync)
    {
        if (pdialog->dp.pasegaLipsync == NULL)
        {
            grfdp &= ~FDP_Lipsync;
        }
    }

    if (grfdp & FDP_Text)
    {
        if (FDoneBinocAchz(&g_binoc))
        {
            grfdp &= ~FDP_Text;
        }
    }

    if (grfdp & FDP_Zoom)
    {
        if (g_pcm->cplook.uZoom == g_binoc.uZoom)
        {
            grfdp &= ~FDP_Zoom;
        }
    }

    if (grfdp & FDP_Time)
    {
        if (g_clock.t >= pdialog->dp.tPauseMin)
        {
            grfdp &= ~FDP_Time;
        }
    }

    g_binoc.chPause = 0;

    if (grfdp == FDP_User)
    {
        JOY *pjoy = (g_grfjoyt & 4) ? &g_joy : &g_joyZero;
        DPK dpk = pdialog->dp.dpk;
        int fPassed = 0;

        switch (dpk)
        {
        case DPK_JoyLeft:
            if (pjoy->uDeflect > 0.8f)
            {
                fPassed = 1;
            }
            break;

        case DPK_JoyRight:
            if (pjoy->uDeflect2 > 0.8f)
            {
                fPassed = 1;
            }
            break;

        case DPK_JoyLeftX:
            if (fabsf(pjoy->x) > 0.8f)
            {
                fPassed = 1;
            }
            break;

        case DPK_JoyLeftY:
            if (fabsf(pjoy->y) > 0.8f)
            {
                fPassed = 1;
            }
            break;

        case DPK_DoubleJump:
            if (g_pjt != NULL && g_pjt->jts == JTS_Jump)
            {
                fPassed = g_pjt->jtbs == JTBS_Jump_Boost;
            }
            break;

        case DPK_VaultOpen:
            if (g_plsCur->fls & 4)
            {
                fPassed = 1;
            }
            break;

        default:
            fPassed = (pjoy->grfbtnPressed & s_mpdpkgrfbtn[dpk]) != 0;
            break;
        }

        if (fPassed)
        {
            grfdp = GRFDP_None;
        }
        else
        {
            g_binoc.chPause = s_mpdpkchPause[dpk];
        }
    }

    pdialog->dp.grfdp = grfdp;
    return grfdp != GRFDP_None;
}

void FUN_001516c0(DIALOG *pdialog)
{
    if (pdialog->dialogs == DIALOGS_Calling)
    {
        return;
    }

    if (pdialog->ideCur < pdialog->cde)
    {
        while (++pdialog->ideCur < pdialog->cde)
        {
            DE *pde = &pdialog->ade[pdialog->ideCur];
            switch (pde->dek)
            {
            case DEK_CallSplice:
            {
                void *pvArg = &pde->oidLabel;
                HandleLoSpliceEvent(pdialog, 0x10, 1, &pvArg);
                break;
            }

            case DEK_ShowLetterbox:
                FUN_001ddb58(pdialog->psw);
                break;

            case DEK_HideLetterbox:
                FUN_001ddbb8(pdialog->psw);
                break;

            case DEK_PreloadVag:
            case DEK_SpeakerLeft:
            case DEK_SpeakerRight:
            case DEK_Talk:
            case DEK_ShowMovie:
            default:
                break;
            }
        }
    }

    if (pdialog->dialogk == DIALOGK_Confront)
    {
        PopUiActiveBlot(&g_ui);
    }
}

void HandleDialogEvents(DIALOG *pdialog)
{
    if (pdialog->ideCur >= pdialog->cde)
    {
        return;
    }

    while (!FPauseDialog(pdialog))
    {
        if (pdialog->dp.pasegaLipsync != NULL)
        {
            RetractAsega(pdialog->dp.pasegaLipsync);
            pdialog->dp.pasegaLipsync = NULL;
        }

        if (++pdialog->ideCur >= pdialog->cde)
        {
            FUN_001516c0(pdialog);
            break;
        }

        HandleDialogEvent(pdialog, &pdialog->ade[pdialog->ideCur]);
    }
}

void FUN_00151860(DIALOG *pdialog, BLOT *pblot)
{
    if (pblot)
    {
        ((void (*)(BLOT *, DIALOG *))STRUCT_OFFSET(pblot->pvtblot, 0x158, void *))(pblot, pdialog);
    }
    else
    {
        BLOT *pbinoc = &g_binoc;
        STRUCT_OFFSET(pbinoc, 0x324, DIALOG *) = pdialog;
        PushUiActiveBlot(&g_ui, pbinoc);
    }
}

void TriggerDialog(DIALOG *pdialog)
{
    NOTE *pnote = &g_note;

    if (STRUCT_OFFSET(pnote, 0x260, int) >= 2)
    {
        return;
    }

    if (STRUCT_OFFSET(pnote, 0x26c, int) != 0)
    {
        return;
    }

    if (SetVagUnpaused())
    {
        return;
    }

    if (g_wipe.wipes == WIPES_WipingOut)
    {
        return;
    }

    if (pdialog == g_pdialogPlaying)
    {
        return;
    }

    DIALOGS dialogs = DIALOGS_Triggered;

    if (*pdialog->pfPlayed != 0)
    {
        if (pdialog->dialogk != DIALOGK_Confront)
        {
            dialogs = DIALOGS_UnableToCall;
        }
        else
        {
            dialogs = pdialog->dialogs;
        }
    }
    else
    {
        int cpfEquivalence = pdialog->cpfEquivalence;

        if (cpfEquivalence > 0)
        {
            for (int i = 0; i < cpfEquivalence; i++)
            {
                if (*pdialog->apfEquivalence[i] != 0)
                {
                    dialogs = DIALOGS_UnableToCall;
                    break;
                }
            }
        }
    }

    SetDialogDialogs(pdialog, dialogs);
}

void UntriggerDialog(DIALOG *pdialog)
{
    if (pdialog->dialogs != DIALOGS_Triggered && pdialog->dialogs != DIALOGS_Playing)
    {
        SetDialogDialogs(pdialog, DIALOGS_Enabled);
    }
}
