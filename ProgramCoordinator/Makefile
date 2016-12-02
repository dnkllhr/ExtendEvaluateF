CC=g++
CFLAGS=-Wall -std=c++14 -pthread -lpthread
DCFLAGS=-g -D__testing
DEPS=ProgramCoordinator.h ../ExternalPlayers/TurnCoordinator/TurnCoordinator.h
CLEAN=*.o CmdServer ExternalClient DaveServer

default: ExternalClient DaveServer CmdServer

tests: ExternalClient DaveServer CmdServer

CmdServer: CmdServer.cpp
	$(CC) $(CFLAGS) $< -o $@

DaveServer: DaveServer.cpp
	$(CC) $(CFLAGS) $< -o $@

ExternalClient: ExternalClient.cpp $(DEPS)
	$(CC) $(CFLAGS) $(DCFLAGS) $< -o $@
	cp -f ExternalClient ../ExternalClient

#ProgramCoordinator-Test.o: ProgramCoordinator.cpp $(DEPS)
#	$(CC) $(CFLAGS) $(DCFLAGS) -c $< -o $@
#	cp -f ProgramCoordinator-Test.o ../Compiled/ProgramCoordinator.o

clean:
	rm -rf $(CLEAN)
