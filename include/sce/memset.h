/**
 * @file memset.h
 *
 * @brief Memset.
 */
#ifndef MEMSET_H
#define MEMSET_H

#include "common.h"

extern "C"
{
    void* memset(void* ptr, s32 value, size_t num);
}

#endif // MEMSET_H
