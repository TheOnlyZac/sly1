/**
 * @file splice/sidebag.h
 *
 * @brief Sidebag for splice.
 */
#ifndef SPLICE_SIDEBAG_H
#define SPLICE_SIDEBAG_H

#include "common.h"

class CRef;
class CVarb;

/**
 * @brief Sidebag.
 */
class CSidebag
{
public:
    CVarb *m_pvarb;

    CRef RefAddBinding(int n, CRef *pref);
    CRef RefSetBinding(int n, CRef *pref);
    int FFindBinding(int n, CRef *pref);
    void CloneTo(CSidebag *psidebagClone);
};

/**
 * @brief Creates a new sidebag.
 *
 * @return A pointer to the newly created sidebag.
 */
CSidebag *PsidebagNew();

#endif // SPLICE_SIDEBAG_H
