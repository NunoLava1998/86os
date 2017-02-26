
struct gdt_t {
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_medium;
	unsigned char access_byte;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__ ((packed));

struct gdtp {
	unsigned short limit;
	unsigned int base;
} __attribute__ ((packed));

struct gdt_t gdt_table[5];
struct gdtp gdtptr;

void make_gdt_entry(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char granularity) {
	gdt_table[num].limit_low = limit;
	gdt_table[num].base_low = base;
	gdt_table[num].base_medium = (base >> 16);
	gdt_table[num].base_high = (base >> 24);
	gdt_table[num].limit_low = limit;
	gdt_table[num].granularity = ((limit >> 16) & 0x0F) | (granularity & 0xF0);
	gdt_table[num].access_byte = access;
}

extern void gdt_flush(void);


void load_gdt(void) {
	make_gdt_entry(0, 0, 0, 0, 0); // Null segment.
	make_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
	make_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
	make_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // Usermode code segment
	make_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // Usermode data segment
	
	gdt_flush();
}