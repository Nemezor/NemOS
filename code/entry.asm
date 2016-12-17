[BITS 32]

section .text
    ; multiboot header
    align 4
    dd 0x1BADB002
    dd 0x04
    dd -(0x1BADB002 + 0x04)
	times 5 dd 0
	dd 0
	dd 1280 ;1280
	dd 720 ;720
	dd 32 ;32

global __start__

extern __setup_kernel_entry
extern __asm_utils_stop

; Entry point of the system
__start__:
    cli
    mov esp, reserved_stack_space
	push reserved_memory
    push eax
    push ebx
    call __setup_kernel_entry
    add esp, 8
	call __asm_utils_stop

section .bss
    resb 8192 ; reserved stack
    reserved_stack_space:
	reserved_memory:
	resb 4096 ; scratch memory