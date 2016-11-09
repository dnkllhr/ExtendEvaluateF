CC=g++
CPPFLAGS=-isystem gtest/include
CFLAGS=-g -Wall -Wextra -pthread -lpthread
GTEST_DEPS=gtest/gtest_main.a
DEPS=Compiled/Tile-Test.o ../Compiled/Tile.o

default:
	mkdir -p Compiled
	$(MAKE) -C ./Core
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPS) $(GTEST_DEPS) -o tests
	./tests --gtest_output=xml:test_result.xml

clean:
	$(MAKE) -C ./Core -f Makefile clean
	rm -rf Compiled/*
