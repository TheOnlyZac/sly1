/**
 * @file splice/pair.h
 */
#ifndef SPLICE_PAIR_H
#define SPLICE_PAIR_H

#include "common.h"
#include "splice/ref.h"

/**
 * @class CPair
 *
 * @todo Fill in class.
 */
class CPair
{
public:
    CRef m_ref;

    /**
     * @brief Clones this pair to another pair, recursively cloning any next pairs.
     *
     * @param ppairClone Pointer to the pair to clone to.
     * @param pframeClone Pointer to the frame to use for cloning references.
     */
    void CloneTo(CPair *ppairClone, CFrame *pframeClone);

private:
    CPair *m_ppairNext;
};

/**
 * @brief Allocates a new pair from the pair splot heap.
 *
 * @return Pointer to the newly allocated pair.
 */
CPair *PpairNew();

/**
 * @brief Deletes a pair by the calling destructor for its ref.
 *
 * @param ppair Pointer to the pair to delete.
 */
void DeletePair(CPair *ppair);

#endif // SPLICE_PAIR_H
