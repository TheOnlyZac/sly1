# SCE common paths

SCE = C:/usr/local/sce

# Unfortunately winepath emits a name that make chokes on
# with a very cryptic error, so we have to hardcode wine's
# drive_c here.
SCE_WINE = $(HOME)/.wine/drive_c/usr/local/sce

SCE_COMMON = $(SCE)/common
SCE_EE = $(SCE)/ee
SCE_IOP = $(SCE)/iop

SCE_EE_GCC = $(SCE_EE)/gcc
SCE_IOP_GCC = $(SCE_IOP)/gcc
