/**
 * @file sidebag.h
 *
 * @brief Declares the CSidebag class.
*/
#pragma once
#include <gc.h>

/**
 * @brief Sidebag
 *
 * A sidebag is a data structure that stores the results of a computation that is
 * performed in parallel with the main computation.
 *
 * The sidebag is used to store the results of the parallel computation until
 * the main computation is ready to use them.
*/
struct CSidebag {
    int m_csbb;
    struct SBB m_asbb[16];
};
