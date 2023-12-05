include build/ee-common.mk

OBJS := $(OBJDIR)/crt0.o $(OBJS)
OUTDIR := bin/$(CONFIG)

# This incantation is done to avoid modifying the SCE linker scripts.
$(OUTDIR)/$(NAME): $(OBJDIR)/ $(OUTDIR)/ $(OBJS)
	cd $(OBJDIR)/ && $(CXX) $(CXXFLAGS) -o ../../$@ $(notdir $(OBJS)) $(LDFLAGS)

# :( have to duplicate the rule
$(OBJDIR)/crt0.o: $(CRT0_S)
	$(CC) -c -xassembler-with-cpp $(CCFLAGS) $< -o $@

$(OBJDIR)/:
	mkdir -p $@

$(OUTDIR)/: 
	mkdir -p $@

clean-products:
	$(RM) -f $(OBJS) $(OUTDIR)/$(NAME)
