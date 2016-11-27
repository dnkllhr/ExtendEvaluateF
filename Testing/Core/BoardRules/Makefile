CC=g++
CFLAGS=-Wall -std=c++14 -g -Wextra -pthread -isystem ../../gtest/internal
DEPS=../../../Core/BoardRules/*.h
GTEST_HEADERS=../../gtest/*.h ../../gtest/internal/*.h
GTEST_DIR=../..
CLEAN=*.o

Board-Rules-Test.o: Board-Rules-Test.cpp $(DEPS) $(GTEST_HEADERS)
	$(CC) -I$(GTEST_DIR) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	cp -f Board-Rules-Test.o ../../Compiled/Board-Rules-Test.o

clean:
	rm -rf $(CLEAN)
