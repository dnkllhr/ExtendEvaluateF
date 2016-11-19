CC=g++
CFLAGS=-Wall -g -std=c++14
DEPS=Board.h
CLEAN=*.o

Board.o: Board.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f Board.o ../../Compiled/

clean:
	rm -rf $(CLEAN)
