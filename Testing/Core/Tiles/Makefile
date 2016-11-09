CC=g++
CFLAGS=-Wall -std=c++14 -g -Wextra -pthread -isystem ../../gtest/internal
DEPS=../../../Core/Tiles/*.h
GTEST_HEADERS=../../gtest/*.h ../../gtest/internal/*.h
GTEST_DIR=../..
CLEAN=*.o

Tile-Test.o: Tile-Test.cpp $(DEPS) $(GTEST_HEADERS)
	$(CC) -I$(GTEST_DIR) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	cp -uf Tile-Test.o ../../Compiled/Tile-Test.o

clean:
	rm -rf $(CLEAN)
