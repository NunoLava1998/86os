
#ifndef _PROTOTYPES_H
#define _PROTOTYPES_H

extern int x;
extern int y;
extern unsigned short int* vptr;
extern void update_vptr(int, int);
extern void scroll(void);
extern void putc(char, unsigned char, unsigned char);
extern void puts(const char*, unsigned char, unsigned char);
extern void make_gdt_entry(int, unsigned long, unsigned long, unsigned char, unsigned char);
extern void gdt_flush(void);
extern void load_gdt(void);
extern int default_isr(void);
extern int default_irq(void);
extern void memset(void*, unsigned char, int);
extern void lidt_core(unsigned long);
extern void make_idt_entry(int, unsigned long, unsigned short, unsigned char);
extern void load_idt(void);
extern unsigned char inb(unsigned short);
extern void outb(unsigned short, unsigned char);
extern void hw_wait(void);
extern void pic_initialize(void);
extern void pic_start(void);


#endif // _PROTOTYPES_H