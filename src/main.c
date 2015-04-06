#include <system.h>

extern unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count) {
	for (int i = 0; i < count; i++) {
		dest[i] = src[i];
	}
	return dest;
}

extern unsigned char *memset(unsigned char *dest, unsigned char val, int count) {
	for (int i = 0; i < count; i++) {
		dest[i] = val;
	}
	return dest;
}

extern unsigned short *memcpyw(unsigned short *dest, const unsigned short *src, int count) {
	for (int i = 0; i < count; i++) {
		dest[i] = src[i];
	}
	return dest;
}

extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count) {
	for (int i = 0; i < count; i++) {
		dest[i] = val;
	}
	return dest;
}

extern int strlen(const char *str) {
	int result = 0;
	while (str[result] != '\0') {
		result++;
	}
	return result;
}

extern unsigned char read_port(unsigned short port) {
	unsigned char res;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (res) : "dN" (port));
	return res;
}

extern void write_port(unsigned short port, unsigned char data) {
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}

void kernel_main() {
	for (;;);
}