# file to build
source-1 = logger.cpp
source-2 = templateMethodGames.cpp

# file to output
target-1 = logger
target-2 = games

compiler = g++

# compiler flags
flags = -std=c++17

# build file
build-1: 
	$(compiler) $(flags) $(source-1) -o $(target-1)
build-2: 
	$(compiler) $(flags) $(source-2) -o $(target-2)

logger: build-1
	./$(target-1)

games: build-2
	./$(target-2)

# "clean" and "test" are not produced by make
.PHONY: clean test

# delete built file
clean:
	rm -f $(target)