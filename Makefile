src = $(wildcard src/*.c)
c_flags = -Iincludes/ -m32

all:
	nasm -f elf32 yash.asm -o yash.o
	gcc ${c_flags} -c ${src} -o yashc.o
	ld -m elf_i386 -T yash.ld -o kernel yash.o yashc.o

run:
	qemu-system-i386 -kernel kernel