#include <system.h>

extern void *memcpy(void *restrict dest, const void *restrict src, size_t count) {
	unsigned char *a = dest;
	unsigned char *b = src;
	for (size_t i = 0; i < count; i++) {
		a[i] = b[i];
	}
	return dest;
}

extern void *memset(void *dest, int val, size_t count) {
	unsigned char *a = dest;
	for (size_t i = 0; i < count; i++) {
		a[i] = (unsigned char) val;
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
	while (str[result] != (char) 0) {
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

int kernel_main() {
	init_video();
	set_colour(12, 0);
	put_str("testing 123");
	for (;;);
	return 0;
}