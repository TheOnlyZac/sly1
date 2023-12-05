# Core make entrypoint, used to unify/clean up rules
#
# NAME=NAME
# TARGET=ee|iop
# TARGETTYPE=bin|lib|irx
# SRCS = sources...

# TODO: Other configurations if possible
debug_Valid := y
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

include build/$(TARGET)-$(TARGETTYPE).mk

