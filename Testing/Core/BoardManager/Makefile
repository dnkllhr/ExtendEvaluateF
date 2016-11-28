CC=g++
CFLAGS=-Wall -std=c++14 -g -D__testing -Wextra -pthread -isystem ../../gtest/internal
DEPS=../../../Core/Board/*.h ../../../Core/BoardManager/*.h
GTEST_HEADERS=../../gtest/*.h ../../gtest/internal/*.h
GTEST_DIR=../..
CLEAN=*.o

BoardManager-Test.o: BoardManager-Test.cpp $(DEPS) $(GTEST_HEADERS)
	$(CC) -I$(GTEST_DIR) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	cp -f BoardManager-Test.o ../../Compiled/BoardManager-Test.o

clean:
	rm -rf $(CLEAN)
