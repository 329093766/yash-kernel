CC=gcc
C_FLAGS= -Wall -Wextra -pedantic -m32 -O0 -std=c99 -finline-functions -nostdinc -ffreestanding -Iincludes/
LD=ld

all: kernel
	rm -f *.o

kernel: yash.o yash.ld main.o vga.o
	${LD} -m elf_i386 -T yash.ld -o kernel *.o

%.o: src/%.c
	${CC} ${C_FLAGS} -c -o $@ $<

yash.o: yash.asm
	nasm -f elf32 yash.asm -o yash.o

clean:
	rm -f *.o kernel

run:
	qemu-system-i386 -kernel kernel