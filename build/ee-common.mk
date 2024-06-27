include build/sce-common.mk

ifeq ($(WINE),y)
CC := wine $(SCE_EE)/gcc/bin/ee-gcc.exe
CXX := wine $(SCE_EE)/gcc/bin/ee-gcc.exe
CRT0_S := $(SCE_WINE)/ee/lib/crt0.s
AS := wine $(SCE_WINE)/ee/bin/ee-as.exe
else
CC := $(SCE_EE_GCC)/bin/ee-gcc.exe
CXX := $(SCE_EE_GCC)/bin/ee-gcc.exe
CRT0_S := $(SCE_EE)/lib/crt0.s
AS := $(SCE_EE)/bin/ee-as.exe
endif

# Rewrite the object files to maintain directory structure
OBJS := $(patsubst $(SDIR)/%,$(OBJDIR)/%,$(SRCS:.cpp=.o))
OBJS := $(patsubst $(SDIR)/%,$(OBJDIR)/%,$(OBJS:.c=.o))

# shared for both c/c++ compilation
BASEFLAGS := -G0 -fno-common

ifeq ($(CONFIG),debug)
BASEFLAGS += -O2 -g
endif

ifeq ($(CONFIG),release)
BASEFLAGS += -O2
endif

$(OBJDIR)/%.o: %.s
	mkdir -p $(@D)
	$(CC) -c -xassembler-with-cpp $(CCFLAGS) $< -o $@

$(OBJDIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) -x c++ -c $(CCFLAGS) $< -o $@

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) -c $(CXXFLAGS) $< -o $@
