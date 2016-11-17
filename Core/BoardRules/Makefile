CC=g++
CFLAGS=-Wall -g -std=c++14
DEPS=../Tiles/Tile.h ../Tiles/TerrainType.h ../Tiles/TileType.h ../Tiles/PreyType.h ../Tiles/TileStack.h Regions.h Rules.h
CLEAN=*.o

default: Regions.o Rules.o

Regions.o: Regions.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f Regions.o ../../Compiled/Regions.o

Rules.o: Rules.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f Rules.o ../../Compiled/Rules.o

clean:
	rm -rf $(CLEAN)
