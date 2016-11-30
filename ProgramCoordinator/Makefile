CC=g++
CFLAGS=-Wall -std=c++14
DCFLAGS=-g -D__testing
DEPS=ProgramCoordinator.h ../ExternalPlayers/TurnCoordinator/TurnCoordinator.h
CLEAN=*.o

default: ExternalClient.o

#tests: ExternalClient-Test.o

ExternalClient.o: ExternalClient.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f ExternalClient.o ../Compiled/ExternalClient.o

#ProgramCoordinator-Test.o: ProgramCoordinator.cpp $(DEPS)
#	$(CC) $(CFLAGS) $(DCFLAGS) -c $< -o $@
#	cp -f ProgramCoordinator-Test.o ../Compiled/ProgramCoordinator.o

clean:
	rm -rf $(CLEAN)
