# cppWebSearch makefile
CC = g++

CFLAGS = -Wall -Wextra -g
# -I. look in current directory for header files
# -I/filepath look in specific directory for header files
# -L/filepath look in specific directory for libraries (binaries)
# -lwhatever Include specific library with name "whatever"
# -g debugging information


OBS = main.o cppWebSearch.o

all: test

test: $(OBS)
	$(CC) $(OBS) -o test



clean:
	rm *o 
