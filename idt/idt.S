
.global lidt_core
.global default_isr
.global default_irq

lidt_core:
	movl 4(%esp), %eax
	lidt (%eax)
	ret
default_isr:
	pusha
	push %ds
	push %es
	# Nothing to do here.
	pop %es
	pop %ds
	popa
	iret
	ret
default_irq:
	pusha
	push %ds
	push %es
	# Nothing to do here.
	pop %es
	pop %ds
	popa
	mov $0x20, %al
	outb %al, $0x20
	iret
	ret
