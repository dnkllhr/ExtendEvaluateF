default:
	mkdir -p Compiled
	$(MAKE) -C ./Core

tests:
	mkdir -p Compiled
	$(MAKE) -C ./Core -f Makefile tests
	$(MAKE) -C ./Testing

test-clean:
	$(MAKE) -C ./Testing -f Makefile clean

clean:
	$(MAKE) -C ./Core -f Makefile clean
	$(MAKE) -C ./Testing -f Makefile clean
	rm -rf Compiled/*
