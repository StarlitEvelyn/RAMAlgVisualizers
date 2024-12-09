# Compiler and flags
CC = gcc
CFLAGS = -Wall -g
RM = rm -f
ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXE_EXT = .exe
else
    EXE_EXT =
endif

# Targets
TARGETS = fifo lru
OBJECTS = $(addsuffix $(EXE_EXT), $(TARGETS))

.PHONY: all clean fifo lru

# Default target: Build all executables
all: $(OBJECTS)

# Build FIFO
fifo$(EXE_EXT): fifo.c
	$(CC) $(CFLAGS) -o $@ $<

# Build LRU
lru$(EXE_EXT): lru.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean up build artifacts
clean:
	$(RM) $(OBJECTS)
