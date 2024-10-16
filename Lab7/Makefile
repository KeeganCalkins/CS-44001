# file to build
sources = testHashmapUpdated.cpp hashmap.hpp 

# file to output
target = hashmap

compiler = g++

# compiler flags
flags = -std=c++17

# build file
build: 
	$(compiler) $(flags) $(sources) -o $(target)

run: build
	./$(target)

# "clean" and "test" are not produced by make
.PHONY: clean test

# delete built file
clean:
	rm -f $(target)