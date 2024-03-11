# This is HW1 makefile

CXX = g++  # the compiler
CXXFLAGS = -std=c++20 -Wall  # flags for the compiler (use c++17 standards, turn on all optional warnings); add -ggdb if you want to use gdb to debug!

# runs for "make all"
all: main

# note that lines below targets must be
# TABBED in (not spaces!)
	
Player.o: Player.cpp
	$(CXX) $(CXXFLAGS) -c Player.cpp

Game.o: Game.cpp
	$(CXX) $(CXXFLAGS) -c Game.cpp

# The commands : "make main" and "make all", compile the main executable

main: Player.o Game.o main.cpp
	$(CXX) $(CXXFLAGS) main.cpp Player.o Game.o -o main

# The command : "make test", compiles the test executable

test: Player.o Game.o test.cpp
	$(CXX) $(CXXFLAGS) test.cpp Player.o Game.o -o test

clean:
	rm Player.o Game.o Player Game Player.exe Game.exe main main.exe test test.exe
