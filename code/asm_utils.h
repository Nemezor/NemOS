#ifndef HEADER_ASM_UTILS
#define HEADER_ASM_UTILS

#include "ports.h"

extern void __asm_utils_hang(void);
extern void __asm_utils_stop(void);
extern void __asm_utils_load_gdt(long gdt_ptr, long gdt_size);
extern void __asm_utils_load_idt(long idt_ptr, long idt_size);
extern void __asm_utils_cli();
extern void __asm_utils_sti();
extern void __asm_utils_out8(short port, char data);
extern void __asm_utils_out16(short port, short data);
extern void __asm_utils_out32(short port, long data);
extern char __asm_utils_in8(short port);
extern short __asm_utils_in16(short port);
extern long __asm_utils_in32(short port);
extern void __asm_utils_io_wait();
extern void __asm_utils_int_syscall(long code);
extern void __asm_utils_spinlock();

#endif