default:
	$(MAKE) -C ./Tiles
	$(MAKE) -C ./Board
	$(MAKE) -C ./BoardRules
	$(MAKE) -C ./BoardManager
	$(MAKE) -C ./Entry-Points

tests:
	$(MAKE) -C ./Tiles -f Makefile tests
	$(MAKE) -C ./Board -f Makefile tests
	$(MAKE) -C ./BoardRules -f Makefile tests
	$(MAKE) -C ./BoardManager -f Makefile tests
	$(MAKE) -C ./Entry-Points -f Makefile tests

clean:
	$(MAKE) -C ./Tiles -f Makefile clean
	$(MAKE) -C ./Board -f Makefile clean
	$(MAKE) -C ./BoardRules -f Makefile clean
	$(MAKE) -C ./BoardManager -f Makefile clean
	$(MAKE) -C ./Entry-Points -f Makefile clean
