CC=g++
CFLAGS=-Wall -g -std=c++14
DEPS=Tile.h TerrainType.h TileType.h PreyType.h TileStack.h
CLEAN=*.o

default: Tile.o TileStack.o

Tile.o: Tile.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f Tile.o ../../Compiled/Tile.o

TileStack.o: TileStack.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f TileStack.o ../../Compiled/TileStack.o

clean:
	rm -rf $(CLEAN)
