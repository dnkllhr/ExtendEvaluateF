CC=g++
CFLAGS=-Wall -g -std=c++14
DEPS=Coord.h Move.h BoardManager.h
CLEAN=*.o

BoardManager.o: BoardManager.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f BoardManager.o ../../Compiled/BoardManager.o

clean:
	rm -rf $(CLEAN)
