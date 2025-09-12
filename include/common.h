/**
 * @file common.h
 *
 * @brief Common header file.
 */
#ifndef COMMON_H
#define COMMON_H

#include "include_asm.h"
#include "types.h"
#include "vtables.h"
#include "spaprops.h"

// Helper macros for decompilation

/**
 * @brief Helper macro for accessing struct fields when the struct itself is
 * not implemented, incomplete or incorrect.
 *
 * @param pointer Pointer to the struct.
 * @param offset Offset of the field within the struct.
 * @param type Type of the field.
 */
#define STRUCT_OFFSET(pointer, offset, type) (*(type *)((uint8_t *)(pointer) + (offset)))

/**
 * @brief Helper macro for padding between known struct fields.
 *
 * @param name Name of the padding field.
 * @param size Number of 4-byte words in the padding field.
 */
#define PADDING(name, size) uint32_t padding_##name[(size)]

// Global system values
extern int _gpReg; // Global pointer register

/**
 * @brief RGBA color value.
 */
struct RGBA
{
    uchar bRed;
    uchar bGreen;
    uchar bBlue;
    uchar bAlpha;

    inline void operator=(const int rgba)
    {
        bRed = (rgba >> 24) & 0xFF;
        bGreen = (rgba >> 16) & 0xFF;
        bBlue = (rgba >> 8) & 0xFF;
        bAlpha = rgba & 0xFF;
    }
};


#endif /* COMMON_H */
