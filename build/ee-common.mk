include build/sce-common.mk

ifeq ($(WINE),y)
CC := wine $(SCE_EE)/gcc/bin/ee-gcc.exe
CXX := wine $(SCE_EE)/gcc/bin/ee-gcc.exe
CRT0_S := $(SCE_WINE)/ee/lib/crt0.s
else
CC := $(SCE_EE_GCC)/bin/ee-gcc.exe
CXX := $(SCE_EE_GCC)/bin/ee-gcc.exe
CRT0_S := $(SCE_EE)/lib/crt0.s
endif


# Scary Make Incantations: Volume 1
OBJS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(filter %.cpp,$(notdir $(SRCS))))
OBJS += $(patsubst %.c,$(OBJDIR)/%.o,$(filter %.c,$(notdir $(SRCS))))
OBJS += $(patsubst %.s,$(OBJDIR)/%.o,$(filter %.s,$(notdir $(SRCS))))

# shared for both c/c++ compilation
BASEFLAGS := -G0 -fno-common

ifeq ($(CONFIG),debug)
BASEFLAGS += -O2 -g
endif

ifeq ($(CONFIG),release)
BASEFLAGS += -O2
endif

$(OBJDIR)/%.o: %.s
	$(CC) -c -xassembler-with-cpp $(CCFLAGS) $< -o $@

$(OBJDIR)/%.o: %.c
	$(CC) -c $(CCFLAGS) $< -o $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@