CC=g++
CFLAGS=-Wall -std=c++14 -g -D__testing -Wextra -pthread -isystem ../../gtest/internal
DEPS=../../../Core/Board/*.h ../../../Core/BoardManager/*.h
GTEST_HEADERS=../../gtest/*.h ../../gtest/internal/*.h
GTEST_DIR=../..
CLEAN=*.o

Board-Test.o: Board-Test.cpp $(DEPS) $(GTEST_HEADERS)
	$(CC) -I$(GTEST_DIR) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	cp -f Board-Test.o ../../Compiled/Board-Test.o

clean:
	rm -rf $(CLEAN)
