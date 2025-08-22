/**
 * @file types.h
 *
 * @brief Common types used across the codebase.
*/
#ifndef TYPES_H
#define TYPES_H

// Exact-width integers (don't use these in most cases)
typedef signed char      int8_t;
typedef short            int16_t;
typedef int              int32_t;
typedef long long        int64_t;

typedef unsigned char    uint8_t;
typedef unsigned short   uint16_t;
typedef unsigned int     uint32_t;
typedef unsigned long long uint64_t;

// Unsigned aliases
typedef uint8_t     uchar;
typedef uint16_t    ushort;
typedef uint32_t    uint;
typedef uint64_t    ulong;

// Helper types for unknown struct fields
typedef uchar     undefined1;
typedef ushort    undefined2;
typedef uint    undefined4;
typedef ulong    undefined8;

// Misc
typedef uchar byte;
#define nullptr (void *)0x0
typedef union QW;
typedef int32_t  s32; // used only by Splat

#endif // TYPES_H
