CC=g++
CFLAGS=-Wall -std=c++14
DCFLAGS=-g -Dtesting
DEPS=ProgramCoordinator.h ../ExternalPlayers/TurnCoordinator/TurnCoordinator.h
CLEAN=*.o

default: ProgramCoordinator.o

tests: ProgramCoordinator-Test.o

ProgramCoordinator.o: ProgramCoordinator.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f ProgramCoordinator.o ../Compiled/ProgramCoordinator.o

ProgramCoordinator-Test.o: ProgramCoordinator.cpp $(DEPS)
	$(CC) $(CFLAGS) $(DCFLAGS) -c $< -o $@
	cp -f ProgramCoordinator-Test.o ../Compiled/ProgramCoordinator.o

clean:
	rm -rf $(CLEAN)
