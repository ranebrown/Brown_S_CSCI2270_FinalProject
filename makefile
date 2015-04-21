# cppWebSearch makefile

# Compiler to use
CC = clang++

# Compiler flags
CFLAGS = -Wall -Wextra -g
	# -g debugging information

# Include paths for header files
INCLUDES = -I. -I/Users/Rane/Documents/Programming/Libraries/boost_1_57_0
	# -I. looks in current directory for header files

# Paths to required libraries
LFLAGS = -L/Users/Rane/Documents/Programming/Libraries/boost_1_57_0/stage/lib -L/usr/local/lib -L/Users/Rane/Documents/Programming/Libraries/cpp-netlib-0.11.1-final

# The specific libraries that project depends on
LIBS = -lboost_system -lboost_thread -lcppnetlib-uri -lcppnetlib-client-connections -lssl -lcrypto 

# All source files
SRCS = main.cpp cppWebSearch.cpp

# All object files
OBJS = $(SRCS:.cpp=.o)
	# Uses macro to replace extension of all source files

# name of executable
MAIN = test

# following section is generic

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)	

# Automatically builds all object files from source files
# -c option compiles but does not link (create object files)
# -o is output filename
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

# This is used in case there is a file named clean 
.PHONY: clean
clean:
	rm *.o $(MAIN)

