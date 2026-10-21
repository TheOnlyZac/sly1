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

/**
 * @brief Splice garbage collector.
 */
class CGc
{
private:
    int m_cpframeRoot;
    CFrame *m_apframeRoot[256];

    /** @todo: This might be more root frames? I don't see anything else referencing this memory. */
    STRUCT_PADDING(64);

    int m_cpsidebagRoot;
    CSidebag *m_apsidebagRoot[128];
    int m_cpframeStack;
    CFrame *m_apframeStack[512];
    int m_cppairStack;
    CPair *m_appairStack[256];
    int m_cpprocStack;
    CProc *m_approcStack[1024];

    /**
     * @brief Adds a frame to the processing stack when searching for live objects.
     *
     * @param pframe Frame to push.
     */
    void PushFrame(CFrame *pframe);

    /**
     * @brief Pops a frame from the processing stack when searching for live objects.
     *
     * @return Next frame to process.
     */
    CFrame *PframePop();

    /**
     * @brief Adds a pair to the processing stack when searching for live objects.
     *
     * @param ppair Pair to push.
     */
    void PushPair(CPair *ppair);

    /**
     * @brief Pops a pair from the processing stack when searching for live objects.
     *
     * @return Next pair to process.
     */
    CPair *PpairPop();

    /**
     * @brief Adds a proc to the processing stack when searching for live objects.
     *
     * @param pproc Proc to push.
     */
    void PushProc(CProc *pproc);

    /**
     * @brief Pops a proc from the processing stack when searching for live objects.
     *
     * @return Next proc to process.
     */
    CProc *PprocPop();

    /**
     * @brief Searches for all live CFrame, CPair, and CProc instances and marks them alive.
     */
    void MarkLiveObjects();

public:
    CGc();
    ~CGc();

    /**
     * @brief Initializes the garbage collector
     */
    void Startup();

    /**
     * @brief Stops the garbage collector (which doesn't do anything)
     */
    void Shutdown();

    /**
     * @brief Adds a root splice frame to the GC list.
     *
     * @param pframe Frame to add.
     */
    void AddRootFrame(CFrame *pframe);

    /**
     * @brief Adds a root splice sidebag to the GC list.
     *
     * @param psidebag Sidebag to add.
     */
    void AddRootSidebag(CSidebag *psidebag);

    /**
     * @brief Calls UpdateRecyclable() on each global splotheap
     * @todo Come up with a better description once Splotheap's UpdateRecyclable() is decompiled.
     */
    void UpdateRecyclable();

    /**
     * @brief Checks live objects and frees memory that is no longer in use.
     */
    void Collect();
};

extern CGc g_gc;

#endif // SPLICE_GC_H
