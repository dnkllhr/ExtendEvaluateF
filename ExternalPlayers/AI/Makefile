CC=g++
CFLAGS=-Wall -std=c++14
DCFLAGS=-g -Dtesting
DEPS=FuzzyLogic.h AI.h
CLEAN=*.o

default: 
	AI.o FuzzyLogic.o

tests: 
	Fuzzy-Test.o AI-Test.o

AI.o: AI.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f AI.o ../../Compiled/AI.o

FuzzyLogic.o: FuzzyLogic.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	cp -f FuzzyLogic.o ../../Compiled/FuzzyLogic.o

AI-Test.o: AI.cpp $(DEPS)
	$(CC) $(CFLAGS) $(DCFLAGS) -c $< -o $@
	cp -f AI-Test.o ../../Compiled/AI.o

Fuzzy-Test.o: Fuzzy-Test.cpp $(DEPS)
	$(CC) $(CFLAGS) $(DCFLAGS) -c $< -o $@
	cp -f Fuzzy-Test.o ../../Compiled/FuzzyLogic.o

clean:
	rm -rf $(CLEAN)
