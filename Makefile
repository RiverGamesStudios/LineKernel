all:

i386:
	cd i386; make

run-i386:
	cd i386; make run

clean:
	cd i386; make clean

.PHONY: all i386 run-i386 clean
