default:
	$(MAKE) -C ./AI
	$(MAKE) -C ./TurnCoordinator

tests:
	$(MAKE) -C ./AI -f Makefile tests
	$(MAKE) -C ./TurnCoordinator -f Makefile tests

clean:
	$(MAKE) -C ./AI -f Makefile clean
	$(MAKE) -C ./TurnCoordinator -f Makefile clean
