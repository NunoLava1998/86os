#include "vga.h"

int x = 0;
int y = 0;
unsigned short int* vptr = (unsigned short int*)0xB8000;

void update_vptr(int x_format, int y_format) {
	x = x_format;
	y = y_format;
	vptr = (unsigned short int *)0xB8000 + (y * 80 + x);
}

void update_coord(unsigned short int* ptr) {
	unsigned int x_format = 0;
	unsigned int y_format = 0;
	y_format = ((unsigned int)ptr - 0xB8000) / 160;
	x_format = (((unsigned int)ptr - 0xB8000 - (y * 180) / 2));
	x = x_format;
	y = y_format;
}

void putc(char c, unsigned char bc, unsigned char fc) {
	update_vptr(x, y);
	update_coord((unsigned short int *)vptr);
	if (x >= 80 && y >= 25) {
		x = 0;
		y = 0;
		update_vptr(x, y);
	}
	if (x > 80) {
		if (y > 25) {
			x = 0;
			y = 0;
			update_vptr(x, y);
		} else {
			y++;
			x = 0;
			update_vptr(x, y);
		}
	}
	if (c == '\n') {
		if (y > 25) {
			x = 0;
			y = 0;
			update_vptr(x, y);
			return;
		} else {
			y++;
			x = 0;
			update_vptr(x, y);
			return;
		}
	}
	*vptr = (c | ((bc << 4) | (fc & 0x0F)) << 8);
	if (y > 25) {
		x = 0;
		y = 0;
		update_vptr(x, y);
	} else {
		if (x < 80) {
			x++;
			update_vptr(x, y);
		} else {
			y++;
			x = 0;
			update_vptr(x, y);
		}
	}
}

void puts(const char* s, unsigned char bc, unsigned char fc) {
	unsigned int size = 0;
	while(s[size] != '\0') {
		size++;
	}
	for (unsigned int i = 0; i < size; i++) {
		putc(s[i], bc, fc);
	}
}