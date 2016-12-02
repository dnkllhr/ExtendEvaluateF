CC=g++
CPPFLAGS=-isystem gtest/include
CFLAGS=-g -Wall -Wextra -pthread -lpthread
DEPS=Compiled/Tile-Test.o ../Compiled/Tile.o ../Compiled/TileStack.o ../Compiled/Board.o Compiled/Board-Test.o ../Compiled/BoardManager.o Compiled/BoardManager-Test.o \
	../Compiled/Move.o ../Compiled/Coord.o ../Compiled/Rules.o ../Compiled/Regions.o Compiled/Fuzzy-Test.o ../Compiled/FuzzyLogic.o ../Compiled/TurnCoordinator.o \
	Compiled/TurnCoordinator-Test.o ../Compiled/AI.o Compiled/Board-Rules-Test.o
GTEST_DEPS=gtest/gtest_main.a


default:
	mkdir -p Compiled
	$(MAKE) -C ./Core
	$(MAKE) -C ./ExternalPlayers
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPS) $(GTEST_DEPS)  -o tests
	./tests --gtest_output=xml:test_result.xml || /bin/true

gtestlib:
	cd 
	$(MAKE) -C googletest-master/googletest/make gtest.a
	$(MAKE) -C googletest-master/googletest/make gtest_main.a
	cp googletest-master/googletest/make/gtest.a gtest/
	cp googletest-master/googletest/make/gtest_main.a gtest/


clean:
	$(MAKE) -C ./Core -f Makefile clean
	$(MAKE) -C ./ExternalPlayers -f Makefile clean
	rm -rf Compiled/*
