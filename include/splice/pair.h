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
    CRef m_ref;
    CPair* m_ppairNext;

public:
    void CloneTo(CPair* ppairClone, CFrame* pframeClone);
};

CPair* PpairNew();
void DeletePair(CPair* ppair);

#endif // SPLICE_PAIR_H
