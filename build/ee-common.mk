include build/sce-common.mk

ifeq ($(WINE),y)
CC := wine $(SCE_EE)/gcc/bin/ee-gcc.exe
CXX := wine $(SCE_EE)/gcc/bin/ee-gcc.exe
CRT0_S := $(SCE_WINE)/ee/lib/crt0.s
else
CC = $(SCE_EE_GCC)/bin/ee-gcc.exe
CXX = $(SCE_EE_GCC)/bin/ee-gcc.exe
CRT0_S := $(SCE_EE)/lib/crt0.s
endif

# shared for both c/c++ compilation
BASEFLAGS = -G0 -fno-common

ifeq ($(CONFIG),debug)
	BASEFLAGS += -O0 -g
endif

ifeq ($(CONFIG),release)
	BASEFLAGS += -O2
endif

# :( have to duplicate the rule
crt0.o: $(CRT0_S)
	$(CC) -c -xassembler-with-cpp $(CCFLAGS) $< -o $@

%.o: %.s
	$(CC) -c -xassembler-with-cpp $(CCFLAGS) $< -o $@


%.o: %.c
	$(CC) -c $(CXXFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
