#
#  Makefile
#  FullBacano
#
#  Compiles the DSP engine of the FullBacano filter as a static library
#
#  Created by Rafael Vega on 2011-11-10.
#

# Parameters
COMPILER = g++
LINKER = ar
COMPILER_FLAGS = -Wall -g -c -I../include
LINKER_FLAGS = rcs
CPP_FILES = $(wildcard *.cpp)
OBJECTS = $(notdir $(CPP_FILES:.cpp=.o)) # List of .cpp files with .o extension

# make the library by default
all: library

# Link library
library: $(OBJECTS)
	$(LINKER) $(LINKER_FLAGS) ../bin/libfullbacano.a $(OBJECTS)

# Compile all cpp files into their own .o file
%.o: %.cpp
	$(COMPILER) $(COMPILER_FLAGS) $*.cpp -o $*.o

# Clean
.PHONY: clean
clean:
	-rm *.o
	-rm ../bin/libfullbacano.a
