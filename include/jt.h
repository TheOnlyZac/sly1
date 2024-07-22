/**
 * @file jt.h
 *
 * @brief Sly entity.
 */
#ifndef JT_H
#define JT_H

#include "common.h"
#include <step.h>

/**
 * @brief Sly entity.
 *
 * JT = "jewel thief" = codename for Sly.
 *
 * @todo Implement struct.
 */
struct JT : public STEP
{
    // ...
};

/**
 * @brief Stubbed, does nothing.
 *
 * @param pjt Pointer to JT entity.
 * @param fProfile Profile flag.
 *
 * @deprecated
 */
void ProfileJt(JT* pjt, int fProfile);

extern JT* g_pjt;

#endif // JT_H
