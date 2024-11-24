/**
 * @file memset.h
 *
 * @brief Memset.
 */
#ifndef MEMSET_H
#define MEMSET_H
#include <stddef.h>

extern "C"
{
    void* memset(void* ptr, int value, size_t num);
}

#endif // MEMSET_H
