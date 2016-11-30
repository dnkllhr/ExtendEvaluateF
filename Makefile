DEPS=Compiled/AI.o Compiled/Board.o Compiled/BoardManager.o Compiled/Coord.o Compiled/FuzzyLogic.o Compiled/Move.o Compiled/Regions.o Compiled/Rules.o Compiled/Tile.o Compiled/TileStack.o Compiled/TurnCoordinator.o Compiled/TurnCoordinator-Main.o

default:
	mkdir -p Compiled
	$(MAKE) -C ./Core
	$(MAKE) -C ./ExternalPlayers
	g++ -Wall -std=c++14 $(DEPS) -o GameInstance
	$(MAKE) -C ./ProgramCoordinator

tests:
	mkdir -p Compiled
	$(MAKE) -C ./Core -f Makefile tests
	$(MAKE) -C ./ExternalPlayers -f Makefile tests
	$(MAKE) -C ./ProgramCoordinator -f Makefile tests
	$(MAKE) -C ./Testing

test-clean:
	$(MAKE) -C ./Testing -f Makefile clean

clean:
	$(MAKE) -C ./Core -f Makefile clean
	$(MAKE) -C ./ExternalPlayers -f Makefile clean
	$(MAKE) -C ./ProgramCoordinator -f Makefile clean
	$(MAKE) -C ./Testing -f Makefile clean
	rm -rf Compiled/* GameInstance
