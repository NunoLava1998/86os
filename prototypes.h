
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


#endif // _PROTOTYPES_H