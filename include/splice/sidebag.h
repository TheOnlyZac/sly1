/**
 * @file splice/sidebag.h
 *
 * @brief Sidebag for splice.
 */
#ifndef SPLICE_SIDEBAG_H
#define SPLICE_SIDEBAG_H

#include "common.h"

class CRef;

/**
 * @brief Unknown.
 * @todo Find where this struct should be implemented.
 */
struct SBB
{
    int n;
    // CRef ref;
};

/**
 * @brief Sidebag.
 */
class CSidebag
{
private:
    int m_csbb;
    SBB m_asbb[16];

public:
    CSidebag& RefAddBinding(int n, CRef *pref);

    CSidebag& RefSetBinding(int n, CRef *pref);

    bool FFindBinding(int n, CRef *pref);

    void CloneTo(CSidebag *psidebagClone);
};

/**
 * @brief Creates a new sidebag.
 *
 * @return A pointer to the newly created sidebag.
 */
CSidebag *PsidebagNew();

#endif // SPLICE_SIDEBAG_H
