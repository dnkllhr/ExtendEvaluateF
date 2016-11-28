CC=g++
CFLAGS=-Wall -std=c++14 -Wextra -pedantic
DCFLAGS=-g -D__testing
DEPS=../Tiles/Tile.h ../Tiles/TerrainType.h ../Tiles/TileType.h ../Tiles/PreyType.h ../Tiles/TileStack.h Regions.h Rules.h
CLEAN=*.o

default: Regions.o Rules.o

tests: Regions-Test.o Rules-Test.o

Regions.o: Regions.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f Regions.o ../../Compiled/Regions.o

Regions-Test.o: Regions.cpp $(DEPS)
	$(CC) $(CFLAGS) $(DCFLAGS) -c $< -o $@
	cp -f Regions-Test.o ../../Compiled/Regions.o

Rules.o: Rules.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f Rules.o ../../Compiled/Rules.o

Rules-Test.o: Rules.cpp $(DEPS)
	$(CC) $(CFLAGS) $(DCFLAGS) -c $< -o $@
	cp -f Rules-Test.o ../../Compiled/Rules.o

clean:
	rm -rf $(CLEAN)
