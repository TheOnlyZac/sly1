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
 * @brief Accesses a value on a struct by its offset and type. For use when the
 * struct is unimplemented, incomplete or inaccurate.
 *
 * @param pointer Pointer to the struct.
 * @param offset Offset of the field within the struct.
 * @param type Type of the field.
 */
#define STRUCT_OFFSET(pointer, offset, type) (*(type *)((uint8_t *)(pointer) + (offset)))

// Helper macros for struct padding (workaround for eegcc not supporting macro expansion in struct fields)
#define STRUCT_PADDING_CAT(a, b) a##b
#define STRUCT_PADDING_INTERNAL(a, b) STRUCT_PADDING_CAT(a, b)

/**
 * @brief Inserts an array of padding words into a struct. It generates a unique
 * name for the padding field using the line number.
 *
 * @param name Name of the padding field.
 * @param size Number of 4-byte words in the padding field.
 */
#define STRUCT_PADDING(size) uint32_t STRUCT_PADDING_INTERNAL(_pad_, __LINE__)[size]

/**
 * @brief Inserts a four-byte word followed by four bytes of 0x00.
 */
#define JUNK_WORD(val) asm(".word " #val "\n\t" ".word 0x00000000\n\t")

/**
 * @brief Shortcut macro for junk `addiu $29, $29, imm` instructions.
 * Takes the immediate value as a hex byte and emits the corresponding instruction word.
 */
#define JUNK_ADDIU(imm) JUNK_WORD(0x27BD00##imm)

/**
 * @brief Inserts a four-byte nop on it's own.
 */
#define JUNK_NOP() asm(".word 0x00000000\n\t")

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


#endif // COMMON_H
