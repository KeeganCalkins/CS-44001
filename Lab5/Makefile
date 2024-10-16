# file to build
sources-1 = rosterMap.cpp
sources-2 = rosterSet.cpp

# file to output
target-1 = roster1

target-2 = roster2

compiler = g++

# compiler flags
flags = -std=c++17

# build file
build-1: 
	$(compiler) $(flags) $(sources-1) -o $(target-1)

run-1: build-1
	./$(target-1) cs1.txt cs2.txt cs3.txt cs4.txt dropouts.txt

build-2: 
	$(compiler) $(flags) $(sources-2) -o $(target-2)

run-2: build-2
	./$(target-2) cs1.txt cs2.txt cs3.txt cs4.txt dropouts.txt

# "clean" and "test" are not produced by make
.PHONY: clean test

# delete built file
clean:
	rm -f $(target)