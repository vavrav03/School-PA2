LD=g++
CXX=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -Wno-long-long -O2

all: prepare solution

solution: solution.o
	$(LD) $(CXXFLAGS) -o build/solution build/solution.o

solution.o: solution.cpp
	$(CXX) $(CXXFLAGS) -c -o build/solution.o solution.cpp

prepare:
	mkdir -p build

run: all
	./build/solution

clean:
	rm -r build