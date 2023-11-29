#pragma once

typedef unsigned char byte; //todo move to util header

/**
 * Slotheap
 *
 * A slotheap is a heap of fixed size slots.  The slots are allocated in a
 * contiguous block of memory. The slotheap maintains a pointer to the next
 * free slot.
*/
struct SLOTHEAP {
    int cb; // size of each slot
    byte* ab; // pointer to the block of memory
    struct SLOT* pslotFree; // pointer to the next free slot
    int cAlloc; // number of slots allocated
    int cInUse; // number of slots in use
};

/**
 * Slot
 *
 * Represents one slot in the slotheap.
*/
struct SLOT {
    struct SLOT* pslotNext; // pointer to the next slot in the free list
};
