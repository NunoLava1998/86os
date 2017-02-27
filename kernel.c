
#include <prototypes.h>

void kmain(void) {
	load_gdt();
	load_idt();
	pic_start();
	for(;;);
}