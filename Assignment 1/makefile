# C Compiler
CC = gcc

# C Flags
#  -Wall	Turn on most warnings
#  -Wextra	Turns on most other warnings
#  -pedantic 	Ensure compliance with std
#  -std=c99	Use the C99 Standard
CFLAGS = -Wall -Wextra -std=c99 -pedantic

# Debugging Flags
#  -g3		Request highest level of GDB access
DFLAGS = -g3

# Target executable
TARGET = encode

all:
	$(CC) $(CFLAGS) -o $(TARGET).o $(TARGET).c

debug:
	$(CC) $(CFLAGS) $(DFLAGS) -o $(TARGET).o $(TARGET).c

clean:
	rm -r *.o *.o.*
