NAME := SCUS_971.98
TARGET := ee
TARGETTYPE := bin

SDIR = src/P2
IDIR = include
VPATH := $(SDIR)
SRCS := $(wildcard $(SDIR)/*.cpp)

# Custom compiler flags
CCDEFINES := -D__BUILD_USER=\"$(USER)\"
CCINCLUDES = -I$(SCE_COMMON)/include -I$(SCE_EE)/include -I$(IDIR)
CCFLAGS = -Wall -Wno-unused $(BASEFLAGS) -fno-strict-aliasing $(CCINCLUDES) $(CCDEFINES)
CXXFLAGS = $(CCFLAGS)
LDLIBS = -L$(SCE_EE)/lib -lsn -lc -lm -lpad -lmpeg -ldma -lipu -lkernl
LDFLAGS = -nostartfiles -Wl,-Map,../../$(OUTDIR)/$(NAME).map -T$(SCE_EE)/lib/app.cmd $(LDLIBS)


include build/core.mk

.PHONY: all clean clean-products

all: $(OUTDIR)/$(NAME)

clean: clean-products
	$(RM) -f $(OUTDIR)/*$(NAME).map $(SDIR)/*.o
