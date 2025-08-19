/**
 * @file memory.h
 */
#ifndef MEMORY_H
#define MEMORY_H

#include "common.h"

typedef struct _reent;

/**
 * @todo
 */
void *PvAllocGlobalImpl(int cb);

#ifdef PROTO
/**
 * @brief Shows an error message on the screen.
 * @note Called if we have run out of memory on the stack.
 *
 * @param rgba Background color for the text box.
 */
void HardLockError(RGBA *rgba);
#endif

/**
 * @brief Stubbed, does nothing.
 *
 * @note Would have checked to see if we are out of stack memory.
 *
 * @deprecated
 */
void CheckForOutOfMemory();

/**
 * @brief Allocates memory for an SW.
 *
 * @param cb Size in bytes.
 *
 * @return Pointer to the allocated memory.
 */
void *PvAllocSwImpl(int cb);

/**
 * @brief Clears the SW stack.
 */
void FreeSw();

/**
 * @brief Allocates memory for an SW and copies data to it.
 *
 * @param cb Size of the block in bytes.
 * @param pvBase Data to copy.
 *
 * @return Pointer to the allocated memory.
 */
void *PvAllocSwCopyImpl(int cb, void *pvBase);

/**
 * @brief Allocates memory for an SW and clears it.
 *
 * @param cb Size in bytes.
 *
 * @return Pointer to the allocated memory.
 */
void *PvAllocSwClearImpl(int cb);

/**
 * @brief Initializes a new allocation frame on the stack.
 */
void InitStackImpl();

/**
 * @brief Allocates memory on the stack.
 *
 * @param cb Size in bytes.
 *
 * @note Rounds up `cb` to next multiple of 16.
 */
void *PvAllocStackImpl(int cb);

/**
 * @brief Allocates memory on the stack and clears it.
 *
 * @param cb Size in bytes.
 *
 * @note Rounds up `cb` to next multiple of 16.
 */
void *PvAllocStackClearImpl(int cb);

/**
 * @brief Unravels the current stack allocation frame.
 */
void FreeStackImpl();

extern "C"
{
    void *malloc(uint __size);
    void *_malloc_r(_reent *pre, uint __size);
    void free(void *pv);
}

/**
 * @brief Copies an array of quadwords (16-byte blocks).
 *
 * @param pvDst Destination pointer.
 * @param pvSrc Source pointer.
 * @param cqw Number of quadwords to copy (16 bytes each).
 *
 * @note Total bytes copied will be `cqw * 16`.
 */
void CopyAqw(void *pvDst, void *pvSrc, int cqw);

/**
 * @brief Copies an array of bytes (one byte at a time).
 *
 * @param pvDst Destination pointer.
 * @param pvSrc Source pointer.
 * @param cb Number of bytes to copy.
 */
void CopyAb(void *pvDst, void *pvSrc, uint cb);

#endif // MEMORY_H
