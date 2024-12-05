/**
 * @file rand.h
 * @note /sce/ee/gcc/src/newlib/libc/stdlib/rand.c
 *
 * @brief Random number generation.
 */
#ifndef RAND_H
#define RAND_H

typedef unsigned int undefined4;
typedef unsigned int u_int;

extern "C"
{
    struct RNG {
        undefined4 field0_0x0;
        undefined4 field1_0x4;
        undefined4 field2_0x8;
        undefined4 field3_0xc;
        undefined4 field4_0x10;
        undefined4 field5_0x14;
        undefined4 field6_0x18;
        undefined4 field7_0x1c;
        undefined4 field8_0x20;
        undefined4 field9_0x24;
        undefined4 field10_0x28;
        undefined4 field11_0x2c;
        undefined4 field12_0x30;
        undefined4 field13_0x34;
        undefined4 field14_0x38;
        undefined4 field15_0x3c;
        undefined4 field16_0x40;
        undefined4 field17_0x44;
        undefined4 field18_0x48;
        undefined4 field19_0x4c;
        undefined4 field20_0x50;
        undefined4 field21_0x54;
        u_int next;
    };

    /**
     * @brief Seed the random number generator.
     */
    void srand(u_int seed);

    /**
     * @brief Generate a random number.
     */
    u_int rand();
};

#endif // RAND_H
