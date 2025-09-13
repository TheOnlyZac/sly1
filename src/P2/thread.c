#include <sdk/ee/eekernel.h>
#include <sce/memset.h>
#include <thread.h>
#include <frm.h>

int SemaCreate(int initCount, int maxCount)
{
    SemaParam sp;

    memset(&sp, 0, sizeof(SemaParam));
    sp.initCount = initCount;
    sp.maxCount = maxCount;
    return CreateSema(&sp);
}

INCLUDE_ASM("asm/nonmatchings/P2/thread", junk_001E22B8);

void InitCritSect(CRITSECT *pcritsect)
{
    pcritsect->thread = -1;
    pcritsect->sema = SemaCreate(1, 1);
}

void EnterCritSect(CRITSECT *pcritsect)
{
    int threadId = GetThreadId();

    if (threadId != pcritsect->thread)
    {
        WaitSema(pcritsect->sema);
        pcritsect->thread = threadId;
        pcritsect->cEnter = 1;
    }
    else
    {
        pcritsect->cEnter++;
    }
}

void LeaveCritSect(CRITSECT *pcritsect)
{
    int critSects = pcritsect->cEnter - 1;
    pcritsect->cEnter = critSects;

    if (critSects == 0) {
        pcritsect->thread = -1;
        SignalSema(pcritsect->sema);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/thread", junk_001E2390);

void StartupThread()
{
    ThreadParam tp;

    g_athread.cEnter = GetThreadId();
    ChangeThreadPriority(g_athread.cEnter, 4);
    memset(&tp, 0, sizeof(ThreadParam));

    tp.stackSize = 0x20000;
    tp.stack = g_abRenderLoopStack;
    tp.initPriority = 2;
    tp.gpReg = &_gpReg;
    tp.entry = FrameRenderLoop;

    g_athread.thread = CreateThread(&tp);
}
