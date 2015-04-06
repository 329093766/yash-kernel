#ifndef __SYSTEM_H
#define __SYSTEM_H

#define nullptr ((void *) 0UL)

#define SCREEN_BUFFER_HEIGHT 25
#define SCREEN_BUFFER_WIDTH 80
#define VGA_START 0xB8000

#define TABSIZE 8
#define BACKSPACE_CHAR 0x08
#define TAB_CHAR 0x09

typedef long size_t;
typedef unsigned long uintptr_t;

/** CORE UTILITIES */
extern void *memcpy(void *restrict dest, const void *restrict src, size_t count);
extern void *memset(void *dest, int val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
extern int strlen(const char *str);

extern unsigned char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);

/** VIDEO DRIVER */
void scroll();
void move_cursor();
void clear();
void put_char(char c);
void put_str(char *str);
void set_colour(unsigned char foreground, unsigned char background);
void init_video();

extern int kernel_main();

#endif // __SYSTEM_H