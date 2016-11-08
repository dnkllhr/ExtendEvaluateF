CC=g++
CFLAGS=-Wall -std=c++14
DEPS=Tile.h TerrainType.h TileType.h
CLEAN=*.o

Tile.o: Tile.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(CLEAN)
