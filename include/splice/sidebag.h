/**
 * @file splice/sidebag.h
 *
 * @brief Sidebag for splice.
 */
#ifndef SPLICE_SIDEBAG_H
#define SPLICE_SIDEBAG_H

#include "common.h"

class CRef;

// todo Find where this struct should be implemented.
struct SBB
{
};

class CSidebag
{
private:
    int m_csbb;
    SBB m_asbb[16];

public:
    CSidebag& RefAddBinding(int, CRef*);
    CSidebag& RefSetBinding(int, CRef*);
    bool FFindBinding(int, CRef*);
    void CloneTo(CSidebag*);

};

/**
 * @brief Creates a new sidebag.
 *
 * @return A pointer to the newly created sidebag.
 */
CSidebag* PsidebagNew();

#endif // SPLICE_SIDEBAG_H
