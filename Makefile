all:

i386:
	cd i386; make
	@echo "Made i386"

run-i386:
	cd i386; make run

check-i386:
	cd i386; make check

iso-i386:
	cd i386; make iso
	@echo "Made i386 iso"

run-iso-i386:
	qemu-system-i386 -cdrom i386/LineKernel.iso

clean:
	cd i386; make clean
	@echo "Cleaned up"

.PHONY: all i386 run-i386 check-i386 iso-i386 clean
