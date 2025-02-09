# file to build
source-1 = sort.cpp
source-2 = uselist.cpp list.hpp

# file to output
target-1 = sort
target-2 = list

compiler = g++

# compiler flags
flags = -std=c++17

# build file
build-1: 
	$(compiler) $(flags) $(source-1) -o $(target-1)
build-2: 
	$(compiler) $(flags) $(source-2) -o $(target-2)

run1: build-1
	./$(target-1)

run2: build-2
	./$(target-2)

# "clean" and "test" are not produced by make
.PHONY: clean test

# delete built file
clean:
	rm -f $(target-1) $(target-2)