/**
 * @file splice/frame.h
 */
#ifndef SPLICE_FRAME_H
#define SPLICE_FRAME_H

#include "common.h"

// Forward.
class CRef;
class CVarb;
typedef uint SYMID;

/**
 * @brief Splice stack frame.  Each frame can have up to 4 parent frames.
 */
class CFrame
{
public:
    /* 0x00 */ int m_cpframeParent;
    /* 0x04 */ CFrame *m_apframeParent[4];
    /* 0x14 */ CVarb *m_pvarb;
    /* 0x18 */ int m_fVisited;

    /**
     * @brief Sets this frame to have one single parent frame.
     *
     * @param pframeParent Parent frame.
     */
    void SetSingleParent(CFrame *pframeParent);

    /**
     * @brief Adds a parent frame to this frame.
     * This method isn't bounds checked and can overflow with too many parents.
     *
     * @param pframeParent Parent frame.
     */
    void AddParent(CFrame *pframeParent);

    /**
     * @brief Adds a new variable binding to this frame.
     * Does not check if the symbol already exists, so this may insert duplicates.
     *
     * @param symid Symbol ID to add.
     * @param pref Value of the symbol to add.
     * @return Void reference.
     */
    CRef RefAddBinding(SYMID symid, CRef *pref);

    /**
     * @brief Sets the value for an existing variable binding.
     * If the symbol was not found, then this silently fails.
     *
     * @param symid Symbol ID to set.
     * @param pref Value of the symbol to set.
     * @return Void reference.
     */
    CRef RefSetBinding(SYMID symid, CRef *pref);

    /**
     * @brief Checks if a symbol binding exists in this frame.
     *
     * @param symid Symbol ID to search for.
     * @param fRecursive If true, will also search parent frames.
     * @param pref If found, will be set to the value of the bound symbol.
     * @return true if found, false otherwise.
     */
    int FFindBinding(SYMID symid, int fRecursive, CRef *pref);

    /**
     * @brief Finds a symbol binding in this frame.
     *
     * @param symid Symbol ID to search for.
     * @param fRecursive If true, will also search parent frames.
     * @return The reference value of the symbol if found, NULL otherwise.
     */
    CRef *PrefFindBinding(SYMID symid, int fRecursive);

    /**
     * @brief Clones this frame into a new frame.
     *
     * @param pframeClone New frame to clone into.
     */
    void CloneTo(CFrame *pframeClone);
};

/**
 * @brief Creates a new frame.
 */
CFrame *PframeNew();

/**
 * @brief Deletes the frame.
 */
void DeleteFrame(CFrame *pframe);

#endif // SPLICE_FRAME_H
