include build/ee-common.mk

OBJS := $(OBJDIR)/crt0.o $(OBJS)
OUTDIR := bin/$(CONFIG)

CRT0_S = $(ASM_PATH)sce/crt0.s

# This incantation is done to avoid modifying the SCE linker scripts.
$(OUTDIR)/$(NAME): $(OBJDIR)/ $(OUTDIR)/ $(OBJS)
	cd $(OBJDIR)/ && $(CXX) $(CXXFLAGS) -o ../../$@ $(OBJS:$(OBJDIR)/%=%) $(LDFLAGS)

# :( have to duplicate the rule
$(OBJDIR)/crt0.o: $(CRT0_S)
	@echo "Compiling $<"
	$(CC) -c -xassembler-with-cpp $(CCFLAGS) $(CRT0_S) -o $@

$(OBJDIR)/:
	mkdir -p $@

$(OUTDIR)/:
	mkdir -p $@

clean-products:
	$(RM) $(OBJS) $(OUTDIR)/*/$(NAME)
