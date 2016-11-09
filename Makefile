default:
	mkdir -p Compiled
	$(MAKE) -C ./Core

test:
	$(MAKE) -C ./Testing 

test-clean:
	$(MAKE) -C ./Testing -f Makefile clean

clean:
	$(MAKE) -C ./Core -f Makefile clean
	rm -rf Compiled/*
