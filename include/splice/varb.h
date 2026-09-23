/**
 * @file splice/varb.h
 *
 * @brief Variable bindings for splice.
 */
#ifndef SPLICE_VARB_H
#define SPLICE_VARB_H

#include "common.h"
#include "splice/ref.h"

class CFrame;

/**
 * @brief Variable binding, stored as a linked list.
 */
class CVarb
{
public:
    SYMID m_symid;
    CRef m_ref;
    CVarb *m_pvarbNext;

    /**
     * @brief Clones this variable binding to another binding.
     *
     * @param pvarbClone Pointer to the target variable binding.
     * @param pframeClone Pointer to the frame used for cloning references.
     */
    void CloneTo(CVarb *pvarbClone, CFrame *pframeClone);
};

/**
 * @brief Allocates a new variable binding from the varb splot heap.
 *
 * @return Pointer to the newly allocated variable binding.
 */
CVarb *PvarbNew();

/**
 * @brief Deletes a variable binding by invoking its reference destructor.
 *
 * @param pvarb Pointer to the variable binding to delete.
 */
void DeleteVarb(CVarb *pvarb);

#endif // SPLICE_VARB_H
