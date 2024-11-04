/**
 * @file splice/gc.h
 */
#ifndef SPLICE_GC_H
#define SPLICE_GC_H

#include "common.h"

class CFrame;
class CPair;
class CProc;
class CSidebag;

class CGc {
private:
    int m_cpframeRoot;
    CFrame* m_apframeRoot[256];

    char unk_pad[0x100];

    int m_cpsidebagRoot;
    CSidebag* m_apsidebagRoot[128];
    int m_cpframeStack;
    CFrame* m_apframeStack[512];
    int m_cppairStack;
    CPair* m_appairStack[256];
    int m_cpprocStack;
    CProc* m_approcStack[1024];
    
public:
    CGc();
    ~CGc();
    void Startup();
    void Shutdown();
    void AddRootFrame(CFrame* pframe);
    void AddRootSidebag(CSidebag* psidebag);
    void PushFrame(CFrame* pframe);
    CFrame* PframePop();
    void PushPair(CPair* ppair);
    CPair* PpairPop();
    void PushProc(CProc* pproc);
    CProc* PprocPop();
    void UpdateRecyclable();
    void MarkLiveObjects();
    void Collect();
};

// static CGc g_gc;

#endif // SPLICE_GC_H
