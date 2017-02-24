
.section .multiboot # The multiboot header, as we defined in the linker.ld file.
.align 4 # Align by 4 bytes.

.long 0x1BADB002 # Place the MAGIC variable...
.long (1<<0 | 1<<1) # Place the FLAGS variable...
.long -(0x1BADB002 + (1<<0 | 1<<1)) # Place the CHECKSUM variable, to prove that we are a multiboot-capable OS.

.section .bss # The code here will be placed in .bss until we reach the .text segment.
.align 16 # Align by 16 bytes.
stack_bottom:
.skip 16384 # Skip 16 KB.
stack_top:

.section .text # Hooray, at the stack (ss)'s top we will place our code!
.global _start # Indicate to the compiler and linker we're gonna define our _start function in this file. The _stack function initializes
			   # our kernel.
.type _start, @function

_start: # Our _start function goes here.

	# Set up a stack. Languages like C cannot work without a (properly-defined) stack.
	mov $stack_top, %esp
	
	# We should call the kernel for now. We don't need a extern to kmain beacuse GAS/GCC already does it for us.
	call kmain
	
	# If the C kernel (kmain) exits for whatever reason, we should keep it in a halted state.
	
	cli # Disable interrupts.
1:	hlt # Halt...
	jmp 1 # In case it returns from the halt instruction somehow, just halt again...
	
# Set the size of the _start symbol/function to the current location '.' minus it's start.
.size _start, . - _start
	

	
