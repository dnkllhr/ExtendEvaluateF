default:
	$(MAKE) -C ./Tiles
	$(MAKE) -C ./BoardRules

tests:
	$(MAKE) -C ./Tiles -f Makefile tests
	$(MAKE) -C ./BoardRules -f Makefile tests

clean:
	$(MAKE) -C ./Tiles -f Makefile clean
	$(MAKE) -C ./BoardRules -f Makefile clean
