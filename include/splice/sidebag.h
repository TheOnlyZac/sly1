/**
 * @file splice/sidebag.h
 *
 * @brief Sidebag for splice.
 */
#ifndef SPLICE_SIDEBAG_H
#define SPLICE_SIDEBAG_H

#include "common.h"

// Forward declarations
class CRef;
class CVarb;

/**
 * @brief Sidebag.
 */
class CSidebag
{
public:
    CVarb *m_pvarb;

    /**
     * @brief Adds a new variable binding to this sidebag.
     * Does not check if the symbol already exists, so this may insert duplicates.
     *
     * @param symid Symbol ID to add.
     * @param pref Value of the symbol to add.
     * @return Void reference.
     */
    CRef RefAddBinding(int symid, CRef *pref);

    /**
     * @brief Sets the value for an existing variable binding.
     * If the symbol was not found, then this silently fails.
     *
     * @param symid Symbol ID to set.
     * @param pref Value of the symbol to set.
     * @return Void reference.
     */
    CRef RefSetBinding(int symid, CRef *pref);

    /**
     * @brief Checks if a symbol binding exists in this frame.
     *
     * @param symid Symbol ID to search for.
     * @param pref If found, will be set to the value of the bound symbol.
     * @return true if found, false otherwise.
     */
    int FFindBinding(int symid, CRef *pref);

    /**
     * @brief Clones this sidebag into a new sidebag.
     *
     * @param pframeClone New sidebag to clone into.
     */
    void CloneTo(CSidebag *psidebagClone);
};

/**
 * @brief Creates a new sidebag.
 *
 * @return A pointer to the newly created sidebag.
 */
CSidebag *PsidebagNew();

#endif // SPLICE_SIDEBAG_H
