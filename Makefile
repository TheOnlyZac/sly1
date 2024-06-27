NAME := SCUS_971.98
TARGET := ee
TARGETTYPE := bin

ASM_PATH 	:= asm/
ASSET_PATH 	:= assets/
SPLAT_C_PATH := src/
ASMS := $(shell find $(ASM_PATH) -name '*.s')

SDIR = src/P2
IDIR = include
VPATH := $(SDIR)
SRCS := $(shell find $(SDIR) -name '*.cpp' -or -name '*.c')

# Output
LDSCRIPTS := -T ../../sly1.ld -T ../../config/undefined_syms_auto.txt -T ../../config/undefined_funcs_auto.txt

# Splat configuration
PYTHON          ?= python3
SPLAT           ?= $(PYTHON) -m splat split
SPLAT_YAML      ?= config/sly1.yaml

# Custom compiler flags
CCDEFINES := -D__BUILD_USER=\"$(USER)\"
CCINCLUDES = -I$(IDIR) -I$(SCE_COMMON)/include -I$(SCE_EE)/include

CCFLAGS = -Wall -Wno-unused $(BASEFLAGS) -fno-strict-aliasing $(CCINCLUDES) $(CCDEFINES)
CXXFLAGS = $(CCFLAGS)

LDLIBS = -L$(SCE_EE)/lib -lsn -lc -lm -lpad -lmpeg -ldma -lipu -lkernl
LDFLAGS = -fuse-ld=mold -nostartfiles $(LDSCRIPTS) $(LDLIBS)

include build/core.mk #!-------- core.mk

#* Phony targets
.PHONY: all extract clean clean-products

#* `make all` - builds the final ELF
all: $(OUTDIR)/$(NAME)

#* `make clean` - removes build artifacts
clean: clean-products
	$(RM) -f $(OUTDIR)/*$(NAME).map $(SDIR)/*.o
	$(RM) -rf $(ASM_PATH) $(ASSET_PATH) $(SPLAT_C_PATH) $(LD_SCRIPT)

#* `make extract` - runs splat to extract the assets
extract:
	$(RM) -r asm/ $(LD_SCRIPT)
	$(SPLAT) $(SPLAT_YAML) $(SPLAT_FLAGS)
