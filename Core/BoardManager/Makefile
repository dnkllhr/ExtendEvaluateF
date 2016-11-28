CC=g++
CFLAGS=-Wall -std=c++14
DCFLAGS=-g -D__testing
DEPS=../Tiles/Tile.h ../Tiles/TerrainType.h ../Tiles/TileType.h ../Tiles/PreyType.h ../Board/Board.h ../BoardRules/Rules.h Coord.h Move.h BoardManager.h
CLEAN=*.o

default: BoardManager.o Move.o Coord.o

tests: BoardManager-Test.o Move-Test.o Coord-Test.o

BoardManager.o: BoardManager.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f BoardManager.o ../../Compiled/BoardManager.o

BoardManager-Test.o: BoardManager.cpp $(DEPS)
	$(CC) $(CFLAGS) $(DCFLAGS) -c $< -o $@
	cp -f BoardManager-Test.o ../../Compiled/BoardManager.o

Move.o: Move.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f Move.o ../../Compiled/Move.o

Move-Test.o: Move.cpp $(DEPS)
	$(CC) $(CFLAGS) $(DCFLAGS) -c $< -o $@
	cp -f Move-Test.o ../../Compiled/Move.o

Coord.o: Coord.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f Coord.o ../../Compiled/Coord.o

Coord-Test.o: Coord.cpp $(DEPS)
	$(CC) $(CFLAGS) $(DCFLAGS) -c $< -o $@
	cp -f Coord-Test.o ../../Compiled/Coord.o

clean:
	rm -rf $(CLEAN)
