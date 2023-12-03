CC = wine $(EE)/gcc/bin/ee-gcc
CFLAGS = -Wall -Wno-unused -g -I$(IDIR) -I$(EEIDIR) -I$(GPPIDIR)
TARGET = SCUS_971.98

SCE = /usr/local/sce
EE = $(SCE)/ee
GCC = $(EE)/gcc
TLIB = $(SCE)/tlib_255

SRCS = $(wildcard $(SDIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)
CRT0 = $(GCC)/ee/lib/crt0.o

SDIR = src/P2
IDIR = src/P2
EEIDIR = $(GCC)/ee/include
GPPIDIR = $(GCC)/include/g++-2
LIBDIR = lib

#LDSCRIPT = -T$(EE)/lib/relapp.cmd
LDSCRIPT = -T$(EE)/lib/relapp.cmd
LDFLAGS = -L$(LIBDIR) -lsn -lc -lm -lkernl

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(CRT0) $(LDSCRIPT) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -f $(OBJS) $(TARGET)
