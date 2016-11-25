default:
	mkdir -p Compiled
	$(MAKE) -C ./Core
	$(MAKE) -C ./Common

tests:
	mkdir -p Compiled
	$(MAKE) -C ./Core -f Makefile tests
	$(MAKE) -C ./Common -f Makefile tests
	$(MAKE) -C ./Testing

test-clean:
	$(MAKE) -C ./Testing -f Makefile clean

clean:
	$(MAKE) -C ./Core -f Makefile clean
	$(MAKE) -C ./Common -f Makefile clean
	$(MAKE) -C ./Testing -f Makefile clean
	rm -rf Compiled/*
