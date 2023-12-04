# SCE paths
SCE := C:/usr/local/sce
EE := $(SCE)/ee
GCC := $(EE)/gcc

# There's probably a slightly better detection heuristic
# but this one seems to work more than well enough
ifneq ($(OS),Windows_NT)
CC := wine $(EE)/gcc/bin/ee-gcc.exe
# driver doesn't exist for some reason
CXX := wine $(EE)/gcc/bin/ee-gcc.exe
# Unfortunately winepath emits a name that make chokes on
# with a very cryptic error, so it has to be done like this :(
CRT0_S := $(HOME)/.wine/drive_c/usr/local/sce/ee/lib/crt0.s
else
CC = $(EE)/gcc/bin/ee-gcc.exe
CXX = $(EE)/gcc/bin/ee-gcc.exe
CRT0_S := $(EE)/lib/crt0.s
endif

TARGET = SCUS_971.98
TFLAGS = -G0 -fno-common

ASFLAGS = $(TFLAGS)
CFLAGS = -Wall -Wno-unused $(TFLAGS) -fno-strict-aliasing -g -I$(EE)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions
LDFLAGS = -nostartfiles -Wl,-Map,$(TARGET).map -T$(EE)/lib/relapp.cmd -L$(EE)/lib -lsn -lc -lm -lkernl

SDIR = src/P2

CFLAGS += -I$(SDIR)

SRCS = $(wildcard $(SDIR)/*.cpp)
OBJS = crt0.o $(SRCS:.cpp=.o)


.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDSCRIPT) $(LDFLAGS)

# :( have to duplicate the rule
crt0.o: $(CRT0_S)
	$(CC) -c -xassembler-with-cpp $(CCFLAGS) $< -o $@

%.o: %.s
	$(CC) -c -xassembler-with-cpp $(CCFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -f $(OBJS) $(TARGET) $(TARGET).map
