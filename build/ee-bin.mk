include build/ee-common.mk #!-------- ee-common.mk

OBJS := $(OBJDIR)/crt0.o $(OBJS)
OUTDIR := out/$(CONFIG)

#CRT0_S = $(ASM_PATH)sce/crt0.s

# This incantation is done to avoid modifying the SCE linker scripts.
#* Rule to build the final ELF
$(OUTDIR)/$(NAME): $(OBJDIR)/ $(OUTDIR)/ $(OBJS)
	cd $(OBJDIR)/ && $(CXX) $(CXXFLAGS) -o ../../$@ $(OBJS:$(OBJDIR)/%=%) $(LDFLAGS)

# :( have to duplicate the rule for crt0.o
$(OBJDIR)/crt0.o: $(CRT0_S)
	$(CC) -c -xassembler-with-cpp $(CCFLAGS) $(CRT0_S) -o $@

#* Rule to create the object directory
$(OBJDIR)/:
	mkdir -p $@

#* Rule to ccreate the output directory
$(OUTDIR)/:
	mkdir -p $@

clean-products:
	$(RM) $(OBJS) $(OUTDIR)/*/$(NAME)
