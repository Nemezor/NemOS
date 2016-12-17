[BITS 32]

global __asm_utils_hang
global __asm_utils_stop
global __asm_utils_load_gdt
global __asm_utils_load_idt
global __asm_utils_cli
global __asm_utils_sti
global __asm_utils_out8
global __asm_utils_out16
global __asm_utils_out32
global __asm_utils_in8
global __asm_utils_in16
global __asm_utils_in32
global __asm_utils_io_wait
global __asm_utils_int_syscall
global __asm_utils_spinlock

gdtr:
	dw 0
	dd 0
idtr:
	dw 0
	dd 0

halt:
	hlt
	jmp halt

__asm_utils_hang:
	cli
	mov byte [0xB8F9F], 0xC
	mov byte [0xB8F9E], 'T'
	mov byte [0xB8F9D], 0xC
	mov byte [0xB8F9C], 'L'
	mov byte [0xB8F9B], 0xC
	mov byte [0xB8F9A], 'A'
	mov byte [0xB8F99], 0xC
	mov byte [0xB8F98], 'H'
	jmp halt

__asm_utils_stop:
	cli
	mov byte [0xB8F9F], 0xB
	mov byte [0xB8F9E], 'P'
	mov byte [0xB8F9D], 0xB
	mov byte [0xB8F9C], 'O'
	mov byte [0xB8F9B], 0xB
	mov byte [0xB8F9A], 'T'
	mov byte [0xB8F99], 0xB
	mov byte [0xB8F98], 'S'
	jmp halt

__asm_utils_load_gdt:
	mov eax, [esp + 4]
	mov [gdtr + 2], eax
	mov ax, [esp + 8]
	mov [gdtr], ax
	mov eax, gdtr
	lgdt [gdtr]
	call reload_segments
	ret

reload_segments:
	jmp 0x08:.reload_CS
.reload_CS:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret

__asm_utils_load_idt:
	mov eax, [esp + 4]
	mov [idtr + 2], eax
	mov ax, [esp + 8]
	mov [idtr], ax
	mov eax, idtr
	lidt [idtr]
	ret

__asm_utils_cli:
	cli
	ret

__asm_utils_sti:
	sti
	ret

__asm_utils_out8:
	mov al, [esp + 8]
	mov dx, [esp + 4]
	out dx, al
	ret

__asm_utils_out16:
	mov ax, [esp + 8]
	mov dx, [esp + 4]
	out dx, ax
	ret

__asm_utils_out32:
	mov eax, [esp + 8]
	mov dx, [esp + 4]
	out dx, eax
	ret

__asm_utils_in8:
	mov dx, [esp + 4]
	in al, dx
	ret

__asm_utils_in16:
	mov dx, [esp + 4]
	in ax, dx
	ret

__asm_utils_in32:
	mov dx, [esp + 4]
	in eax, dx
	ret

__asm_utils_io_wait:
	xor al, al
	out 0x80, al
	ret

__asm_utils_int_syscall:
	mov eax, [esp + 4]
	int 0x80
	ret

__asm_utils_spinlock:
	jmp halt