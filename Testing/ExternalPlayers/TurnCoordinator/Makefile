CC=g++
CFLAGS=-Wall -std=c++14 -g -D__testing -Wextra -pthread -isystem ../../gtest/internal
DEPS=../../../ExternalPlayers/TurnCoordinator/TurnCoordinator.h
GTEST_HEADERS=../../gtest/*.h ../../gtest/internal/*.h
GTEST_DIR=../..
CLEAN=*.o

TurnCoordinator-Test.o: TurnCoordinator-Test.cpp $(DEPS) $(GTEST_HEADERS)
	$(CC) -I$(GTEST_DIR) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	cp -f TurnCoordinator-Test.o ../../Compiled/TurnCoordinator-Test.o

clean:
	rm -rf $(CLEAN)
