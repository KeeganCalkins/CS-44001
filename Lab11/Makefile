# file to build
source-1 = DecoratorDrink.cpp
source-2 = ChainDrink.cpp ChainDrink.hpp
source-3 = ObserverDrink.cpp ObserverDrink.hpp

# file to output
target-1 = decorator
target-2 = chain
target-3 = observer

compiler = g++

# compiler flags
flags = -std=c++17

# build file
build-1: 
	$(compiler) $(flags) $(source-1) -o $(target-1)
build-2: 
	$(compiler) $(flags) $(source-2) -o $(target-2)
build-3: 
	$(compiler) $(flags) $(source-3) -o $(target-3)

run1: build-1
	./$(target-1)

run2: build-2
	./$(target-2)

run3: build-3
	./$(target-3)

# "clean" and "test" are not produced by make
.PHONY: clean test

# delete built file
clean:
	rm -f $(target-1) $(target-2) $(target-3)