CC=g++
CPPFLAGS=-isystem gtest/include
CFLAGS=-g -Wall -Wextra -pthread -lpthread
DEPS=Compiled/Tile-Test.o ../Compiled/Tile.o Compiled/Board-Test.o ../Compiled/Board.o ../Compiled/Move.o ../Compiled/Coord.o ../Compiled/Fuzzy-Test.o ../Compiled/FuzzyLogic.o
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	GTEST_DEPS=gtest/gtest_main.a
endif
ifeq ($(UNAME_S), Darwin)
	GTEST_DEPS=gtest/gtest_main_mac.a
endif


default:
	mkdir -p Compiled
	$(MAKE) -C ./Core
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPS) $(GTEST_DEPS) -o tests
	./tests --gtest_output=xml:test_result.xml

clean:
	$(MAKE) -C ./Core -f Makefile clean
	rm -rf Compiled/*
