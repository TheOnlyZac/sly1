/**
 * @file slotheap.h
 *
 * @brief Fixed-size memory pool allocator using a linked list of free slots.
 */
#ifndef SLOTHEAP_H
#define SLOTHEAP_H

#include "common.h"

/**
 * @brief Slot.
 */
struct SLOT
{
    /* 0x00 */ SLOT *pslotNext;
}; // 0x04 bytes.

/**
 * @brief Slot heap.
 */
struct SLOTHEAP
{
    /* 0x00 */ int cb;
    /* 0x04 */ byte *ab;
    /* 0x08 */ SLOT *pslotFree;
}; // 0x0c bytes.

/**
 * @brief Initializes a slot heap with a linked list of free slots.
 *
 * @param pslotheap Pointer to the slot heap.
 * @param cb        Size of a slot in bytes.
 * @param c         Number of slots to allocate.
 */
void _InitSlotheap(SLOTHEAP *pslotheap, int cb, int c);

/**
 * @brief Creates the slot heap with slots aligned to 8 bytes.
 *
 * @param pslotheap Pointer to the slot heap.
 * @param cb        Size of a slot in bytes.
 * @param c         Number of slots to allocate.
 */
void CreateSlotheapSw(SLOTHEAP *pslotheap, int cb, int c);

/**
 * @brief Creates the slot heap with slots aligned to 64 bytes.
 *
 * @param pslotheap Pointer to the slot heap.
 * @param cb        Size of a slot in bytes.
 * @param c         Number of slots to allocate.
 */
void CreateSlotheapSwAlign64(SLOTHEAP *pslotheap, int cb, int c);

/**
 * @brief Allocates a slot from the slot heap.
 *
 * @param pslotheap Pointer to the slot heap.
 *
 * @return Pointer to an allocated slot.
 */
void *PvAllocSlotheapUnsafe(SLOTHEAP *pslotheap);

/**
 * @brief Wrapper for PvAllocSlotheapUnsafe.
 *
 * @param pslotheap Pointer to the slot heap.
 *
 * @return Pointer to an allocated slot.
 */
void *PvAllocSlotheapImpl(SLOTHEAP *pslotheap);

/**
 * @brief Allocates a slot from the slot heap and clears it.
 *
 * @param pslotheap Pointer to the slot heap.
 *
 * @return Pointer to an allocated slot.
 */
void *PvAllocSlotheapClearImpl(SLOTHEAP *pslotheap);

/**
 * @brief Frees a slot and returns it to the slot heap.
 *
 * @param pslotheap Pointer to the slot heap.
 * @param pv        Pointer to the slot being freed.
 */
void FreeSlotheapPv(SLOTHEAP *pslotheap, void *pv);

#endif // SLOTHEAP_H
