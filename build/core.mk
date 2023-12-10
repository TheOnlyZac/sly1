# Core make entrypoint, used to unify/clean up rules
#
# NAME=NAME
# TARGET=ee|iop
# TARGETTYPE=bin|lib|irx
# SRCS = sources...

# TODO: Other configurations if possible
debug_Valid := y
#debugopt_Valid := y
release_Valid := y

# There's probably a slightly better detection heuristic
# but this one seems to work more than well enough
ifneq ($(OS),Windows_NT)
WINE := y
else
WINE := n
endif

ifeq ($(CONFIG),)
CONFIG := debug
endif

ifneq ($($(CONFIG)_Valid),y)
$(error Invalid configuration)
endif

# Moved here since it doesn't really have to be specified in the target common file.
OBJDIR := obj/$(CONFIG)

include build/$(TARGET)-$(TARGETTYPE).mk

# Make targets for allowing "only compile/only remove this object file" workflows
# Useful for decompilation tooling that wants to use this.
.PHONY: objonly objflush

ifeq ($(COMPILEME),)
# Running these targets without a object file to compile is a logic error.
objonly:
	$(error No object file provided, please set the COMPILEME variable to the object file you want to compile.)
objflush:
	$(error No object file provided)
else
objonly: $(OBJDIR)/ $(OBJDIR)/$(COMPILEME)
	$(info $(OBJDIR)/$(COMPILEME))
objflush:
	$(RM) $(OBJDIR)/$(COMPILEME)
endif
