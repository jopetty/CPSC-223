# C Compiler
CC = gcc

# C Flags
#  -Wall	Turn on most warnings
#  -Wextra	Turns on most other warnings
#  -pedantic 	Ensure compliance with std
#  -std=c99	Use the C99 Standard
CFLAGS = -Wall -Wextra -std=c99 -pedantic -Wstrict-prototypes

# Debugging Flags
#  -g3		Request highest level of GDB access
DFLAGS = -g3

# Release Flags
#  -O3	High levels of optimization
#  -Wunreachable-code	Warn when code cannot be reached
RFLAGS = -O3 -Wunreachable-code

# Target executable
TARGET = main

all:
	$(CC) $(CFLAGS) -o $(TARGET).o $(TARGET).c num.c

debug:
	$(CC) $(CFLAGS) $(DFLAGS) -o $(TARGET).o $(TARGET).c num.c

release:
	$(CC) $(RFLAGS) -o $(TARGET).o $(TARGET).c num.c

clean:
	rm -r *.o*
