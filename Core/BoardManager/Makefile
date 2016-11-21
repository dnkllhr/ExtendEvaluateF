CC=g++
CFLAGS=-Wall -std=c++14
DCFLAGS=-g -Dtesting
DEPS=../Tiles/Tile.h ../Tiles/TerrainType.h ../Tiles/TileType.h ../Tiles/PreyType.h ../Board/Board.h ../BoardRules/Rules.h Coord.h Move.h BoardManager.h
CLEAN=*.o

default: BoardManager.o

tests: BoardManager-Test.o

BoardManager.o: BoardManager.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f BoardManager.o ../../Compiled/BoardManager.o

BoardManager-Test.o: BoardManager.cpp $(DEPS)
	$(CC) $(CFLAGS) $(DCFLAGS) -c $< -o $@
	cp -f BoardManager-Test.o ../../Compiled/BoardManager.o

clean:
	rm -rf $(CLEAN)
