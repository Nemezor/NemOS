#ifndef HEADER_ISR_WRAPPERS
#define HEADER_ISR_WRAPPERS

#include "isr.h"

extern void __isr_wrappers_irq_0();
extern void __isr_wrappers_irq_1();
extern void __isr_wrappers_irq_2();
extern void __isr_wrappers_irq_3();
extern void __isr_wrappers_irq_4();
extern void __isr_wrappers_irq_5();
extern void __isr_wrappers_irq_6();
extern void __isr_wrappers_irq_7();
extern void __isr_wrappers_irq_8();
extern void __isr_wrappers_irq_9();
extern void __isr_wrappers_irq_10();
extern void __isr_wrappers_irq_11();
extern void __isr_wrappers_irq_12();
extern void __isr_wrappers_irq_13();
extern void __isr_wrappers_irq_14();
extern void __isr_wrappers_irq_15();

extern void __isr_wrappers_int_div_by_zero();
extern void __isr_wrappers_int_debug();
extern void __isr_wrappers_int_NMI();
extern void __isr_wrappers_int_breakpoint();
extern void __isr_wrappers_int_INTO();
extern void __isr_wrappers_int_BOUND();
extern void __isr_wrappers_int_invalid_opcode();
extern void __isr_wrappers_int_co_not_avail();
extern void __isr_wrappers_int_double_fault();
extern void __isr_wrappers_int_co_seg_overrun();
extern void __isr_wrappers_int_TSS_error();
extern void __isr_wrappers_int_seg_not_present();
extern void __isr_wrappers_int_stack_fault();
extern void __isr_wrappers_int_GPF();
extern void __isr_wrappers_int_page_fault();
extern void __isr_wrappers_int_co_error();

extern void __isr_wrappers_int_syscall();

#endif