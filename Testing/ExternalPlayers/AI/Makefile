CC=g++
CFLAGS=-Wall -std=c++14 -g -Wextra -pthread -isystem ../../gtest/internal
DEPS=../../../ExternalPlayers/FuzzyLogic.h
GTEST_HEADERS=../../gtest/*.h ../../gtest/internal/*.h
GTEST_DIR=../..
CLEAN=*.o

Fuzzy-Test.o: Fuzzy-Test.cpp $(DEPS) $(GTEST_HEADERS)
    $(CC) -I$(GTEST_DIR) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
    cp -f Tile-Test.o ../../Compiled/Fuzzy-Test.o

clean:
    rm -rf $(CLEAN)
