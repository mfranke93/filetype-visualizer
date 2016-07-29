# variables
CXX = g++
CXX_FLAGS = -Wall -std=c++11
LD_FLAGS = 

FILES = src/main.cpp src/io/filereader.cpp

# targets
.PHONY: all

all: main

main: $(FILES)
	$(CXX) $(CXX_FLAGS) $(LD_FLAGS) -o main $(FILES)
