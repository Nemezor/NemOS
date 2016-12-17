[BITS 32]

global msr_read
global msr_write

msr_read:
	mov ecx, [esp + 4]
	rdmsr
	ret

msr_write:
	mov ecx, [esp + 4]
	mov eax, [esp + 8]
	mov edx, [esp + 12]
	wrmsr
	ret