
#include "../prototypes.h"

// For now, inb, outb and hw_wait is needed.
// We'll define it now.

unsigned char inb(unsigned short port) {
	unsigned char return_value;
	__asm__ __volatile__ ("inb %1, %0" : "=a"(return_value) : "Nd"(port));
	return return_value;
}

void outb(unsigned short port, unsigned char value) {
	__asm__ __volatile__ ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void hw_wait(void) {
	__asm__ __volatile__ ("jmp 1f\n\t"
						  "1: jmp 2f\n\t"
						  "2: " );
}

void clear_mask(unsigned char irq) {
	unsigned short port;
	unsigned char value;
	if (irq < 8) {
		port = 0x21;
	} else {
		port = 0xA1;
		irq -= 8;
	}
	value = inb(port) & ~(1 << irq);
	outb(port, value);
}

void pic_initialize(void) {
	
	unsigned char mask_1 = inb(0x21);
	unsigned char mask_2 = inb(0xA1);
	
	outb(0x20, 0x11);
	hw_wait();
	outb(0xA0, 0x11);
	hw_wait();
	outb(0x21, 0x20);
	hw_wait();
	outb(0xA1, 0x28);
	hw_wait();
	outb(0x21, 4);
	hw_wait();
	outb(0xA1, 2);
	hw_wait();
	outb(0x21, 0x01);
	hw_wait();
	outb(0xA1, 0x01);
	hw_wait();
	outb(0x21, mask_1);
	outb(0xA1, mask_2);
}

void pic_start(void) {
	pic_initialize();
	unsigned short port = 0x21;
	unsigned char value = inb(0x21) & ~(1 << (unsigned char)0x00);
	outb(port, value);
	value = inb(0x21) & ~(1 << (unsigned char)0x01);
	outb(port, value);
}