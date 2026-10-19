#include <cplcy.h>
#include <sound.h>
#include <989snd.h>
#include <cm.h>

extern float RAD_CplookTiltDefault; // RAD_CplookTiltDefault

void InitCplcy(CPLCY *pcplcy, CM *pcm)
{
    pcplcy->pcm = pcm;
}

int FActiveCplcy(CPLCY *pcplcy)
{
    return STRUCT_OFFSET(pcplcy->pcm, 0x3D8, CPLCY *) == pcplcy;
}

void SetCpmanCpmt(CPMAN *pcpman, CPMT cpmt)
{
    pcpman->cpmt = cpmt;
}

void UpdateCpman(CPMAN *pcpman, CPDEFI *pcpdefi, JOY *pjoy, float dt)
{
    return;
}

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", PosCplookAnchor__FP6CPLOOK);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", PosCplookEye__FP6CPLOOK);

void StartCplookSound(CPLOOK *pcplook)
{
    StartSound(
        SFXID_UiBinocZoom, &pcplook->pambBinoc,
        NULL, NULL,
        3000.0f, 300.0f,
        1.0f, 0.0f, 0.0f,
        NULL, NULL
    );

    if (pcplook->pambBinoc)
    {
        snd_PauseSound(pcplook->pambBinoc->sfxh);
    }

    StartSound(
        SFXID_UiBinocAmbient,
        &pcplook->pambAmbient,
        NULL, NULL,
        3000.0f, 300.0f,
        1.0f, 0.0f, 0.0f,
        NULL, NULL
    );

    pcplook->fSoundPaused = 1;
}

void PushCplookLookk(CPLOOK *pcplook, LOOKK lookk)
{
    if ((uint)pcplook->clookk < 4)
    {
        pcplook->alookk[pcplook->clookk++] = lookk;
    }
}

LOOKK LookkPopCplook(CPLOOK *pcplook)
{
    if (pcplook->clookk <= 0)
    {
        return LOOKK_Nil;
    }

    return pcplook->alookk[--pcplook->clookk];
}

LOOKK LookkCurCplook(CPLOOK *pcplook)
{
    if (pcplook->clookk <= 0)
    {
        return LOOKK_Nil;
    }

    return pcplook->alookk[pcplook->clookk - 1];
}

void InitCplook(CPLOOK *pcplook, CM *pcm)
{
    InitCplcy(pcplook, pcm);
    pcplook->clookk = 0;
    pcplook->rZoomMax = 10.0f;
    PushCplookLookk(pcplook, LOOKK_User);
    pcplook->rScreenSniper = 0.5f;
    pcplook->sRadiusSniper = -1.0f;
    pcplook->paloFocusSniper = NULL;
}

void ActivateCplook(CPLOOK *pcplook, void *pv)
{
    CM *pcm = pcplook->pcm;
    DecomposeRotateMatrixPanTilt(&pcm->mat, &pcplook->radPan, &pcplook->radTilt);

    pcplook->radTilt = RAD_CplookTiltDefault;
    pcplook->swPan = 0.0f;
    pcplook->swTilt = 0.0f;
    pcplook->uZoom = 0.0f;
    pcplook->svuZoom = 0.0f;

    const float radFOV = pcm->radFOV2;
    pcplook->lmFOV.gMin = radFOV / pcplook->rZoomMax;
    pcplook->lmFOV.gMax = radFOV;

    VECTOR posAnchor = PosCplookAnchor(pcplook);
    ResetCmLookAtSmooth(pcm, &posAnchor);
    pcplook->unknown = pcm->sNearClip;
    SetCmNearClip(pcm, 49.0f);
}

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", UpdateCplook__FP6CPLOOKP6CPDEFIP3JOYf);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", DeactivateCplook__FP6CPLOOKPv);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", InitCpalign__FP7CPALIGNP2CM);

void ActivateCpalign(CPALIGN *pcpalign, void *pv)
{
    // pcpalign->pcm->acpr[0].psoFocus->posWorldPrev
    ResetCmLookAtSmooth(pcpalign->pcm, &STRUCT_OFFSET(pcpalign->pcm->acpr[0].psoFocus, 0x370, VECTOR));
}

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", UpdateCpalign__FP7CPALIGNP6CPDEFIP3JOYf);

void ActivateCpaseg(CPASEG *pcpaseg, void *pv)
{
    pcpaseg->pcamera = (CAMERA *)pv;
}

void DeactivateCpaseg(CPASEG *pcpaseg, void *pv)
{
    pcpaseg->pcamera = NULL;
}

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", UpdateCpaseg__FP6CPASEGP6CPDEFIP3JOYf);
