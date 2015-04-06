#include <system.h>

unsigned short *vga_memory;
int attribute = 0x0F;
int cursor_x = 0, cursor_y = 0;

void scroll() {
	unsigned blank = 0x20 | (attribute << 8);
	unsigned temp;

	// scroll up
	if (cursor_y >= SCREEN_BUFFER_HEIGHT) {
		temp = cursor_y - SCREEN_BUFFER_HEIGHT + 1;
		memcpy(vga_memory, vga_memory + temp * SCREEN_BUFFER_WIDTH, (SCREEN_BUFFER_HEIGHT - temp) * SCREEN_BUFFER_WIDTH * 2);
		memsetw(vga_memory + (SCREEN_BUFFER_HEIGHT - temp) * SCREEN_BUFFER_WIDTH, blank, SCREEN_BUFFER_WIDTH);
		cursor_y = SCREEN_BUFFER_HEIGHT - 1;
	}
}

void move_cursor() {
	unsigned temp = cursor_y * SCREEN_BUFFER_WIDTH + cursor_x;
	write_port(0x3D4, 14);
	write_port(0x3D5, temp >> 8);
	write_port(0x3D4, 15);
	write_port(0x3D5, temp);
}

void clear() {
	unsigned blank = 0x20 | (attribute << 8);

	for (int i = 0; i < SCREEN_BUFFER_HEIGHT; i++) {
		memsetw(vga_memory + i * SCREEN_BUFFER_WIDTH, blank, SCREEN_BUFFER_WIDTH);
	}

	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

void put_char(char c) {
	unsigned short *loc;
	unsigned attrib = attribute << 8;

	switch (c) {
		// backspace
		case BACKSPACE_CHAR:
			if (!cursor_x) cursor_x--;
			break;
		// tab
		case TAB_CHAR:
			cursor_x = (cursor_x + TABSIZE) & ~(TABSIZE - 1);
			break;
		// carriage return
		case '\r':
			cursor_x = 0;
			break;
		// newline
		case '\n':
			cursor_x = 0;
			cursor_y++;
			break;
		// space
		case ' ':
			loc = vga_memory + (cursor_y * SCREEN_BUFFER_WIDTH + cursor_x);
			*loc = c | attrib;
			cursor_x++;
			break;
	}
	if (cursor_x >= SCREEN_BUFFER_WIDTH) {
		cursor_x = 0;
		cursor_y++;
	}

	scroll();
	move_cursor();
}

void put_str(char *str) {
	size_t str_size = strlen(str);
	for (size_t i = 0; i < str_size; i++) {
		put_char(str[i]);
	}
}

void set_colour(unsigned char foreground, unsigned char background) {
	attribute = (background << 4) | (foreground & 0x0F);
}

void init_video() {
	vga_memory = (unsigned short*) VGA_START;
	clear();
	move_cursor();
}