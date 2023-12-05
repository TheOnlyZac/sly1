NAME := SCUS_971.98
TARGET := ee
TARGETTYPE := bin

SDIR = src/P2
VPATH := $(SDIR)
SRCS := $(wildcard $(SDIR)/*.cpp)

# Custom compiler flags
CCFLAGS = -Wall -Wno-unused $(BASEFLAGS) -fno-strict-aliasing -I$(SCE_COMMON)/include -I$(SCE_EE)/include -I$(SDIR)
CXXFLAGS = $(CCFLAGS)
LDFLAGS = -nostartfiles -Wl,-Map,../../$(OUTDIR)/$(NAME).map -T$(SCE_EE)/lib/app.cmd -L$(SCE_EE)/lib -lsn -lc -lm -lkernl


include build/core.mk

.PHONY: all clean clean-products

all: $(OUTDIR)/$(NAME)

clean: clean-products
	$(RM) -f $(OBJDIR)/$(NAME).map
