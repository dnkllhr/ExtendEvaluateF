CC=g++
CFLAGS=-Wall -std=c++14 -g -Wextra -pthread -isystem ../../gtest/internal
DEPS=../../../Core/Board/Board.h
GTEST_HEADERS=../../gtest/*.h ../../gtest/internal/*.h
GTEST_DIR=../..
CLEAN=*.o

Board-Test.o: Board-Test.cpp $(DEPS) $(GTEST_HEADERS)
	$(CC) -I$(GTEST_DIR) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	cp -f Board-Test.o ../../../Compiled/Board-Test.o

clean:
	rm -rf $(CLEAN)
