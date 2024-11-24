#include <joy.h>
#include <clock.h>
#include <transition.h>
#include <sce/memset.h>
#include <sce/pad.h>

extern void* PvAllocGlobalImpl(int); // todo: remove when function is known

void StartupJoy()
{
    UpdateGrfjoytFromGrfusr();
    scePadInit(0);
    InitJoy(&g_joy, 0, 0);
}

void AddGrfusr(int mask)
{
    g_grfusr |= mask;
    UpdateGrfjoytFromGrfusr();
}

void RemoveGrfusr(int mask)
{
    g_grfusr &= ~mask;
    UpdateGrfjoytFromGrfusr();
}

void UpdateGrfjoytFromGrfusr()
{
    if (g_grfusr & 0x84)
    {
        // Unknown state
        g_grfjoyt = 0;
    }
    else if (g_grfusr & FUSR_Menu)
    {
        // Pause menu/dialog box is open
        g_grfjoyt = 5;
    }
    else if (g_grfusr & FUSR_HandsOff)
    {
        // In-game cutscene/transition/animation is playing
        g_grfjoyt = 4;
    }
    else
    {
        // Game is running normally
        g_grfjoyt = 7;
    }
}

// todo: investigate if aullDma assignment can be cleaned up when type is known
void InitJoy(JOY *pjoy, int nPort, int nSlot)
{
    memset(pjoy, 0, sizeof(JOY));
    SetJoyJoys(pjoy, JOYS_Searching, JOYK_Unknown);
    pjoy->nPort = nPort;
    pjoy->nSlot = nSlot;
    pjoy->aullDma = (uint*)(((int)PvAllocGlobalImpl(0x140) + 0x3F) & ~0x3F);
    scePadPortOpen(pjoy->nPort, pjoy->nSlot, pjoy->aullDma);
    pjoy->prumble = (RUMBLE *)PvAllocGlobalImpl(0x20);
    pjoy->fRumbleEnabled = true;
}

INCLUDE_ASM(const s32, "P2/joy", UpdateJoy__FP3JOY);

void SetJoyJoys(JOY *pjoy,JOYS joys,JOYK joyk)
{
    JOYK joykPrev;
    LM *almDeflect2;
    LM *almDeflect;
    float *almDeflect2Max;
    float *almDeflectMax;
    uint i;

    if (joys != pjoy->joys || joyk != pjoy->joyk)
    {
        if (joyk == JOYK_Unknown)
        {
            pjoy->term = 0;
            joys = JOYS_Searching;
            joykPrev = pjoy->joyk;
        }
        else
        {
            joykPrev = pjoy->joyk;
        }

        if (joykPrev < 3 && 2 < joyk)
        {
            InitRumble(pjoy->prumble,pjoy->nPort,pjoy->nSlot);
        }

        if (joys == JOYS_Ready)
        {
            i = 0;
            pjoy->tRead = 0.0;
            pjoy->fStickMoved2 = 0;
            almDeflectMax = &pjoy->almDeflect[0].gMax;
            pjoy->fStickMoved = 0;
            almDeflect2Max = &pjoy->almDeflect2[0].gMax;
            pjoy->grfbtn = 0;
            almDeflect = pjoy->almDeflect;
            almDeflect2 = pjoy->almDeflect2;

            for (; i < 4; i++) {
                almDeflect2->gMin = -0.75;
                almDeflect->gMin = -0.75;
                almDeflect2++;
                *almDeflect2Max = 0.75;
                almDeflect++;
                *almDeflectMax = 0.75;
                almDeflect2Max += 2;
                almDeflectMax += 2;
            }
        }

        pjoy->joys = joys;
        pjoy->joyk = joyk;
        pjoy->tJoys = g_clock.tReal;
    }
}

INCLUDE_ASM(const s32, "P2/joy", GetJoyXYDeflection__FP3JOYUcUcPfN23PUcT6PiP2LM);

INCLUDE_ASM(const s32, "P2/joy", FReadJoy__FP3JOY);

void SetJoyBtnHandled(JOY *pjoy, GRFBTN btn)
{
    pjoy->grfbtnPressed &= ~btn;
}

void TriggerJoyRumbleRumk(JOY *pjoy, RUMK rumk, float dt)
{
    if (pjoy->fRumbleEnabled && pjoy->joyk > JOYK_Analog && pjoy->joys == JOYS_Ready)
    {
        TriggerRumbleRumk(pjoy->prumble, rumk, dt);
    }
}

INCLUDE_ASM(const s32, "P2/joy", func_0016EC80);

void StartJoySelection(JOY *pjoy)
{
    pjoy->dxLatch = 0;
    pjoy->dyLatch = 0;
}

INCLUDE_ASM(const s32, "P2/joy", DxSelectionJoy__FP3JOY);

INCLUDE_ASM(const s32, "P2/joy", DySelectionJoy__FP3JOY);

INCLUDE_ASM(const s32, "P2/joy", UBtnpJoy__FP3JOY4BTNP);

void AddCode(CODE *pcode)
{
    CODE *p_inputs_counter = g_pcode;

    while (p_inputs_counter != nullptr)
    {
        if (pcode == p_inputs_counter)
        {
            return;
        }
        p_inputs_counter = p_inputs_counter->pchtNext;
    }

    pcode->pchtNext = g_pcode;
    g_pcode = pcode;
    if (g_joy.grfbtn == *pcode->ajbc)
    {
        pcode->nInputCounter = 1;
    }
    else
    {
        pcode->nInputCounter = 0;
    }
}

INCLUDE_ASM(const s32, "P2/joy", func_0016F1F0);

void _ResetCodes()
{
    CODE *pcode = g_pcode;
    if (g_pcode != nullptr)
    {
        g_pcode->nInputCounter = 0;
        while (pcode = pcode->pchtNext, pcode != nullptr)
        {
            pcode->nInputCounter = 0;
        }
    }
}

void _MatchCodes(JOY *pjoy, GRFBTN btn)
{
    if (g_pcode != nullptr && pjoy == &g_joy && btn != g_joy.grfbtn && g_joy.grfbtn != 0)
    {
        CODE * pcode = g_pcode;

        while(pcode != nullptr)
        {
            if (pcode->nInputCounter < pcode->cjbc)
            {
                if (g_joy.grfbtn == pcode->ajbc[pcode->nInputCounter])
                {
                    pcode->nInputCounter++;
                }
                else
                {
                    pcode->nInputCounter = 0;
                }
            }
            pcode = pcode->pchtNext;
        }
        g_tCodeCheck = g_clock.tReal + 1.0f;
    }
}

INCLUDE_ASM(const s32, "P2/joy", UpdateCodes__Fv);

void ClearFchts()
{
    g_grfcht = FCHT_None;
    ResetWorld(FTRANS_None);
}

INCLUDE_ASM(const s32, "P2/joy", AddFcht__Fi);
// void AddFcht(int nParam)
// {
//     g_grfcht |= nParam & ~FCHT_ResetWorld;
//     if (nParam & FCHT_ResetWorld)
//     {
//         ResetWorld(FTRANS_None);
//     }
// }

INCLUDE_ASM(const s32, "P2/joy", func_0016F470);

INCLUDE_ASM(const s32, "P2/joy", Chetkido__Fv);

INCLUDE_ASM(const s32, "P2/joy", StartupCodes__Fv);
