#ifndef INCLUDE_ASM_H
#define INCLUDE_ASM_H

#if !defined(SPLAT) && !defined(__CTX__) && !defined(PERMUTER) && !defined(SKIP_ASM)
#ifndef INCLUDE_ASM
#define INCLUDE_ASM_INTERNAL(TYPE, BASE_FOLDER, FOLDER, NAME, ARGS...) \
    __asm__(                                                           \
        ".section .text\n"                                             \
        "\t.align\t3\n"                                                \
        "\t.globl\t" #NAME "\n"                                        \
        "\t.ent\t" #NAME "\n" #NAME ":\n"                              \
        "\t.include \"asm/" BASE_FOLDER "/" FOLDER "/" #NAME ".s\"\n"  \
        "\t.set reorder\n"                                             \
        "\t.set at\n"                                                  \
        "\t.end\t" #NAME);
#define INCLUDE_ASM(TYPE, FOLDER, NAME, ARGS...) INCLUDE_ASM_INTERNAL(TYPE, "nonmatchings", FOLDER, NAME, ARGS)
#endif
__asm__(".include \"include/macro.inc\"\n");
#else
#define INCLUDE_ASM(TYPE, FOLDER, NAME, ARGS...)
#endif

#endif /* INCLUDE_ASM_H */
