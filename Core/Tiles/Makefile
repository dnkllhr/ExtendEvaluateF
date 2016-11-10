CC=g++
CFLAGS=-Wall -g -std=c++14
DEPS=Tile.h TerrainType.h TileType.h
CLEAN=*.o

Tile.o: Tile.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -uf Tile.o ../../Compiled/Tile.o

clean:
	rm -rf $(CLEAN)
