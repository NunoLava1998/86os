
.extern gdtptr
.global gdt_flush

.section .text

gdt_flush:
	lgdt gdtptr
	ljmp $0x08,$code_segm
code_segm:
	mov $0x10, %eax
	mov %eax, %ds
	mov %eax, %es
	mov %eax, %fs
	mov %eax, %gs
	mov %eax, %ss
	ret
