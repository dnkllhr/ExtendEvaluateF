default:
	mkdir -p Compiled
	$(MAKE) -C ./Core
	$(MAKE) -C ./ExternalPlayers
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
	rm -rf Compiled/*
