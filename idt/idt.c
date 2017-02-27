#include "../prototypes.h"



extern int default_isr(void);
extern int default_irq(void);

// From now on, memset is needed. 

void memset(void* bufptr, unsigned char value, int size) {
	unsigned char* buf = (unsigned char *)bufptr;
	for (int i = 0; i < size; i++) {
		buf[i] = value;
	}
}	

struct idt_t {
	unsigned short base_low;
	unsigned short selector;
	unsigned char unused;
	unsigned char flags;
	unsigned short base_high;
} __attribute__ ((packed));

struct idt_t idt_entry[256];

extern void lidt_core(unsigned long idtp);

void make_idt_entry(int num, unsigned long base, unsigned short selector, unsigned char flags) {
	idt_entry[num].base_low = base;
	idt_entry[num].base_high = (base >> 16);
	idt_entry[num].selector = selector;
	idt_entry[num].unused = 0;
	idt_entry[num].flags = flags;
}


void load_idt(void) {
	
	struct idt_p {
		unsigned short limit;
		unsigned long base;
	} __attribute__ ((packed));
	struct idt_p idtp;
	unsigned short size = sizeof(idt_entry);
	idtp.limit = (size * 256) - 1;
	idtp.base = (unsigned int)&idt_entry;
	
	memset(&idt_entry, '\0', 256);
	
	for (int i = 0; i < 32; i++) {
		make_idt_entry(i, (unsigned)default_isr, 0x08, 0x8E);
	}
	for (int i = 32; i < 48; i++) {
		make_idt_entry(i, (unsigned)default_irq, 0x08, 0x8E);
	}
	
	lidt_core((unsigned long)&idtp);
	
}
