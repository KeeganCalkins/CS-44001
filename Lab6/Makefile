# file to build
sources1 = lemons.cpp
sources2 = oranges.cpp
sources3 = apples.cpp
sources4 = peaches.cpp

# file to output
target1 = lemons

target2 = oranges

target3 = apples

target4 = peaches

compiler = g++

# compiler flags
flags = -std=c++17

# build file
build1: 
	$(compiler) $(flags) $(sources1) -o $(target1)

lemons: build1
	./$(target1)

build2: 
	$(compiler) $(flags) $(sources2) -o $(target2)

oranges: build2
	./$(target2)

build3: 
	$(compiler) $(flags) $(sources3) -o $(target3)

apples: build3
	./$(target3)

build4: 
	$(compiler) $(flags) $(sources4) -o $(target4)

peaches: build4
	./$(target4)

# "clean" and "test" are not produced by make
.PHONY: clean test

# delete built file
clean:
	rm -f $(target1) $(target2)	$(target3) $(target4)