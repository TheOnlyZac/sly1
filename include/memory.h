/**
 * @file memory.h
 */
#ifndef MEMORY_H
#define MEMORY_H

#include "common.h"

/**
 * @brief Allocate a block of memory.
 *
 * @param cb Size of the block in bytes.
 */
void *PvAllocSwImpl(uint cb);

/**
 * @brief Allocate a block of memory and copy data to it from the given pointer.
 *
 * @param cb Size of the block in bytes.
 * @param pvSrc Data to copy.
 */
void *PvAllocSwCopyImpl(uint cb, void *pvSrc);

/**
 * @brief Allocate a block of memory and clear it.
 *
 * @param cb Size of the block in bytes.
 */
void *PvAllocSwClearImpl(uint cb);

/**
 * @brief Copies a block of memory from one location to another.
 *
 * @param pvDst Pointer to the destination memory location.
 * @param pvSrc Pointer to the source memory location.
 * @param cb Number of bytes to copy.
 */
void CopyAb(void *pvDst, void *pvSrc, uint cb);

#endif // MEMORY_H
