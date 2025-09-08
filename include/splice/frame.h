/**
 * @file splice/frame.h
 */
#ifndef SPLICE_FRAME_H
#define SPLICE_FRAME_H

#include "common.h"

// Forward.
class CRef;

class CFrame
{
public:
    void SetSingleParent(CFrame *pframeParent);
    void AddParent(CFrame *pframeParent);
    CFrame *RefAddBinding(int symid, CRef * pref);
    CFrame *RefSetBinding(int symid, CRef *pref);
    int FFindBinding(int symid, int fRecursive, CRef *pref);
    CRef *PrefFindBinding(int symid, int fRecursive);
    void CloneTo(CFrame *pframeClone);
};

// ...

CFrame *PframeNew();

/**
 * @brief Deletes the frame.
 */
void DeleteFrame(CFrame *pframe);

#endif // SPLICE_FRAME_H
