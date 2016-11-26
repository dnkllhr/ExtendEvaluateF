CC=g++
CPPFLAGS=-isystem gtest/include
CFLAGS=-g -Wall -Wextra -pthread -lpthread
DEPS=Compiled/Tile-Test.o ../Compiled/Tile.o ../Compiled/TileStack.o ../Compiled/Board.o Compiled/Board-Test.o ../Compiled/BoardManager.o ../Compiled/Move.o ../Compiled/Coord.o ../Compiled/Rules.o ../Compiled/Regions.o Compiled/Fuzzy-Test.o ../Compiled/FuzzyLogic.o Compiled/BoardManager-Test.o
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
	$(MAKE) -C ./ExternalPlayers
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPS) $(GTEST_DEPS) -o tests
	./tests --gtest_output=xml:test_result.xml || /bin/true

clean:
	$(MAKE) -C ./Core -f Makefile clean
	$(MAKE) -C ./ExternalPlayers -f Makefile clean
	rm -rf Compiled/*
