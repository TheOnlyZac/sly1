CC = C:/usr/local/sce/ee/gcc/bin/ee-gcc
CFLAGS = -Wall -Wno-unused -g -I$(IDIR) -I$(SCEIDIR) -I$(GCCIDIR)

TARGET = SCUS_971.98

SRCS = $(wildcard $(SDIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

SDIR = src/P2
IDIR = src/P2
SCEIDIR = C:/usr/local/sce/ee/gcc/ee/include
GCCIDIR = C:/usr/local/sce/ee/gcc/include/g++-2

LINKSCRIPT 	= C:/usr/local/sce/ee/gcc/ee/lib/r5900.ld
LIBS 		= C:/usr/local/sce/ee/lib/libsn.a C:/usr/local/sce/ee/gcc/ee/lib/libc.a

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) -T $(LINKSCRIPT) -lm

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -f $(OBJS) $(TARGET)
