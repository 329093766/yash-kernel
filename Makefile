CC=gcc
C_FLAGS= -m32 -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -std=c99 -g -Wall -fno-builtin -Iincludes/
LD=ld

all: kernel

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