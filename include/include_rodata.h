#ifndef INCLUDE_RODATA_H
#define INCLUDE_RODATA_H

#ifndef INCLUDE_RODATA
#define INCLUDE_RODATA(FOLDER, NAME)                                           \
  __asm__(                                                                     \
      ".section .rodata\n"                                                     \
      "\t.include" FOLDER "/" #NAME                                            \
      ".s\"\n"                                                                 \
      ".section .text");
#endif

#endif /* INCLUDE_RODATA_H */
