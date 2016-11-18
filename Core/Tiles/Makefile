CC=g++
CFLAGS=-Wall -std=c++14
DCFLAGS=-g -Dtesting
DEPS=Tile.h TerrainType.h TileType.h PreyType.h TileStack.h
CLEAN=*.o

default: Tile.o TileStack.o

tests: Tile-Test.o TileStack-Test.o

Tile.o: Tile.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f Tile.o ../../Compiled/Tile.o

Tile-Test.o: Tile.cpp $(DEPS)
	$(CC) $(CFLAGS) $(DCFLAGS) -c $< -o $@
	cp -f Tile-Test.o ../../Compiled/Tile.o

TileStack.o: TileStack.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f TileStack.o ../../Compiled/TileStack.o

TileStack-Test.o: TileStack.cpp $(DEPS)
	$(CC) $(CFLAGS) $(DCFLAGS) -c $< -o $@
	cp -f TileStack-Test.o ../../Compiled/TileStack.o

clean:
	rm -rf $(CLEAN)
