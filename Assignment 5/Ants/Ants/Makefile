# C Compiler
CC = gcc

# C Flags
CFLAGS = -Wall -Wextra -std=c99 -pedantic -Wstrict-prototypes -g3

# Target Executable
TARGET = ants

all: ants

ants:
	$(CC) $(CFLAGS) -o $(TARGET) main.c parser.c ant.c
